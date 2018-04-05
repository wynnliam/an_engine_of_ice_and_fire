//Liam "AFishyFez" Wynn, 1/19/2016, A Clash of Colors

#include "PropHandler.h"
#include <cstring>

#include "DrawComponentList.h"

#include "../Actors/Prop/PropSimple.h"
#include "../Actors/Prop/Door/PropDoorTests.h"

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

PropHandler::PropHandler()
{
}

PropHandler::~PropHandler()
{
}

Prop* PropHandler::GetProp(const char* toGet, const DrawComponentTable& drawTable) const
{
	if(!toGet)
		return NULL;

	Prop* result; //What we will return

	if(strcmp(toGet, "SIMPLE") == 0)
	{
		result = new PropSimple;
		result->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_PROP_SIMPLE_DRAW"));
	}

	else if(strcmp(toGet, "DOOR_A") == 0)
	{
		result = new PropDoorToA;
		result->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_TEST_PROP_DRAW"));
	}

	else if(strcmp(toGet, "DOOR_B") == 0)
	{
		result = new PropDoorToB;
		result->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_TEST_PROP_DRAW"));
	}

	else
		result = NULL;


	if(result)
		result->SetID(toGet);

	return result;
}
