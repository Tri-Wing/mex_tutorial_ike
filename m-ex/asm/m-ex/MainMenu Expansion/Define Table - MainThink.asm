#To be inserted @ 8022db1c
.include "../../Globals.s"
.include "../Header.s"

.set MenuID,0
.set REG_MenuDef, 3

# check if exists
  lwz r12,OFST_mexMenu(r13)
  cmpwi r12,0
  beq Original
  lwz REG_MenuDef,mexMenu_MenuDef(r12)
  addi  REG_MenuDef,REG_MenuDef, MenuID * MenuDefStride
  b Exit

Original:
  subi	r3, r3, 18768

Exit: