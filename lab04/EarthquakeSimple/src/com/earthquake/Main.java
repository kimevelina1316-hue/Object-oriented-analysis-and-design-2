package com.earthquake;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    // Создаём процессор (вся логика в одном классе)
                    EarthquakeProcessor processor = new EarthquakeProcessor();
                    
                    // Загружаем данные из CSV напрямую
                    processor.loadFromCSV("data/earthquake_tsunami_preprocessed.csv");
                    
                    // Создаём и показываем GUI
                    EarthquakeGUI gui = new EarthquakeGUI(processor);
                    gui.setVisible(true);
                    
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null,
                        "Ошибка запуска: " + e.getMessage(),
                        "Ошибка",
                        JOptionPane.ERROR_MESSAGE);
                    e.printStackTrace();
                }
            }
        });
    }
}