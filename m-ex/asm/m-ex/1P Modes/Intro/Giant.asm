#To be inserted @ 80184294
.include "../../../Globals.s"
.include "../../Header.s"

# check if custom ftDemoIntro file is loaded for this fighter
  lwz r11,OFST_mexData(rtoc)
  lwz r11,Arch_Fighter(r11)
  lwz r11,Arch_Fighter_DefineIDs(r11)
  add	r12, r31, r30
  lbz r12,0xF4(r12)
  mulli r12,r12,3
  add r11,r11,r12
  lbz r11,0x0(r11)  # internal ID
  mulli r11,r11,RuntimeIntroParam_Stride
  lwz r12,OFST_mexData(rtoc)
  lwz r12,Arch_Fighter(r12)
  lwz r12,Arch_Fighter_RuntimeIntroParam(r12)
  lwzx r11,r11,r12
  cmpwi r11,0
  beq NoCustom

# get param
  lfs f31,0x18(r11)
  lfs f30,0x1C(r11)
  lfs f29,0x20(r11)
  b Exit

NoCustom:
# original
  lfs	f1, 0x0074 (r4)

Exit:
  li r11,1
  cmpwi r11,0 # stupid comparison because upcoming jobj assert

branch r0,0x8018429c