#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include <errno.h>
#include <string.h>
#include <pcap/pcap.h>

int main(int argc, char *argv[])
{
    pcap_t *handle;			/* Session handle */
    char *dev;			/* The device to sniff on */
    int write_len;

    char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */

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

    unsigned char myPing[] = {
        0x5c, 0x92, 0x5e, 0xa3, 0x53, 0x02, 0x40, 0xee, 0x15, 0xb7, 0x24, 0xee, 0x08, 0x00, 0x45, 0x00,
        0x00, 0x26, 0x00, 0x01, 0x00, 0x00, 0x40, 0x01, 0xf7, 0x5a, 0xc0, 0xa8, 0x01, 0x21, 0xc0, 0xa8,
        0x01, 0x0a, 0x08, 0x00, 0x43, 0x0c, 0x1c, 0x6c, 0x00, 0x01, 0x6c, 0x69, 0x62, 0x6e, 0x65, 0x74,
        0x20, 0x3a, 0x44, 0x00
    };

    /*unsigned char radiotapheader[] = {
        0x00, 0x00, 0x38, 0x00, 0x2f, 0x40, 0x40, 0xa0,
        0x20, 0x08, 0x00, 0xa0, 0x20, 0x08, 0x00, 0x00,   
        0xf9, 0xe4, 0xd1, 0x9e, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x02, 0x85, 0x09, 0xa0, 0x00, 0xd8, 0x00,   
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xf9, 0xe4, 0xd1, 0x9e, 0x00, 0x00, 0x00, 0x00,   
        0x00, 0x00, 0x01, 0x01, 0xd1, 0x00, 0xd8, 0x01,
    };

    unsigned char ieee80211beacon[] = {
        0x80, 0x00, 0x00, 0x00, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xee,
        0x40, 0xee, 0x15, 0xb7, 0x24, 0x54,
        0x40, 0xee, 0x15, 0xb7, 0x24, 0x54,
        0xb0, 0x22
    };

    int sz = sizeof(radiotapheader) + sizeof(ieee80211beacon);
    unsigned char* packet = (unsigned char*) malloc(sz * sizeof(unsigned char));
    memcpy(packet, radiotapheader, sizeof(radiotapheader));
    memcpy(packet + sizeof(radiotapheader), ieee80211beacon, sizeof(ieee80211beacon));*/

    // copy from wireshark RX radiotap header.
    // Cost 80 bytes.
    // unsigned char ieee80211[] = {
    //     0x00,                                             // revision
    //     0x00,                                             // Pad
    //     0x38, 0x00,                                       // Header Length (56)
    //     0x2f, 0x40, 0x40, 0xa0,                           // Present Flags 1
    //     0x20, 0x08, 0x00, 0xa0,                           // Present Flags 2
    //     0x20, 0x08, 0x00, 0x00,                           // Present Flags 3
    //     0xf9, 0xe4, 0xd1, 0x9e, 0x00, 0x00, 0x00, 0x00,   // Timestamp
    //     0x00,                                             // Flags
    //     0x02,                                             // Data Rate
    //     0x85, 0x09,                                       // Channel Freq (2437)
    //     0xa0, 0x00,                                       // Channel Flags
    //     0xd8,                                             // Antenna Signals 
    //     0x00,                                             //
    //     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   //
    //     0xf9, 0xe4, 0xd1, 0x9e, 0x00, 0x00, 0x00, 0x00,   //
    //     0x00, 0x00, 0x01, 0x01, 0xd1, 0x00, 0xd8, 0x01,   //
    //     0x80, 0x00,                                       // Frame Control
    //     0x00, 0x00,                                       // Duration ID
    //     0xff, 0xff, 0xff, 0xff, 0xff, 0xee,               // DA
    //     0xff, 0xff, 0xff, 0xff, 0xff, 0xee,               // SA
    //     0xff, 0xff, 0xff, 0xff, 0xff, 0xee,               // BSS ID
    //     0xb0, 0x22
    // };

    // radiotap header reducing
    // Cost 62 bytes.
    // unsigned char ieee80211[] = {
    //     0x00,                                             // Version
    //     0x00,                                             // Pad
    //     0x26, 0x00,                                       // Header Length (38)
    //     0x2f, 0x40, 0x40, 0x00,                           // Present Flags 1
    //     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // Timestamp
    //     0x00,                                             // Flags
    //     0x00,                                             // Data Rates
    //     0x3c, 0x14,                                       // Channel Freq
    //     0x40, 0x01,                                       // Channel Flags
    //     0x00, 0x00,                                       // antenna signals
    //     0x00, 0x00,                                       // RX flags
    //     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // Timestamp same as previous one
    //     0x00, 0x00, 0x01, 0x01,                           // timestamp info
    //     0x80, 0x00,                                       // Frame Control
    //     0x00, 0x00,                                       // Duration ID
    //     0xff, 0xff, 0xff, 0xff, 0xee, 0xee,               // DA
    //     0xff, 0xff, 0xff, 0xff, 0xee, 0xee,               // SA
    //     0xff, 0xff, 0xff, 0xff, 0xee, 0xee,               // BSS ID
    //     0xb0, 0x22
    // };

    // radiotap header minimizing
    // Cost 32 bytes.
    unsigned char ieee80211[] = {
        0x00,                                             // Version
        0x00,                                             // Pad
        0x08, 0x00,                                       // Header Length (8)
        0x00, 0x00, 0x00, 0x00,                           // Present Flags 1
        0x80, 0x00,                                       // Frame Control
        0x00, 0x00,                                       // Duration ID
        0xff, 0xff, 0xff, 0xff, 0xee, 0xee,               // DA
        0xff, 0xff, 0xff, 0xff, 0xee, 0xee,               // SA
        0xff, 0xff, 0xff, 0xff, 0xee, 0xee,               // BSS ID
        0xb0, 0x22
    };

    write_len = pcap_inject(handle, &ieee80211, sizeof(ieee80211));

    if(write_len == -1) {
        fprintf(stderr, "pcap inject error\n");
        return(2);
    }
    
	/* cleanup */
	pcap_close(handle);
    //free(packet);
	printf("\n%d bytes Send complete.\n", write_len);    
    
    return(0);
}