#ifndef __FC_HDR_H
#define __FC_HDR_H

#include <stdio.h>

extern void Show_Frame_Control_Info(unsigned short);

struct fc_hdr {
    
    unsigned char frame;
    // protocol_version 2bits
	// unsigned char protocol_version;

    // type 2bits
	// unsigned char type;
    
    // subtype 4bits
	// unsigned char subtype;

    unsigned char flags;

} __attribute__ ((packed));

#define GET_Protocol_Version(hdr) (hdr & 0x03)
#define GET_Type(hdr) (hdr >> 2 & 0x03)
#define GET_Subtype(hdr) (hdr >> 4 & 0x03)
#define GET_To_DS(hdr) (hdr >> 8 & 0x01)
#define GET_From_DS(hdr) (hdr >> 9 & 0x01)
#define GET_More_Frag(hdr) (hdr >> 10 & 0x01)
#define GET_Retry(hdr) (hdr >> 11 & 0x01)
#define GET_Extension(hdr) (hdr >> 8 & 0x0f)
#define GET_Power_Mgmt(hdr) (hdr >> 12 & 0x01)
#define GET_More_Data(hdr) (hdr >> 13 & 0x01)
#define GET_Protected_Frame(hdr) (hdr >> 14 & 0x01)
#define GET_HTC(hdr) (hdr >> 15 & 0x01)

enum Frame_Type {
    Management,
    Control,
    Data,
    Extension,
};

const char* Frame_Type_String[] = {
    "Management",
    "Control",
    "Data",
    "Extension"
};

enum Mgmt_Frame_Type {
    Association_Request,
    Association_Response,
    Reassociation_Request,
    Reassociation_Response,
    Probe_Request,
    Probe_Response,
    Timimg_Advertisement,
    Reserved,
    Beacon,
    ATM,
    Disassociation,
    Authentication,
    Deauthentication,
    Action,
    Action_No_Ack,
    Reserved
};

const char* Mgmt_Frame_Type_String[] = {
    "Association_Request",
    "Association_Response",
    "Reassociation_Request",
    "Reassociation_Response",
    "Probe_Request",
    "Probe_Response",
    "Timimg_Advertisement",
    "Reserved",
    "Beacon",
    "ATM",
    "Disassociation",
    "Authentication",
    "Deauthentication",
    "Action",
    "Action_No_Ack",
    "Reserved"
};

enum Contorl_Frame_Type {
    Reserved,
    Reserved,
    Reserved,
    Reserved,
    Beamforming_Report_Poll,
    VHT_NDP_Announcement,
    Control_Frame_Extension,
    Control_Wrapper,
    Block_Ack_Request,
    Block_Ack,
    PS_Poll,
    RTS,
    CTS,
    Ack,
    CF_End,
    CF_End_CF_Ack
};

const char* Contorl_Frame_Type_String[] = {
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Beamforming_Report_Poll",
    "VHT_NDP_Announcement",
    "Control_Frame_Extension",
    "Control_Wrapper",
    "Block_Ack_Request",
    "Block_Ack",
    "PS_Poll",
    "RTS",
    "CTS",
    "Ack",
    "CF_End",
    "CF_End_CF_Ack"
};

enum Data_Frame_Type {
    Data,
    Data_CF_Ack,
    Data_CF_Poll,
    Data_CF_Ack_CF_Poll,
    Null_No_Data,
    CF_Ack_No_Data,
    CF_Poll_No_Data,
    CF_Ack_CF_Poll_No_Data,
    Qos_Data,
    Qos_Data_CF_Ack,
    Qos_Data_CF_Poll,
    Qos_Data_CF_Ack_CF_Poll,
    Qos_Null_No_Data,
    Reserved,
    Qos_CF_Poll_No_Data,
    Qos_CF_Ack_CF_Poll,
};

const char* Data_Frame_Type_String[] = {
    "Data",
    "Data_CF_Ack",
    "Data_CF_Poll",
    "Data_CF_Ack_CF_Poll",
    "Null_No_Data",
    "CF_Ack_No_Data",
    "CF_Poll_No_Data",
    "CF_Ack_CF_Poll_No_Data",
    "Qos_Data",
    "Qos_Data_CF_Ack",
    "Qos_Data_CF_Poll",
    "Qos_Data_CF_Ack_CF_Poll",
    "Qos_Null_No_Data",
    "Reserved",
    "Qos_CF_Poll_No_Data",
    "Qos_CF_Ack_CF_Poll",
};

enum Extension_Frame_Type {
    DMG_Beacon,
    Reserved
};

const char* Extension_Frame_Type_String[] = {
    "DMG_Beacon",
    "Reserved"
};

#endif