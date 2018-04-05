//Liam "AFishyFez" Wynn, 1/20/2015, AEOIAF: Color

/*
This class stores the prototypes and declaration for
the AEOIAFColor class. This class is simply a wrapper
class to the SDL_Color class, simply adding some extra
functionality to the class
*/

#ifndef AEOIAF_COLOR
#define AEOIAF_COLOR

#include <SDL2/SDL.h>
#include <math.h>
#include <algorithm>

namespace AEOIAF_Content
{
    class AEOIAFColor
    {
        public:
            AEOIAFColor();
            AEOIAFColor(int r, int g, int b, int a);

            AEOIAFColor& operator = (const AEOIAFColor& copyFrom);
            bool operator == (const AEOIAFColor& compareTo) const;

            void Copy(const AEOIAFColor& copyFrom);
            bool Equals(const AEOIAFColor& compareTo) const;

            int GetR() const { return color.r; }
            void SetR(int val) { color.r = val; }

            int GetG() const { return color.g; }
            void SetG(int val) { color.g = val; }

            int GetB() const { return color.b; }
            void SetB(int val) { color.b = val; }

            int GetA() const { return color.a; }
            void SetA(int val) { color.a = val; }

            void SetColor(int r, int g, int b);
            void SetColor(int r, int g, int b, int a);
            //Make a color from a given HSV value
            void SetColor(float hue, float sat, float val);

            float GetHue() const;
            float GetSaturation() const;
            float GetValue() const;

            /*STATIC COLORS*/
            static AEOIAFColor AliceBlue();
            static AEOIAFColor AntiqueWhite();
            static AEOIAFColor Aqua();
            static AEOIAFColor Aquamarine();
            static AEOIAFColor Azure();
            static AEOIAFColor Beige();
            static AEOIAFColor Bisque();
            static AEOIAFColor Black();
            static AEOIAFColor BlanchedAlmond();
            static AEOIAFColor Blue();
            static AEOIAFColor BlueViolet();
            static AEOIAFColor Brown();
            static AEOIAFColor BurlyWood();
            static AEOIAFColor CadetBlue();
            static AEOIAFColor Chartreuse();
            static AEOIAFColor Chocolate();
            static AEOIAFColor Coral();
            static AEOIAFColor CornflowerBlue();
            static AEOIAFColor Cornsilk();
            static AEOIAFColor Crimson();
            static AEOIAFColor Cyan();
            static AEOIAFColor DarkBlue();
            static AEOIAFColor DarkCyan();
            static AEOIAFColor DarkGoldenrod();
            static AEOIAFColor DarkGray();
            static AEOIAFColor DarkGreen();
            static AEOIAFColor DarkKhaki();
            static AEOIAFColor DarkMagenta();
            static AEOIAFColor DarkOliveGreen();
            static AEOIAFColor DarkOrange();
            static AEOIAFColor DarkOrchid();
            static AEOIAFColor DarkRed();
            static AEOIAFColor DarkSalmon();
            static AEOIAFColor DarkSeaGreen();
            static AEOIAFColor DarkSlateBlue();
            static AEOIAFColor DarkSlateGrey();
            static AEOIAFColor DarkTurquoise();
            static AEOIAFColor DarkViolet();
            static AEOIAFColor DeepPink();
            static AEOIAFColor DeepSkyBlue();
            static AEOIAFColor DimGray();
            static AEOIAFColor DodgerBlue();
            static AEOIAFColor Firebrick();
            static AEOIAFColor FloralWhite();
            static AEOIAFColor Fuchsia();
            static AEOIAFColor Gainsboro();
            static AEOIAFColor GhostWhite();
            static AEOIAFColor Gold();
            static AEOIAFColor Goldenrod();
            static AEOIAFColor Gray();
            static AEOIAFColor Green();
            static AEOIAFColor GreenYellow();
            static AEOIAFColor Honeydew();
            static AEOIAFColor HotPink();
            static AEOIAFColor IndianRed();
            static AEOIAFColor Indigo();
            static AEOIAFColor Ivory();
            static AEOIAFColor Khaki();
            static AEOIAFColor Lavender();
            static AEOIAFColor LavenderBush();
            static AEOIAFColor LawnGreen();
            static AEOIAFColor LemonChiffon();
            static AEOIAFColor LightBlue();
            static AEOIAFColor LightCoral();
            static AEOIAFColor LightCyan();
            static AEOIAFColor LightGoldenrod();
            static AEOIAFColor LightGray();
            static AEOIAFColor LightGreen();
            static AEOIAFColor LightPink();
            static AEOIAFColor LightSalmon();
            static AEOIAFColor LightSeaGreen();
            static AEOIAFColor LightSkyBlue();
            static AEOIAFColor LightSlateGray();
            static AEOIAFColor LightSteelBlue();
            static AEOIAFColor LightYellow();
            static AEOIAFColor Lime();
            static AEOIAFColor LimeGreen();
            static AEOIAFColor Linen();
            static AEOIAFColor Magenta();
            static AEOIAFColor Maroon();
            static AEOIAFColor MediumAquamarine();
            static AEOIAFColor MediumBlue();
            static AEOIAFColor MediumOrchid();
            static AEOIAFColor MediumPurple();
            static AEOIAFColor MediumSeaGreen();
            static AEOIAFColor MediumSlateBlue();
            static AEOIAFColor MediumSpringGreen();
            static AEOIAFColor MediumTurquoise();
            static AEOIAFColor MediumVioletRed();
            static AEOIAFColor MidnightBlue();
            static AEOIAFColor MintCream();
            static AEOIAFColor MistyRose();
            static AEOIAFColor Moccasin();
            static AEOIAFColor NavajoWhite();
            static AEOIAFColor Navy();
            static AEOIAFColor OldLace();
            static AEOIAFColor Olive();
            static AEOIAFColor OliveDrab();
            static AEOIAFColor Orange();
            static AEOIAFColor OrangeRed();
            static AEOIAFColor Orchid();
            static AEOIAFColor PaleGoldenrod();
            static AEOIAFColor PaleGreen();
            static AEOIAFColor PaleTurquoise();
            static AEOIAFColor PaleVioletRed();
            static AEOIAFColor PapayaWhip();
            static AEOIAFColor PeachPuff();
            static AEOIAFColor Peru();
            static AEOIAFColor Pink();
            static AEOIAFColor Plum();
            static AEOIAFColor PowderBlue();
            static AEOIAFColor Purple();
            static AEOIAFColor Red();
            static AEOIAFColor RosyBrown();
            static AEOIAFColor RoyalBlue();
            static AEOIAFColor SaddleBrown();
            static AEOIAFColor Salmon();
            static AEOIAFColor SandyBrown();
            static AEOIAFColor SeaGreen();
            static AEOIAFColor SeaShell();
            static AEOIAFColor Sienna();
            static AEOIAFColor Silver();
            static AEOIAFColor SkyBlue();
            static AEOIAFColor SlateBlue();
            static AEOIAFColor SlateGray();
            static AEOIAFColor Snow();
            static AEOIAFColor SpringGreen();
            static AEOIAFColor SteelBlue();
            static AEOIAFColor Tan();
            static AEOIAFColor Teal();
            static AEOIAFColor Thistle();
            static AEOIAFColor Tomato();
            static AEOIAFColor Transparent();
            static AEOIAFColor Turquoise();
            static AEOIAFColor Violet();
            static AEOIAFColor Wheat();
            static AEOIAFColor White();
            static AEOIAFColor WhiteSmoke();
            static AEOIAFColor Yellow();
            static AEOIAFColor YellowGreen();

        private:
            //Returns if a color channel is invalid (r, g, b, or a).
            //Make private because it's really an internal utility function
            bool InvalidChannel(int channel);

            SDL_Color color;
    };
}

#endif // AEOIAF_COLOR
