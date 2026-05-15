package com.lab.gui;

import com.lab.domain.Earthquake;
import com.lab.domain.EarthquakeService;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;

public class EarthquakeGUI extends JFrame {
    private EarthquakeService service;
    private JTextArea resultArea;
    private JTable earthquakeTable;
    private DefaultTableModel tableModel;
    private JTextField idSearchField;
    private JTextField magnitudeSearchField;

    public EarthquakeGUI(EarthquakeService service) {
        this.service = service;
        setTitle("🌍 Система анализа землетрясений (Separated Interface)");
        setSize(1000, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        
        initComponents();
    }

    private void initComponents() {
        JPanel mainPanel = new JPanel(new BorderLayout(10, 10));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        JPanel controlPanel = createControlPanel();
        mainPanel.add(controlPanel, BorderLayout.NORTH);

        JPanel tablePanel = createTablePanel();
        mainPanel.add(tablePanel, BorderLayout.CENTER);

        JPanel resultPanel = createResultPanel();
        mainPanel.add(resultPanel, BorderLayout.SOUTH);

        add(mainPanel);
    }

    private JPanel createControlPanel() {
        JPanel panel = new JPanel(new GridLayout(2, 3, 10, 10));
        panel.setBorder(BorderFactory.createTitledBorder("Управление"));

        JButton top5Button = new JButton("📊 Топ-5 сильнейших");
        top5Button.addActionListener(e -> showTop5());
        panel.add(top5Button);

        JButton allButton = new JButton("📋 Все землетрясения");
        allButton.addActionListener(e -> showAllEarthquakes());
        panel.add(allButton);

        JPanel idPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        idPanel.add(new JLabel("ID:"));
        idSearchField = new JTextField(5);
        idPanel.add(idSearchField);
        JButton searchIdButton = new JButton("🔍 Найти");
        searchIdButton.addActionListener(e -> searchById());
        idPanel.add(searchIdButton);
        panel.add(idPanel);

        JPanel magPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        magPanel.add(new JLabel("Магнитуда:"));
        magnitudeSearchField = new JTextField(5);
        magPanel.add(magnitudeSearchField);
        JButton searchMagButton = new JButton("🔍 Глубины");
        searchMagButton.addActionListener(e -> searchByMagnitude());
        magPanel.add(searchMagButton);
        panel.add(magPanel);

        JButton statsButton = new JButton("📈 Статистика");
        statsButton.addActionListener(e -> showStatistics());
        panel.add(statsButton);

        return panel;
    }

    private JPanel createTablePanel() {
        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(BorderFactory.createTitledBorder("Данные"));

        String[] columns = {"ID", "Магнитуда", "Глубина (км)", "Широта", "Долгота", "Год", "Месяц", "Цунами"};
        tableModel = new DefaultTableModel(columns, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        earthquakeTable = new JTable(tableModel);
        earthquakeTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane scrollPane = new JScrollPane(earthquakeTable);
        
        panel.add(scrollPane, BorderLayout.CENTER);

        return panel;
    }

    private JPanel createResultPanel() {
        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(BorderFactory.createTitledBorder("Результат"));

        resultArea = new JTextArea(5, 50);
        resultArea.setEditable(false);
        resultArea.setFont(new Font("Monospaced", Font.PLAIN, 12));
        resultArea.setBackground(new Color(240, 240, 240));
        JScrollPane scrollPane = new JScrollPane(resultArea);
        
        panel.add(scrollPane, BorderLayout.CENTER);

        return panel;
    }

    private void showTop5() {
        tableModel.setRowCount(0);
        Earthquake[] top5 = service.getTop5Earthquakes();
        
        for (Earthquake eq : top5) {
            if (eq != null) {
                addEarthquakeToTable(eq);
            }
        }
        
        resultArea.setText("=== ТОП-5 СИЛЬНЕЙШИХ ЗЕМЛЕТРЯСЕНИЙ ===\n");
        resultArea.append("Всего найдено: " + top5.length + " записей\n");
    }

    private void showAllEarthquakes() {
        tableModel.setRowCount(0);
        Earthquake[] all = service.getAllEarthquakes();
        
        for (Earthquake eq : all) {
            addEarthquakeToTable(eq);
        }
        
        resultArea.setText("=== ВСЕ ЗЕМЛЕТРЯСЕНИЯ ===\n");
        resultArea.append("Всего записей: " + all.length + "\n");
    }

    private void searchById() {
        try {
            Long id = Long.parseLong(idSearchField.getText().trim());
            tableModel.setRowCount(0);
            
            Earthquake eq = service.searchById(id);
            if (eq != null) {
                addEarthquakeToTable(eq);
                resultArea.setText("=== РЕЗУЛЬТАТ ПОИСКА ПО ID: " + id + " ===\n");
                resultArea.append(eq.toString() + "\n");
            } else {
                resultArea.setText("❌ Землетрясение с ID " + id + " не найдено\n");
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, 
                "Введите корректный ID (число)", 
                "Ошибка", 
                JOptionPane.ERROR_MESSAGE);
        }
    }

    private void searchByMagnitude() {
        try {
            Double magnitude = Double.parseDouble(magnitudeSearchField.getText().trim());
            Double[] depths = service.getDepthsByMagnitude(magnitude);
            
            resultArea.setText("=== ГЛУБИНЫ ДЛЯ МАГНИТУДЫ: " + magnitude + " ===\n");
            resultArea.append("Найдено записей: " + depths.length + "\n\n");
            
            if (depths.length > 0) {
                double sum = 0;
                for (double depth : depths) {
                    sum += depth;
                }
                double avg = sum / depths.length;
                
                double min = depths[0];
                double max = depths[0];
                for (double depth : depths) {
                    if (depth < min) min = depth;
                    if (depth > max) max = depth;
                }
                
                resultArea.append(String.format("Средняя глубина: %.2f км\n", avg));
                resultArea.append(String.format("Минимальная: %.2f км\n", min));
                resultArea.append(String.format("Максимальная: %.2f км\n", max));
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, 
                "Введите корректную магнитуду (число)", 
                "Ошибка", 
                JOptionPane.ERROR_MESSAGE);
        }
    }

    private void showStatistics() {
        Earthquake[] all = service.getAllEarthquakes();
        
        int total = all.length;
        double sumMagnitude = 0;
        double sumDepth = 0;
        int tsunamiCount = 0;
        
        // Инициализируем min/max первым значением
        double minDepth = total > 0 ? all[0].getDepth() : 0;
        double maxDepth = total > 0 ? all[0].getDepth() : 0;
        
        for (Earthquake eq : all) {
            sumMagnitude += eq.getMagnitude();
            double depth = eq.getDepth();
            sumDepth += depth;
            
            // Обновляем min/max глубины
            if (depth < minDepth) minDepth = depth;
            if (depth > maxDepth) maxDepth = depth;
            
            if (eq.hasTsunami()) {
                tsunamiCount++;
            }
        }
        
        double avgMagnitude = total > 0 ? sumMagnitude / total : 0;
        double avgDepth = total > 0 ? sumDepth / total : 0;
        
        resultArea.setText("=== ОБЩАЯ СТАТИСТИКА ===\n\n");
        resultArea.append("📊 Основные показатели:\n");
        resultArea.append("─────────────────────────\n");
        resultArea.append("Общее количество: " + total + "\n");
        resultArea.append(String.format("Средняя магнитуда: %.2f\n", avgMagnitude));
        resultArea.append(String.format("Средняя глубина: %.2f км\n", avgDepth));
        resultArea.append("\n📏 Глубина:\n");
        resultArea.append("─────────────────────────\n");
        resultArea.append(String.format("Минимальная: %.2f км\n", minDepth));
        resultArea.append(String.format("Максимальная: %.2f км\n", maxDepth));
        resultArea.append(String.format("Разброс: %.2f км\n", maxDepth - minDepth));
        resultArea.append("\n🌊 Цунами:\n");
        resultArea.append("─────────────────────────\n");
        resultArea.append("С цунами: " + tsunamiCount + " (" + 
                         String.format("%.1f", (tsunamiCount * 100.0 / total)) + "%)\n");
        resultArea.append("Без цунами: " + (total - tsunamiCount) + "\n");
    }

    private void addEarthquakeToTable(Earthquake eq) {
        tableModel.addRow(new Object[]{
            eq.getId(),
            eq.getMagnitude(),
            eq.getDepth(),
            eq.getLatitude(),
            eq.getLongitude(),
            eq.getYear(),
            eq.getMonth(),
            eq.hasTsunami() ? "ДА ✓" : "нет"
        });
    }
}