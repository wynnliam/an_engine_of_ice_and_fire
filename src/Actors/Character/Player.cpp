//Liam "AFishyFez" Wynn, 4/16/2015, AEOIAF: Player

#include "Player.h"
#include "../../Utilities/Utility_Components/InputHandler.h"
#include "../../Utilities/Utility_Components/Constants.h"
#include "../../Level/Level.h"
#include "../Item/Weapon/Weapon.h"
#include "../Item/Shield/Shield.h"
#include <math.h>
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

Player::Player()
{
	CreateComponents();
}

Player::Player(const char* newID) : Character(newID)
{
	CreateComponents();
}

Player::Player(const Player& toCopy)
{
    Copy(toCopy);
}

Player::~Player()
{
}

Player& Player::operator = (const Player& toCopy)
{
    Copy(toCopy);
    return *this;
}

void Player::Copy(const Player& toCopy)
{
    if(this == &toCopy)
        return;

    camera = toCopy.camera;

    Character::Copy(toCopy);
}

Player* Player::GetCopy()
{
	return new Player(*this);
}

void Player::CreateComponents()
{
	SetMovableComponent(new MovableComponent);
	SetCollisionComponent(new CollisionComponent(64, 64));
}

void Player::Update(Level* level, SDL_Event* e, float deltaTime)
{
    if(!movableComponent || !level)
        return;

	//We use the mouse position quite a bit, so let's just grab it once
    Vector mousePosition = InputHandler::GetMousePosition();

	UpdateMovementAndPosition(level, deltaTime);

    //Call this first so we can fix mouse position and make rotation correct
    UpdateCamera(mousePosition, level);
	//Now we can look at the mouse position
	LookAt(mousePosition);

	UpdateEquippedItems(level, e, deltaTime);
}

//If the level or movable compnent are NULL, then return. Save the previous
//position. Then, check for inpu Then update the position of the player.
//Finally, handle any wall collisions
void Player::UpdateMovementAndPosition(Level* level, float deltaTime)
{
	if(!level || !movableComponent)
		return;

    Vector direction; //Describe the direction of movement we want
    
	//So we can go back to our old position in the event of a collision
    SavePreviousPosition();

    HandleInput(direction);
    UpdateMovement(direction, deltaTime);

    //Make sure the collisions are handled before we update the camera
    //Otherwise we get a weird shifting effect with the camera
    HandleWallCollisions(level);
}

void Player::HandleInput(Vector& direction) const
{
	float dirX, dirY; //Components for the new direction

    //Handle y-axis movement
    if(InputHandler::KeyPressed(SDL_SCANCODE_W))
        dirY = -1.0f;
    else if(InputHandler::KeyPressed(SDL_SCANCODE_S))
        dirY = 1.0f;
    else
        dirY = 0.0f;

	//Handle x-axis movement 
    if(InputHandler::KeyPressed(SDL_SCANCODE_A))
        dirX = -1.0f;
    else if(InputHandler::KeyPressed(SDL_SCANCODE_D))
        dirX = 1.0f;
    else
        dirX = 0.0f;

	direction.SetX(dirX);
	direction.SetY(dirY);
}

void Player::UpdateMovement(const Vector& direction, float deltaTime)
{
	if(!movableComponent)
		return;

    movableComponent->SetDirection(direction);
	//Note that this is the speed
	movableComponent->SetMagnitude(4.0f);

	movableComponent->Update(deltaTime);
}

//If the movementComponent or level are NULL, then return. Update the camera
//using the position of the player. Transform the mouse position by the inverse
//of the camera matrix (don't ask about the math. In Todd Howard's words,
//"It just works"). Then update the level's draw matrix, mouse position, and
//player position.
void Player::UpdateCamera(Vector& mousePosition, AEOIAF_Level::Level* level)
{
	if(!movableComponent || !level)
		return;

	Matrix inverseCameraMatrix;
	Vector position = movableComponent->GetPosition();

	camera.Update(position, AEOIAF_SCREEN_WIDTH, AEOIAF_SCREEN_HEIGHT, false);
	inverseCameraMatrix = Matrix::Inverse(camera.GetViewMatrix());

	mousePosition = Matrix::Transform(mousePosition, inverseCameraMatrix);

	level->SetDrawMatrix(&camera.GetViewMatrix());
	level->SetDrawCamera(&camera);
	level->SetMousePosition(mousePosition);
	level->SetPlayerPosition(position);
}

void Player::UpdateEquippedItems(Level* level, SDL_Event* e, float deltaTime)
{
	if(!equippedWeapon || !equippedShield)
		return;
	
	equippedWeapon->Update(level, e, deltaTime);
	equippedShield->Update(level, e, deltaTime);
}

//We have to grab the position, apply an offset to center him,
//then after drawing we must reset the position
void Player::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                  Matrix* matrix)
{
	if(!movableComponent)
		return;

	//The offset applied to the position to draw relative to the
	//center of the character texture
	int halfCharSize = AEOIAF_CHAR_SIZE / 2;
	//Since the position of the character changes for drawing, we
	//need this to reset it
	Vector position = movableComponent->GetPosition();
	//The offset vector we apply to make the character draw
	//relative to the origin
	Vector offset(halfCharSize, halfCharSize);

	movableComponent->SetPosition(position - offset);

    Character::Draw(renderer, flip, true, false, true, &camera.GetViewMatrix());

	//The variable position has not not been modified, so we can set it back
	movableComponent->SetPosition(position);

	if(equippedWeapon)
		equippedWeapon->Draw(renderer, flip, true, false, true, &camera.GetViewMatrix());
	if(equippedShield)
		equippedShield->Draw(renderer, flip, true, false, true, &camera.GetViewMatrix());
}
