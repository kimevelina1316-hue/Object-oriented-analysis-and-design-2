package com.lab;

import com.lab.domain.EarthquakeService;
import com.lab.gui.EarthquakeGUI;
import com.lab.persistence.JdbcEarthquakeRepository;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    JdbcEarthquakeRepository repository = 
                        new JdbcEarthquakeRepository("data/earthquake_tsunami_preprocessed.csv");
                    
                    EarthquakeService service = new EarthquakeService(repository);
                    
                    EarthquakeGUI gui = new EarthquakeGUI(service);
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