#include "Ike.h"

__attribute__((used)) static struct FtState move_logic[] = {
    // State: 341 - AttackS4
    {
        62,         // AnimationID
        0x241A09,   // StateFlags
        0xA,        // AttackID
        0x0,        // BitFlags
        0x80114D50, // AnimationCallback
        0x80114E04, // IASACallback
        0x80114E64, // PhysicsCallback
        0x80114E98, // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 342 - AttackHi4
    {
        66,         // AnimationID
        0x240A0A,   // StateFlags
        0xB,        // AttackID
        0x80,       // BitFlags
        0x80115C9C, // AnimationCallback
        0x80115E74, // IASACallback
        0x80115EB8, // PhysicsCallback
        0x80115F14, // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 343 - AttackHi4
    {
        295,        // AnimationID
        0x24080A,   // StateFlags
        0xB,        // AttackID
        0x0,        // BitFlags
        0x80115F88, // AnimationCallback
        0x801160B4, // IASACallback
        0x801160E4, // PhysicsCallback
        0x80116104, // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 344 - AttackHi4
    {
        296,        // AnimationID
        0x24080A,   // StateFlags
        0xB,        // AttackID
        0x0,        // BitFlags
        0x8011620C, // AnimationCallback
        0x801162B0, // IASACallback
        0x801162E0, // PhysicsCallback
        0x80116420, // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 345 - AttackLw4
    {
        67,         // AnimationID
        0x240A0B,   // StateFlags
        0xC,        // AttackID
        0x80,       // BitFlags
        0x80116638, // AnimationCallback
        0x801166D4, // IASACallback
        0x80116718, // PhysicsCallback
        0x8011674C, // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 346 - AttackLw4
    {
        297,        // AnimationID
        0x24080B,   // StateFlags
        0xC,        // AttackID
        0x0,        // BitFlags
        0x80116798, // AnimationCallback
        0x80116828, // IASACallback
        0x80116858, // PhysicsCallback
        0x80116878, // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 347 - AttackLw4
    {
        298,        // AnimationID
        0x24080B,   // StateFlags
        0xC,        // AttackID
        0x0,        // BitFlags
        0x80116958, // AnimationCallback
        0x801169BC, // IASACallback
        0x801169EC, // PhysicsCallback
        0x80116A9C, // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 348 - SpecialNStart
    {
        295,                  // AnimationID
        0x340111,             // StateFlags
        0x12,                 // AttackID
        0x0,                  // BitFlags
        SpecialNStart_AnimCb, // AnimationCallback
        SpecialNStart_IASACb, // IASACallback
        SpecialNStart_PhysCb, // PhysicsCallback
        SpecialNStart_CollCb, // CollisionCallback
        0x800761C8,           // CameraCallback
    },
    // State: 349 - SpecialNLoop
    {
        296,                 // AnimationID
        0x340111,            // StateFlags
        0x12,                // AttackID
        0x0,                 // BitFlags
        SpecialNLoop_AnimCb, // AnimationCallback
        SpecialNLoop_IASACb, // IASACallback
        SpecialNLoop_PhysCb, // PhysicsCallback
        SpecialNLoop_CollCb, // CollisionCallback
        0x800761C8,          // CameraCallback
    },
    // State: 350 - SpecialNEnd1
    {
        298,                // AnimationID
        0x340111,           // StateFlags
        0x12,               // AttackID
        0x0,                // BitFlags
        SpecialNEnd_AnimCb, // AnimationCallback
        SpecialNEnd_IASACb, // IASACallback
        SpecialNEnd_PhysCb, // PhysicsCallback
        SpecialNEnd_CollCb, // CollisionCallback
        0x800761C8,         // CameraCallback
    },
    // State: 351 - SpecialNEnd2
    {
        298,                // AnimationID
        0x340111,           // StateFlags
        0x12,               // AttackID
        0x0,                // BitFlags
        SpecialNEnd_AnimCb, // AnimationCallback
        SpecialNEnd_IASACb, // IASACallback
        SpecialNEnd_PhysCb, // PhysicsCallback
        SpecialNEnd_CollCb, // CollisionCallback
        0x800761C8,         // CameraCallback
    },
    // State: 352 - SpecialAirNStart
    {
        299,                     // AnimationID
        0x340511,                // StateFlags
        0x12,                    // AttackID
        0x0,                     // BitFlags
        SpecialAirNStart_AnimCb, // AnimationCallback
        SpecialAirNStart_IASACb, // IASACallback
        SpecialAirNStart_PhysCb, // PhysicsCallback
        SpecialAirNStart_CollCb, // CollisionCallback
        0x800761C8,              // CameraCallback
    },
    // State: 353 - SpecialAirNLoop
    {
        300,        // AnimationID
        0x340511,   // StateFlags
        0x12,       // AttackID
        0x0,        // BitFlags
        0x0,        // AnimationCallback
        0x0,        // IASACallback
        0x0,        // PhysicsCallback
        0x0,        // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 354 - SpecialAirNEnd1
    {
        301,        // AnimationID
        0x340511,   // StateFlags
        0x12,       // AttackID
        0x0,        // BitFlags
        0x0,        // AnimationCallback
        0x0,        // IASACallback
        0x0,        // PhysicsCallback
        0x0,        // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 355 - SpecialAirNEnd2
    {
        302,        // AnimationID
        0x340511,   // StateFlags
        0x12,       // AttackID
        0x0,        // BitFlags
        0x0,        // AnimationCallback
        0x0,        // IASACallback
        0x0,        // PhysicsCallback
        0x0,        // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 356 - SpecialSStart
    {
        303,                  // AnimationID
        0x0,                  // StateFlags
        0x13,                 // AttackID
        0x0,                  // BitFlags
        SpecialSStart_AnimCb, // AnimationCallback
        SpecialSStart_IASACb, // IASACallback
        SpecialSStart_PhysCb, // PhysicsCallback
        SpecialSStart_CollCb, // CollisionCallback
        0x800761C8,           // CameraCallback
    },
    // State: 357 - SpecialSHold
    {
        304,                 // AnimationID
        0x0,                 // StateFlags
        0x13,                // AttackID
        0x0,                 // BitFlags
        SpecialSHold_AnimCb, // AnimationCallback
        SpecialSHold_IASACb, // IASACallback
        SpecialSHold_PhysCb, // PhysicsCallback
        SpecialSHold_CollCb, // CollisionCallback
        0x800761C8,          // CameraCallback
    },
    // State: 358 - SpecialSDash
    {
        305,                 // AnimationID
        0x340113,            // StateFlags
        0x14,                // AttackID
        0x0,                 // BitFlags
        SpecialSDash_AnimCb, // AnimationCallback
        SpecialSDash_IASACb, // IASACallback
        SpecialSDash_PhysCb, // PhysicsCallback
        SpecialSDash_CollCb, // CollisionCallback
        0x800761C8,          // CameraCallback
    },
    // State: 359 - SpecialSAttack
    {
        306,        // AnimationID
        0x0,        // StateFlags
        0x14,       // AttackID
        0x0,        // BitFlags
        0x0,        // AnimationCallback
        0x0,        // IASACallback
        0x0,        // PhysicsCallback
        0x0,        // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 360 - SpecialSEnd
    {
        307,                // AnimationID
        0x340113,           // StateFlags
        0x14,               // AttackID
        0x0,                // BitFlags
        SpecialSEnd_AnimCb, // AnimationCallback
        SpecialSEnd_IASACb, // IASACallback
        SpecialSEnd_PhysCb, // PhysicsCallback
        SpecialSEnd_CollCb, // CollisionCallback
        0x800761C8,         // CameraCallback
    },
    // State: 361 - SpecialAirSStart
    {
        308,                     // AnimationID
        0x340113,                // StateFlags
        0x14,                    // AttackID
        0x0,                     // BitFlags
        SpecialAirSStart_AnimCb, // AnimationCallback
        SpecialAirSStart_IASACb, // IASACallback
        SpecialAirSStart_PhysCb, // PhysicsCallback
        SpecialAirSStart_CollCb, // CollisionCallback
        0x800761C8,              // CameraCallback
    },
    // State: 362 - SpecialAirSHold
    {
        309,                    // AnimationID
        0x340513,               // StateFlags
        0x14,                   // AttackID
        0x0,                    // BitFlags
        SpecialAirSHold_AnimCb, // AnimationCallback
        SpecialAirSHold_IASACb, // IASACallback
        SpecialAirSHold_PhysCb, // PhysicsCallback
        SpecialAirSHold_CollCb, // CollisionCallback
        0x800761C8,             // CameraCallback
    },
    // State: 363 - SpecialAirSDash
    {
        310,                    // AnimationID
        0x340513,               // StateFlags
        0x14,                   // AttackID
        0x0,                    // BitFlags
        SpecialAirSDash_AnimCb, // AnimationCallback
        SpecialAirSDash_IASACb, // IASACallback
        SpecialAirSDash_PhysCb, // PhysicsCallback
        SpecialAirSDash_CollCb, // CollisionCallback
        0x800761C8,             // CameraCallback
    },
    // State: 364 - SpecialAirSAttack
    {
        311,        // AnimationID
        0x340513,   // StateFlags
        0x14,       // AttackID
        0x0,        // BitFlags
        0x0,        // AnimationCallback
        0x0,        // IASACallback
        0x0,        // PhysicsCallback
        0x0,        // CollisionCallback
        0x800761C8, // CameraCallback
    },
    // State: 365 - SpecialAirSEnd
    {
        312,                   // AnimationID
        0x340513,              // StateFlags
        0x14,                  // AttackID
        0x0,                   // BitFlags
        SpecialAirSEnd_AnimCb, // AnimationCallback
        SpecialAirSEnd_IASACb, // IASACallback
        SpecialAirSEnd_PhysCb, // PhysicsCallback
        SpecialAirSEnd_CollCb, // CollisionCallback
        0x800761C8,            // CameraCallback
    },
    // State: 366 - SpecialLw
    {
        313,                         // AnimationID
        0x340113,                    // StateFlags
        0x14,                        // AttackID
        0x0,                         // BitFlags
        SpecialLw_AnimationCallback, // AnimationCallback
        SpecialLw_IASACallback,      // IASACallback
        SpecialLw_PhysicCallback,    // PhysicsCallback
        SpecialLw_CollisionCallback, // CollisionCallback
        0x0,                         // CameraCallback
    },
    // State: 367 - SpecialLwHit
    {
        314,                            // AnimationID
        0x340014,                       // StateFlags
        0x15,                           // AttackID
        0x0,                            // BitFlags
        SpecialLwHit_AnimationCallback, // AnimationCallback
        SpecialLwHit_IASACallback,      // IASACallback
        SpecialLwHit_PhysicCallback,    // PhysicsCallback
        SpecialLwHit_CollisionCallback, // CollisionCallback
        0x0,                            // CameraCallback
    },
    // State: 368 - SpecialAirLw
    {
        315,                            // AnimationID
        0x3C0014,                       // StateFlags
        0x15,                           // AttackID
        0x0,                            // BitFlags
        SpecialAirLw_AnimationCallback, // AnimationCallback
        SpecialAirLw_IASACallback,      // IASACallback
        SpecialAirLw_PhysicCallback,    // PhysicsCallback
        SpecialAirLw_CollisionCallback, // CollisionCallback
        0x800761C8,                     // CameraCallback
    },
    // State: 369 - SpecialAirLwHit
    {
        316,                               // AnimationID
        0x340014,                          // StateFlags
        0x15,                              // AttackID
        0x0,                               // BitFlags
        SpecialAirLwHit_AnimationCallback, // AnimationCallback
        SpecialAirLwHit_IASACallback,      // IASACallback
        SpecialAirLwHit_PhysicCallback,    // PhysicsCallback
        SpecialAirLwHit_CollisionCallback, // CollisionCallback
        0x800761C8,                        // CameraCallback
    },
    // State: 370 - SpecialHi1
    {
        317,                          // AnimationID
        0x0,                          // StateFlags
        0x14,                         // AttackID
        0x0,                          // BitFlags
        SpecialHi1_AnimationCallback, // AnimationCallback
        SpecialHi1_IASACallback,      // IASACallback
        SpecialHi1_PhysicsCallback,   // PhysicsCallback
        SpecialHi1_CollisionCallback, // CollisionCallback
        0x800761C8,                   // CameraCallback
    },
    // State: 371 - SpecialHi2
    {
        318,                          // AnimationID
        0x0,                          // StateFlags
        0x14,                         // AttackID
        0x0,                          // BitFlags
        SpecialHi2_AnimationCallback, // AnimationCallback
        SpecialHi2_IASACallback,      // IASACallback
        SpecialHi2_PhysicsCallback,   // PhysicsCallback
        SpecialHi2_CollisionCallback, // CollisionCallback
        0x800761C8,                   // CameraCallback
    },
    // State: 372 - SpecialHi3
    {
        319,                          // AnimationID
        0x0,                          // StateFlags
        0x14,                         // AttackID
        0x0,                          // BitFlags
        SpecialHi3_AnimationCallback, // AnimationCallback
        SpecialHi3_IASACallback,      // IASACallback
        SpecialHi3_PhysicsCallback,   // PhysicsCallback
        SpecialHi3_CollisionCallback, // CollisionCallback
        0x800761C8,                   // CameraCallback
    },
    // State: 373 - SpecialHi4
    {
        320,                          // AnimationID
        0x0,                          // StateFlags
        0x14,                         // AttackID
        0x0,                          // BitFlags
        SpecialHi4_AnimationCallback, // AnimationCallback
        SpecialHi4_IASACallback,      // IASACallback
        SpecialHi4_PhysicsCallback,   // PhysicsCallback
        SpecialHi4_CollisionCallback, // CollisionCallback
        0x800761C8,                   // CameraCallback
    },
    // State: 374 - SpecialAirHi1
    {
        321,                             // AnimationID
        0x0,                             // StateFlags
        0x1,                             // AttackID
        0x0,                             // BitFlags
        SpecialAirHi1_AnimationCallback, // AnimationCallback
        SpecialAirHi1_IASACallback,      // IASACallback
        SpecialAirHi1_PhysicsCallback,   // PhysicsCallback
        SpecialAirHi1_CollisionCallback, // CollisionCallback
        0x800761C8,                      // CameraCallback
    },
    // State: 375 - SpecialAirHi2
    {
        322,                             // AnimationID
        0x0,                             // StateFlags
        0x14,                            // AttackID
        0x0,                             // BitFlags
        SpecialAirHi2_AnimationCallback, // AnimationCallback
        SpecialAirHi2_IASACallback,      // IASACallback
        SpecialAirHi2_PhysicsCallback,   // PhysicsCallback
        SpecialAirHi2_CollisionCallback, // CollisionCallback
        0x800761C8,                      // CameraCallback
    },
    // State: 376 - SpecialAirHi4
    {
        323,                             // AnimationID
        0x0,                             // StateFlags
        0x14,                            // AttackID
        0x0,                             // BitFlags
        SpecialAirHi4_AnimationCallback, // AnimationCallback
        SpecialAirHi4_IASACallback,      // IASACallback
        SpecialAirHi4_PhysicsCallback,   // PhysicsCallback
        SpecialAirHi4_CollisionCallback, // CollisionCallback
        0x800761C8,                      // CameraCallback
    },
};

void OnLoad(GOBJ *fighter_gobj)
{

    FighterData *fighter_data = fighter_gobj->userdata;
    FighterVars *fighter_vars = &fighter_data->fighter_var;

    void (*cb_OnLoad)(GOBJ * gobj) = (void *)0x801100EC; // Vanilla Shiek OnLoad callback, to be replaced later
    cb_OnLoad(fighter_gobj);

    // Set up face parts visibility
    // Show defualt face face Array 2
    // 0 means on -1 means off
    Fighter_VisTableSet(fighter_gobj, 2, 0);

    // Talk Face Array3
    Fighter_VisTableSet(fighter_gobj, 3, -1);

    // HalfBlink array 4
    Fighter_VisTableSet(fighter_gobj, 4, -1);

    // hide full blink array5
    Fighter_VisTableSet(fighter_gobj, 5, -1);
    // Angry face array6
    Fighter_VisTableSet(fighter_gobj, 6, -1);
    return;
}
