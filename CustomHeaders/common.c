//This file contains common functions for use across the entire project. If code is being rewritten many times across multiple components, consider adding it as a function here.

#include "../m-ex/MexTK/mex.h"

#include <stdbool.h>

///		             ///
/// MOVE LOGIC STUFF ///
///                  ///

#pragma region

//Move logic to check for ground collision and switch from grounded to aerial state if necessary
void CommonEnterAirLogic(
	GOBJ *fighterGOBJ, //Fighter GOBJ to check
	int state,		   //Action state ID to switch to if no ground collision found
	int flags		   //Flags for state change
)
{
	if (!Fighter_CollGround_PassLedge(fighterGOBJ)) // when entering the air change to air state
	{
		FighterData *fighterData = (FighterData *)fighterGOBJ->userdata;

		Fighter_SetAirborne(fighterData);

		ActionStateChange(fighterData->state.frame, fighterData->state.rate, 0, fighterGOBJ, state, flags, 0);
	}
}

//Move logic to check for ground collision and switch from aerial to grounded state if necessary
void CommonLandingLogic(
	GOBJ *fighterGOBJ, //Fighter GOBJ to check
	int state,		   //Action state ID to switch to if ground collision found
	int flags		   //Flags for state change
)
{
	if (Fighter_CollAir_IgnoreLedge_NoCB(fighterGOBJ) != 0) // when colliding with the ground change to the grounded state
	{
		FighterData *fighterData = (FighterData *)fighterGOBJ->userdata;

		Fighter_SetGrounded(fighterData);

		ActionStateChange(fighterData->state.frame, fighterData->state.rate, 0, fighterGOBJ, state, flags, 0);
	}
}

void ActionStateChangePreserveStateVars(float startFrame, float animSpeed, float animBlend, GOBJ *fighter, int stateID, int flags1, GOBJ *alt_state_source)
{
	FighterData *fighter_data = fighter->userdata;

	int state_vars[18];

	memcpy(state_vars, &fighter_data->state_var, sizeof(int) * 18);

	ActionStateChange(startFrame, animSpeed, animBlend, fighter, stateID, flags1, alt_state_source);

	memcpy(&fighter_data->state_var, state_vars, sizeof(int) * 18);

	return;
}

int checkReverseInput_cstick(FighterData *fighter_data)
{
	if (fighter_data->facing_direction > 0 && fighter_data->input.cstick.X < -0.275)
	{
		return 1;
	}
	else if (fighter_data->facing_direction < 0 && fighter_data->input.cstick.X > 0.275)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int checkReverseInput(FighterData *fighter_data)
{
	if (fighter_data->facing_direction > 0 && fighter_data->input.lstick.X < -0.275)
	{
		return 1;
	}
	else if (fighter_data->facing_direction < 0 && fighter_data->input.lstick.X > 0.275)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

float GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrtf(pow(fabs(x2 - x1), 2) + pow(fabs(y2 - y1), 2));
}

float pow(float b, int e)
{
	float result = 1.0;
	for (int i = 0; i < e; i++)
	{
		result *= b;
	}
	return result;
}

DOBJ *JOBJ_DOBJLookup(JOBJ *jobj, int dobj_index)
{
	DOBJ *return_dobj = JOBJ_GetDObj(jobj);
	for (int i = 0; i < dobj_index; i++)
	{
		return_dobj = return_dobj->next;
	}
	return return_dobj;
}

//Returns 1 if ground is hit, 0 if not
int RayCastToGround(Vec3 startPos, int x_offset, int y_offset, int unitsVertical)
{
	Vec3 pos = startPos;
	pos.X += x_offset;
	pos.Y += y_offset;
	int line_index;
	int line_kind;
	Vec3 line_angle;

	return GrColl_RaycastGround(&pos, &line_index, &line_kind, &line_angle, -1, -1, -1, 0, pos.X, pos.Y, pos.X, (pos.Y + unitsVertical), 0);
}

#pragma endregion

///		  ///
/// OTHER ///
///       ///

#pragma region

//Checks if an address is within the bounds of the Gamecube's memory
//Returns true if address exists
bool AddressExists(
	void *adr //Address to check
)
{
	if (adr >= 0x80000000 && adr < 0x81800000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Gets left stick coordinates for a fighter after accounting for stick deadzones
//Returns Vec2 coordinates for the fighter's left stick, where the X/Y coordinates will = 0 if they were greater than -0.2875 and less than +0.2875
Vec2 CalculateStickDeadzones(
	FighterData *fighterData //Userdata of the fighter
)
{
	HSD_Pad *pad = PadGet(fighterData->player_controller_number, PADGET_MASTER);
	Vec2 out = {pad->fstickX, pad->fstickY};

	if (out.X > -0.2875f && out.X < 0.2875f)
	{
		out.X = 0.0f;
	}

	if (out.Y > -0.2875f && out.Y < 0.2875f)
	{
		out.Y = 0.0f;
	}

	return out;
}

int Fighter_InterruptAllAerial_NoAirdodge(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	if (Fighter_CheckJumpInput(fighter_gobj))
	{
		return Fighter_Interrupt_AllAerial(fighter_gobj);
	}
	else if (fighter_data->input.down & (HSD_BUTTON_A | HSD_BUTTON_B))
	{
		return Fighter_Interrupt_AllAerial(fighter_gobj);
	}
	else
	{
		return 0;
	}
}

float Fighter_GetAnimationLength(FighterData *fighter_data, int state_id)
{
	int animID = fighter_data->ftstates_special[state_id - 341].action_id;
	int animAddress = Animation_GetAddress(fighter_data, animID);
	return Animation_GetLength(animAddress);
}

int CheckForAndThrowItem(GOBJ *fighter_gobj)
{
	FighterData *fighter_data = fighter_gobj->userdata;

	GOBJ *held_gobj = fighter_data->item_held;

	if (held_gobj == 0)
	{
		return 0;
	}
	else
	{
		int item_id = Items_GetItemID(held_gobj);
		if (item_id < 60)
		{
			Fighter_EnterLightThrow(fighter_gobj, ASID_LIGHTTHROWF);
		}
		return 1;
	}
}

void DebugPrint(const char *format, ...)
{
	if (*stc_dblevel == DB_MASTER)
		return;

	void *arg = __builtin_apply_args();
	void *ret = __builtin_apply((void *)OSReport, arg, 100);
	__builtin_return(ret);
}

#pragma endregion