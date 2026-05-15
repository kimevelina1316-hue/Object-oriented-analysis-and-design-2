package com.earthquake;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.List;

public class EarthquakeGUI extends JFrame {
    private EarthquakeProcessor processor;
    private JTextArea resultArea;
    private JTable earthquakeTable;
    private DefaultTableModel tableModel;
    private JTextField idSearchField;
    private JTextField magnitudeSearchField;

    public EarthquakeGUI(EarthquakeProcessor processor) {
        this.processor = processor;
        setTitle("🌍 Система анализа землетрясений (БЕЗ ПАТТЕРНА)");
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
        List<Earthquake> top5 = processor.getTop5ByMagnitude();
        
        for (Earthquake eq : top5) {
            addEarthquakeToTable(eq);
        }
        
        resultArea.setText("=== ТОП-5 СИЛЬНЕЙШИХ ЗЕМЛЕТРЯСЕНИЙ ===\n");
        resultArea.append("Всего найдено: " + top5.size() + " записей\n");
    }

    private void showAllEarthquakes() {
        tableModel.setRowCount(0);
        List<Earthquake> all = processor.getAllEarthquakes();
        
        for (Earthquake eq : all) {
            addEarthquakeToTable(eq);
        }
        
        resultArea.setText("=== ВСЕ ЗЕМЛЕТРЯСЕНИЯ ===\n");
        resultArea.append("Всего записей: " + all.size() + "\n");
    }

    private void searchById() {
        try {
            int id = Integer.parseInt(idSearchField.getText().trim());
            tableModel.setRowCount(0);
            
            Earthquake eq = processor.findById(id);
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
            double magnitude = Double.parseDouble(magnitudeSearchField.getText().trim());
            List<Double> depths = processor.getDepthsByMagnitude(magnitude);
            
            resultArea.setText("=== ГЛУБИНЫ ДЛЯ МАГНИТУДЫ: " + magnitude + " ===\n");
            resultArea.append("Найдено записей: " + depths.size() + "\n\n");
            
            if (!depths.isEmpty()) {
                double sum = 0;
                for (double depth : depths) {
                    sum += depth;
                }
                double avg = sum / depths.size();
                
                double min = depths.get(0);
                double max = depths.get(0);
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
        List<Earthquake> all = processor.getAllEarthquakes();
        
        int total = all.size();
        double sumMagnitude = 0;
        double sumDepth = 0;
        int tsunamiCount = 0;
        
        for (Earthquake eq : all) {
            sumMagnitude += eq.getMagnitude();
            sumDepth += eq.getDepth();
            if (eq.hasTsunami()) {
                tsunamiCount++;
            }
        }
        
        double avgMagnitude = total > 0 ? sumMagnitude / total : 0;
        double avgDepth = total > 0 ? sumDepth / total : 0;
        
        resultArea.setText("=== СТАТИСТИКА ===\n\n");
        resultArea.append("Общее количество: " + total + "\n");
        resultArea.append(String.format("Средняя магнитуда: %.2f\n", avgMagnitude));
        resultArea.append(String.format("Средняя глубина: %.2f км\n", avgDepth));
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