//Liam "AFishyFez" Wynn, 1/25/2016, A Clash of Colors

/*
 Here we will store two props: PropDoorToA, and PropDoorToB.
 Basically they will act as the means to transition from one
 level to another
*/

#ifndef ACOC_PROP_DOOR_TESTS
#define ACOC_PROP_DOOR_TESTS

#include "PropDoor.h"

namespace AEOIAF_Actor
{
	class PropDoorToA : public PropDoor
	{
		public:
            PropDoorToA();
            PropDoorToA(const char* newID);
            PropDoorToA(const PropDoorToA& toCopy);
	};
	
	class PropDoorToB : public PropDoor
	{
		public:
            PropDoorToB();
            PropDoorToB(const char* newID);
            PropDoorToB(const PropDoorToB& toCopy);
	};
}

#endif
