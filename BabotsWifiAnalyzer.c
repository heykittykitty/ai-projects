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
#include "network_scanner.h"

#define MAX_NETWORKS 10

int main(int argc, char *argv[]) {
    // Scan for available networks
    Network *networks[MAX_NETWORKS];
    int num_networks = scan_networks(networks);
    if (num_networks == 0) {
        fprintf(stderr, "No networks found!\n");
        return 0;
    }
    
    // Connect to the first network
    if (connect_to_network(networks[0]) == -1) {
        fprintf(stderr, "Failed to connect to network!\n");
        return 0;
    }
    
    // Collect and analyze data
    NetworkInfo *info = get_network_info(networks[0]);
    NetworkParameters *params = get_network_parameters(networks[0]);
    NetworkStats *stats = get_network_stats(networks[0]);
    NetworkSecurity *security = get_network_security(networks[0]);
    int signal_strength = get_network_signal_strength(networks[0]);
    int num_devices = get_network_devices(networks[0]);
    
    // Print the collected data
    printf("Network information:\n");
    printf("\tName: %s\n", info->name);
    printf("\tSignal Strength: %d\n", signal_strength);
    printf("\tChannel: %d\n", params->channel);
    printf("\tBandwidth: %d\n", params->bandwidth);
    printf("\tData Rate: %d\n", params->data_rate);
    printf("\tBytes Sent: %d\n", stats->bytes_sent);
    printf("\tBytes Received: %d\n", stats->bytes_received);
    printf("\tSecurity Protocol: %s\n", security->protocol);
    printf("\tEncryption Type: %s\n", security->encryption_type);
    printf("\tNumber of Devices Connected: %d\n", num_devices);
    
    // Disconnect from the network and clean up
    disconnect_from_network(networks[0]);
    reset_network_state(networks[0]);
    int i;
    for (i = 0; i < num_networks; i++) {
        free(networks[i]);
    }
    
    return 0;
}
