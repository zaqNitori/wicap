#ifndef __FC_HDR_H
#define __FC_HDR_H



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
#define GET_Subtype(hdr) (hdr >> 4 & 0x0f)
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
    Management = 0,
    Control = 1,
    Data = 2,
    Extension = 3,
};

enum Mgmt_Frame_Subtype {
    Association_Request = 0,
    Association_Response = 1,
    Reassociation_Request = 2,
    Reassociation_Response = 3,
    Probe_Request = 4,
    Probe_Response = 5,
    Timimg_Advertisement = 6,
    Mgmt_Reserved = 7,
    Beacon = 8,
    ATM = 9,
    Disassociation = 10,
    Authentication = 11,
    Deauthentication = 12,
    Action = 13,
    Action_No_Ack = 14,
};

enum Contorl_Frame_Subtype {
    ConTrol_Reserved,
    Beamforming_Report_Poll = 4,
    VHT_NDP_Announcement = 5,
    Control_Frame_Extension = 6,
    Control_Wrapper = 7,
    Block_Ack_Request = 8,
    Block_Ack = 9,
    PS_Poll = 10,
    RTS = 11,
    CTS = 12,
    Ack = 13,
    CF_End = 14,
    CF_End_CF_Ack = 15
};

enum Data_Frame_Subtype {
    Data_Data = 0,
    Data_CF_Ack = 1,
    Data_CF_Poll = 2,
    Data_CF_Ack_CF_Poll = 3,
    Null_No_Data = 4,
    CF_Ack_No_Data = 5,
    CF_Poll_No_Data = 6,
    CF_Ack_CF_Poll_No_Data = 7,
    Qos_Data = 8,
    Qos_Data_CF_Ack = 9,
    Qos_Data_CF_Poll = 10,
    Qos_Data_CF_Ack_CF_Poll = 11,
    Qos_Null_No_Data = 12,
    Data_Reserved = 13,
    Qos_CF_Poll_No_Data = 14,
    Qos_CF_Ack_CF_Poll = 15,
};

enum Extension_Frame_Subtype {
    DMG_Beacon = 0,
    Reserved = 1,
};

extern void Show_Frame_Control_Info(unsigned short);

#endif