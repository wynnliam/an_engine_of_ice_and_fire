//Liam "AFishyFez" Wynn, 1/25/2016, A Clash of Colors

#include "PropDoorTests.h"

using namespace AEOIAF_Actor;

PropDoorToA::PropDoorToA()
{
	SetNextLevelName("OTHER");
}

PropDoorToA::PropDoorToA(const char* newID) : PropDoor(newID)
{
	SetNextLevelName("OTHER");
}

PropDoorToA::PropDoorToA(const PropDoorToA& toCopy) : PropDoor(toCopy)
{
}

PropDoorToB::PropDoorToB()
{
	SetNextLevelName("TEST");
}

PropDoorToB::PropDoorToB(const char* newID) : PropDoor(newID)
{
	SetNextLevelName("TEST");
}

PropDoorToB::PropDoorToB(const PropDoorToB& toCopy) : PropDoor(toCopy)
{
}
