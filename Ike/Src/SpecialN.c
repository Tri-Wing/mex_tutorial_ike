#include "./Ike.h"

/*
HOOKS
*/

void SpecialN(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    fighterdata->cb.OnStateChange = SpecialN_OnStateChange;
    fighterdata->phys.self_vel_ground.X /= IKE_SPECIALN_XPRESERVE_RATE;
    ActionStateChange(0.0, 1.0, 0.0, fighter_gobj, STATE_SPECIALNSTART, 0x155, 0);
    Fighter_AdvanceScript(fighter_gobj);
    return;
}

//Aerial version unfinished
void SpecialAirN(GOBJ *fighter_gobj)
{
    // FighterData *fighterdata = fighter_gobj->userdata;

    // fighterdata->cb.OnStateChange = SpecialN_OnStateChange;

    // fighterdata->phys.self_vel.X /= IKE_SPECIALN_XPRESERVE_RATE;

    // if (fighterdata->phys.self_vel.Y <= 0.0f)
    // {
    //     fighterdata->phys.self_vel.Y = 0.0f;
    // }

    // ActionStateChange(0.0, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRNSTART, 0x155, 0);
    // Fighter_AdvanceScript(fighter_gobj);

    return;
}

/*
SPECIALNSTART
*/

void SpecialNStart_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        HSD_Archive *playerFile = File_GetPreloadedFile("PlBf.dat");
        void *colanimdata = Archive_GetPublicAddress(playerFile, "FighterColorAnims");

        ActionStateChange(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALNLOOP, 0x1200, 0);
        ColAnim_Apply(&fighterdata->color[1], colanimdata, 0, 0);
    }
}

void SpecialNStart_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialNStart_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    Fighter_PhysGround_ApplyCustomFriction(fighterdata, IKE_SPECIALN_FRICTION);
    Fighter_PhysGround_ApplyVelocity(fighter_gobj);

    return;
}

void SpecialNStart_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialNStart_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialNStart_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    Fighter_SetAirborne(fighterdata);
    ActionStateChange(fighterdata->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRNSTART, 0x0C4C5084, 0);
    return;
}

/*
SPECIALNLOOP
*/

void SpecialNLoop_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    if (fighterdata->state_var.state_var1 % 30 == 0)
    {
        Vec3 hip_pos;
        int Ike_HipN_index = Fighter_BoneLookup(fighterdata, HipN);
        JOBJ_GetWorldPosition(fighterdata->bones[Ike_HipN_index].joint, 0, &hip_pos);
        Wind_FighterCreate(&hip_pos, 10, 0.5f, 0.05f, 1.0471975803375244f);
    }

    fighterdata->state_var.state_var1++;
    if (fighterdata->state_var.state_var1 > IKE_SPECIALN_MAXCHARGE * 30)
    {
        fighterdata->ftcmd_var.flag0 = 1;
        SpecialN_EnterEnd(fighter_gobj);
    }
    return;
}

void SpecialNLoop_IASACb(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    if ((fighterdata->input.held & HSD_BUTTON_B) == 0)
    {
        fighterdata->ftcmd_var.flag0 = 0;
        SpecialN_EnterEnd(fighter_gobj);
    }
    return;
}

void SpecialNLoop_PhysCb(GOBJ *fighter_gobj)
{
    Fighter_PhysGround_ApplyFriction(fighter_gobj);
}

void SpecialNLoop_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialNLoop_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialNLoop_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    Fighter_SetAirborne(fighterdata);
    ActionStateChange(fighterdata->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRNLOOP, 0x0C4C5084, 0);
    return;
}

/*
SPECIALNEND
*/

void SpecialNEnd_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    if (fighterdata->ftcmd_var.flag0 == 0)
    {
        int idx = 0;
        while (idx < 4)
        {
            if (fighterdata->hitbox[idx].active == 1)
            {
                int damage = IKE_SPECIALN_BASE_DMG + fighterdata->state_var.state_var1 / 30 * IKE_SPECIALN_ADDED_DMG;
                Fighter_UpdateHitboxDamage(&fighterdata->hitbox[idx], damage, fighter_gobj);
            }
            idx++;
        }
    }
    if (fighterdata->state.frame == 9.0f)
    {
        Vec3 hip_pos;
        int Ike_HipN_index = Fighter_BoneLookup(fighterdata, HipN);
        JOBJ_GetWorldPosition(fighterdata->bones[Ike_HipN_index].joint, 0, &hip_pos);
        Wind_FighterCreate(&hip_pos, 120, 0.9f, 0.02f, 1.0471975803375244f);
    }
    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        Fighter_EnterWait(fighter_gobj);
    }
    return;
}

void SpecialNEnd_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialNEnd_PhysCb(GOBJ *fighter_gobj)
{
    Fighter_PhysGround_ApplyFriction(fighter_gobj);
    return;
}

void SpecialNEnd_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
    {
        SpecialNEnd_EnterAerial(fighter_gobj);
    }
    return;
}

void SpecialNEnd_EnterAerial(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    int state_id;
    if (fighterdata->ftcmd_var.flag0 == 0)
    {
        state_id = STATE_SPECIALAIRNEND1;
    }
    else
    {
        state_id = STATE_SPECIALAIRNEND2;
    }

    Fighter_SetAirborne(fighterdata);
    ActionStateChange(fighterdata->state.frame, 1.0f, 0.0f, fighter_gobj, state_id, 0x0C4C508E, 0);

    if (fighterdata->flags.persistent_gfx == 1)
    {
        fighterdata->cb.EnterHitlag = Effect_PauseAll;
        fighterdata->cb.ExitHitlag = Effect_ResumeAll;
    }
    return;
}

/*
SPECIALAIRNSTART
*/

void SpecialAirNStart_AnimCb(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    if (FrameTimerCheck(fighter_gobj) == 0)
    {
        ActionStateChange(0.0f, 1.0f, 0.0f, fighter_gobj, STATE_SPECIALAIRNLOOP, 0x1200, 0);
        Fighter_ApplyColAnim(fighterdata, 0x63, 0);
    }
}

void SpecialAirNStart_IASACb(GOBJ *fighter_gobj)
{
    return;
}

void SpecialAirNStart_PhysCb(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    Fighter_Phys_ApplyVerticalAirFriction(fighterdata);
    Fighter_PhysAir_DecayXVelocity(fighterdata, IKE_SPECIALN_FRICTION);

    return;
}

void SpecialAirNStart_CollCb(GOBJ *fighter_gobj)
{
    if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) != 0)
    {
        SpecialAirNStart_EnterGrounded(fighter_gobj);
    }
    return;
}

void SpecialAirNStart_EnterGrounded(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;

    Fighter_SetGrounded2(fighterdata);
    ActionStateChange(fighterdata->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALNSTART, 0x0C4C5084, 0);
    return;
}

/*
MISC.
*/

void SpecialN_EnterEnd(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;
    int state_id;
    if (fighterdata->ftcmd_var.flag0 == 0)
    {
        state_id = STATE_SPECIALNEND1;
    }
    else
    {
        state_id = STATE_SPECIALNEND2;
    }

    ActionStateChange(1.0f, 1.0f, 0.0f, fighter_gobj, state_id, 0, 0);

    //Spawn GFX here
    //ft->x21BC_callback_Accessory4 = &lbl_801365A8;
}

void SpecialN_OnStateChange(GOBJ *fighter_gobj)
{
    FighterData *fighterdata = fighter_gobj->userdata;
    fighterdata->ftcmd_var.flag0 = 0;
    fighterdata->state_var.state_var1 = 0;
    return;
}