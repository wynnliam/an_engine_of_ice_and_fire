//Liam "AFishyFez" Wynn, 11/7/2015, An Engine of Ice and Fire

/*
 Note that this was not made 11/7/2015. I made this file
 a long time ago, but I've sense removed all the original
 functions, as they lost their purpose, and their design
 was rather poor.

 All that we have here are some helpful, general-purpose
 functions that don't really have a place in a specific
 object. For example, Log2 has a multitude of uses that
 are not confined to one or two classes.
*/

#ifndef HELPFULMETHODS_H
#define HELPFULMETHODS_H

//Performs log for base-2. Returns the power
//such that 2^y = x
double Log2(double x);
//Performs a mod operation that accounts
//for negative numbers
int Mod(int a, int b);
//Given a min, max, and value, normalize
//the value
double Normalize(double min, double max, double val);
//Returns the number of digits of a x
int GetDigitCount(int x);

#endif // HELPFULMETHODS_H
