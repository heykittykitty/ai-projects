#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void scan_networks();
void retrieve_network_info(char *ssid, int *signal_strength, int *channel_usage);

int main()
{
    char ssid[32];
    int signal_strength;
    int channel_usage;
    
    // Scan for available networks
    printf("Scanning for available networks...\n");
    scan_networks();
    
    // Retrieve information about the networks
    printf("Retrieving information about networks...\n");
    retrieve_network_info(ssid, &signal_strength, &channel_usage);
    
    // Print out the network information
    printf("Network SSID: %s\n", ssid);
    printf("Signal Strength: %d\n", signal_strength);
    printf("Channel Usage: %d\n", channel_usage);
    
    return 0;
}

// Scans for available networks
void scan_networks()
{
    int num_networks = 0;
    char ssid[32];
    int signal_strength;
    int channel_usage;
    int i;
    
    printf("Scanning for networks...\n");
    
    // TODO: Write code to scan for available networks
    num_networks = scan_networks();
    
    // Print out the available networks
    printf("Found %d networks:\n", num_networks);
    for (i = 0; i < num_networks; i++) {
        retrieve_network_info(ssid, &signal_strength, &channel_usage);
        printf("  - SSID: %s, Signal Strength: %d, Channel Usage: %d\n", ssid, signal_strength, channel_usage);
    }
}

// Retrieves information about a network
void retrieve_network_info(char *ssid, int *signal_strength, int *channel_usage)
{
    // TODO: Write code to retrieve information about the networks
    // Get the SSID of the network
    get_ssid(ssid);
    
    // Get the signal strength of the network
    *signal_strength = get_signal_strength();
    
    // Get the channel usage of the network
    *channel_usage = get_channel_usage();
}
