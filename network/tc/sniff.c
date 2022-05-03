#include<pcap.h>
#include<stdio.h>

#define ETHER_ADDR_LEN 6

struct ether_data {
    u_char ether_dhost[ETHER_ADDR_LEN];
    u_char ether_shost[ETHER_ADDR_LEN];
    u_short ether_type;
};

struct ip_data{
    u_char ip_vhl;      /* version << 4 | header length >> 2 */
    u_char ip_tos;      /* type of service */
    u_short ip_len;     /* total length */
    u_short ip_id;      /* identification */
    u_short ip_off;     /* fragment offset field */
#define IP_RF 0x8000    /* reserved fragment flag */
#define IP_DF 0x4000    /* don't fragment flag */
#define IP_MF 0x2000    /* more fragments flag */
#define IP_OFFMASK 0x1fff   /* mask for fragmenting bits */
    u_char ip_ttl;      /* time to live */
    u_char ip_p;        /* protocol */
    u_short ip_sum;     /* checksum */
    struct in_addr ip_src,ip_dst;   /* source and dest address */
};
#define IP_HL(ip)   (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)    (((ip)->ip_vhl) >> 4)

struct udp_data{
    u_short udp_sport;
    u_short udp_dport;
    u_short udp_len;
    u_short udp_checksum;
};

struct dns_packet{
    struct ether_data eth;
    struct ip_data ip;
    struct udp_data udp;
    u_char payload;
};

int main(int argc, char *argv[]){
    pcap_if_t *alldevs,*ptr;
    char errbuf[PCAP_ERRBUF_SIZE];

    int dev = pcap_findalldevs(&alldevs, errbuf);
    if(dev == PCAP_ERROR){
        fprintf(stderr, "Error occured in findalldes : %s\n", errbuf);
        pcap_freealldevs(alldevs);
        return 2;
    }

    if(alldevs == NULL){
        fprintf(stderr, "No devices found!\n");
        return 2;
    }

    bpf_u_int32 mask, net;
    if (pcap_lookupnet(alldevs->name, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Can't get netmask for device %s\n", alldevs->name);
        net = 0;
        mask = 0;
}

    fprintf(stdout,"Interfaces present on the system are : \n");
    for(ptr = alldevs ; ptr!=NULL ; ptr=ptr->next){
        fprintf(stdout, "%s\n", ptr->name);
    }

    pcap_t *handle;
    int BUFSIZE = 1024;

    handle = pcap_open_live(alldevs->name, BUFSIZE, 1, 1000, errbuf);
    if(handle == NULL){
        fprintf(stderr, "Couldn't open device %s: %s\n", alldevs->name, errbuf);
        pcap_freealldevs(alldevs);
        return 2;
    }

    const char *filter_str = "udp port 53";
    struct bpf_program prog;

    if(pcap_compile(handle,&prog,filter_str,1,net) != 0 ){
        fprintf(stderr, "Couldn't parsee filter  : %s\n", errbuf);
        pcap_freealldevs(alldevs);
        return 2;
    }

    if(pcap_setfilter(handle, &prog) != 0){
        fprintf(stderr, "Couldn't install filter : %s\n", errbuf);
        pcap_freealldevs(alldevs);
        return 2;
    }
    /* Grab a packet */
    const u_char *packet;
    struct pcap_pkthdr header;
    packet = pcap_next(handle, &header);
    fprintf(stdout, "Filtered a packet with length of [%d]\n", header.len);

    for(int i=0 ; i<header.len ; i++){
        fprintf(stdout,"%c",packet[i]);
    }

    pcap_close(handle);

    return 0;
}
