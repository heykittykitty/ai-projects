#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/in.h> 
#include <netinet/ip.h> 
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "wifi_geolocation.h"

int main(int argc, char *argv[]) {
    // Get the MAC address from the command line
    char *mac_address = argv[1];
    
    // Look up the location of the device
    Location loc = wifi_geolocation_lookup(mac_address);
    if (loc.latitude == 0 && loc.longitude == 0) {
        fprintf(stderr, "Failed to look up location!\n");
        return 0;
    }
    
    // Print the location
    printf("Device location:\n");
    printf("\tLatitude: %f\n", loc.latitude);
    printf("\tLongitude: %f\n", loc.longitude);
    
    return 0;
}
