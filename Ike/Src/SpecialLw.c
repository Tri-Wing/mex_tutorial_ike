#include "Ike.h"

//
void SpecialLw(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	//set velocity
	fighter_data->phys.self_vel.X = 0.0;

	//enter state
	ActionStateChange(0.0, 1.0, 0.0, fighter_gobj, STATE_SPECIALLW, 0x0, 0);
	Fighter_AdvanceScript(fighter_gobj);

	//clear flags
	fighter_data->ftcmd_var.flag1 = 0;
	fighter_data->state_var.state_var1 = 0;
	return;
}

//
void SpecialAirLw(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	//set velocity
	fighter_data->phys.self_vel.X = fighter_data->phys.self_vel.X / IKE_COUNTER_AIR_XVEL_DECAY;
	fighter_data->phys.self_vel.Y = 0.0;

	//enter state
	ActionStateChange(0.0, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRLW, 0x0, 0);
	Fighter_AdvanceScript(fighter_gobj);

	//clear flags
	fighter_data->ftcmd_var.flag1 = 0;
	fighter_data->state_var.state_var1 = 0;
	return;
}

//
void SpecialLwOnHit(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	//set Ike facing direction he was hit from
	fighter_data->facing_direction = fighter_data->shield.hit_direction;

	//lookup hip bone for Ike, spawn wind effect at bone location
	s8 Ike_HipN = Fighter_BoneLookup(fighter_data, HipN);
	Vec3 bone_pos;
	JOBJ_GetWorldPosition(fighter_data->bones[Ike_HipN].joint, 0, &bone_pos);
	Wind_FighterCreate(&bone_pos, 0x78, 0.9, 0.02, 1.0471976);

	//check for grounded / aerial
	if (fighter_data->phys.air_state == 0)
	{
		ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALLWHIT, 0x0, 0);
	}
	else
	{
		ActionStateChange(0, 1, 0, fighter_gobj, STATE_SPECIALAIRLWHIT, 0x0, 0);
	}

	//spawning GFX
	if (fighter_data->flags.immune > -1)
	{
		int fingerBone = Fighter_BoneLookup(fighter_data, L1stNa);
		Effect_SpawnSync(0x510, fighter_gobj, fighter_data->bones[fingerBone].joint, fighter_data->facing_direction);
	}

	//set immune flag
	fighter_data->flags.immune = fighter_data->flags.immune & 0xFF;

	//clear callbacks
	fighter_data->cb.EnterHitlag = 0x0;
	fighter_data->cb.ExitHitlag = 0x0;
	fighter_data->cb.Accessory4 = 0x0;
	return;
}

//
void SpecialLw_AnimationCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;
	void *special_attributes = fighter_data->special_attributes;

	//check subaction flag
	if (fighter_data->ftcmd_var.flag1 == 1)
	{
		fighter_data->ftcmd_var.flag1 = 2;

		//create shield bubble
		Vec3 shield_pos = {IKE_COUNTER_X_OFFSET, IKE_COUNTER_Y_OFFSET, IKE_COUNTER_Z_OFFSET};
		ShieldDef SpecialLw_ShieldDef = {IKE_COUNTER_BONE_NUM, shield_pos, IKE_COUNTER_SIZE};
		CreateShieldBubble(fighter_gobj, &SpecialLw_ShieldDef, SpecialLwOnHit);
		fighter_data->flags.shield_enable = 1;

		//set hitlag frames for when shield is hit
		fighter_data->shield.x19b4 = IKE_COUNTER_HITLAG_FRAMES;
		fighter_data->shield.x19b8 = IKE_COUNTER_HITLAG_FRAMES;
	}
	else if (fighter_data->ftcmd_var.flag1 == 0)
	{
		fighter_data->flags.shield_enable = 0;
	}

	if (FrameTimerCheck(fighter_gobj) == 0)
	{
		Fighter_EnterWait(fighter_gobj);
	}
}

//
void SpecialLw_IASACallback(GOBJ *fighter_gobj)
{
	return;
}

//
void SpecialLw_PhysicCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;
	Fighter_PhysGround_ApplyFriction(fighter_gobj);
	Hitbox_EnableShieldFollowBit(fighter_gobj);
	return;
}

//
void SpecialLw_EnterAerial(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	//enter aerial state
	Fighter_SetAirborne(fighter_data);
	ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRLW, 0xc4c508c, 0);

	//if necessary, create shield again
	if (fighter_data->ftcmd_var.flag1 == 2)
	{
		Vec3 shield_pos = {IKE_COUNTER_X_OFFSET, IKE_COUNTER_Y_OFFSET, IKE_COUNTER_Z_OFFSET};
		ShieldDef SpecialLw_ShieldDef = {IKE_COUNTER_BONE_NUM, shield_pos, IKE_COUNTER_SIZE};

		CreateShieldBubble(fighter_gobj, &SpecialLw_ShieldDef, SpecialLwOnHit);
		fighter_data->flags.shield_enable = 1;
	}
	return;
}

//
void SpecialLw_CollisionCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	//check for ground collision
	if (Fighter_CollGround_StopLedge(fighter_gobj) == 0)
	{
		SpecialLw_EnterAerial(fighter_gobj);
	}
	return;
}

//
void SpecialAirLw_AnimationCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;
	void *special_attributes = fighter_data->special_attributes;

	//check subaction flag
	if (fighter_data->ftcmd_var.flag1 == 1)
	{
		fighter_data->ftcmd_var.flag1 = 2;

		//create shield bubble
		Vec3 shield_pos = {IKE_COUNTER_X_OFFSET, IKE_COUNTER_Y_OFFSET, IKE_COUNTER_Z_OFFSET};
		ShieldDef SpecialLw_ShieldDef = {IKE_COUNTER_BONE_NUM, shield_pos, IKE_COUNTER_SIZE};
		CreateShieldBubble(fighter_gobj, &SpecialLw_ShieldDef, SpecialLwOnHit);
		fighter_data->flags.shield_enable = 1;

		//set hitlag frames for when shield is hit
		fighter_data->shield.x19b4 = IKE_COUNTER_HITLAG_FRAMES;
		fighter_data->shield.x19b8 = IKE_COUNTER_HITLAG_FRAMES;
	}
	else if (fighter_data->ftcmd_var.flag1 == 0)
	{
		fighter_data->flags.shield_enable = 0;
	}

	if (FrameTimerCheck(fighter_gobj) == 0)
	{
		Fighter_EnterFall(fighter_gobj);
	}

	return;
}

//
void SpecialAirLw_IASACallback(GOBJ *fighter_gobj)
{
	return;
}

//
void SpecialAirLw_PhysicCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	Fighter_PhysAir_ApplyGravity(fighter_data, IKE_COUNTER_GRAVITY, IKE_COUNTER_GRAVITY_LIMIT);
	Fighter_PhysAir_DecayXVelocity(fighter_data, IKE_COUNTER_AIR_DECELERATION);
	Hitbox_EnableShieldFollowBit(fighter_gobj);

	return;
}

//
void SpecialAirLw_EnterGrounded(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	//enter grounded state
	Fighter_SetGrounded2(fighter_data);
	ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALLW, 0xc4c508c, 0);

	//if necessary, create shield again
	if (fighter_data->ftcmd_var.flag1 == 2)
	{
		Vec3 shield_pos = {IKE_COUNTER_X_OFFSET, IKE_COUNTER_Y_OFFSET, IKE_COUNTER_Z_OFFSET};
		ShieldDef SpecialLw_ShieldDef = {IKE_COUNTER_BONE_NUM, shield_pos, IKE_COUNTER_SIZE};

		CreateShieldBubble(fighter_gobj, &SpecialLw_ShieldDef, SpecialLwOnHit);
		fighter_data->flags.shield_enable = 1;
	}
	return;
}

//
void SpecialAirLw_CollisionCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) != 0)
	{
		SpecialAirLw_EnterGrounded(fighter_gobj);
	}

	return;
}

//
void SpecialLwHit_AnimationCallback(GOBJ *fighter_gobj)
{
	if (FrameTimerCheck(fighter_gobj) == 0)
	{
		Fighter_EnterWait(fighter_gobj);
	}
	return;
}

//
void SpecialLwHit_IASACallback(GOBJ *fighter_gobj)
{
	return;
}

//
void SpecialLwHit_PhysicCallback(GOBJ *fighter_gobj)
{
	Fighter_PhysGround_ApplyFriction(fighter_gobj);

	return;
}

//
void SpecialLwHit_EnterAerial(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	Fighter_SetAirborne(fighter_data);
	ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALAIRLWHIT, 0xc4c508e, 0);

	return;
}

//
void SpecialLwHit_CollisionCallback(GOBJ *fighter_gobj)
{
	if (Fighter_CollGround_PassLedge(fighter_gobj) == 0)
	{
		SpecialLwHit_EnterAerial(fighter_gobj);
	}
	return;
}

//
void SpecialAirLwHit_AnimationCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	if (FrameTimerCheck(fighter_gobj) == 0)
	{
		Fighter_EnterFall(fighter_gobj);
	}
}

//
void SpecialAirLwHit_IASACallback(GOBJ *fighter_gobj)
{
	return;
}

//
void SpecialAirLwHit_PhysicCallback(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	Fighter_PhysAir_ApplyGravity(fighter_data, IKE_COUNTER_GRAVITY, IKE_COUNTER_GRAVITY_LIMIT);

	Fighter_PhysAir_DecayXVelocity(fighter_data, IKE_COUNTER_AIR_DECELERATION);

	return;
}

//
void SpecialAirLwHit_EnterGrounded(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	Fighter_SetGrounded2(fighter_data);
	ActionStateChange(fighter_data->state.frame, 1.0, 0.0, fighter_gobj, STATE_SPECIALLWHIT, 0xc4c508e, 0);

	return;
}

//
void SpecialAirLwHit_CollisionCallback(GOBJ *fighter_gobj)
{
	if (Fighter_CollAir_IgnoreLedge_NoCB(fighter_gobj) != 0)
	{
		SpecialAirLwHit_EnterGrounded(fighter_gobj);
	}

	return;
}
