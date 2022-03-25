#ifndef IKE_HEADER_FILE_
#define IKE_HEADER_FILE_

#include "../../CustomHeaders/general.h"

///////////////////////
//     Attributes    //
///////////////////////

#define IKE_SPECIALFALLLANDINGLAG 28
#define IKE_SPECIALHI_CONTROL 0.6

//SpecialN

#define IKE_SPECIALN_BASE_DMG 7
#define IKE_SPECIALN_ADDED_DMG 5
#define IKE_SPECIALN_XPRESERVE_RATE 1.25
#define IKE_SPECIALN_FRICTION 0.02
#define IKE_SPECIALN_MAXCHARGE 4

//SpecialS
#define IKE_SPECIALS_SPECIALFALLLANDINGLAG 28
#define IKE_SPECIALS_FRICTION 0.02
#define IKE_SPECIALS_BASEVELOCITY 3.0
#define IKE_SPECIALS_ADDEDVELOCITY 0.5
#define IKE_SPECIALAIRS_ENDVELMULT 0.2
#define IKE_SPECIALS_JUMPVELPRESERVE 0.8
#define IKE_SPECIALAIRS_JUMPVELPRESERVE 1.2

//SpecialHi

//SpecialLw
#define IKE_COUNTER_HITLAG_FRAMES 11.0
#define IKE_COUNTER_AIR_DECELERATION 0.0025
#define IKE_COUNTER_GRAVITY 0.04
#define IKE_COUNTER_GRAVITY_LIMIT 1.2
#define IKE_COUNTER_BONE_NUM 5
#define IKE_COUNTER_X_OFFSET 0.0
#define IKE_COUNTER_Y_OFFSET -0.5
#define IKE_COUNTER_Z_OFFSET 0.0
#define IKE_COUNTER_SIZE 10.0
#define IKE_COUNTER_AIR_XVEL_DECAY 2

///////////////////////
//      m-ex IDs     //
///////////////////////

///////////////////////
//  Special States   //
///////////////////////

// SpecialN
#define STATE_SPECIALNSTART 348
#define STATE_SPECIALNLOOP 349
#define STATE_SPECIALNEND1 350
#define STATE_SPECIALNEND2 351

#define STATE_SPECIALAIRNSTART 352
#define STATE_SPECIALAIRNLOOP 353
#define STATE_SPECIALAIRNEND1 354
#define STATE_SPECIALAIRNEND2 355

// SpecialS
#define STATE_SPECIALSSTART 356
#define STATE_SPECIALSHOLD 357
#define STATE_SPECIALSDASH 358
#define STATE_SPECIALSATTACK 359
#define STATE_SPECIALSEND 360

#define STATE_SPECIALAIRSSTART 361
#define STATE_SPECIALAIRSHOLD 362
#define STATE_SPECIALAIRSDASH 363
#define STATE_SPECIALAIRSATTACK 364
#define STATE_SPECIALAIRSEND 365

// SpecialLw
#define STATE_SPECIALLW 366
#define STATE_SPECIALLWHIT 367

#define STATE_SPECIALAIRLW 368
#define STATE_SPECIALAIRLWHIT 369

// SpecialHi
#define STATE_SPECIALHI1 370
#define STATE_SPECIALHI2 371
#define STATE_SPECIALHI3 372
#define STATE_SPECIALHI4 373
#define STATE_SPECIALAIRHI1 374
#define STATE_SPECIALAIRHI2 375
#define STATE_SPECIALAIRHI4 376

////////////////////////
//   Item Constants   //
////////////////////////

///////////////////////
//       Flags       //
///////////////////////

///////////////////////
//     Constants     //
///////////////////////

///////////////////////
//      Structs      //
///////////////////////

typedef struct FighterVars
{
	int unk[52];
} FighterVars;

typedef struct SpecialSFtCmd
{
	int interruptable;
	int velocity_set;
} SpecialSFtCmd;

typedef struct SpecialS_statevars
{
	int charge;
} SpecialS_statevars;

///////////////////////
//      Statics      //
///////////////////////

///////////////////////
//     Functions     //
///////////////////////

// SpecialS
void SpecialSStart_PhysCb(GOBJ *fighter_gobj);
void SpecialSStart_CollCb(GOBJ *fighter_gobj);
void SpecialSStart_AnimCb(GOBJ *fighter_gobj);
void SpecialSStart_IASACb(GOBJ *fighter_gobj);
void SpecialSStart_EnterAerial(GOBJ *fighter_gobj);

void SpecialSHold_PhysCb(GOBJ *fighter_gobj);
void SpecialSHold_CollCb(GOBJ *fighter_gobj);
void SpecialSHold_AnimCb(GOBJ *fighter_gobj);
void SpecialSHold_IASACb(GOBJ *fighter_gobj);
void SpecialSHold_EnterAerial(GOBJ *fighter_gobj);

void SpecialSDash_PhysCb(GOBJ *fighter_gobj);
void SpecialSDash_CollCb(GOBJ *fighter_gobj);
void SpecialSDash_AnimCb(GOBJ *fighter_gobj);
void SpecialSDash_IASACb(GOBJ *fighter_gobj);
void SpecialSDash_EnterAerial(GOBJ *fighter_gobj);

void SpecialSEnd_PhysCb(GOBJ *fighter_gobj);
void SpecialSEnd_CollCb(GOBJ *fighter_gobj);
void SpecialSEnd_AnimCb(GOBJ *fighter_gobj);
void SpecialSEnd_IASACb(GOBJ *fighter_gobj);
void SpecialSEnd_EnterAerial(GOBJ *fighter_gobj);

// SpecialAirS
void SpecialAirSStart_PhysCb(GOBJ *fighter_gobj);
void SpecialAirSStart_CollCb(GOBJ *fighter_gobj);
void SpecialAirSStart_AnimCb(GOBJ *fighter_gobj);
void SpecialAirSStart_IASACb(GOBJ *fighter_gobj);
void SpecialAirSStart_EnterGrounded(GOBJ *fighter_gobj);

void SpecialAirSHold_PhysCb(GOBJ *fighter_gobj);
void SpecialAirSHold_CollCb(GOBJ *fighter_gobj);
void SpecialAirSHold_AnimCb(GOBJ *fighter_gobj);
void SpecialAirSHold_IASACb(GOBJ *fighter_gobj);
void SpecialAirSHold_EnterGrounded(GOBJ *fighter_gobj);

void SpecialAirSDash_PhysCb(GOBJ *fighter_gobj);
void SpecialAirSDash_CollCb(GOBJ *fighter_gobj);
void SpecialAirSDash_AnimCb(GOBJ *fighter_gobj);
void SpecialAirSDash_IASACb(GOBJ *fighter_gobj);
void SpecialAirSDash_EnterGrounded(GOBJ *fighter_gobj);

void SpecialAirSEnd_PhysCb(GOBJ *fighter_gobj);
void SpecialAirSEnd_CollCb(GOBJ *fighter_gobj);
void SpecialAirSEnd_AnimCb(GOBJ *fighter_gobj);
void SpecialAirSEnd_IASACb(GOBJ *fighter_gobj);
void SpecialAirSEnd_EnterGrounded(GOBJ *fighter_gobj);

// SpecialLw
void SpecialLwOnHit(GOBJ *fighter_gobj);

void SpecialLw_AnimationCallback(GOBJ *fighter_gobj);
void SpecialLw_IASACallback(GOBJ *fighter_gobj);
void SpecialLw_PhysicCallback(GOBJ *fighter_gobj);
void SpecialLw_CollisionCallback(GOBJ *fighter_gobj);

void SpecialLwHit_AnimationCallback(GOBJ *fighter_gobj);
void SpecialLwHit_IASACallback(GOBJ *fighter_gobj);
void SpecialLwHit_PhysicCallback(GOBJ *fighter_gobj);
void SpecialLwHit_CollisionCallback(GOBJ *fighter_gobj);

// SpecialAirLw
void SpecialAirLw_AnimationCallback(GOBJ *fighter_gobj);
void SpecialAirLw_IASACallback(GOBJ *fighter_gobj);
void SpecialAirLw_PhysicCallback(GOBJ *fighter_gobj);
void SpecialAirLw_CollisionCallback(GOBJ *fighter_gobj);

void SpecialAirLwHit_AnimationCallback(GOBJ *fighter_gobj);
void SpecialAirLwHit_IASACallback(GOBJ *fighter_gobj);
void SpecialAirLwHit_PhysicCallback(GOBJ *fighter_gobj);
void SpecialAirLwHit_CollisionCallback(GOBJ *fighter_gobj);

// SpecialN
void SpecialNStart_AnimCb(GOBJ *fighter_gobj);
void SpecialNStart_IASACb(GOBJ *fighter_gobj);
void SpecialNStart_PhysCb(GOBJ *fighter_gobj);
void SpecialNStart_CollCb(GOBJ *fighter_gobj);
void SpecialNStart_EnterAerial(GOBJ *fighter_gobj);

void SpecialNLoop_AnimCb(GOBJ *fighter_gobj);
void SpecialNLoop_IASACb(GOBJ *fighter_gobj);
void SpecialNLoop_PhysCb(GOBJ *fighter_gobj);
void SpecialNLoop_CollCb(GOBJ *fighter_gobj);
void SpecialNLoop_EnterAerial(GOBJ *fighter_gobj);

void SpecialNEnd_AnimCb(GOBJ *fighter_gobj);
void SpecialNEnd_IASACb(GOBJ *fighter_gobj);
void SpecialNEnd_PhysCb(GOBJ *fighter_gobj);
void SpecialNEnd_CollCb(GOBJ *fighter_gobj);
void SpecialNEnd_EnterAerial(GOBJ *fighter_gobj);

void SpecialN_EnterEnd(GOBJ *fighter_gobj);
void SpecialN_OnStateChange(GOBJ *fighter_gobj);

// SpecialAirN
void SpecialAirNStart_AnimCb(GOBJ *fighter_gobj);
void SpecialAirNStart_IASACb(GOBJ *fighter_gobj);
void SpecialAirNStart_PhysCb(GOBJ *fighter_gobj);
void SpecialAirNStart_CollCb(GOBJ *fighter_gobj);
void SpecialAirNStart_EnterGrounded(GOBJ *fighter_gobj);

// SpecialHi
void SpecialHi1_AnimationCallback(GOBJ *fighter_gobj);
void SpecialHi1_IASACallback(GOBJ *fighter_gobj);
void SpecialHi1_PhysicsCallback(GOBJ *fighter_gobj);
void SpecialHi1_CollisionCallback(GOBJ *fighter_gobj);
void SpecialHi1_EnterAerial(GOBJ *fighter_gobj);

void SpecialHi2_AnimationCallback(GOBJ *fighter_gobj);
void SpecialHi2_IASACallback(GOBJ *fighter_gobj);
void SpecialHi2_PhysicsCallback(GOBJ *fighter_gobj);
void SpecialHi2_CollisionCallback(GOBJ *fighter_gobj);
void SpecialHi2_EnterAerial(GOBJ *fighter_gobj);

void SpecialHi3_AnimationCallback(GOBJ *fighter_gobj);
void SpecialHi3_IASACallback(GOBJ *fighter_gobj);
void SpecialHi3_PhysicsCallback(GOBJ *fighter_gobj);
void SpecialHi3_CollisionCallback(GOBJ *fighter_gobj);
void SpecialHi3_EnterGrounded(GOBJ *fighter_gobj);

void SpecialHi4_AnimationCallback(GOBJ *fighter_gobj);
void SpecialHi4_IASACallback(GOBJ *fighter_gobj);
void SpecialHi4_PhysicsCallback(GOBJ *fighter_gobj);
void SpecialHi4_CollisionCallback(GOBJ *fighter_gobj);

// SpecialAirHi
void SpecialAirHi1_AnimationCallback(GOBJ *fighter_gobj);
void SpecialAirHi1_IASACallback(GOBJ *fighter_gobj);
void SpecialAirHi1_PhysicsCallback(GOBJ *fighter_gobj);
void SpecialAirHi1_CollisionCallback(GOBJ *fighter_gobj);
void SpecialAirHi1_EnterGrounded(GOBJ *fighter_gobj);

void SpecialAirHi2_AnimationCallback(GOBJ *fighter_gobj);
void SpecialAirHi2_IASACallback(GOBJ *fighter_gobj);
void SpecialAirHi2_PhysicsCallback(GOBJ *fighter_gobj);
void SpecialAirHi2_CollisionCallback(GOBJ *fighter_gobj);
void SpecialAirHi2_EnterGrounded(GOBJ *fighter_gobj);

void SpecialAirHi4_AnimationCallback(GOBJ *fighter_gobj);
void SpecialAirHi4_IASACallback(GOBJ *fighter_gobj);
void SpecialAirHi4_PhysicsCallback(GOBJ *fighter_gobj);
void SpecialAirHi4_CollisionCallback(GOBJ *fighter_gobj);
void SpecialAirHi4_EnterGrounded(GOBJ *fighter_gobj);

#endif