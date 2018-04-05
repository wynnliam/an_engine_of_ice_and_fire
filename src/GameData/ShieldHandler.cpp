//Liam "AFishyFez" Wynn, 1/20/2016, A Clash of Colors

#include "ShieldHandler.h"
#include <cstring>

#include "DrawComponentList.h"

#include "../Actors/Item/Shield/TestShield.h"

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

ShieldHandler::ShieldHandler()
{
}

ShieldHandler::~ShieldHandler()
{
}

//If toGet or renderer are NULL, then return NULL. Find the associated shield of
//toGet, otherwise return false. If we do find the weapn, then initialize it before
//returning
Shield* ShieldHandler::GetShield(const char* toGet, const DrawComponentTable& drawTable) const
{
	if(!toGet)
		return NULL;

	Shield* result; //What we will return;

	if(strcmp(toGet, "TEST_SHIELD") == 0)
	{
		result = new TestShield;
		result->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_TEST_SHIELD_DRAW"));
	}

	else
		result = NULL;

	return result;
}
