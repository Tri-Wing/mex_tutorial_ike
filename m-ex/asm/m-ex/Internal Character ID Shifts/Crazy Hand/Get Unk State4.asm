#To be inserted @ 8015039c
.include "../../../Globals.s"
.include "../../Header.s"

lwz r3,OFST_Metadata_FtIntNum(rtoc)
subi  r3,r3,5