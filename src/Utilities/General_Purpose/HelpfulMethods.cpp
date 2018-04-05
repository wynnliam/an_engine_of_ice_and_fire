//Liam "AFishyFez" Wynn, 11/7/2015, An Engine of Ice and Fire

#include "HelpfulMethods.h"
#include <cmath>

//If x < 1, then return 0. Then use
//the change-of-base formula to get
//the result of base-2 log(x)
double Log2(double x)
{
	if(x < 1.0)
		return 0.0;

	double result; //What we will return

	result = log(x) / log(2.0);

	return result;
}

//As found here: http://stackoverflow.com/a/4003287
int Mod(int a, int b)
{
	if(b == 0)
		return 0;

	int result;

	if(b < 0)
		result = Mod(-a, -b);
	else
	{
		result = a % b;
		if(result < 0)
			result += b;
	}

	return result;
}

//Found here: http://stn.spotfire.com/spotfire_client_help/norm/norm_scale_between_0_and_1.htm
//If max - min is 0, return 0.0f
double Normalize(double min, double max, double val)
{
	if(max == min)
		return 0.0;

	return (val - min) / (max - min);
}

int GetDigitCount(int x)
{
	if(x < 0) x *= -1;

	return (int)floor(log10(x) + 1);
}
