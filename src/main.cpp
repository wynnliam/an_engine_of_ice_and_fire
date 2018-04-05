//Liam "AFishyFez" Wynn, 6/10/2015, A Clash of Colors

#include <iostream>
#include "GameHandler.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "Welcome to A Clash of Colors!" << endl;
	cout << "By Liam \"AFishyFez\" Wynn!" << endl;

	GameHandler gameHandler("A Clash of Colors");
	gameHandler.RunLoop();

	return 0;
}
