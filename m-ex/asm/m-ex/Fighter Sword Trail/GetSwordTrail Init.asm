#To be inserted @ 800c3098
.include "../../Globals.s"
.include "../Header.s"

.set REG_FighterData, 31

# get trail data get function ptr
  lwz  r4,OFST_mexData(rtoc)
  lwz  r4, Arch_FighterFunc(r4)
  lwz  r4,Arch_FighterFunc_GetTrailData(r4)
  lwz	r3, 0x0004 (REG_FighterData)
  mulli r3,r3,4
  lwzx r3,r3,r4
  cmpwi r3,0
  beq Original
# get trail data from ftfunction
  mtctr r3
  lwz	r3, 0x0 (REG_FighterData)
  bctrl
  mr r5,r3
  branch r12,0x800c30d4
  
Original:
  lwz	r3, 0x0004 (REG_FighterData)