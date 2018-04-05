//Liam "AFishyFez" Wynn, 8/14/2015, An Engine of Ice and Fire

#include "Tracer.h"
#include "../Utility_Components/AxisAllignedBoundingBox.h"
#include <math.h> //For sin and cosine functions
#include <algorithm>
#include <iostream>

using namespace AEOIAF_Utilities;
using namespace std;

Tracer::Tracer()
{
}

Tracer::Tracer(const AEOIAF_Utilities::Vector& newStart, float rotation)
{
	start = newStart;

	end.SetX(cos(rotation) * 10000.0f);
	end.SetY(sin(rotation) * 10000.0f);
}

Tracer::Tracer(const Tracer& toCopy)
{
	Copy(toCopy);
}

Tracer& Tracer::operator= (const Tracer& toCopy)
{
	Copy(toCopy);
	return *this;
}

void Tracer::Copy(const Tracer& toCopy)
{
	start = toCopy.start;
	end = toCopy.end;
}

bool Tracer::Intersects(const AxisAllignedBoundingBox& toCheck) const
{
	float fracLo, fracHi;
	bool result; //What we will return

	fracLo = 0.0f;
	fracHi = 1.0f;

	//First we do a clip line check along the x-axis, then the
	//y-axis. If either fail, we return false
	if(!ClipLine(true, toCheck, fracLo, fracHi) ||
	  !ClipLine(false, toCheck, fracLo, fracHi))
		result = false;
	else
		result = true;

	return result;
}

bool Tracer::ClipLine(bool bIsXDimension, const AxisAllignedBoundingBox& toCheck, float& fracLo, float& fracHi) const
{
	//Describe the fraction scalar we would apply to the tracer
	//to reach toCheck, assuming we hit it. We use these to
	//determine if an intersection with toCheck actually occured
	float dimFracLo, dimFracHi;
	//Used in calculating fracLo and fracHi. Based on bIsXDimension,
	//we use these to determine what component of the min and max of
	//values of toCheck to use
	float toCheckMin, toCheckMax;
	//Used in calculating fracLo and fracHi. Like toCheckMin/Max,
	//These values are determined by bIsXDimension. We get the
	//correct vector component values from the start and end
	//respectively
	float tracerStart, tracerEnd;
	//What we will return
	bool result;

	//Begine by setting toCheckMin/Max and tracerStart/End
	if(bIsXDimension)
	{
		toCheckMin = toCheck.xMin;
		toCheckMax = toCheck.xMax;
		tracerStart = start.GetX();
		tracerEnd = end.GetX();
	}

	else
	{
		toCheckMin = toCheck.yMin;
		toCheckMax = toCheck.yMax;
		tracerStart = start.GetY();
		tracerEnd = end.GetY();
	}

	dimFracLo = (toCheckMin - tracerStart) / (tracerEnd - tracerStart);
	dimFracHi = (toCheckMax - tracerStart) / (tracerEnd - tracerStart);

	if(dimFracHi < dimFracLo)
		swap(dimFracHi, dimFracLo);

	if(dimFracHi < fracLo || dimFracLo > fracHi)
		result = false;
	else
	{
		fracLo = max(dimFracLo, fracLo);
		fracHi = min(dimFracHi, fracHi);

		if(fracLo > fracHi)
			result = false;
		else
			result = true;
	}

	return result;
}
