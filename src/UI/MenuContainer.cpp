//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

#include "MenuContainer.h"
#include "../Utilities/Utility_Components/Vector.h"

using namespace ACOC_UIElements;
using namespace AEOIAF_Utilities;

MenuContainer::MenuContainer()
{
	numComponents = 0;
	components = NULL;	

	background = NULL;
}

MenuContainer::~MenuContainer()
{
	if(components)
	{
		for(int i = 0; i < numComponents; ++i)
		{
			if(components[i])
			{
				delete components[i];
				components[i] = NULL;
			}
		}

		delete[] components;
		components = NULL;
	}

	background = NULL;
}

void MenuContainer::SetMenuComponentDrawComponent(DrawableComponent* val, const int index)
{
	if(!components || index < 0 || index >= numComponents)
		return;

	components[index]->SetDrawableComponent(val);
}

//If the renderer is not NULL nor the components, then initialize
//each non NULL component
void MenuContainer::Initialize(SDL_Renderer* renderer)
{
}

//Basically just loop through each item and invoke the
//update method
void MenuContainer::Update()
{
	if(!components)
		return;

	for(int i = 0; i < numComponents; ++i)
	{
		if(components[i])
			components[i]->Update(*this);
	}
}

void MenuContainer::Draw(SDL_Renderer* renderer)
{
	if(!renderer || !components)
		return;

	if(background)
		background->Draw(renderer, position, SDL_FLIP_NONE, false, false, false);

	for(int i = 0; i < numComponents; ++i)
	{
		if(components[i])
			components[i]->Draw(renderer, position);
	}			
}
