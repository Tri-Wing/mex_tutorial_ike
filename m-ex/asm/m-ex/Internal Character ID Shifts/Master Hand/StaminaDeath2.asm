#To be inserted @ 800c8ea4
.include "../../../Globals.s"
.include "../../Header.s"

lwz r12,OFST_Metadata_FtIntNum(rtoc)
subi  r12,r12,6
cmpw r0,r12