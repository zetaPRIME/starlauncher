#pragma once

namespace starlight {
    class Color {
    private:
        //
        
    public:
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
        
        Color() { }
        Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }
        Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) { }
        ~Color() { }
        
        inline bool operator == (const Color& o) const { return r == o.r && g == o.g && b == o.b && a == o.a; }
        inline bool operator != (const Color& o) const { return r != o.r || g != o.g || b != o.b || a != o.a; }
        
        inline Color operator * (const Color& o) const { return Color(r * o.r, g * o.g, b * o.b, a * o.a); }
        
        // hmm. I guess this will do ¯\_(ツ)_/¯ don't really want to force cstdint
        inline operator const unsigned int() { return (((((int)(a*255))&0xFF)<<24) | ((((int)(b*255))&0xFF)<<16) | ((((int)(g*255))&0xFF)<<8) | ((((int)(r*255))&0xFF)<<0)); }

    };
}
