#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

// another alias
using color = vec3;

// transforming into gamma 2 space (put to power of 2 to undo)

double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
    {
        return std::sqrt(linear_component);
    }
    return 0;
}

void write_color(std::ostream &out, const color &pixel_color)
{
    // colors in gamma 2 space
    auto r = linear_to_gamma(pixel_color.x());
    auto g = linear_to_gamma(pixel_color.y());
    auto b = linear_to_gamma(pixel_color.z());

    static const interval intensity = interval(0, .999);
    // translate to 255 range
    int rbyte = int(255.999 * intensity.clamp(r));
    int gbyte = int(255.999 * intensity.clamp(g));
    int bbyte = int(255.999 * intensity.clamp(b));

    // write pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

color multiply_albedo(color albedo, color r_color)
{
    return color(albedo.x() * r_color.x(), albedo.y() * r_color.y(), albedo.z() * r_color.z());
}

#endif