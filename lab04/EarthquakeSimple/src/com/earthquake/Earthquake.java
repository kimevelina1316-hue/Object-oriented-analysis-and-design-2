package com.earthquake;

public class Earthquake {
    private int id;
    private double magnitude;
    private double depth;
    private double latitude;
    private double longitude;
    private int year;
    private int month;
    private boolean tsunami;

    public Earthquake(int id, double magnitude, double depth, 
                     double latitude, double longitude, 
                     int year, int month, boolean tsunami) {
        this.id = id;
        this.magnitude = magnitude;
        this.depth = depth;
        this.latitude = latitude;
        this.longitude = longitude;
        this.year = year;
        this.month = month;
        this.tsunami = tsunami;
    }

    public int getId() { return id; }
    public double getMagnitude() { return magnitude; }
    public double getDepth() { return depth; }
    public double getLatitude() { return latitude; }
    public double getLongitude() { return longitude; }
    public int getYear() { return year; }
    public int getMonth() { return month; }
    public boolean hasTsunami() { return tsunami; }

    @Override
    public String toString() {
        return String.format(
            "ID: %-4d | Магнитуда: %5.1f | Глубина: %6.1f км | " +
            "Координаты: (%.2f, %.2f) | %d-%02d | Цунами: %s",
            id, magnitude, depth, latitude, longitude, 
            year, month, tsunami ? "ДА" : "нет"
        );
    }
}