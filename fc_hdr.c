#include "fc_hdr.h"

const char* Frame_Type_String[] = {
    "Management",
    "Control",
    "Data",
    "Extension"
};

const char* Mgmt_Frame_Subtype_String[] = {
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

const char* Contorl_Frame_Subtype_String[] = {
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

const char* Data_Frame_Subtype_String[] = {
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

const char* Extension_Frame_Subtype_String[] = {
    "DMG_Beacon",
    "Reserved"
};

void Show_Frame_Info(unsigned short frame_control){
    
    int ftype;
	ftype = GET_Type(frame_control);
	printf("\tFrame Type: %s\n", Frame_Type_String[ftype]);

	int fsubtype = GET_Subtype(frame_control);
	switch (ftype)
	{
	case Management:
		printf("\tFrame Subtype: %s\n", Mgmt_Frame_Subtype_String[fsubtype]);
		break;
	case Control:
		printf("\tFrame Subtype: %s\n", Contorl_Frame_Subtype_String[fsubtype]);
		break;
	case Data:
		printf("\tFrame Subtype: %s\n", Data_Frame_Subtype_String[fsubtype]);
		break;
	default:
		break;
	}
}