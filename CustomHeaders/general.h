#ifndef GENERAL_H
#define GENERAL_H

#include <stdbool.h>
#include "../m-ex/MexTK/mex.h"
#include "./structs.h"

//Statics
#define CRAWL_STICKTHRESHOLD_MIN 0.1
#define CRAWL_STICKTHRESHOLD_MAX 0.6

typedef struct ShieldDef
{
    int bone_index;
    Vec3 shield_offset;
    float collision_size;
} ShieldDef;

//MAP FUNCTIONS
void (*ChangeModelState)(GOBJ *fighter_gobj, int lookupTableIndex, int DOBJflag) = (void *)0x80074b0c;
float (*exp)(float x) = (void *)0x8000ce50;
float (*log)(float x) = (void *)0x803265a8;
int (*IASA_Decide_Aerials)(FighterData *fighter_data) = (void *)0x8008ce68; //Should this be a GOBJ parameter instead?
void (*Interrupt_Jump_Grounded)(GOBJ *fighter_gobj) = (void *)0x800caed0;
void (*Interrupt_Walljump)(GOBJ *fighter_gobj) = (void *)0x8008169c;
void (*Fighter_Freeze)(GOBJ *fighter_gobj, float frames) = (void *)0x80086a4c;
int (*Fighter_IASACheck_Airdodge)(GOBJ *fighter_gobj) = (void *)0x80099a58;
int (*Fighter_IASACheck_AerialAttack)(GOBJ *fighter_gobj) = (void *)0x8008cd68;
void (*AObj_SetCurrentFrame)(AOBJ *aobj, float frame) = (void *)0x8036533c;
void (*Item_InvertVelocityAndFacingDirection)(GOBJ *item_gobj) = (void *)0x80273030;
void (*PSMTXInverse)(Mtx *a, Mtx *dest) = (void *)0x80342320;
void (*HSD_MtxSRTQuat)(Mtx *mtx, Vec3 *scale, Vec4 *rot, Vec3 *trans, int unk) = (void *)0x8037a43c;
//void (*AObj_LoadDesc)(int unk) = (void *) 0x8036439c;
void (*PSMTXScale)(Vec3 *scale, Mtx *a, Mtx *dest) = (void *)0x80342668;
//void (*CheckIfMatchIsOver)(int unk) = (void *) 0x801c1d84;
void (*Effect_CreateCopyPosRot)(int gfxid, GOBJ *gobj, JOBJ *jobj) = (void *)0x8005c5c4;
void (*Interrupt_AS_AerialJumpGoTo)(GOBJ *fighter_gobj) = (void *)0x800cb870;
void (*Fighter_HitlagEnd)(GOBJ *fighter_gobj) = (void *)0x8006d10c;
void (*Fighter_SpawnPlayerMidMatch)(int slot, PlayerData *character_struct) = (void *)0x8016eddc;
int (*Fighter_CheckForDeath)(GOBJ *fighter) = (void *)0x800d3158;
void (*Match_DisplayEndingGFX)(int unk) = (void *)0x802f7034;
LiveLOBJ (*HSD_LOBJGetActiveByIndex)(int unk) = (void *)0x80365458;
void (*LOBJ_Update)(LiveLOBJ *lobj) = (void *)0x80365488;
int (*Hitbox_CheckForHitboxCollisionWithHurtbox)(ftHit hitbox, ItHurt hurtbox) = (void *)0x8000805c;
//void (*Inputs_GetPlayerInstantInputs)(int unk) = (void *) 0x801a36a0;
int (*Fighter_Interrupt_AllAerial)(GOBJ *fighter_gobj) = (void *)0x800CCAAC;
int (*Fighter_Interrupt_AllGrounded)(GOBJ *fighter_gobj) = (void *)0x8008A4D4;
void (*CreateShieldBubble)(GOBJ *fighter_gobj, ShieldDef *shield_def, void *onHit) = (void *)0x8007b1b8;
int (*DataOffset_InternalCharacterIDLoad)(GOBJ *fighter_gobj) = (void *)0x800872a4;
void (*Hitbox_EnableShieldFollowBit)(GOBJ *fighter_gobj) = (void *)0x8007aee0;
int (*Items_GetItemID)(GOBJ *item_gobj) = (void *)0x8026b300;

#include "./common.c"

#endif