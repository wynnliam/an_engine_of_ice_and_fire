//Liam "AFishyFez" Wynn, 1/18/2016, A Clash of Colors

#include "CharacterHandler.h"
#include "DrawComponentList.h"
#include <cstring>

#include "../Actors/Character/Player.h"
#include "../Actors/Character/TestNonPlayer.h"

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

CharacterHandler::CharacterHandler()
{
}

CharacterHandler::~CharacterHandler()
{
}

//If toGet or renderer are NULL, then return. Then determine the character 
//that is associated with toGet. If none match, then return NULL
Character* CharacterHandler::GetCharacter(const char* toGet, const DrawComponentTable& drawTable) const
{
	if(!toGet)
		return NULL;

	Character* result; //What we will return

	if(strcmp(toGet, "PLAYER") == 0)
	{
		result = new Player;
		result->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_PLAYER_DRAW"));
	}

	else if(strcmp(toGet, "SOLDIER") == 0)
	{
		result = new TestSoldier;
		result->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_TEST_SOLDIER_DRAW"));
	}

	else
		result = NULL;

	return result;
}
