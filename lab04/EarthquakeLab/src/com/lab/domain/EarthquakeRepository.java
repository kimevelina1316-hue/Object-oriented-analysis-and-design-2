package com.lab.domain;

public interface EarthquakeRepository {
    Earthquake findById(Long id);
    Earthquake[] findTop5ByMagnitude();
    Double[] getDepthByMagnitude(Double magnitude);
    Earthquake[] findAll();
}