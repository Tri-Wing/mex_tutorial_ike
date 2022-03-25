#To be inserted at 803753b0
.include "../Globals.s"
.include "Header.s"

.set  REG_HeapLo,31
.set  REG_FileSize,28
.set  REG_File,27
.set  REG_HeapID,26
.set  REG_Header,25
.set  REG_mexData,24

backup

#Check if file exists
  bl  FileName
  mflr  r3
  branchl r12,0x8033796c
  cmpwi r3,-1
  beq FileNotExist
#Get size of MnDt.dat
  bl  FileName
  mflr  r3
  branchl r12,0x800163d8
  addi  REG_FileSize,r3,0
#Align
  addi  REG_FileSize,REG_FileSize,31
  rlwinm	REG_FileSize, REG_FileSize, 0, 0, 26
#Create heap of this size
  add r4,REG_HeapLo,REG_FileSize     #heap hi = start + filesize
  addi  r4,r4,32*5              #plus 96 for header
  mr  r3,REG_HeapLo                  #heap lo = start
  mr  REG_HeapLo,r4             #new start = heap hi
  branchl r12,0x803440e8
  mr  REG_HeapID,r3
#Alloc header
  li  r4,68
  branchl r12,0x80343ef0
  mr  REG_Header,r3
#Alloc from this heap
  mr  r3,REG_HeapID
  mr  r4,REG_FileSize
  branchl r12,0x80343ef0
  mr  REG_File,r3
#Load file here
  bl  FileName
  mflr  r3
	mr r4, REG_File
	addi	r5, sp, 0x80
	branchl	r12,0x8001668C
#Init Archive
  lwz r5,0x80(sp)
  mr  r3,REG_Header   #store header
  mr  r4,REG_File      #file
  branchl r12,0x80016a54
#Get symbol offset
  mr  r3,REG_Header
  bl  SymbolName
  mflr  r4
  branchl r12,0x80380358
  mr  REG_mexData,r3
  stw REG_mexData,OFST_mexData(rtoc)

#Copy table pointers
.set  REG_Offsets,9
.set  REG_Count,8
.set  REG_currOffset,7
.set  REG_currArchOffset,6
  bl  rtocOffsets
  mflr  REG_Offsets
  subi  REG_Offsets,REG_Offsets,2
  li  REG_Count,0
CopyPointers_Loop:
#Get offset of rtoc
  mulli REG_currOffset,REG_Count,4
CopyPointers_InitWalkLoop:
#If no more, exit
  lhz r3,0x2(REG_Offsets)
  extsh r3,r3
  cmpwi r3,-1
  beq CopyPointers_Exit
  mr  REG_currArchOffset,REG_mexData
CopyPointers_WalkLoop:
#Get bottom of chain
  lhzu  r3,0x2(REG_Offsets)
  extsh r3,r3
  cmpwi r3,-1
  beq CopyPointers_WalkLoopExit
#Access pointer
  lwzx  REG_currArchOffset,r3,REG_currArchOffset
  b CopyPointers_WalkLoop
CopyPointers_WalkLoopExit:
#Store to
  stwx  REG_currArchOffset,REG_currOffset,rtoc
CopyPointers_IncLoop:
  addi  REG_Count,REG_Count,1
  b CopyPointers_Loop
CopyPointers_Exit:

#Init preload table
PreloadInit:
  lwz r3,OFST_Metadata_FtExtNum(rtoc)
  load  r4,0x803ba648
  li  r5,0
PreloadInit_Loop:
  stw r3,0x0(r4)
  addi  r4,r4,8
  addi  r5,r5,1
  cmpwi r5,8
  blt PreloadInit_Loop

#Flush instruction cache so code can be run from this file
  mr  r3,REG_File
  mr  r4,REG_FileSize
  branchl r12,0x80328f50

# TEMP #
# set last major num
  #li  r3,45
  #stw r3,OFST_MetaData_TermMajor(rtoc)

# persistent file reloc
  bl  tempalloc
  mflr  r3
  stw r3,OFST_HeapRuntime(rtoc)

# xFunction lookup
  bl  tempalloc2
  mflr  r3
  stw r3,OFST_XFunctionLookup(rtoc)

  b Exit

tempalloc:
blrl
.long 0
.long 0
.long 0
.long 0

.rept (PersistHeapNum)
.long -1    
.long -1    # pointer to runtime struct
.long 0     # start address for this heap
.long 0     # heap size
.long 1     # unk
.long 1     # isDisable, creates the heap when this is 0
.long 1     # bool, is set to 0 after heap is created
.endr

tempalloc2:
blrl
.rept xFuncLookup_Max + 1
.long 0 # xFunction ptr
.endr

FileName:
blrl
.string "MxDt.dat"
.align 2
SymbolName:
blrl
.string "mexData"
.align 2
Assert_Name:
blrl
.string "m-ex"
.align 2
ErrorString:
blrl
.string "Error: MxDt.dat not found on disc\n"
.align 2


rtocOffsets:
  blrl
  #indexed by rtoc order
  .hword Arch_Menu,Arch_Menu_CSS,-1
  .hword Arch_Fighter,Arch_Fighter_NameText,-1
  .hword Arch_Fighter,Arch_Fighter_DefineIDs,-1
  .hword Arch_Fighter,Arch_Fighter_CostumeFileSymbols,-1
  .hword Arch_Fighter,Arch_Fighter_CharFiles,-1
  .hword Arch_Fighter,Arch_Fighter_AnimFiles,-1
  .hword Arch_Fighter,Arch_Fighter_EffectFileIDs,-1
  .hword Arch_Effect, Effect_Files, -1
  .hword Arch_Fighter,Arch_Fighter_SSMFileIDs,-1
  .hword Arch_FGM,Arch_FGM_Files,-1
  .hword Arch_Fighter,Arch_Fighter_AnimCounts,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_MoveLogic,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onLoad,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onDeath,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialLw,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialLwAir,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialS,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialSAir,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialN,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialNAir,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialHi,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_SpecialHiAir,-1
  .hword Arch_Fighter,Arch_Fighter_CostumeIDs,-1
  .hword Arch_Fighter,Arch_Fighter_RuntimeCostumePointers,-1
  .hword Arch_FGM,Arch_FGM_RuntimeStruct,-1
  .hword Arch_FGM,0x0,-1 #SSM ID Def, unused now
  .hword Arch_FGM,Arch_FGM_Flags,-1 #ssm buffer sizes
  .hword Arch_Fighter,Arch_Fighter_GmRst_AnimFiles,-1
  .hword Arch_Fighter,Arch_Fighter_InsigniaIDs,-1
  .hword Arch_Fighter,Arch_Fighter_GmRst_Scale,-1
  .hword Arch_Fighter,Arch_Fighter_FtDemo_SymbolNames,-1
  .hword Arch_Fighter,Arch_Fighter_AnnouncerCall,-1
  .hword Arch_Fighter,Arch_Fighter_GmRst_VictoryTheme,-1
  .hword Arch_Effect,Effect_effBehaviorTable,-1
  .hword Arch_ItemsAdded,-1
  .hword Arch_Fighter,-1 #item index, need to implement this
  .hword Arch_FGM,Arch_FGM_LookupTable,-1 #audio groups
  .hword Arch_BGM,Arch_BGM_Files,-1
  .hword Arch_Fighter,Arch_Fighter_ftDataPointers,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onFloat,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onDoubleJump,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onZair,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onLanding,-1
  .hword Arch_Fighter,Arch_Fighter_onWallJump,-1
  .hword Arch_Fighter,Arch_Fighter_GmRstPointers,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onFSmash,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onUSmash,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_onDSmash,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_OnItemPickup,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_OnItemPickup2,-1
  .hword Arch_FighterFunc,Arch_FighterFunc_OnItemRelease,-1
  .hword Arch_Fighter,Arch_Fighter_BGM,-1
  .hword Arch_Fighter,Arch_Fighter_ViWaitFileNames,-1
  .hword Arch_Scene,Scene_Major,-1
  .hword Arch_Scene,Scene_Minor,-1
  .hword Arch_Effect,Effect_RuntimeUnk1,-1
  .hword Arch_Effect,Effect_RuntimeUnk3,-1
  .hword Arch_Effect,Effect_RuntimeTexGrNum,-1
  .hword Arch_Effect,Effect_RuntimeTexGrData,-1
  .hword Arch_Effect,Effect_RuntimeUnk4,-1
  .hword Arch_Effect,Effect_RuntimePtclLast,-1
  .hword Arch_Effect,Effect_RuntimePtclData,-1
  .hword Arch_Metadata,Arch_Metadata_FtIntNum,-1    # xFunction lookup here
  #CSS
  .hword  Arch_Menu,Arch_Menu_MenuParam,-1
  #Map
  .hword  Arch_Menu,Arch_Menu_SSS,-1
  .hword  Arch_Map,Arch_Map_StageIDs,-1
  .hword  Arch_Map,Arch_Map_Audio,-1
  .hword  Arch_grFunction,-1
  .hword  Arch_Map,Arch_Map_LineTypeData,-1
  #Kirby
  .hword Arch_Kirby,Arch_Kirby_AbilityFileNames,-1
  .hword Arch_Kirby,Arch_Kirby_AbilityCostumeFileNames,-1
  .hword Arch_Kirby,Arch_Kirby_EffectIDs,-1
  .hword Arch_Kirby,Arch_Kirby_AbilityCostumeRuntimeStruct,-1
  .hword Arch_Kirby,Arch_Kirby_AbilityRuntimeStruct,-1
  .hword Arch_Kirby,Arch_Kirby_FtCmdRuntime,-1
  .hword Arch_KirbyFunction,Arch_KirbyFunction_OnAbilityGain,-1
  .hword Arch_KirbyFunction,Arch_KirbyFunction_OnAbilityLose,-1
  .hword Arch_KirbyFunction,Arch_Kirby_SpecialN,-1
  .hword Arch_KirbyFunction,Arch_Kirby_SpecialNAir,-1
  .hword Arch_KirbyFunction,Arch_Kirby_OnHit,-1
  .hword Arch_KirbyFunction,Arch_Kirby_InitItem,-1
  .hword Arch_KirbyFunction,Arch_Kirby_MoveLogicRuntime,-1
  #Metadata
  .hword Arch_Metadata,Arch_Metadata_FtIntNum,-1
  .hword Arch_Metadata,Arch_Metadata_FtExtNum,-1
  .hword Arch_Metadata,Arch_Metadata_CSSIconCount,-1
  .hword Arch_Metadata,Arch_Metadata_SSSIconCount,-1
  .hword Arch_Metadata,Arch_Metadata_SSMCount,-1
  .hword Arch_Metadata,Arch_Metadata_BGMCount,-1
  .hword Arch_Metadata,Arch_Metadata_EffectCount,-1
  .hword Arch_Metadata,Arch_Metadata_TermMajor,-1
  .hword Arch_Metadata,Arch_Metadata_TermMinor,-1
  .hword Arch_Metadata,Arch_Metadata_GrIntNum,-1
  .hword Arch_Metadata,Arch_Metadata_GrExtNum,-1
  .hword Arch_Metadata,-1
  .hword  -1
  .align 2

FileNotExist:
#OSReport
  bl  ErrorString
  mflr  r3
  branchl r12,0x803456a8
#Assert
  bl  Assert_Name
  mflr  r3
  li  r4,0
  load  r5,0x804d3940
  branchl r12,0x80388220

Exit:
  mr  r3,REG_HeapLo
  restore
  mr  r31,r3
  stw	r31, -0x3FE8 (r13)
  mr	r3, r31
  mr	r4, r29
