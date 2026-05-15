package com.lab.domain;

public class Earthquake {
    private Long id;
    private Double magnitude;
    private Double depth;
    private Double latitude;
    private Double longitude;
    private Integer year;
    private Integer month;
    private Boolean tsunami;

    public Earthquake(Long id, Double magnitude, Double depth, 
                     Double latitude, Double longitude, 
                     Integer year, Integer month, Boolean tsunami) {
        this.id = id;
        this.magnitude = magnitude;
        this.depth = depth;
        this.latitude = latitude;
        this.longitude = longitude;
        this.year = year;
        this.month = month;
        this.tsunami = tsunami;
    }

    public Long getId() { return id; }
    public Double getMagnitude() { return magnitude; }
    public Double getDepth() { return depth; }
    public Double getLatitude() { return latitude; }
    public Double getLongitude() { return longitude; }
    public Integer getYear() { return year; }
    public Integer getMonth() { return month; }
    public Boolean hasTsunami() { return tsunami; }

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