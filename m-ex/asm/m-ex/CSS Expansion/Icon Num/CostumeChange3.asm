#To be inserted @ 8026015c
.include "../../../Globals.s"
.include "../../Header.s"

lwz r12,OFST_Metadata_CSSIconCount(rtoc)
cmpw	r3, r12
