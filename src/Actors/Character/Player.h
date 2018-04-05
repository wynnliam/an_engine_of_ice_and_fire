//Liam "AFishyFez" Wynn, 4/15/2015, AEOIAF: Player

/*
Extending from Character, the Player is the character
that the user controls. To make a video game, of course
you need this fellow. Due to his significance and size,
the Player class shall have his own files
*/

#ifndef AEOIAF_PLAYER
#define AEOIAF_PLAYER

#include "Character.h"
#include "../../Utilities/Utility_Components/Camera.h"

namespace AEOIAF_Actor
{
    class Player : public Character
    {
        public:
            Player();
            Player(const char* newID);
            Player(const Player& toCopy);
            virtual ~Player();

            virtual Player& operator = (const Player& toCopy);

            AEOIAF_Utilities::Camera& Camera() { return camera; }

            void Copy(const Player& toCopy);
			virtual Player* GetCopy();

			void CreateComponents();

            //Update the actor
            void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
            //Draw the actor
            void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL);

        private:
			//Manages all logic in moving the character
			void UpdateMovementAndPosition(AEOIAF_Level::Level* level, float deltaTime);
			//Sets direction of movement based on key presses
            void HandleInput(AEOIAF_Utilities::Vector& direction) const;
			//Given direction, we decide our velocity and update position accordingly
            void UpdateMovement(const AEOIAF_Utilities::Vector& direction, float deltaTime);
			//Updates the player's view camera
            void UpdateCamera(AEOIAF_Utilities::Vector& mousePosition, AEOIAF_Level::Level* level);
			//Updates equipped items
			void UpdateEquippedItems(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);

            //Basically the viewport for the player
            AEOIAF_Utilities::Camera camera;
    };
}

#endif // AEOIAF_PLAYER
