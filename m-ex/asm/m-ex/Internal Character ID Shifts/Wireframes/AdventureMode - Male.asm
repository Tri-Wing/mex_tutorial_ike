#To be inserted @ 8017c930
.include "../../../Globals.s"
.include "../../Header.s"

lwz r12,OFST_Metadata_FtIntNum(rtoc)
subi  r0,r12,4