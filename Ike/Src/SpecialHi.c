#include "./Ike.h"

/*
HOOKS
*/

void SpecialHi(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALHI1, 0, 0);
    Fighter_AdvanceScript(fighter_gobj);

    return;
}

void SpecialAirHi(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALAIRHI1, 0, 0);
    Fighter_AdvanceScript(fighter_gobj);

    fighter_data->phys.self_vel.Y = 0.0;

    return;
}

/*
SPECIALHI1
*/

void SpecialHi1_AnimationCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALHI2, 0, 0);
    }
}

void SpecialHi1_IASACallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialHi1_PhysicsCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysGround_ApplyFriction(fighter_gobj);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);
}

void SpecialHi1_CollisionCallback(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialHi1_EnterAerial(fighter_gobj);
    }
}

void SpecialHi1_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRHI1, 0x0C4C5084, 0);
    return;
}

/*
SPECIALHI2
*/

void SpecialHi2_AnimationCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALHI3, 0, 0);
    }
}

void SpecialHi2_IASACallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialHi2_PhysicsCallback(GOBJ *fighter_gobj)
{
    Fighter_Phys_UseAnimPos(fighter_gobj);
}

void SpecialHi2_CollisionCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (fighter_data->ftcmd_var.flag1 == 0)
    {
        if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
        {
            SpecialHi2_EnterAerial(fighter_gobj);
        }
    }
    else
    {
        Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj);
    }
}

void SpecialHi2_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRHI2, 0x0C4C5084, 0);
    return;
}

/*
SPECIALHI3
*/

void SpecialHi3_AnimationCallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialHi3_IASACallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialHi3_PhysicsCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    fighter_data->phys.self_vel.Y = -4.0;
    Fighter_PhysAir_DecayXVelocity(fighter_data, fighter_data->attr.aerial_friction);
    Fighter_PhysAir_ApplyAerialDrift(fighter_data);
}

void SpecialHi3_CollisionCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_CollAir_GrabFacingLedgeWalljump(fighter_gobj, 0, SpecialHi3_EnterGrounded);
}

void SpecialHi3_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALHI4, 0x0C4C5084, 0);
    return;
}

/*
SPECIALHI4
*/

void SpecialHi4_AnimationCallback(GOBJ *fighter_gobj)
{
    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        Fighter_EnterWait(fighter_gobj);
    }
}

void SpecialHi4_IASACallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialHi4_PhysicsCallback(GOBJ *fighter_gobj)
{
    Fighter_PhysGround_ApplyFriction(fighter_gobj);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);
}

void SpecialHi4_CollisionCallback(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        Fighter_EnterFall(fighter_gobj);
    }
}

/*
SPECIALAIRHI1
*/

void SpecialAirHi1_AnimationCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALAIRHI2, 0, 0);
    }
}

void SpecialAirHi1_IASACallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialAirHi1_PhysicsCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysAir_DecayXVelocity(fighter_data, fighter_data->attr.aerial_friction);

    return;
}

void SpecialAirHi1_CollisionCallback(GOBJ *fighter_gobj)
{
    Fighter_CollAir_GrabFacingLedgeWalljump(fighter_gobj, 0, SpecialAirHi1_EnterGrounded);
}

void SpecialAirHi1_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALHI1, 0x0C4C5084, 0);
    return;
}

/*
SPECIALAIRHI2
*/

void SpecialAirHi2_AnimationCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALHI3, 0, 0);
    }
}

void SpecialAirHi2_IASACallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialAirHi2_PhysicsCallback(GOBJ *fighter_gobj)
{
    Fighter_Phys_UseAnimPos(fighter_gobj);
}

void SpecialAirHi2_CollisionCallback(GOBJ *fighter_gobj)
{
    if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) == 1)
    {
        SpecialAirHi2_EnterGrounded(fighter_gobj);
    }
}

void SpecialAirHi2_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);

    int flag = fighter_data->ftcmd_var.flag1;
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALHI2, 0x0C4C5084, 0);
    fighter_data->ftcmd_var.flag1 = flag;

    return;
}

/*
SPECIALAIRHI4
*/

void SpecialAirHi4_AnimationCallback(GOBJ *fighter_gobj)
{
    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        Fighter_EnterFall(fighter_gobj);
    }
}

void SpecialAirHi4_IASACallback(GOBJ *fighter_gobj)
{
    return;
}

void SpecialAirHi4_PhysicsCallback(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysAir_ApplyGravity(fighter_data, fighter_data->attr.gravity, fighter_data->attr.terminal_velocity);
}

void SpecialAirHi4_CollisionCallback(GOBJ *fighter_gobj)
{
    Fighter_CollAir_GrabFacingLedgeWalljump(fighter_gobj, 0, SpecialAirHi4_EnterGrounded);
}

void SpecialAirHi4_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);

    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALHI4, 0x0C4C5084, 0);

    return;
}