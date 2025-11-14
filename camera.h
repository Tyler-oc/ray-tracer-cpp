#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "utils.h"

class camera
{
public:
    // image

    double aspect_ratio = 16.0 / 9.0; // width to height
    int image_width = 256;
    int samples_per_pixel = 10;

    void render(const hittable &world)
    {
        initialize();
        // render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) // go column wise
        {
            std::clog << "\rScanlines remaining: " << image_height - j - 1 << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) // row wise
            {
                color pixel_color(0, 0, 0); // black

                // sample the surrounding points and take the average to blend and not get a stair step look on objects
                for (int samples = 0; samples < samples_per_pixel; samples++)
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }

                write_color(std::cout, pixel_samples_scale * pixel_color); // average the sample colors
            }
        }

        std::clog << "\rDone. \n";
    }

private:
    int image_height;
    double pixel_samples_scale; // color scale factor for sum of sampled pixels
    point3 center;              // center point
    point3 pixel00_loc;         // location of pixel 0 0
    vec3 pixel_delta_u;         // offset to pixel to the right
    vec3 pixel_delta_v;         // offset to pixel down

    void initialize()
    {
        // calc image height and ensure at least 1

        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height; // realistically this should be higher for good results, like 50

        pixel_samples_scale = 1.0 / samples_per_pixel; // term to average samples

        // Distance from the projection plane to the camera origin.
        auto focal_length = 1.0;

        // Height of the viewport in world units (at the projection plane).
        auto viewport_height = 2.0;

        // Compute the viewport width to preserve the image aspect ratio.
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Camera position in world space; placed at the origin.
        center = point3(0, 0, 0);

        // horizontal and vertical vectors down viewport edges
        auto viewport_u = vec3(viewport_width, 0, 0);   // horizontal
        auto viewport_v = vec3(0, -viewport_height, 0); // vertical

        pixel_delta_u = viewport_u / image_width;  // displacement per pixel horizontal
        pixel_delta_v = viewport_v / image_height; // displacement per pixel vertical

        // location of upper left for viewport and pixel
        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j)
    {
        auto offset = sample_square();
        // get random point near pixel at i, j
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;                       // originates at center
        auto ray_direction = pixel_sample - ray_origin; // get direction from origin to sample

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const
    {
        // returns vector to random point in unit square of length 1 around origin
        return vec3(random_double() - .5, random_double() - .5, 0);
    }

    color ray_color(const ray &r, const hittable &world) const
    {
        hit_record rec;
        // check if the ray hits an object in the world
        if (world.hit(r, interval(0, infinity), rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1)); // if it hits, set the color accordingly.
        }
        // linear blend of blue and white: blendVal = (1-a) * startVal + a*endVal
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif