//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

/*
 The Menu Component is the base class for all things
 you would find in a menu. Menu components would be
 things like buttons and text boxes.
*/

#ifndef ACOC_UI_MENU_COMPONENT
#define ACOC_UI_MENU_COMPONENT

#include "../Basic_Components/DrawableComponent.h"
#include "../Basic_Components/CollisionComponent.h"
#include <SDL2/SDL.h>

namespace AEOIAF_Utilities
{
	class Vector;
}

namespace ACOC_UIElements
{
	class MenuContainer;

	class MenuComponent
	{
		public:
			MenuComponent();
			MenuComponent(AEOIAF_Utilities::DrawableComponent* drawComponent,
						  AEOIAF_Utilities::CollisionComponent* collideComponent,
						  const AEOIAF_Utilities::Vector& offset);
			virtual ~MenuComponent();

			bool IsActive() const { return bIsActive; } 

			void SetDrawableComponent(AEOIAF_Utilities::DrawableComponent* val);
			void SetCollisionComponent(AEOIAF_Utilities::CollisionComponent* val);
			
			AEOIAF_Utilities::Vector GetOffset() const { return offset; }
			void SetOffset(const AEOIAF_Utilities::Vector& val) { offset = val; }

			virtual void Update(MenuContainer& container) = 0;
			virtual void Draw(SDL_Renderer* renderer, const AEOIAF_Utilities::Vector& containerPosition);

		protected:
			//Use this to display the component
			AEOIAF_Utilities::DrawableComponent* drawComponent;
			//Use this for checking clicks or whatever
			AEOIAF_Utilities::CollisionComponent* collideComponent;
			//The relative position to the menu component
			AEOIAF_Utilities::Vector offset;
			//Context dependent, but used if say we are focusing on
			//a text box, or we clicked a button, or whatever
			bool bIsActive;
	};
}

#endif
