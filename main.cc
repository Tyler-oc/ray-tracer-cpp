#include "utils.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main()
{
    // camera

    camera camera;

    // world
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera.render(world);

    return 0;
}