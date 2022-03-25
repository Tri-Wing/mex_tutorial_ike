#To be inserted @ 803d7088
.include "../../Globals.s"
.include "../Header.s"

.set  REG_FighterData,31
.set  REG_FighterID,30
.set  REG_ArticleID,29
.set  REG_ID,28
.set  REG_MEXItemLookup,27

backup

#Backup args
  lwz  REG_FighterData,0x2C(r3)
  mr  REG_ArticleID,r4

# Get table
  lwz r3,OFST_mexData(rtoc)
  lwz r3,Arch_Fighter(r3)
  lwz r3,Arch_Fighter_MEXItemLookup(r3)
  lwz REG_FighterID,0x4(REG_FighterData)
  mulli r4,REG_FighterID,MEXItemLookup_Stride
  add REG_MEXItemLookup,r3,r4
#Check if exists
  lwz r3,0x0(REG_MEXItemLookup)
  cmpw  REG_ArticleID,r3
  blt HasItem
#Does not have item, check if this is kirby
  cmpwi REG_FighterID,4
  bne DoesNotExist
#Check if kirby has a copy ability
  lwz r5,0x2238(REG_FighterData)
  cmpwi r5,4
  beq DoesNotExist
#Check if this fighter has the item
  lwz r3,OFST_mexData(rtoc)
  lwz r3,Arch_Fighter(r3)
  lwz r3,Arch_Fighter_MEXItemLookup(r3)
  mulli r4,r5,MEXItemLookup_Stride
  add REG_MEXItemLookup,r3,r4
  lwz r3,0x0(REG_MEXItemLookup)
  cmpw  REG_ArticleID,r3
  bge DoesNotExist
HasItem:
#Get external item ID from internal
  lwz r3,0x4(REG_MEXItemLookup)
  mulli r4,REG_ArticleID,2
  lhzx r3,r3,r4
  b Exit

#############################################
DoesNotExist:
#OSReport
  bl  ErrorString
  mflr  r3
  mr r4,REG_FighterID
  mr  r5,REG_ArticleID
  branchl r12,0x803456a8
#Assert
  bl  Assert_Name
  mflr  r3
  li  r4,0
  load  r5,0x804d3940
  branchl r12,0x80388220
Assert_Name:
blrl
.string "m-ex"
.align 2
ErrorString:
blrl
.string "error: fighter %d does not have item %d\n"
.align 2
###############################################

Exit:
  restore
  blr
