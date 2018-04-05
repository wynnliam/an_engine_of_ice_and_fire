//Liam "AFishyFez" Wynn, 5/7/2015, AEOIAF: Test AI Character

/*
Eh, I doubt I'll keep this around. I'm just using it to test
out my AI stuff.
*/

#include "NonPlayer.h"
#include "../../Level/Level_AI_Data/LevelPathfinding.h"

namespace AEOIAF_Actor
{
    class TestSoldier : public NonPlayer
    {
        public:
            TestSoldier();
            TestSoldier(const char* newID);
            TestSoldier(const TestSoldier& toCopy);

			TestSoldier* GetCopy();

			void CreateComponents();

            //Update the actor
            void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
			//Draw thy actor
			void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL);

        private:
			void UpdateDestination(AEOIAF_Level::Level* level);

			int destArea;
			AEOIAF_Level::Path currentPath;

			AEOIAF_Utilities::DrawableComponent* colDraw;
    };
}
