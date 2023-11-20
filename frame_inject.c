#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include <errno.h>
#include <string.h>
#include <pcap/pcap.h>
#include "radiotap_iter.h"

struct ieee80211_hdr {
  uint16_t /*__le16*/ frame_control;
  uint16_t /*__le16*/ duration_id;
  uint8_t addr1[6];
  uint8_t addr2[6];
  uint8_t addr3[6];
  uint16_t /*__le16*/ seq_ctrl;
  //uint8_t addr4[6];
} __attribute__ ((packed));

const uint8_t mac[6] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab};

int main(int argc, char *argv[])
{
    pcap_t *handle;			/* Session handle */
    char *dev;			/* The device to sniff on */
    bpf_u_int32 netp;
    char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
    struct bpf_program fp;		/* The compiled filter */
    char filter_exp[] = "type mgt subtype assoc-req";	/* The filter expression */
    int num_packets = 2;			/* number of packets to capture */

    /* check for capture device name on command-line */
	if (argc == 2) {
		dev = argv[1];
	}
	else {
		fprintf(stderr, "error: unrecognized command-line options\n\n");
		return 1;
	}
    
    /* Open the session in promiscuous mode */
    handle = pcap_open_live(dev, BUFSIZ, 1, 100, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return(2);
    }

    struct ieee80211_hdr my_hdr = {
        //beacon
        .frame_control = 0x80,
        .duration_id = 0,
        .addr1 = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00},
        //.addr2 = "\x40\xee\x15\xb7\x24\x54",
        .addr2 = {0x87, 0x87, 0x87, 0x87, 0x87, 0x87},
        .addr3 = 0,
        .seq_ctrl = 0,
        .addr4 = 0
    };
    

    if(pcap_inject(handle, &my_hdr, sizeof(my_hdr)) == -1) {
        fprintf(stderr, "pcap inject error\n");
        return(2);
    }
    
	/* cleanup */
	pcap_close(handle);

	printf("\nSend complete.\n");    
    
    return(0);
}
