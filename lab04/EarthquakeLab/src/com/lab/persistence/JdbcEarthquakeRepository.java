package com.lab.persistence;

import com.lab.domain.Earthquake;
import com.lab.domain.EarthquakeRepository;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class JdbcEarthquakeRepository implements EarthquakeRepository {
    private List<Earthquake> earthquakes;
    private String csvPath;

    public JdbcEarthquakeRepository(String csvPath) {
        this.csvPath = csvPath;
        this.earthquakes = new ArrayList<>();
        loadFromCSV();
    }

    private void loadFromCSV() {
        try (BufferedReader br = new BufferedReader(new FileReader(csvPath))) {
            String line = br.readLine(); // Пропускаем заголовок
            Long id = 1L;

            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length >= 13) {
                    try {
                        Double magnitude = Double.parseDouble(parts[0].trim());
                        Double depth = Double.parseDouble(parts[7].trim());
                        Double latitude = Double.parseDouble(parts[8].trim());
                        Double longitude = Double.parseDouble(parts[9].trim());
                        Integer year = Integer.parseInt(parts[10].trim());
                        Integer month = Integer.parseInt(parts[11].trim());
                        Boolean tsunami = parts[12].trim().equalsIgnoreCase("1") || 
                                        parts[12].trim().equalsIgnoreCase("true") ||
                                        parts[12].trim().equalsIgnoreCase("True");

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
        } catch (IOException e) {
            System.err.println("✗ Ошибка чтения CSV файла: " + e.getMessage());
        }
    }

    @Override
    public Earthquake findById(Long id) {
        for (Earthquake eq : earthquakes) {
            if (eq.getId().equals(id)) {
                return eq;
            }
        }
        return null;
    }

    @Override
    public Earthquake[] findTop5ByMagnitude() {
        List<Earthquake> sorted = new ArrayList<>(earthquakes);
        Collections.sort(sorted, new Comparator<Earthquake>() {
            @Override
            public int compare(Earthquake a, Earthquake b) {
                return Double.compare(b.getMagnitude(), a.getMagnitude());
            }
        });

        Earthquake[] top5 = new Earthquake[5];
        for (int i = 0; i < Math.min(5, sorted.size()); i++) {
            top5[i] = sorted.get(i);
        }
        return top5;
    }

    @Override
    public Double[] getDepthByMagnitude(Double targetMagnitude) {
        List<Double> depths = new ArrayList<>();
        for (Earthquake eq : earthquakes) {
            if (Math.abs(eq.getMagnitude() - targetMagnitude) < 0.1) {
                depths.add(eq.getDepth());
            }
        }
        return depths.toArray(new Double[0]);
    }

    @Override
    public Earthquake[] findAll() {
        return earthquakes.toArray(new Earthquake[0]);
    }
}