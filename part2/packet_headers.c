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
    unsigned char etherType[2];
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
	unsigned char src_port[2];
	unsigned char dest_port[2];
	unsigned char seq_num[4];
	unsigned char ack[4];
	unsigned char offset_res_flag[2];
	unsigned char window_size[2];
	unsigned char check_sum[2];
	unsigned char urgent[2];
	unsigned char option[4];		//this char just indicates the first 4 bytes of the optional section. We me need to have a    
};

struct tls_h{
	unsigned char type;
	unsigned char version[2];
	unsigned char length[2];
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
	struct tls_h * tls;
    
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
    for (i = 0; (packet = pcap_next(pcap,&header)) != NULL; i++){
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
        
 	// print src and dest port number
	tcp = (struct tcp_h *) (packet + sizeof(struct ethernet_h) + sizeof(struct ip_h)); //calulate tcp header and map to struct
	printf("source port- ");
	unsigned short src_port = *((unsigned short*)tcp->src_port);	
	src_port = src_port>>8 | src_port<<8;
	printf("%u",src_port);

	printf("\n");
	printf("destination port- ");
	unsigned short dest_port = *((unsigned short*)tcp->dest_port);
	dest_port = dest_port>>8 | dest_port<<8;
	printf("%u",dest_port);
	printf("\n");

        
	//calulate tls header and map to struct. This calculation  checks for the first tls message if any. It checks only for TLSv1 (using 0x0301)
	int size = header.len;
	if( size >= sizeof(struct ethernet_h) + sizeof(struct ip_h) + sizeof(struct tcp_h)+ sizeof(struct tls_h)){ 	//check if header has enough bytes for tls
		tls = (struct tls_h *) (packet + sizeof(struct ethernet_h) + sizeof(struct ip_h) + sizeof(struct tcp_h)); 
		unsigned char version_upper = *((unsigned char*)tls->version);
		unsigned char version_lower = *((unsigned char*)tls->version+1);
		if (version_upper == 0x03 && version_lower == 0x01){
			printf("TLS 1.0: Yes\n");
		}
		else{
			printf("TLS 1.0: No\n");
		}
		version_upper = 0;	//clearing values
		version_lower = 0;	//clearing values	
	}
	else{
		printf("TLS 1.0: No\n");
	}
	printf("\n");
    }
}
