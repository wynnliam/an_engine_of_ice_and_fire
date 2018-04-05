//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

/*
 Menus are quite different from Actors, despite having similar
 functions. For one, they do not interact with other objects
 like an Actor might. The purpose of the Menu Container (and
 the entire menu system for that matter) is to handle graphical
 overlays such as the main menu, HUDs, and other things like that.

 The Menu Container is responsible for storing and managing an array
 of Menu Components.
*/

#ifndef ACOC_MENU_CONTAINER
#define ACOC_MENU_CONTAINER

#include "MenuComponent.h"
#include "../Basic_Components/DrawableComponent.h"
#include <SDL2/SDL.h>

namespace AEOIAF_Utilities
{
	class Vector;
}

namespace ACOC_UIElements
{
	class MenuContainer
	{
		public:
			MenuContainer();
			virtual ~MenuContainer();

			AEOIAF_Utilities::DrawableComponent* GetBackground() { return background; }
			void SetBackground(AEOIAF_Utilities::DrawableComponent* val) { background = val; }

			void SetMenuComponentDrawComponent(AEOIAF_Utilities::DrawableComponent* val, const int index);

			int GetNumComponents() const { return numComponents; }
			AEOIAF_Utilities::Vector GetPosition() const { return position; }

			//It will initialize all components in the menu
			virtual void Initialize(SDL_Renderer* renderer);
			//Something that a text-box would greatly appreciate
			virtual void ProcessInput(SDL_Event& e) = 0;
			//Update all components
			virtual void Update();
			//Draw all components
			virtual void Draw(SDL_Renderer* renderer);

		protected:
			int numComponents; //The number of components in this menu
			MenuComponent** components;

			AEOIAF_Utilities::DrawableComponent* background; //Simply draws the background texture

			AEOIAF_Utilities::Vector position; //The position of the menu on screen (usually it's (0,0))
	};
}

#endif
