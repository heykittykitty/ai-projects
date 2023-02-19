#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <net/if.h>
#include <linux/if_ether.h>
#unclude <linux/if_arp.h>
#include <linux/if_ether.h>

int main(int argc, char *argv[]) {
    // Create a raw socket
    int sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(sock_raw < 0) {
        perror("Socket Error");
        return 1;
    }

    // Get the interface name
    struct ifreq ifr;
    strncpy(ifr.ifr_name, argv[1], IFNAMSIZ);

    // Get the interface index
    if(ioctl(sock_raw, SIOCGIFINDEX, &ifr) == -1) {
        perror("IOCTL Error");
        return 1;
    }

    // Get the interface MAC address
    if(ioctl(sock_raw, SIOCGIFHWADDR, &ifr) == -1) {
        perror("IOCTL Error");
        return 1;
    }

    // Get the source address
    struct sockaddr_in source;
    source.sin_family = AF_INET;
    source.sin_addr.s_addr = inet_addr(argv[2]);

    // Create the ARP header
    struct arphdr arp;
    arp.ar_hrd = htons(ARPHRD_ETHER);
    arp.ar_pro = htons(ETH_P_IP);
    arp.ar_hln = ETH_ALEN;
    arp.ar_pln = 4;
    arp.ar_op = htons(ARPOP_REQUEST);

    // Create the ethernet header
    struct ethhdr eth;
    memcpy(eth.h_dest, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
    memcpy(eth.h_source, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
    eth.h_proto = htons(ETH_P_ARP);

    // Combine the headers and payload
    unsigned char buffer[sizeof(struct arphdr) + sizeof(struct ethhdr)];
    memcpy(buffer, &arp, sizeof(struct arphdr));
    memcpy(buffer + sizeof(struct arphdr), &eth, sizeof(struct ethhdr));

    // Send the packet
    if (sendto(sock_raw, buffer, sizeof(buffer), 0, (struct sockaddr *) &source, sizeof(source)) < 0) {
        perror("Sendto Error");
        return 1;
    }

    // Close the socket
    close(sock_raw);
    printf("Finished");
    return 0;
}
