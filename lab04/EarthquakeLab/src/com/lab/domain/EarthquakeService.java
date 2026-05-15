package com.lab.domain;

public class EarthquakeService {
    private EarthquakeRepository repository;

    public EarthquakeService(EarthquakeRepository repository) {
        this.repository = repository;
    }

    public Earthquake[] getTop5Earthquakes() {
        return repository.findTop5ByMagnitude();
    }

    public Earthquake searchById(Long id) {
        return repository.findById(id);
    }

    public Earthquake[] getAllEarthquakes() {
        return repository.findAll();
    }

    public Double[] getDepthsByMagnitude(Double magnitude) {
        return repository.getDepthByMagnitude(magnitude);
    }
}