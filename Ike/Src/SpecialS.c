#include "./Ike.h"

/*
HOOKS
*/

void SpecialS(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    ActionStateChange(0.0, 1.0, 0.0, fighter_gobj, STATE_SPECIALSSTART, 0x155, 0);
    Fighter_AdvanceScript(fighter_gobj);

    script_flags->interruptable = 0;
    script_flags->velocity_set = 0;
    state_vars->charge = 0;

    return;
}

void SpecialAirS(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    ActionStateChange(0.0, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRSSTART, 0x155, 0);
    Fighter_AdvanceScript(fighter_gobj);

    script_flags->interruptable = 0;
    script_flags->velocity_set = 0;
    state_vars->charge = 0;

    return;
}

/*
SPECIALSSTART
*/

void SpecialSStart_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALSHOLD, 0x1200, 0);
        state_vars->charge = 0;
    }
    return;
}

void SpecialSStart_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialSStart_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysGround_ApplyCustomFriction(fighter_data, IKE_SPECIALS_FRICTION);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);

    return;
}

void SpecialSStart_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialSStart_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialSStart_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRSSTART, 0x0C4C5084, 0);
    return;
}

/*
SPECIALSHOLD
*/

void SpecialSHold_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    if (state_vars->charge < 59)
    {
        state_vars->charge += 1;
    }
    else if (state_vars->charge == 59)
    {
        state_vars->charge += 1;
        Fighter_PlaySFX(fighter_gobj, 5097, 200, 75);
    }

    if (!(fighter_data->input.held & HSD_BUTTON_B))
    {
        ActionStateChangePreserveStateVars(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALSDASH, 0x1200, 0);
    }

    return;
}

void SpecialSHold_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialSHold_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysGround_ApplyCustomFriction(fighter_data, IKE_SPECIALS_FRICTION);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);

    return;
}

void SpecialSHold_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialSHold_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialSHold_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRSHOLD, 0x0C4C5084, 0);
    return;
}

/*
SPECIALSDASH
*/

void SpecialSDash_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALSEND, 0x1200, 0);
    }

    return;
}

void SpecialSDash_IASACb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (Fighter_IASACheck_JumpF(fighter_gobj))
    {
        float vel = fighter_data->phys.self_vel.X;
        Interrupt_Jump_Grounded(fighter_gobj);
        fighter_data->phys.self_vel_ground.X = vel * IKE_SPECIALS_JUMPVELPRESERVE;
    }
    return;
}

void SpecialSDash_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    fighter_data->phys.self_vel.X = fighter_data->facing_direction * (IKE_SPECIALS_BASEVELOCITY + IKE_SPECIALS_ADDEDVELOCITY * (state_vars->charge / 10));

    return;
}

void SpecialSDash_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialSDash_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialSDash_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChangePreserveStateVars(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRSDASH, 0x0C4C5084, 0);
    return;
}

/*
SPECIALSATTACK
*/

void SpecialSAttack_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        Fighter_EnterWait(fighter_gobj);
    }

    return;
}

void SpecialSAttack_IASACb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;

    if (script_flags->interruptable != 0)
    {
        Fighter_Interrupt_AllGrounded(fighter_gobj);
    }
    return;
}

void SpecialSAttack_PhysCb(GOBJ *fighter_gobj)
{
    Fighter_PhysGround_ApplyFriction(fighter_gobj);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);

    return;
}

void SpecialSAttack_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialSAttack_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialSAttack_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChangePreserveStateVars(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRSATTACK, ASC_PRESERVE_HITBOX, 0);
    return;
}

/*
SPECIALSEND
*/

void SpecialSEnd_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        Fighter_EnterWait(fighter_gobj);
    }

    return;
}

void SpecialSEnd_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialSEnd_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysGround_ApplyFriction(fighter_gobj);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);

    return;
}

void SpecialSEnd_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialSEnd_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialSEnd_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChangePreserveStateVars(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRSEND, 0x0C4C5084, 0);
    return;
}

/*
SPECIALAIRSSTART
*/

void SpecialAirSStart_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALAIRSHOLD, 0x1200, 0);
        state_vars->charge = 0;
    }
    return;
}

void SpecialAirSStart_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialAirSStart_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysAir_ApplyGravity(fighter_data, fighter_data->attr.gravity, fighter_data->attr.terminal_velocity);
    Fighter_PhysAir_DecayXVelocity(fighter_data, fighter_data->attr.aerial_friction);
    Fighter_PhysAir_ApplyAerialDrift(fighter_data);

    return;
}

void SpecialAirSStart_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) == 1)
    {
        SpecialAirSStart_EnterGrounded(fighter_gobj);
    }
    return;
}

void SpecialAirSStart_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALSSTART, 0x0C4C5084, 0);

    return;
}

/*
SPECIALAIRSHOLD
*/

void SpecialAirSHold_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    if (state_vars->charge < 59)
    {
        state_vars->charge += 1;
    }
    else if (state_vars->charge == 59)
    {
        state_vars->charge += 1;
        Fighter_PlaySFX(fighter_gobj, 5097, 200, 75);
    }

    if (!(fighter_data->input.held & HSD_BUTTON_B))
    {
        ActionStateChangePreserveStateVars(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALAIRSDASH, 0x1200, 0);
    }

    return;
}

void SpecialAirSHold_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialAirSHold_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_PhysAir_ApplyGravity(fighter_data, fighter_data->attr.gravity, fighter_data->attr.terminal_velocity);
    Fighter_PhysAir_DecayXVelocity(fighter_data, fighter_data->attr.aerial_friction);
    Fighter_PhysAir_ApplyAerialDrift(fighter_data);

    return;
}

void SpecialAirSHold_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) == 1)
    {
        SpecialAirSHold_EnterGrounded(fighter_gobj);
    }
    return;
}

void SpecialAirSHold_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);
    ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALSHOLD, 0x0C4C5084, 0);

    return;
}

/*
SPECIALAIRSDASH
*/

void SpecialAirSDash_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALAIRSEND, 0x1200, 0);
    }

    return;
}

void SpecialAirSDash_IASACb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (fighter_data->input.down & (HSD_BUTTON_B | HSD_BUTTON_A))
    {
        ActionStateChange(0.0, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRSATTACK, ASC_PRESERVE_VELOCITY, 0);
    }
    else if (Fighter_IASACheck_JumpAerial(fighter_gobj))
    {
        float vel = fighter_data->phys.self_vel.X;
        Interrupt_AS_AerialJumpGoTo(fighter_gobj);
        fighter_data->phys.self_vel.X = vel * IKE_SPECIALAIRS_JUMPVELPRESERVE;
    }
    else if (Fighter_IASACheck_WallJump(fighter_gobj))
    {
        Interrupt_Walljump(fighter_gobj);
    }
    return;
}

void SpecialAirSDash_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialS_statevars *state_vars = &fighter_data->state_var;

    fighter_data->phys.self_vel.Y = 0;
    fighter_data->phys.self_vel.X = fighter_data->facing_direction * (IKE_SPECIALS_BASEVELOCITY + IKE_SPECIALS_ADDEDVELOCITY * (state_vars->charge / 10));

    return;
}

void SpecialAirSDash_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) == 1)
    {
        SpecialAirSDash_EnterGrounded(fighter_gobj);
    }
    return;
}

void SpecialAirSDash_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetAirborne(fighter_data);
    ActionStateChangePreserveStateVars(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALSDASH, 0x0C4C5084, 0);
    return;
}

/*
SPECIALAIRSATTACK
*/

void SpecialAirSAttack_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        Fighter_EnterWait(fighter_gobj);
    }

    return;
}

void SpecialAirSAttack_IASACb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;

    if (script_flags->interruptable != 0)
    {
        Fighter_Interrupt_AllGrounded(fighter_gobj);
    }
    return;
}

void SpecialAirSAttack_PhysCb(GOBJ *fighter_gobj)
{
    Fighter_PhysGround_ApplyFriction(fighter_gobj);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);

    return;
}

void SpecialAirSAttack_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) == 1)
    {
        SpecialAirSAttack_EnterGrounded(fighter_gobj);
    }
    return;
}

void SpecialAirSAttack_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);
    ActionStateChangePreserveStateVars(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALSATTACK, ASC_PRESERVE_HITBOX, 0);
    return;
}

/*
SPECIALAIRSEND
*/

void SpecialAirSEnd_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        Fighter_EnterSpecialFall(fighter_gobj, 1, 1, 0, fighter_data->attr.aerial_drift_base, IKE_SPECIALS_SPECIALFALLLANDINGLAG);
    }

    return;
}

void SpecialAirSEnd_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialAirSEnd_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;
    SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;

    //Multiply velocity on the first frame only
    if (script_flags->velocity_set == 0)
    {
        script_flags->velocity_set = 1;
        fighter_data->phys.self_vel.X *= IKE_SPECIALAIRS_ENDVELMULT;
    }

    Fighter_PhysAir_ApplyGravity(fighter_data, fighter_data->attr.gravity, fighter_data->attr.terminal_velocity);
    Fighter_PhysAir_DecayXVelocity(fighter_data, fighter_data->attr.aerial_friction);
    Fighter_PhysAir_ApplyAerialDrift(fighter_data);

    return;
}

void SpecialAirSEnd_CollCb(GOBJ *fighter_gobj)
{
    Fighter_CollAir_GrabFacingLedgeWalljump(fighter_gobj, 0, SpecialAirSEnd_EnterGrounded);
    return;
}

void SpecialAirSEnd_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighter_data = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighter_data);
    ActionStateChangePreserveStateVars(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALSEND, 0x0C4C5084, 0);
    return;
}
