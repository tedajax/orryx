#ifndef ORRYX_COLOR_H
#define ORRYX_COLOR_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

namespace orx
{
    struct Color
    {
        Color()
        : r(0.f), g(0.f), b(0.f), a(1.f)
        {
        }

        Color(const Color& other)
            : r(other.r), g(other.g), b(other.b), a(other.a)
        {
        }

        Color(f32 red, f32 green, f32 blue, f32 alpha = 1.f)
            : r(red), g(green), b(blue), a(alpha)
        {
        }

        static Color FromRGBA(u32 color);
        static Color FromARGB(u32 color);
        static Color FromABGR(u32 color);
        static Color FromHSV(f32 h, f32 s, f32 v, f32 a = 1.f);

        static const Color Red() { return Color::FromRGBA(0xFF0000FF); }
        static const Color Green() { return Color::FromRGBA(0x00FF00FF); }
        static const Color Blue() { return Color::FromRGBA(0x0000ffFF); }

        static const Color DarkRed() { return Color::FromRGBA(0x7F0000FF); }
        static const Color DarkGreen() { return Color::FromRGBA(0x007F00FF); }
        static const Color DarkBlue() { return Color::FromRGBA(0x00007FFF); }

        static const Color Cyan() { return Color::FromRGBA(0x00FFFFFF); }
        static const Color Magenta() { return Color::FromRGBA(0xFF00FFFF); }
        static const Color Yellow() { return Color::FromRGBA(0xFFFF00FF); }

        static const Color Orange() { return Color::FromRGBA(0xFF6600FF); }
        static const Color Purple() { return Color::FromRGBA(0x6600FFFF); }

        static const Color White() { return Color::FromRGBA(0xFFFFFFFF); }
        static const Color Black() { return Color::FromRGBA(0x000000FF); }
        static const Color LightGrey() { return Color::FromRGBA(0xBDBDBDFF); }
        static const Color Grey() { return Color::FromRGBA(0x7F7F7FFF); }
        static const Color DarkGrey() { return Color::FromRGBA(0x3F3F3FFF); }
        static const Color Clear() { return Color::FromRGBA(0x00000000); }

        static const Color cRed;
        static const Color cGreen;
        static const Color cBlue;
        static const Color cDarkRed;
        static const Color cDarkGreen;
        static const Color cDarkBlue;
        static const Color cCyan;
        static const Color cMagenta;
        static const Color cYellow;
        static const Color cOrange;
        static const Color cPurple;
        static const Color cWhite;
        static const Color cBlack;
        static const Color cLightGrey;
        static const Color cGrey;
        static const Color cDarkGrey;
        static const Color cClear;

        f32 r, g, b, a;
    };
}

#endif