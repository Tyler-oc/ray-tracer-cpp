#include "utils.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main()
{

    // world
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(.8, .8, 0));
    auto material_center = make_shared<lambertian>(color(.3, .2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_bubble = make_shared<dielectric>(1.0 / 1.5);
    auto material_right = make_shared<metal>(color(.4, .8, .2), .6);

    world.add(make_shared<sphere>(point3(0, -100.5, -1.0), 100, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1.2), .5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), .5, material_left));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3(1.0, 0, -1.0), .5, material_right));

    // camera setup

    camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 100;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    camera.render(world);

    return 0;
}