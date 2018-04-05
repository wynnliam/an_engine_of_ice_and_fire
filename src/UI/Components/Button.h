//Liam "AFishyFez" Wynn, 6/20/2015, A Clash of Colors

/*
 A simply button class. All this does is handle the logic of checking
 if it was clicked. Any extra functionallity should be handled in a
 child class.
*/

#include "../MenuComponent.h"

using namespace ACOC_UIElements;

namespace ACOC_UIElements
{
	class Button : public MenuComponent
	{
		public:
			Button();
			Button(AEOIAF_Utilities::DrawableComponent* drawComponent,
				   AEOIAF_Utilities::CollisionComponent* collideComponent,
				   const AEOIAF_Utilities::Vector& offset) : MenuComponent(drawComponent, collideComponent, offset) {}

			void Update(MenuContainer& container);
	};
}
