#To be inserted @ 800f1aa8
.include "../../Globals.s"
.include "../Header.s"

#Check if a nonspecial character
  lwz r4,OFST_Metadata_FtIntNum(rtoc)
  cmplw	r0, r4
  bgt Exit

#Run OnHit
  mulli r4,r0,4
  lwz  r3,OFST_KirbyOnHit(rtoc)
  lwzx  r12,r3,r4
  cmpwi r12,0
  beq Exit
  mr  r3,r31
  mtctr r12
  bctrl
  b Exit

Original:
  branch  r12,0x800f1ab0

Exit:
  branch  r12,0x800f1b58
