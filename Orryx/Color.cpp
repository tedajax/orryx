#include "Color.h"

namespace orx
{
    const Color Color::cRed = Color::Red();
    const Color Color::cGreen = Color::Green();
    const Color Color::cBlue = Color::Blue();
    const Color Color::cDarkRed = Color::DarkRed();
    const Color Color::cDarkGreen = Color::DarkGreen();
    const Color Color::cDarkBlue = Color::DarkBlue();
    const Color Color::cCyan = Color::Cyan();
    const Color Color::cMagenta = Color::Magenta();
    const Color Color::cYellow = Color::Yellow();
    const Color Color::cOrange = Color::Orange();
    const Color Color::cPurple = Color::Purple();
    const Color Color::cWhite = Color::White();
    const Color Color::cBlack = Color::Black();
    const Color Color::cLightGrey = Color::LightGrey();
    const Color Color::cGrey = Color::Grey();
    const Color Color::cDarkGrey = Color::DarkGrey();
    const Color Color::cClear = Color::Clear();

    Color Color::FromRGBA(u32 color)
    {
        f32 r = ((color >> 24) & 0xFF) / 255.f;
        f32 g = ((color >> 16) & 0xFF) / 255.f;
        f32 b = ((color >> 8) & 0xFF) / 255.f;
        f32 a = ((color >> 0) & 0xFF) / 255.f;

        Color result = { r, g, b, a };
        return result;
    }

    Color Color::FromARGB(u32 color)
    {
        f32 r = ((color >> 16) & 0xFF) / 255.f;
        f32 g = ((color >> 8) & 0xFF) / 255.f;
        f32 b = ((color >> 0) & 0xFF) / 255.f;
        f32 a = ((color >> 24) & 0xFF) / 255.f;

        Color result = { r, g, b, a };
        return result;
    }

    Color Color::FromABGR(u32 color)
    {
        f32 r = ((color >> 0) & 0xFF) / 255.f;
        f32 g = ((color >> 8) & 0xFF) / 255.f;
        f32 b = ((color >> 16) & 0xFF) / 255.f;
        f32 a = ((color >> 24) & 0xFF) / 255.f;

        Color result = { r, g, b, a };
        return result;
    }

    Color Color::FromHSV(f32 h, f32 s, f32 v, f32 a /* = 1.f */)
    {
        while (h > 360.0f) { h -= 360.0f; }
        while (h < 0.0f) { h += 360.0f; }
        float c = v * s;
        float x = c * (1.0f - fabs(fmod((h / 60.0f), 2.f) - 1.0f));
        float m = v - c;
        float rp = 0.0f, gp = 0.0f, bp = 0.0f;
        if (h < 60)
        {
            rp = c;
            gp = x;
        }
        else if (h < 120)
        {
            rp = x;
            gp = c;
        }
        else if (h < 180)
        {
            gp = c;
            bp = x;
        }
        else if (h < 240)
        {
            gp = x;
            bp = c;
        }
        else if (h < 300)
        {
            rp = x;
            bp = c;
        }
        else if (h < 360)
        {
            rp = c;
            bp = x;
        }
        f32 r = rp + m;
        f32 g = gp + m;
        f32 b = bp + m;
        Color result = {
            r, g, b, a
        };
        return result;
    }
}