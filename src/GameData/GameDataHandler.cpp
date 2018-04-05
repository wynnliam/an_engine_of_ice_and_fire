//Liam "AFishyFez" Wynn, 7/27/2015, A Clash of Colors

#include "GameDataHandler.h"

#include "../Actors/Character/Character.h"
#include "../Actors/Prop/Prop.h"
#include "../Actors/Item/Weapon/Weapon.h"
#include "../Actors/Item/Shield/Shield.h"
#include "../Actors/Particle/Particle.h"

#include "../Utilities/Utility_Components/Vector.h"

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Audio;
using namespace AEOIAF_Actor;

GameDataHandler::GameDataHandler()
{
	renderer = NULL;
	currentLevel = NULL;
	streamHandler = NULL;	

	SetStreamHandler(new StreamDataHandler);
}

GameDataHandler::GameDataHandler(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	currentLevel = NULL;
	streamHandler = NULL;
	
	SetStreamHandler(new StreamDataHandler);
}

GameDataHandler::~GameDataHandler()
{
	if(currentLevel)
	{
		delete currentLevel;
		currentLevel = NULL;
	}

	SetStreamHandler(NULL);
}

void GameDataHandler::SetStreamHandler(StreamDataHandler* val)
{
	if(streamHandler)
		delete streamHandler;

	streamHandler = val;
}

Level* GameDataHandler::GetLevel(const char* toGet)
{
	if(!toGet || !renderer)
		return NULL;

	return levelHandler.GetLevel(toGet, *this, *streamHandler, renderer);
}

Character* GameDataHandler::GetCharacter(const char* toGet) const
{
	if(!toGet || !renderer)
		return NULL;

	return characterHandler.GetCharacter(toGet, drawComponentTable);
}

Prop* GameDataHandler::GetProp(const char* toGet) const
{
	if(!toGet || !renderer)
		return NULL;

	return propHandler.GetProp(toGet, drawComponentTable);
}

Weapon* GameDataHandler::GetWeapon(const char* toGet) const
{
	if(!toGet || !renderer)
		return NULL;

	return weaponHandler.GetWeapon(toGet, drawComponentTable);
}

Shield* GameDataHandler::GetShield(const char* toGet) const
{
	if(!toGet || !renderer)
		return NULL;

	return shieldHandler.GetShield(toGet, drawComponentTable);
}

ParticleEmitter* GameDataHandler::GetParticleEmitter(const char* toGet) const
{
	if(!toGet || !renderer)
		return NULL;

	return particleHandler.GetParticleEmitter(toGet, drawComponentTable);
}

Actor* GameDataHandler::GetActorUnknownType(const char* toGet, char& type) const
{
	if(!toGet || !renderer)
	{
		type = 'U';
		return NULL;
	}

	Actor* result;

	if((result = GetCharacter(toGet)) != NULL)
		type = 'C';
	else if((result = GetProp(toGet)) != NULL)
		type = 'P';
	else if((result = GetWeapon(toGet)) != NULL)
		type = 'W';
	else if((result = GetShield(toGet)) != NULL)
		type = 'S';
	else if((result = GetParticleEmitter(toGet)) != NULL)
		type = 'A';
	else
		type = 'U';

	return result;
}

bool GameDataHandler::LoadDrawComponents()
{
	if(!renderer)
		return false;

	DrawableComponent* acocTestSoldierDraw = new DrawableComponent("Content/TestPlayer.png");
	acocTestSoldierDraw->Initialize(renderer);
	drawComponentTable.Insert("ACOC_TEST_SOLDIER_DRAW", acocTestSoldierDraw);

	DrawableComponent* acocPlayerDraw = new DrawableComponent("Content/ACOC_Assests/Characters/player.png");
	acocPlayerDraw->Initialize(renderer);
	drawComponentTable.Insert("ACOC_PLAYER_DRAW", acocPlayerDraw);

	DrawableComponent* acocTestShield = new DrawableComponent("Content/shield.png");
	acocTestShield->Initialize(renderer);
	drawComponentTable.Insert("ACOC_TEST_SHIELD_DRAW", acocTestShield);

	DrawableComponent* acocTestMelee = new DrawableComponent("Content/melee_weapon.png");
	acocTestMelee->Initialize(renderer);
	drawComponentTable.Insert("ACOC_TEST_MELEE_DRAW", acocTestMelee);

	DrawableComponent* acocTestMeleeAnim = new DrawableComponent("Content/melee_sheet.png");
	acocTestMeleeAnim->Initialize(renderer);
	drawComponentTable.Insert("ACOC_TEST_MELEE_ANIM_DRAW", acocTestMeleeAnim);

	DrawableComponent* acocTestProjectile = new DrawableComponent("Content/playerBullet.png");
	acocTestProjectile->Initialize(renderer);
	drawComponentTable.Insert("ACOC_TEST_PROJECTILE", acocTestProjectile);

	DrawableComponent* acocTestParticle = new DrawableComponent("Content/ACOC_Assests/Particles/test_particle.png");
	acocTestParticle->Initialize(renderer);
	drawComponentTable.Insert("ACOC_TEST_PARTICLE_DRAW", acocTestParticle);

	DrawableComponent* acocTestProp = new DrawableComponent("Content/door.png");
	acocTestProp->Initialize(renderer);
	drawComponentTable.Insert("ACOC_TEST_PROP_DRAW", acocTestProp);

	DrawableComponent* acocSimple = new DrawableComponent("Content/rum_from_rum.png");
	acocSimple->Initialize(renderer);
	drawComponentTable.Insert("ACOC_PROP_SIMPLE_DRAW", acocSimple);

	DrawableComponent* acocMainMenuBackground = new DrawableComponent("Content/MenuContent/PlaceHolderMenu2.jpg");
	acocMainMenuBackground->Initialize(renderer);
	drawComponentTable.Insert("ACOC_MAIN_MENU_BACKGROUND", acocMainMenuBackground);
	
	DrawableComponent* acocMainMenuPlay = new DrawableComponent("Content/MenuContent/play.png");
	acocMainMenuPlay->Initialize(renderer);
	drawComponentTable.Insert("ACOC_MAIN_MENU_PLAY_DRAW", acocMainMenuPlay);

	return true;
}

void GameDataHandler::InsertDrawableComponent(const char* id, DrawableComponent* component)
{
	drawComponentTable.Insert(id, component);
}

DrawableComponent* GameDataHandler::GetDrawableComponent(const char* id)
{
	return drawComponentTable.GetDrawableComponent(id);
}

bool GameDataHandler::LoadAudioComponents()
{
	MusicComponent* openingMusic = new MusicComponent("Content/sounds/Cold.mp3");
	audioComponentTable.Insert("ACOC_INTRO_SONG", openingMusic);

	SoundComponent* rifle = new SoundComponent("Content/sounds/test_rifle.wav", 2);
	audioComponentTable.Insert("ACOC_TEST_RIFLE_SOUND", rifle);

	return true;
}

AudioComponent* GameDataHandler::GetAudioComponent(const char* id)
{
	AudioComponent* result = audioComponentTable.GetComponent(id);
	if(result)
		result->Initialize();
	return result;
}
