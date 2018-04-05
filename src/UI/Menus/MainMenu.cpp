//Liam "AFishyFez" Wynn, 6/20/2015, A Clash of Colors

#include "MainMenu.h"
#include "../Components/Button.h"
#include "../../Basic_Components/DrawableComponent.h"
#include "../../Basic_Components/CollisionComponent.h"
#include "../../Utilities/Utility_Components/Vector.h"

using namespace ACOC_UIElements;
using namespace AEOIAF_Utilities;

MenuMainMenu::MenuMainMenu()
{
	numComponents = 1;

	components = new MenuComponent*[numComponents];
	
	CollisionComponent* buttonColComp = new CollisionComponent(256, 128);
	Vector buttonOffset(192, 176);
	components[0] = new Button;
	components[0]->SetOffset(buttonOffset);
	components[0]->SetCollisionComponent(buttonColComp);

	bPlay = false;
}

MenuMainMenu::~MenuMainMenu()
{
}

void MenuMainMenu::ProcessInput(SDL_Event& e)
{
}

void MenuMainMenu::Update()
{
	if(!components)
		return;

	for(int i = 0; i < numComponents; ++i)
	{
		if(components[i])
			components[i]->Update(*this);
	}

	//We want to go to the WorldGen State if compent[0] (Play button)
	//is not NULL, and we clicked it (as handled in its Update function)
	bPlay = components[0] && components[0]->IsActive();
}
