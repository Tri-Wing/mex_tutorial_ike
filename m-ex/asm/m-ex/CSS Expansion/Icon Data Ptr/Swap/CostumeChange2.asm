#To be inserted @ 802600f0
.include "../../../../Globals.s"
.include "../../../Header.s"

lwz  r3,OFST_MnSlChrIconData(rtoc)
addi  r3,r3,0xDD
lbzx	r3, r3, r0
