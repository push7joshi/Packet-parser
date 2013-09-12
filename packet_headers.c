#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h> //library for parsing pcap files
#include <stdint.h> //include int32_t

/*****************************************
 *
 * packet_headers.c
 *
 * P538 - Computer Networks
 * Original author: Adam J. Aviv
 *
 *
 * Reads a pcap trace and prints out the packet headers, both
 * the Ethernet and TCP/IP headers
 *
 *
 * USAGE: ./packet_headers trace.pcap
 ****************************************/


/***************************************
 *
 * Structs to represent headers
 *
 ***************************************/
struct ethernet_h{
    unsigned char destAddress[6];
    unsigned char srcAddress[6];
        // etherType: if value < 1500(max allowed frame size); specifies length - ver802.2
        // else value > 1536; specifies which protocol is encapsulated in the payload - Ethernet II framing
    unsigned char etherType[2];
};

struct ip_h4
{
    /*need these to compute packet lengths*/
    unsigned char v_ihl; //internet header length
    unsigned char service; //Type of service - used to define the way routers handle the datagram
    unsigned short int total_len; //16 bits, max packet size - 2^16 - 65,536
    
    unsigned short int identification; //Used along with src address to uniquely id a datagram
    unsigned short flags; // 00000xxx {Reserved = 0, Don't Fragment, Fragment}
    unsigned char ttl; //no. of hops
    unsigned char protocol; //http://bit.ly/c0xBMt list of ip protocols
    unsigned short checksum;
    unsigned int destAddress;
    unsigned int srcAddress;
};

struct ip_h
{
    /*need these to compute packet lengths*/
    unsigned char v_ihl; //internet header length
    unsigned char service; //Type of service - used to define the way routers handle the datagram
    unsigned char total_len[2]; //16 bits, max packet size - 2^16 - 65,536
    
    unsigned char identification[2]; //Used along with src address to uniquely id a datagram
    unsigned char offset[2]; // 00000xxx {Reserved = 0, Don't Fragment, Fragment} 00000000
    unsigned char ttl; //no. of hops
    unsigned char protocol; //http://bit.ly/c0xBMt list of ip protocols
    unsigned char checksum[2];
    unsigned char srcAddress[4];
    unsigned char destAddress[4];
};


struct tcp_h{
    
};


int main(int argc, char * argv[])
{
    /*Stuff needed to parse file*/
    pcap_t *pcap;
    char errbuf [PCAP_ERRBUF_SIZE];
    const unsigned char * packet;
    struct pcap_pkthdr header;
    int i, j;
    
    /*Header Structs*/
    struct ethernet_h * ethernet, eth1;
    struct ip_h * ip;
    struct tcp_h * tcp;
    
    if (argc != 2) {
        printf("Please specify input file!");
        exit(1);
    }
    
    /*opening trace file*/
    if ((pcap = pcap_open_offline(argv[1],errbuf)) == NULL){
        fprintf(stderr, "ERROR: reading pcap file %s : %s\n",
                argv[0],errbuf);
        exit(1);
    }
    
    /* reading one packet at a time and counting packets seen */
    for (i = 0; i < 5; i++)
    {
        (packet = pcap_next(pcap,&header));
        printf("-------- Packet %d ------------\n",i);
        printf("Size: %d bytes\n",header.len);
        
        /*ethernet header memory map*/
        ethernet = (struct ethernet_h *)(packet);
        printf("\nMAC src:\t");
        for(j=0;j<6;j++)
        {
            printf("%02x:", ethernet->srcAddress[j]);
        }
        
        printf("\nMAC dest:\t");
        for(j=0;j<6;j++)
        {
            printf("%02x:", ethernet->destAddress[j]);
        }
        /*cacluate start of IP header and map to struct*/
        ip = (struct ip_h *) (packet + sizeof(struct ethernet_h));
        
        printf("\b\nIP src: \t");
        for (j=0;j<4;j++)
        {
            printf(" %u ", ip->srcAddress[j]);
        }
        printf("\nIP dest: \t");
        for (j=0;j<4;j++)
        {
            printf(" %u ", ip->destAddress[j]);
        }
        printf("\n");        
            //tcp = (struct tcp_h *) (packet + sizeof(struct ethernet_h) + sizeof(struct ip_h));
        
            //TODO: print src and dest port number
        
        
            //TODO: TLS 1.0
    }
}
