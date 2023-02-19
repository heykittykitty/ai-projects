#ifndef WIFI_GEOLOCATION_H
#define WIFI_GEOLOCATION_H

typedef struct {
    double latitude;
    double longitude;
} Location;

// Look up the location of a device based on its MAC address
Location wifi_geolocation_lookup(char *mac_address);

#endif // WIFI_GEOLOCATION_H
