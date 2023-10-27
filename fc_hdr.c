#include "fc_hdr.h"

static void Show_Frame_Info(unsigned short frame_control){
    
    int ftype;
	ftype = GET_Type(frame_control);
	printf("\tFrame Type: %s\n", Frame_Type_String(ftype));

	int fsubtype = GET_Subtype(frame_control);
	switch (ftype)
	{
	case Management:
		printf("\tFrame Subtype: %s\n", Mgmt_Frame_Type_String(fsubtype));
		break;
	case Control:
		printf("\tFrame Subtype: %s\n", Contorl_Frame_Type_String(fsubtype));
		break;
	case Data:
		printf("\tFrame Subtype: %s\n", Data_Frame_Type_String(fsubtype));
		break;
	default:
		break;
	}
}