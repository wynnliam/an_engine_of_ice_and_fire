//Liam "AFishyFez" Wynn, 1/20/2016, A Clash of Colors

#include "WeaponHandler.h"
#include <cstring>

#include "DrawComponentList.h"

#include "../Actors/Item/Weapon/Tracer/TestWeaponTracer.h"
#include "../Actors/Item/Weapon/Projectile/TestWeaponProjectile.h"
#include "../Actors/Item/Weapon/Projectile/TestProjectile.h"
#include "../Actors/Item/Weapon/Melee/WeaponMeleeTest.h"

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

WeaponHandler::WeaponHandler()
{
}

WeaponHandler::~WeaponHandler()
{
}

//If toGet or renderer are NULL, then return NULL. Find the associated weapon of
//toGet, otherwise return false. If we do find the weapn, then initialize it before
//returning
Weapon* WeaponHandler::GetWeapon(const char* toGet, const DrawComponentTable& drawTable) const
{
	if(!toGet)
		return NULL;

	Weapon* result; //What we will return

	if(strcmp(toGet, "TRACER_TEST") == 0)
		result = new TestWeaponTracer;
	else if(strcmp(toGet, "PROJECTILE_TEST") == 0)
	{
		result = new TestWeaponProjectile;
		TestProjectile* temp = new TestProjectile;
		temp->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_TEST_PROJECTILE"));
		dynamic_cast<TestWeaponProjectile*>(result)->SetProjectileType(temp);
	}

	else if(strcmp(toGet, "MELEE_TEST") == 0)
	{
		WeaponMeleeTest* temp = new WeaponMeleeTest;
		temp->SetAnimationDrawComponent(drawTable.GetDrawableComponent("ACOC_TEST_MELEE_ANIM_DRAW"));
		result = temp;
	}

	else
		result = NULL;

	return result;
}
