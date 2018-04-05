//Liam "AFishyFez" Wynn, 10/11/2015, A Clash of Colors

/*
 Shields are a means of defending oneself from attacks.
 Essentially, they stay by the character's side. When hit
 by an item, we check if the shield was hit instead. If so,
 then the shield will absorb the attack.

 Like Weapons, the bare basics of a shield is handled here.
 That is, we essentially include a couple of functions for
 collision detection, updating the placement of the shield,
 relative to the owner, and really that's about it.
*/

#ifndef AEOIAF_SHIELD
#define AEOIAF_SHIELD

#include "../Item.h"
#include "../../../Utilities/General_Purpose/Matrix.h"

namespace AEOIAF_Actor
{
	class Shield : public Item
	{
		public:
            Shield();
            Shield(const char* newID);
            Shield(const Shield& toCopy);
            virtual ~Shield();

            virtual Shield& operator = (const Shield& toCopy);

            virtual void Copy(const Shield& toCopy);
			virtual Shield* GetCopy();

			AEOIAF_Utilities::Vector GetOffset() { return offset; }
			void SetOffset(const AEOIAF_Utilities::Vector& val) { offset = val; }
		
			float GetDrawRotationOffset() { return drawRotationOffset; }
			void SetDrawRotationOffset(const float val) { drawRotationOffset = val; }

			//Update the position and collision component of the shield
            virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
		
			//Determines if we collide with another actor
			virtual bool CollidesWith(Actor* toCheck) const;
			//Determines if our collision component collides with toCheck
			virtual bool CollidesWith(AEOIAF_Utilities::AxisAllignedBoundingBox& toCheck) const;
			//Determines if our collision component collides with tracer
			virtual bool CollidesWith(const AEOIAF_Utilities::Tracer& tracer) const;
			
			virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
							  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
							  AEOIAF_Utilities::Matrix* matrix = NULL);
		protected:
			//Update the rotation matrices and shield rotation
			//value
			virtual void UpdateRotationValuesAndMatrices();
			//Determines the position to place the shield at
			virtual AEOIAF_Utilities::Vector GetTransformedPosition();
			//Creates a transformed axis alligned bounding box
			AEOIAF_Utilities::AxisAllignedBoundingBox GetTransformedBoundingBox();
			//Updates the position of the collision box
			void UpdateCollisionBoxPosition(int width, int height);

			//The offset relative to the owner's position
			//that we apply to the shield to get its final
			//draw position
			AEOIAF_Utilities::Vector offset;
			//Position of the collision box for the shield
			AEOIAF_Utilities::Vector colBoxPos;
			//Since the collisionComponent stores the base collision
			//box that we use to calculate the transformed collision
			//box, we store that transformed collision box here
			AEOIAF_Utilities::AxisAllignedBoundingBox transformedColBox;
			//A rotation matrix that we apply to the offset
			//to get a rotated offset. Also applied to collision
			//box
			AEOIAF_Utilities::Matrix offsetRotationMatrix;
			//A matrix we apply to the collision box to account for
			//the draw rotation of the shield
			AEOIAF_Utilities::Matrix colBoxRotationMatrix;
			//A rotation we add to the owner's rotation, so
			//that the shield isn't facing the exact same way
			//as the owner. If set to zero, then it will face
			//the the same way the owner is
			float drawRotationOffset;

		private:
			AEOIAF_Utilities::DrawableComponent* rectangleRegion;
	};
}

#endif
