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
//	unsigned char preamble[7];
//	unsigned char delimiter;

    unsigned char destAddress[6];
	unsigned char srcAddress[6];
    // if value < 1500(max allowed frame size); specifies length - ver802.2
    // else value > 1536; specifies which protocol is encapsulated in the payload - Ethernet II framing
    unsigned int etherType;
};

struct ip_h{
    /*need these to compute packet lengths*/
    unsigned char v_ihl; //internet header length
    unsigned char service; //Type of service - used to define the way routers handle the datagram
    unsigned short int total_len; //16 bits, max packet size - 2^16 - 65,536
    unsigned short int identification; //Used along with src address to uniquely id a datagram
    unsigned int flags; // 00000xxx {Reserved = 0, Don't Fragment, Fragment}
    unsigned char ttl; //no. of hops
    unsigned char protocol; //http://bit.ly/c0xBMt list of ip protocols
    unsigned short checksum;
    unsigned int srcAddress;
    unsigned int destAddress;
};

struct tcp_h{

};


int main(int argc, char * argv[]){
  /*Stuff needed to parse file*/
  pcap_t *pcap;
  char errbuf [PCAP_ERRBUF_SIZE];
  const unsigned char * packet;
  struct pcap_pkthdr header;
  int i;

  /*Header Structs*/
  struct ethernet_h * ethernet;
  struct ip_h * ip;
  struct tcp_h * tcp;


  /*opening trace file*/
  if ((pcap = pcap_open_offline(argv[1],errbuf)) == NULL){
    fprintf(stderr, "ERROR: reading pcap file %s : %s\n", 
            argv[0],errbuf);
    exit(1);
  }

 
  /* reading one packet at a time and counting packets seen */
  for (i = 0; (packet = pcap_next(pcap,&header)) != NULL; i++){

    printf("-------- Packet %d ------------\n",i);
    printf("Size: %d bytes\n",header.len);
	//printf("Size %ld", sizeof(struct ethernet_h));
    /*ethernet header memory map*/
	printf("src address- ");
    ethernet = (struct ethernet_h *) (packet);
	unsigned char* src = ethernet->srcAddress;
	int j;
	for(j=0; j<6; j+=1){
		printf("%02x:",(*(src+j)));
	}
	printf("\n");

	printf("dest address- ");
    	ethernet = (struct ethernet_h *) (packet);
	unsigned char* dest = ethernet->destAddress;
	for(j=0; j<6; j+=1){
		printf("%02x:",(*(dest+j)));
	}
	printf("\n");

    /*cacluate start of IP header and map to struct*/
    ip = (struct ip_h *) (packet + sizeof(struct ethernet_h));

    //TODO: print src and dest IP

    tcp = (struct tcp_h *) (packet + sizeof(struct ethernet_h) + sizeof(struct ip_h));

    //TODO: print src and dest port number


	//TODO: TLS 1.0
  }



}
