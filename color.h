#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

// another alias
using color = vec3;

void write_color(std::ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // translate to 255 range
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // write pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif