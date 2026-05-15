package com.earthquake;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class EarthquakeProcessor {
    private List<Earthquake> earthquakes;

    public EarthquakeProcessor() {
        this.earthquakes = new ArrayList<>();
    }

    public void loadFromCSV(String filePath) throws IOException {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line = br.readLine(); // Пропускаем заголовок
            int id = 1;

            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length >= 13) {
                    try {
                        double magnitude = Double.parseDouble(parts[0].trim());
                        double depth = Double.parseDouble(parts[7].trim());
                        double latitude = Double.parseDouble(parts[8].trim());
                        double longitude = Double.parseDouble(parts[9].trim());
                        int year = Integer.parseInt(parts[10].trim());
                        int month = Integer.parseInt(parts[11].trim());
                        boolean tsunami = parts[12].trim().equalsIgnoreCase("1") || 
                                        parts[12].trim().equalsIgnoreCase("true");

                        Earthquake eq = new Earthquake(
                            id++, magnitude, depth, 
                            latitude, longitude, 
                            year, month, tsunami
                        );
                        earthquakes.add(eq);
                    } catch (Exception e) {
                        System.err.println("⚠️  Ошибка парсинга строки: " + line);
                    }
                }
            }
            System.out.println("✅ Успешно загружено " + earthquakes.size() + " записей из CSV\n");
        }
    }

    // Топ-5 по магнитуде
    public List<Earthquake> getTop5ByMagnitude() {
        List<Earthquake> sorted = new ArrayList<>(earthquakes);
        Collections.sort(sorted, new Comparator<Earthquake>() {
            @Override
            public int compare(Earthquake a, Earthquake b) {
                return Double.compare(b.getMagnitude(), a.getMagnitude());
            }
        });

        List<Earthquake> top5 = new ArrayList<>();
        for (int i = 0; i < Math.min(5, sorted.size()); i++) {
            top5.add(sorted.get(i));
        }
        return top5;
    }

    // Поиск по ID
    public Earthquake findById(int id) {
        for (Earthquake eq : earthquakes) {
            if (eq.getId() == id) {
                return eq;
            }
        }
        return null;
    }

    // Глубины для заданной магнитуды
    public List<Double> getDepthsByMagnitude(double targetMagnitude) {
        List<Double> depths = new ArrayList<>();
        for (Earthquake eq : earthquakes) {
            if (Math.abs(eq.getMagnitude() - targetMagnitude) < 0.1) {
                depths.add(eq.getDepth());
            }
        }
        return depths;
    }

    // Все землетрясения
    public List<Earthquake> getAllEarthquakes() {
        return new ArrayList<>(earthquakes);
    }

    public int getTotalCount() {
        return earthquakes.size();
    }
}