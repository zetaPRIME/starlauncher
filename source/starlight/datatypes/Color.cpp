#include "Color.h"

using starlight::Color;

//
//#define RGBA8(r, g, b, a) ((((a)&0xFF)<<24) | (((b)&0xFF)<<16) | (((g)&0xFF)<<8) | (((r)&0xFF)<<0))

//#define RGBA8_GET_R(c) (((c) >>  0) & 0xFF)
//#define RGBA8_GET_G(c) (((c) >>  8) & 0xFF)
//#define RGBA8_GET_B(c) (((c) >> 16) & 0xFF)
//#define RGBA8_GET_A(c) (((c) >> 24) & 0xFF)

const Color Color::white = Color(1,1,1);