#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
 
void packet_analyzer(unsigned char* buffer, int size)
{
    //Get the IP Header part of this packet
    struct iphdr *iph = (struct iphdr*)buffer;
   
    //Get the TCP Header part of this packet
    struct tcphdr *tcph=(struct tcphdr*)(buffer + sizeof(struct iphdr));
   
    //Get the UDP Header part of this packet
    struct udphdr *udph = (struct udphdr*)(buffer + sizeof(struct iphdr));
 
    printf("\n\n***********************IP Header*************************\n");
    printf("IP Version        : %d\n",(unsigned int)iph->version);
    printf("IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    printf("Type Of Service   : %d\n",(unsigned int)iph->tos);
    printf("IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    printf("Identification    : %d\n",ntohs(iph->id));
    printf("TTL      : %d\n",(unsigned int)iph->ttl);
    printf("Protocol : %d\n",(unsigned int)iph->protocol);
    printf("Checksum : %d\n",ntohs(iph->check));
    printf("Source IP        : %s\n",inet_ntoa(iph->saddr));
    printf("Destination IP   : %s\n",inet_ntoa(iph->daddr));
 
    if(iph->protocol == 6)
    {
        printf("\n**********************TCP Header*************************\n");
        printf("Source Port      : %u\n",ntohs(tcph->source));
        printf("Destination Port : %u\n",ntohs(tcph->dest));
        printf("Sequence Number    : %u\n",ntohl(tcph->seq));
        printf("Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
        printf("Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
        printf("Urgent Flag          : %d\n",(unsigned int)tcph->urg);
        printf("Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
        printf("Push Flag            : %d\n",(unsigned int)tcph->psh);
        printf("Reset Flag           : %d\n",(unsigned int)tcph->rst);
        printf("Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
        printf("Finish Flag          : %d\n",(unsigned int)tcph->fin);
        printf("Window         : %d\n",ntohs(tcph->window));
        printf("Checksum       : %d\n",ntohs(tcph->check));
        printf("Urgent Pointer : %d\n",tcph->urg_ptr);
    }
    else if(iph->protocol == 17)
    {
        printf("\n**********************UDP Header*************************\n");
        printf("Source Port      : %d\n" , ntohs(udph->source));
        printf("Destination Port : %d\n" , ntohs(udph->dest));
        printf("UDP Length       : %d\n" , ntohs(udph->len));
        printf("UDP Checksum     : %d\n" , ntohs(udph->check));
    }
}
