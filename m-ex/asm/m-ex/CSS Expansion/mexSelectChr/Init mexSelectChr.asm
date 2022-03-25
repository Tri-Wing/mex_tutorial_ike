#To be inserted @ 802647fc
.include "../../../Globals.s"
.include "../../Header.s"

#Check for mexSelectChr
  lwz r3,OFST_mexSelectChr(r13)
  cmpwi r3,0
  beq Original

#Get floats
  lwz r3,OFST_Menu_Param(rtoc)
  lfs f2,Arch_Menu_MenuParam(r3)
  bl  Floats
  mflr  r3

#Scale puck collision radius
  lfs f1,0x0(r3)
  fmuls f1,f1,f2
  stfs  f1,-0x34AC(rtoc)
#Scale puck pickup radius
  lfs f1,0x4(r3)
  fmuls f1,f1,f2
  stfs  f1,-0x34CC(rtoc)
#Scale puck icon bound radius
  lfs f1,0x8(r3)
  fmuls f1,f1,f2
  stfs  f1,-0x35CC(rtoc)
#Scale cursor speed
  lfs f1,0xC(r3)
  fmuls f1,f1,f2
  stfs  f1,-0x3560(rtoc)

#Store PlayerCard->IconGrid Y boundary
  #stfs  f1,-0x353C(rtoc)

#Store rules X left boundary (y is checked at 802616f0)
  #stfs  f1,-0x3510(rtoc)
#Store rules X right boundary (y is checked at 802616f0)
  #stfs  f1,-0x3568(rtoc)

#Store back X left boundary (y is checked at 8026128c)
  #stfs  f1,-0x3518(rtoc)

#Store Teams X right boundary (y is checked at 8026177c)
  #stfs  f1,-0x350C(rtoc)

#Store Nametag Scale XY
  #stfs  f1,-0x3430(rtoc)
  #stfs  f1,-0x342C(rtoc)

#Store Nametag XY Shift
  #stfs  f1,-0x3580(rtoc)
  #stfs  f1,-0x3418(rtoc)

#Store Rules Y bottom boundary (used for all rules Y requirement)
  #stfs  f1,-0x3514(rtoc)

.set REG_IconData,31
.set REG_LoopCount,30
.set REG_mexIconData,29

#Init loop
  backup
  load  REG_IconData,0x803f0b24
  lwz  REG_mexIconData,OFST_MnSlChrIconData(rtoc)
  addi	REG_mexIconData, REG_mexIconData, 220
  li  REG_LoopCount,0

Hide_Loop:
#Hide JObj
  lwz	r3, -0x49E0 (r13)
  addi  r4,sp,0x80
  lbz r5,0x5(REG_IconData)
  li  r6,-1
  crclr 6
  branchl r12,0x80011e24
  lwz  r3,0x80(sp)
  lwz r4,0x14(r3)
  li  r5,1
  rlwimi r4,r5,4,27,27
  stw r4,0x14(r3)
#unlocked
  li  r3,2
  stb r3,0x2(REG_mexIconData)
Hide_LoopInc:
  addi  REG_LoopCount,REG_LoopCount,1
  addi  REG_IconData,REG_IconData,0x1C
  addi  REG_mexIconData,REG_mexIconData,0x1C
  cmpwi REG_LoopCount,25
  blt Hide_Loop

.set  REG_mexSelectChr,30
.set  REG_IconsJObj,29
#Init
  lwz REG_mexSelectChr,OFST_mexSelectChr(r13)

InitPositionsModel:
  .set  REG_GObj,20
  .set  REG_JObj,21
  #Create GObj
    li  r3,4
    li  r4,5
    li  r5,128
    branchl r12,0x803901f0
    mr  REG_GObj,r3
  #Load joint
    lwz r3,SlChr_PositionModel(REG_mexSelectChr)
    branchl r12,0x80370e44
    mr  REG_IconsJObj,r3
    stw	REG_IconsJObj, OFST_mexSelectChr_IconJoint (r13)
  #Store object pointer
    mr  r3,REG_GObj
    lbz	r4, -0x3E57 (r13)
    mr  r5,REG_IconsJObj
    branchl r12,0x80390a70
  #Add GX Link
    mr  r3,REG_GObj
    load  r4,0x80391070
    li  r5,1
    li  r6,128
    branchl r12,0x8039069c
  #Add proc
    mr  r3,REG_GObj
    load  r4,0x8022eae0
    li  r5,4
    branchl r12,0x8038fd54
  #Add anim
    mr  r3,REG_IconsJObj
    lwz r4,SlChr_IconAnimJoint(REG_mexSelectChr)
    lwz r5,SlChr_IconMatAnim(REG_mexSelectChr)
    li  r6,0
    branchl r12,0x8036fb5c

/*
  #Play animation
    mr  r3,REG_IconsJObj
    lfs	f1, -0x3640 (rtoc)
    branchl r12,0x8036f8bc
    mr  r3,REG_IconsJObj
    branchl r12,0x80370928
*/

  #Play animation
  mr  r3,REG_IconsJObj
  li r4,6
  li r5,0x20
  load r6,0x8036410c
  li r7,1
  branchl r12,0x80364c08
  mr  r3,REG_IconsJObj
  branchl r12,0x80370928


  /*
  #Store pointer to all children
  .set  REG_ThisJObj,22
  .set  REG_IconData,23
  #Init
    lwz  REG_IconData,OFST_MnSlChrIconData(rtoc)
    addi  REG_IconData,REG_IconData,220
    lwz  REG_ThisJObj,0x10(REG_IconsJObj)    #get child
  InitPositionsModel_Loop:
    stw REG_ThisJObj,0x18(REG_IconData)
  InitPositionsModel_IncLoop:
    addi  REG_IconData,REG_IconData,0x1C    #next icon
    lwz  REG_ThisJObj,0x8(REG_ThisJObj)    #get sibling
    cmpwi REG_ThisJObj,0
    bne InitPositionsModel_Loop
  */

#Skip Original Code
  restore
  branch  r12,0x80264924

Floats:
blrl
.float 8      #puck collision radius
.float  9     #puck pickup radius
.float  1.5     #icon boundary radius
.float 0.0002   #cursor speed

Original:
/*
# Use original Icon Struct
  load  r3,0x803f0b24
  stw r3,OFST_MnSlChrIconData(rtoc)
# Use original Icon count
  li  r3,26
  stw r3,OFST_Metadata_CSSIconCount(rtoc)
*/
# Original code
  addi	r20, r20, 220
