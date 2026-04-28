# -*- coding: utf-8 -*-
import tkinter as tk
from tkinter import ttk, Canvas
from abc import ABC, abstractmethod
import random


# ==================== КОМПОНЕНТЫ (знают друг о друге!) ====================

class Brush:
    """Щётка - знает о других компонентах!"""
    def __init__(self, water_tank, gui):
        self.water_tank = water_tank  # Прямая ссылка на бак!
        self.gui = gui
        self.is_rotating = False
    
    def execute(self, mode):
        if mode == "mop" or mode == "dust":
            self.is_rotating = True
            # Щётка сама проверяет воду!
            if self.water_tank.is_empty():
                self.gui.update_log("⚠️ Щётка: Бак пуст!")
            return "Щётка включена"
        return ""
    
    def stop(self):
        self.is_rotating = False


class WaterTank:
    """Бак с водой - независимый, но все к нему обращаются"""
    def __init__(self):
        self.water_level = 100
        self.is_open = False
    
    def execute(self, mode):
        if mode == "mop" or mode == "dust":
            self.is_open = True
            self.water_level -= 10
            return "Вода подается"
        return ""
    
    def is_empty(self):
        return self.water_level <= 0
    
    def stop(self):
        self.is_open = False


class TrashBin:
    """Бак для мусора"""
    def __init__(self):
        self.is_open = False
    
    def execute(self, mode):
        if mode == "sweep":
            self.is_open = True
            return "Бак открыт"
        return ""
    
    def stop(self):
        self.is_open = False


class Broom:
    """Метла"""
    def __init__(self, trash_bin, gui):
        self.trash_bin = trash_bin  # Прямая ссылка на бак!
        self.gui = gui
        self.is_sweeping = False
    
    def execute(self, mode):
        if mode == "sweep":
            self.is_sweeping = True
            # Метла проверяет бак!
            if not self.trash_bin.is_open:
                self.gui.update_log("⚠️ Метла: Бак закрыт!")
            return "Метла активна"
        return ""
    
    def stop(self):
        self.is_sweeping = False


class Cloth:
    """Тряпка"""
    def __init__(self, water_tank, gui):
        self.water_tank = water_tank  # Прямая ссылка на бак!
        self.gui = gui
        self.is_wet = False
    
    def execute(self, mode):
        if mode == "dust":
            # Тряпка сама проверяет воду!
            if self.water_tank.is_empty():
                self.gui.update_log("⚠️ Тряпка: Нет воды!")
                return ""
            self.is_wet = True
            return "Тряпка увлажнена"
        return ""
    
    def stop(self):
        self.is_wet = False


# ==================== GUI (ВСЁ управление здесь - БОЛЬШОЙ БОГ!) ====================

class RobotGUI:
    """Графический интерфейс - теперь это "Божественный объект" """
    
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("🤖 Робот-уборщик (БЕЗ Mediator)")
        self.root.geometry("900x750")
        self.root.configure(bg="#E3F2FD")
        
        # Создаем ВСЕ компоненты ПРЯМО ЗДЕСЬ
        self.water_tank = WaterTank()
        self.brush = Brush(self.water_tank, self)
        self.trash_bin = TrashBin()
        self.broom = Broom(self.trash_bin, self)
        self.cloth = Cloth(self.water_tank, self)
        
        self.mode_var = tk.StringVar(value="mop")
        self.is_cleaning = False
        self.stains = []
        self.robot_parts = {}
        self.robot_x = 50
        self.robot_y = 200
        self.target_stain = None
        self.speed = 3
        
        self._create_widgets()
    
    def _create_widgets(self):
        """Создать элементы интерфейса"""
        # Панель управления
        control_frame = ttk.LabelFrame(self.root, text=" 📋 Панель управления", padding=10)
        control_frame.pack(fill="x", padx=15, pady=10)
        
        # Выбор режима
        mode_frame = ttk.Frame(control_frame)
        mode_frame.pack(fill="x", pady=5)
        
        ttk.Label(mode_frame, text="Выберите режим:", font=("Arial", 11, "bold"), 
                 background="#E3F2FD").pack(side="left", padx=5)
        
        modes = [
            ("mop", "🧽 Мытьё полов (вода + щётка)"),
            ("dust", "✨ Протереть пыль (тряпка + вода)"),
            ("sweep", "🧹 Подмести (метла + бак)")
        ]
        
        for value, text in modes:
            ttk.Radiobutton(mode_frame, text=text, variable=self.mode_var, 
                          value=value).pack(side="left", padx=15, anchor="w")
        
        # Кнопка
        btn_frame = ttk.Frame(control_frame)
        btn_frame.pack(fill="x", pady=10)
        
        self.start_btn = ttk.Button(btn_frame, text="🚀 Запустить уборку", 
                                   command=self._on_start, width=25)
        self.start_btn.pack(side="left", padx=5)
        
        # Область анимации
        anim_frame = ttk.LabelFrame(self.root, text=" 🎬 Анимация уборки", padding=10)
        anim_frame.pack(fill="both", expand=True, padx=15, pady=10)
        
        self.canvas = Canvas(anim_frame, bg="#B3E5FC", height=400, 
                            highlightthickness=3, highlightbackground="#0288D1")
        self.canvas.pack(fill="both", expand=True)
        
        # Лог действий
        log_frame = ttk.LabelFrame(self.root, text=" 📝 Лог действий", padding=10)
        log_frame.pack(fill="x", padx=15, pady=10)
        
        self.log_text = tk.Text(log_frame, height=8, state="disabled", 
                               bg="#FFFFFF", font=("Consolas", 10))
        self.log_text.pack(fill="x")
    
    def _on_start(self):
        """Обработчик кнопки Старт - ВСЯ ЛОГИКА ЗДЕСЬ!"""
        if not self.is_cleaning:
            mode = self.mode_var.get()
            self.is_cleaning = True
            self.start_btn.config(state="disabled")
            
            # БЕЗ посредника - GUI сам решает кто что делает!
            if mode == "mop":
                # GUI должен ЗНАТЬ порядок активации!
                self.water_tank.execute(mode)
                self.brush.execute(mode)
                self.update_log("🧽 Режим: Мытьё полов")
                self.update_log("   → WaterTank: АКТИВЕН")
                self.update_log("   → Brush: ВКЛЮЧЕНА")
                
            elif mode == "dust":
                # GUI должен ЗНАТЬ о зависимостях!
                self.water_tank.execute(mode)
                self.cloth.execute(mode)
                self.update_log("✨ Режим: Протереть пыль")
                self.update_log("   → WaterTank: АКТИВЕН")
                self.update_log("   → Cloth: УВЛАЖНЕНА")
                
            elif mode == "sweep":
                # GUI должен ЗНАТЬ все компоненты!
                self.trash_bin.execute(mode)
                self.broom.execute(mode)
                self.update_log("🧹 Режим: Подмести")
                self.update_log("   → TrashBin: ОТКРЫТ")
                self.update_log("   → Broom: АКТИВНА")
            
            self._start_animation(mode)
    
    def _start_animation(self, mode):
        """Запустить анимацию уборки"""
        self.canvas.delete("all")
        self.stains = []
        self.robot_x = 50
        self.robot_y = 200
        self.robot_parts = {}
        self.target_stain = None
        
        self._draw_floor()
        self._create_stains(mode)
        self.robot_parts = self._draw_robot(self.robot_x, self.robot_y)
        self._find_next_target()
        
        self.root.after(100, self._animate_cleaning)
    
    def _draw_floor(self):
        """Нарисовать пол с сеткой"""
        self.canvas.create_rectangle(30, 30, 850, 370, fill="#E1F5FE", 
                                    outline="#0288D1", width=3)
        
        for i in range(0, 820, 50):
            self.canvas.create_line(30+i, 30, 30+i, 370, fill="#81D4FA", width=1)
            self.canvas.create_line(30, 30+i, 850, 30+i, fill="#81D4FA", width=1)
        
        self.canvas.create_text(440, 360, text="ПОЛ", font=("Arial", 14, "bold"), 
                               fill="#0277BD")
    
    def _create_stains(self, mode):
        """Создать пятна/загрязнения"""
        if mode == "mop":
            for i in range(6):
                x = random.randint(100, 780)
                y = random.randint(60, 300)
                size = random.randint(25, 45)
                stain = self.canvas.create_oval(x-size, y-size, x+size, y+size, 
                                               fill="#4FC3F7", outline="#0288D1", width=2)
                self.stains.append({'item': stain, 'x': x, 'y': y, 'size': size, 'type': 'water'})
            
            for i in range(4):
                x = random.randint(100, 780)
                y = random.randint(60, 300)
                stain = self.canvas.create_polygon(
                    x, y-20, x+25, y-12, x+30, y+12, x+12, y+25, x-18, y+18, x-22, y-8,
                    fill="#8D6E63", outline="#5D4037", width=1)
                self.stains.append({'item': stain, 'x': x, 'y': y, 'size': 25, 'type': 'dirt'})
                
        elif mode == "dust":
            for i in range(8):
                x = random.randint(100, 780)
                y = random.randint(60, 300)
                cloud = []
                for j in range(3):
                    circle = self.canvas.create_oval(
                        x+j*18-12, y-12, x+j*18+12, y+12,
                        fill="#CFD8DC", outline="#90A4AE", width=1)
                    cloud.append(circle)
                self.stains.append({'item': cloud, 'x': x, 'y': y, 'size': 30, 'type': 'dust'})
                
        elif mode == "sweep":
            for i in range(12):
                x = random.randint(100, 780)
                y = random.randint(60, 300)
                if random.random() > 0.5:
                    trash = self.canvas.create_rectangle(
                        x-10, y-10, x+10, y+10,
                        fill="#795548", outline="#3E2723", width=1)
                else:
                    trash = self.canvas.create_polygon(
                        x, y-12, x+12, y+10, x-12, y+10,
                        fill="#5D4037", outline="#3E2723", width=1)
                self.stains.append({'item': trash, 'x': x, 'y': y, 'size': 15, 'type': 'trash'})
    
    def _draw_robot(self, x, y):
        """Нарисовать робота как фигурку"""
        parts = {}
        
        parts['body'] = self.canvas.create_rectangle(
            x-30, y-35, x+30, y+35, 
            fill="#66BB6A", outline="#2E7D32", width=3)
        
        parts['head'] = self.canvas.create_oval(
            x-20, y-55, x+20, y-25,
            fill="#81C784", outline="#2E7D32", width=3)
        
        parts['eye_left'] = self.canvas.create_oval(
            x-12, y-48, x-6, y-40, fill="white", outline="black", width=1)
        parts['eye_right'] = self.canvas.create_oval(
            x+6, y-48, x+12, y-40, fill="white", outline="black", width=1)
        
        parts['pupil_left'] = self.canvas.create_oval(
            x-10, y-46, x-7, y-42, fill="black")
        parts['pupil_right'] = self.canvas.create_oval(
            x+8, y-46, x+11, y-42, fill="black")
        
        parts['antenna'] = self.canvas.create_line(
            x, y-55, x, y-70, fill="#2E7D32", width=2)
        parts['antenna_top'] = self.canvas.create_oval(
            x-4, y-74, x+4, y-66, fill="#FF5722", outline="#E64A19", width=1)
        
        parts['wheel_left'] = self.canvas.create_oval(
            x-28, y+30, x-18, y+45, fill="#424242", outline="#212121", width=2)
        parts['wheel_right'] = self.canvas.create_oval(
            x+18, y+30, x+28, y+45, fill="#424242", outline="#212121", width=2)
        
        parts['indicator'] = self.canvas.create_oval(
            x-25, y-30, x-15, y-20, fill="#FFEB3B", outline="#F57F17", width=1)
        
        return parts
    
    def _find_next_target(self):
        """Найти ближайшее пятно"""
        if not self.stains:
            self.target_stain = None
            return
        
        min_distance = float('inf')
        closest_stain = None
        
        for stain in self.stains:
            distance = ((self.robot_x - stain['x'])**2 + (self.robot_y - stain['y'])**2)**0.5
            if distance < min_distance:
                min_distance = distance
                closest_stain = stain
        
        self.target_stain = closest_stain
        
        if self.target_stain:
            x, y = self.target_stain['x'], self.target_stain['y']
            self.canvas.create_line(x-15, y-15, x+15, y+15, fill="red", width=2, tag="target")
            self.canvas.create_line(x+15, y-15, x-15, y+15, fill="red", width=2, tag="target")
    
    def _animate_cleaning(self):
        """Анимация движения к цели"""
        if not self.is_cleaning:
            return
        
        if not self.target_stain:
            self.is_cleaning = False
            self.start_btn.config(state="normal")
            self.update_log("✅ Уборка завершена! Все пятна удалены.")
            return
        
        target_x = self.target_stain['x']
        target_y = self.target_stain['y']
        
        dx = target_x - self.robot_x
        dy = target_y - self.robot_y
        distance = (dx**2 + dy**2)**0.5
        
        if distance < 40:
            if isinstance(self.target_stain['item'], list):
                for item in self.target_stain['item']:
                    self.canvas.delete(item)
            else:
                self.canvas.delete(self.target_stain['item'])
            
            self.canvas.delete("target")
            self.stains.remove(self.target_stain)
            self.update_log(f"🧹 Убрано: {self.target_stain['type']} на позиции ({int(self.target_stain['x'])}, {int(self.target_stain['y'])})")
            
            self._find_next_target()
        else:
            self.robot_x += (dx / distance) * self.speed
            self.robot_y += (dy / distance) * self.speed
            
            if self.robot_parts:
                self._update_robot_position()
        
        if self.robot_x >= 780:
            self.is_cleaning = False
            self.start_btn.config(state="normal")
            self.update_log("✅ Уборка завершена! Все пятна удалены.")
            return
        
        self.root.after(50, self._animate_cleaning)
    
    def _update_robot_position(self):
        """Обновить позицию всех частей робота"""
        x = self.robot_x
        y = self.robot_y
        
        if 'body' in self.robot_parts:
            self.canvas.coords(self.robot_parts['body'], x-30, y-35, x+30, y+35)
        if 'head' in self.robot_parts:
            self.canvas.coords(self.robot_parts['head'], x-20, y-55, x+20, y-25)
        if 'eye_left' in self.robot_parts:
            self.canvas.coords(self.robot_parts['eye_left'], x-12, y-48, x-6, y-40)
        if 'eye_right' in self.robot_parts:
            self.canvas.coords(self.robot_parts['eye_right'], x+6, y-48, x+12, y-40)
        if 'pupil_left' in self.robot_parts:
            self.canvas.coords(self.robot_parts['pupil_left'], x-10, y-46, x-7, y-42)
        if 'pupil_right' in self.robot_parts:
            self.canvas.coords(self.robot_parts['pupil_right'], x+8, y-46, x+11, y-42)
        if 'antenna' in self.robot_parts:
            self.canvas.coords(self.robot_parts['antenna'], x, y-55, x, y-70)
        if 'antenna_top' in self.robot_parts:
            self.canvas.coords(self.robot_parts['antenna_top'], x-4, y-74, x+4, y-66)
        if 'wheel_left' in self.robot_parts:
            self.canvas.coords(self.robot_parts['wheel_left'], x-28, y+30, x-18, y+45)
        if 'wheel_right' in self.robot_parts:
            self.canvas.coords(self.robot_parts['wheel_right'], x+18, y+30, x+28, y+45)
        if 'indicator' in self.robot_parts:
            self.canvas.coords(self.robot_parts['indicator'], x-25, y-30, x-15, y-20)
    
    def update_log(self, message):
        """Обновить лог"""
        self.log_text.config(state="normal")
        self.log_text.insert("end", message + "\n")
        self.log_text.see("end")
        self.log_text.config(state="disabled")
    
    def run(self):
        """Запустить приложение"""
        self.root.mainloop()


# ==================== ЗАПУСК ====================

if __name__ == "__main__":
    app = RobotGUI()
    app.run()