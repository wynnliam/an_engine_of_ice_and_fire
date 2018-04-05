#include "AEOIAFColor.h"

using namespace AEOIAF_Content;
using namespace std;

AEOIAFColor::AEOIAFColor()
{
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
}

AEOIAFColor::AEOIAFColor(int r, int g, int b, int a)
{
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

AEOIAFColor& AEOIAFColor::operator = (const AEOIAFColor& copyFrom)
{
    Copy(copyFrom);
    return *this;
}

bool AEOIAFColor::operator == (const AEOIAFColor& compareTo) const
{
    return Equals(compareTo);
}

void AEOIAFColor::Copy(const AEOIAFColor& copyFrom)
{
    if(this == &copyFrom)
        return;

    color.r = copyFrom.color.r;
    color.g = copyFrom.color.g;
    color.b = copyFrom.color.b;
    color.a = copyFrom.color.a;
}

bool AEOIAFColor::Equals(const AEOIAFColor& compareTo) const
{
	if(this == &compareTo)
		return true;

    return color.r == compareTo.color.r
        && color.g == compareTo.color.g
        && color.b == compareTo.color.b
        && color.a == compareTo.color.a;
}

void AEOIAFColor::SetColor(int r, int g, int b)
{
    if(InvalidChannel(r) || InvalidChannel(g) || InvalidChannel(b))
        return;

    color.r = r;
    color.g = g;
    color.b = b;
}

void AEOIAFColor::SetColor(int r, int g, int b, int a)
{
    if(InvalidChannel(r) || InvalidChannel(g) || InvalidChannel(b) || InvalidChannel(a))
        return;

    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

void AEOIAFColor::SetColor(float hue, float sat, float val)
{
    int hi = (int)floor(hue / 60.0f) % 6;
    float f = hue / 60.0f - floor(hue / 60.0f);

    val *= 255;
    int v = (int)(val);
    int p = (int)(val * (1 - sat));
    int q = (int)(val * (1 - f * sat));
    int t = (int)(val * (1 - (1 - f) * sat));

    switch(hi)
    {
        case 0:
            SetColor(v, t, p, 255);
            break;
        case 1:
            SetColor(q, v, p, 255);
            break;
        case 2:
            SetColor(p, v, t, 255);
            break;
        case 3:
            SetColor(p, q, v, 255);
            break;
        case 4:
            SetColor(t, p, v, 255);
            break;
        default:
            SetColor(v, p, q, 255);
            break;
    }
}

bool AEOIAFColor::InvalidChannel(int channel)
{
    return channel < 0 || channel > 255;
}

float AEOIAFColor::GetHue() const
{
    //We have a shade of gray, so it has no hue
    if(color.r == color.g && color.g == color.b)
        return 0;

    float maximum = max(max(color.r, color.g), color.b);
    float minimum = min(min(color.r, color.g), color.b);

    float r = (maximum - color.r) / (maximum - minimum);
    float g = (maximum - color.g) / (maximum - minimum);
    float b = (maximum - color.b) / (maximum - minimum);

    float hue;

    if (color.r == maximum)
        hue = 60 * (b - g);
    else if (color.g == maximum)
        hue = 60 * (2 +(r - b));
    else if (color.b == maximum)
        hue = 60 * (4 + (g - r));
    else
        hue = 0;

    if (hue >= 360)
        hue = hue - 360;
    if (hue < 0)
        hue = hue + 360;

    return hue;
}

float AEOIAFColor::GetSaturation() const
{
    float maximum = max(max(color.r, color.g), color.b);
    float minimum = min(min(color.r, color.g), color.b);

    return (maximum - minimum) / maximum;
}

float AEOIAFColor::GetValue() const
{
    return max(max(color.r, color.g), color.b) / 255;
}

/*STATIC COLORS*/
AEOIAFColor AEOIAFColor::AliceBlue()
{
    return AEOIAFColor(240, 248, 255, 255);
}

AEOIAFColor AEOIAFColor::AntiqueWhite()
{
    return AEOIAFColor(250, 235, 215, 255);
}

AEOIAFColor AEOIAFColor::Aqua()
{
    return AEOIAFColor(0, 255, 255, 255);
}

AEOIAFColor AEOIAFColor::Aquamarine()
{
    return AEOIAFColor(127, 255, 212, 255);
}

AEOIAFColor AEOIAFColor::Azure()
{
    return AEOIAFColor(0, 127, 255, 255);
}

AEOIAFColor AEOIAFColor::Beige()
{
    return AEOIAFColor(245, 245, 220, 255);
}

AEOIAFColor AEOIAFColor::Bisque()
{
    return AEOIAFColor(255, 228, 196, 255);
}

AEOIAFColor AEOIAFColor::Black()
{
    return AEOIAFColor(0, 0, 0, 255);
}

AEOIAFColor AEOIAFColor::BlanchedAlmond()
{
    return AEOIAFColor(255, 235, 205, 255);
}

AEOIAFColor AEOIAFColor::Blue()
{
    return AEOIAFColor(0, 0, 255, 255);
}

AEOIAFColor AEOIAFColor::BlueViolet()
{
    return AEOIAFColor(138, 43, 226, 255);
}

AEOIAFColor AEOIAFColor::Brown()
{
    return AEOIAFColor(165, 42, 42, 255);
}

AEOIAFColor AEOIAFColor::BurlyWood()
{
    return AEOIAFColor(222, 184, 135, 255);
}

AEOIAFColor AEOIAFColor::CadetBlue()
{
    return AEOIAFColor(95, 158, 160, 255);
}

AEOIAFColor AEOIAFColor::Chartreuse()
{
    return AEOIAFColor(127, 255, 0, 255);
}

AEOIAFColor AEOIAFColor::Chocolate()
{
    return AEOIAFColor(210, 105, 30, 255);
}

AEOIAFColor AEOIAFColor::Coral()
{
    return AEOIAFColor(255, 127, 80, 255);
}

AEOIAFColor AEOIAFColor::CornflowerBlue()
{
    return AEOIAFColor(100, 149, 237, 255);
}

AEOIAFColor AEOIAFColor::Cornsilk()
{
    return AEOIAFColor(255, 248, 220, 255);
}

AEOIAFColor AEOIAFColor::Crimson()
{
    return AEOIAFColor(220, 20, 60, 255);
}

AEOIAFColor AEOIAFColor::Cyan()
{
    return AEOIAFColor(0, 255, 255, 255);
}

AEOIAFColor AEOIAFColor::DarkBlue()
{
    return AEOIAFColor(0, 0, 139, 255);
}

AEOIAFColor AEOIAFColor::DarkCyan()
{
    return AEOIAFColor(0, 139, 139, 255);
}

AEOIAFColor AEOIAFColor::DarkGoldenrod()
{
    return AEOIAFColor(184, 134, 11, 255);
}

AEOIAFColor AEOIAFColor::DarkGray()
{
    return AEOIAFColor(169, 169, 169, 255);
}

AEOIAFColor AEOIAFColor::DarkGreen()
{
    return AEOIAFColor(0, 100, 0, 255);
}

AEOIAFColor AEOIAFColor::DarkKhaki()
{
    return AEOIAFColor(189, 183, 107, 255);
}

AEOIAFColor AEOIAFColor::DarkMagenta()
{
    return AEOIAFColor(139, 0, 139, 255);
}

AEOIAFColor AEOIAFColor::DarkOliveGreen()
{
    return AEOIAFColor(85, 107, 47, 255);
}

AEOIAFColor AEOIAFColor::DarkOrange()
{
    return AEOIAFColor(255, 140, 0, 255);
}

AEOIAFColor AEOIAFColor::DarkOrchid()
{
    return AEOIAFColor(153, 50, 204, 255);
}

AEOIAFColor AEOIAFColor::DarkRed()
{
    return AEOIAFColor(139, 0, 0, 255);
}

AEOIAFColor AEOIAFColor::DarkSalmon()
{
    return AEOIAFColor(233, 150, 122, 255);
}

AEOIAFColor AEOIAFColor::DarkSeaGreen()
{
    return AEOIAFColor(143, 188, 143, 255);
}

AEOIAFColor AEOIAFColor::DarkSlateBlue()
{
    return AEOIAFColor(72, 61, 139, 255);
}

AEOIAFColor AEOIAFColor::DarkSlateGrey()
{
    return AEOIAFColor(47, 79, 79, 255);
}

AEOIAFColor AEOIAFColor::DarkTurquoise()
{
    return AEOIAFColor(0, 206, 209, 255);
}

AEOIAFColor AEOIAFColor::DarkViolet()
{
    return AEOIAFColor(148, 0, 211, 255);
}

AEOIAFColor AEOIAFColor::DeepPink()
{
    return AEOIAFColor(255, 20, 147, 255);
}

AEOIAFColor AEOIAFColor::DeepSkyBlue()
{
    return AEOIAFColor(0, 191, 255, 255);
}

AEOIAFColor AEOIAFColor::DimGray()
{
    return AEOIAFColor(105, 105, 105, 255);
}

AEOIAFColor AEOIAFColor::DodgerBlue()
{
    return AEOIAFColor(30, 144, 255, 255);
}

AEOIAFColor AEOIAFColor::Firebrick()
{
    return AEOIAFColor(178, 34, 34, 255);
}

AEOIAFColor AEOIAFColor::FloralWhite()
{
    return AEOIAFColor(255, 250, 240, 255);
}

AEOIAFColor AEOIAFColor::Fuchsia()
{
    return AEOIAFColor(255, 0, 255, 255);
}

AEOIAFColor AEOIAFColor::Gainsboro()
{
    return AEOIAFColor(220, 220, 220, 255);
}

AEOIAFColor AEOIAFColor::GhostWhite()
{
    return AEOIAFColor(248, 248, 255, 255);
}

AEOIAFColor AEOIAFColor::Gold()
{
    return AEOIAFColor(255, 215, 0, 255);
}

AEOIAFColor AEOIAFColor::Goldenrod()
{
    return AEOIAFColor(218, 165, 32, 255);
}

AEOIAFColor AEOIAFColor::Gray()
{
    return AEOIAFColor(128, 128, 128, 255);
}

AEOIAFColor AEOIAFColor::Green()
{
    return AEOIAFColor(0, 128, 0, 255);
}

AEOIAFColor AEOIAFColor::GreenYellow()
{
    return AEOIAFColor(173, 255, 47, 255);
}

AEOIAFColor AEOIAFColor::Honeydew()
{
    return AEOIAFColor(240, 255, 240, 255);
}

AEOIAFColor AEOIAFColor::HotPink()
{
    return AEOIAFColor(255, 105, 180, 255);
}

AEOIAFColor AEOIAFColor::IndianRed()
{
    return AEOIAFColor(205, 92, 92, 255);
}

AEOIAFColor AEOIAFColor::Indigo()
{
    return AEOIAFColor(75, 0, 130, 255);
}

AEOIAFColor AEOIAFColor::Ivory()
{
    return AEOIAFColor(255, 255, 240, 255);
}

AEOIAFColor AEOIAFColor::Khaki()
{
    return AEOIAFColor(240, 230, 140, 255);
}

AEOIAFColor AEOIAFColor::Lavender()
{
    return AEOIAFColor(230, 230, 250, 255);
}

AEOIAFColor AEOIAFColor::LavenderBush()
{
    return AEOIAFColor(255, 240, 245, 255);
}

AEOIAFColor AEOIAFColor::LawnGreen()
{
    return AEOIAFColor(124, 252, 0, 255);
}

AEOIAFColor AEOIAFColor::LemonChiffon()
{
    return AEOIAFColor(255, 250, 205, 255);
}

AEOIAFColor AEOIAFColor::LightBlue()
{
    return AEOIAFColor(173, 216, 230, 255);
}

AEOIAFColor AEOIAFColor::LightCoral()
{
    return AEOIAFColor(240, 128, 128, 255);
}

AEOIAFColor AEOIAFColor::LightCyan()
{
    return AEOIAFColor(224, 255, 255, 255);
}

AEOIAFColor AEOIAFColor::LightGoldenrod()
{
    return AEOIAFColor(250, 250, 210, 255);
}

AEOIAFColor AEOIAFColor::LightGray()
{
    return AEOIAFColor(211, 211, 211, 255);
}

AEOIAFColor AEOIAFColor::LightGreen()
{
    return AEOIAFColor(144, 238, 144, 255);
}

AEOIAFColor AEOIAFColor::LightPink()
{
    return AEOIAFColor(255, 182, 193, 255);
}

AEOIAFColor AEOIAFColor::LightSalmon()
{
    return AEOIAFColor(255, 160, 122, 255);
}

AEOIAFColor AEOIAFColor::LightSeaGreen()
{
    return AEOIAFColor(32, 178, 170, 255);
}

AEOIAFColor AEOIAFColor::LightSkyBlue()
{
    return AEOIAFColor(135, 206, 250, 255);
}

AEOIAFColor AEOIAFColor::LightSlateGray()
{
    return AEOIAFColor(119, 136, 153, 255);
}

AEOIAFColor AEOIAFColor::LightSteelBlue()
{
    return AEOIAFColor(176, 196, 222, 255);
}

AEOIAFColor AEOIAFColor::LightYellow()
{
    return AEOIAFColor(255, 255, 224, 255);
}

AEOIAFColor AEOIAFColor::Lime()
{
    return AEOIAFColor(0, 255, 0, 255);
}

AEOIAFColor AEOIAFColor::LimeGreen()
{
    return AEOIAFColor(50, 205, 50, 255);
}

AEOIAFColor AEOIAFColor::Linen()
{
    return AEOIAFColor(250, 240, 230, 255);
}

AEOIAFColor AEOIAFColor::Magenta()
{
    return AEOIAFColor(255, 0, 255, 255);
}

AEOIAFColor AEOIAFColor::Maroon()
{
    return AEOIAFColor(128, 0, 0, 255);
}

AEOIAFColor AEOIAFColor::MediumAquamarine()
{
    return AEOIAFColor(102, 205, 170, 255);
}

AEOIAFColor AEOIAFColor::MediumBlue()
{
    return AEOIAFColor(0, 0, 205, 255);
}

AEOIAFColor AEOIAFColor::MediumOrchid()
{
    return AEOIAFColor(186, 85, 211, 255);
}

AEOIAFColor AEOIAFColor::MediumPurple()
{
    return AEOIAFColor(147, 112, 219, 255);
}

AEOIAFColor AEOIAFColor::MediumSeaGreen()
{
    return AEOIAFColor(60, 179, 113, 255);
}

AEOIAFColor AEOIAFColor::MediumSlateBlue()
{
    return AEOIAFColor(123, 104, 238, 255);
}

AEOIAFColor AEOIAFColor::MediumSpringGreen()
{
    return AEOIAFColor(0, 250, 154, 255);
}

AEOIAFColor AEOIAFColor::MediumTurquoise()
{
    return AEOIAFColor(72, 209, 204, 255);
}

AEOIAFColor AEOIAFColor::MediumVioletRed()
{
    return AEOIAFColor(199, 21, 133, 255);
}

AEOIAFColor AEOIAFColor::MidnightBlue()
{
    return AEOIAFColor(0, 0, 205, 255);
}

AEOIAFColor AEOIAFColor::MintCream()
{
    return AEOIAFColor(245, 255, 250, 255);
}

AEOIAFColor AEOIAFColor::MistyRose()
{
    return AEOIAFColor(255, 228, 225, 255);
}

AEOIAFColor AEOIAFColor::Moccasin()
{
    return AEOIAFColor(255, 228, 181, 255);
}

AEOIAFColor AEOIAFColor::NavajoWhite()
{
    return AEOIAFColor(255, 222, 173, 255);
}

AEOIAFColor AEOIAFColor::Navy()
{
    return AEOIAFColor(0, 0, 128, 255);
}

AEOIAFColor AEOIAFColor::OldLace()
{
    return AEOIAFColor(253, 245, 230, 255);
}

AEOIAFColor AEOIAFColor::Olive()
{
    return AEOIAFColor(128, 128, 0, 255);
}

AEOIAFColor AEOIAFColor::OliveDrab()
{
    return AEOIAFColor(107, 142, 35, 255);
}

AEOIAFColor AEOIAFColor::Orange()
{
    return AEOIAFColor(255, 165, 0, 255);
}

AEOIAFColor AEOIAFColor::OrangeRed()
{
    return AEOIAFColor(255, 69, 0, 255);
}

AEOIAFColor AEOIAFColor::Orchid()
{
    return AEOIAFColor(218, 112, 214, 255);
}

AEOIAFColor AEOIAFColor::PaleGoldenrod()
{
    return AEOIAFColor(238, 232, 170, 255);
}

AEOIAFColor AEOIAFColor::PaleGreen()
{
    return AEOIAFColor(152, 251, 152, 255);
}

AEOIAFColor AEOIAFColor::PaleTurquoise()
{
    return AEOIAFColor(175, 238, 238, 255);
}

AEOIAFColor AEOIAFColor::PaleVioletRed()
{
    return AEOIAFColor(219, 112, 147, 255);
}

AEOIAFColor AEOIAFColor::PapayaWhip()
{
    return AEOIAFColor(255, 239, 213, 255);
}

AEOIAFColor AEOIAFColor::PeachPuff()
{
    return AEOIAFColor(255, 218, 185, 255);
}

AEOIAFColor AEOIAFColor::Peru()
{
    return AEOIAFColor(205, 133, 63, 255);
}

AEOIAFColor AEOIAFColor::Pink()
{
    return AEOIAFColor(255, 192, 203, 255);
}

AEOIAFColor AEOIAFColor::Plum()
{
    return AEOIAFColor(221, 160, 221, 255);
}

AEOIAFColor AEOIAFColor::PowderBlue()
{
    return AEOIAFColor(176, 224, 230, 255);
}

AEOIAFColor AEOIAFColor::Purple()
{
    return AEOIAFColor(128, 0, 128, 255);
}

AEOIAFColor AEOIAFColor::Red()
{
    return AEOIAFColor(255, 0, 0, 255);
}

AEOIAFColor AEOIAFColor::RosyBrown()
{
    return AEOIAFColor(188, 143, 143, 255);
}

AEOIAFColor AEOIAFColor::RoyalBlue()
{
    return AEOIAFColor(65, 105, 225, 255);
}

AEOIAFColor AEOIAFColor::SaddleBrown()
{
    return AEOIAFColor(139, 69, 19, 255);
}

AEOIAFColor AEOIAFColor::Salmon()
{
    return AEOIAFColor(250, 128, 114, 255);
}

AEOIAFColor AEOIAFColor::SandyBrown()
{
    return AEOIAFColor(244, 164, 96, 255);
}

AEOIAFColor AEOIAFColor::SeaGreen()
{
    return AEOIAFColor(46, 139, 87, 255);
}

AEOIAFColor AEOIAFColor::SeaShell()
{
    return AEOIAFColor(255, 245, 238, 255);
}

AEOIAFColor AEOIAFColor::Sienna()
{
    return AEOIAFColor(160, 82, 45, 255);
}

AEOIAFColor AEOIAFColor::Silver()
{
    return AEOIAFColor(192, 192, 192, 255);
}

AEOIAFColor AEOIAFColor::SkyBlue()
{
    return AEOIAFColor(135, 206, 235, 255);
}

AEOIAFColor AEOIAFColor::SlateBlue()
{
    return AEOIAFColor(106, 90, 205, 255);
}

AEOIAFColor AEOIAFColor::SlateGray()
{
    return AEOIAFColor(112, 128, 144, 255);
}

AEOIAFColor AEOIAFColor::Snow()
{
    return AEOIAFColor(255, 250, 250, 255);
}

AEOIAFColor AEOIAFColor::SpringGreen()
{
    return AEOIAFColor(0, 255, 127, 255);
}

AEOIAFColor AEOIAFColor::SteelBlue()
{
    return AEOIAFColor(70, 130, 180, 255);
}

AEOIAFColor AEOIAFColor::Tan()
{
    return AEOIAFColor(210, 180, 140, 255);
}

AEOIAFColor AEOIAFColor::Teal()
{
    return AEOIAFColor(0, 128, 128, 255);
}

AEOIAFColor AEOIAFColor::Thistle()
{
    return AEOIAFColor(216, 191, 216, 255);
}

AEOIAFColor AEOIAFColor::Tomato()
{
    return AEOIAFColor(255, 99, 71, 255);
}

AEOIAFColor AEOIAFColor::Transparent()
{
    return AEOIAFColor(0, 0, 0, 0);
}

AEOIAFColor AEOIAFColor::Turquoise()
{
    return AEOIAFColor(64, 224, 208, 255);
}

AEOIAFColor AEOIAFColor::Violet()
{
    return AEOIAFColor(238, 130, 238, 255);
}

AEOIAFColor AEOIAFColor::Wheat()
{
    return AEOIAFColor(245, 222, 179, 255);
}

AEOIAFColor AEOIAFColor::White()
{
    return AEOIAFColor(255, 255, 255, 255);
}

AEOIAFColor AEOIAFColor::WhiteSmoke()
{
    return AEOIAFColor(245, 245, 245, 255);
}

AEOIAFColor AEOIAFColor::Yellow()
{
    return AEOIAFColor(255, 255, 0, 255);
}

AEOIAFColor AEOIAFColor::YellowGreen()
{
    return AEOIAFColor(154, 205, 50, 255);
}
