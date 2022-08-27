#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_writer.h"

Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, Sphere& sphere){
    float sphere_dist = std::numeric_limits<float>::max();
    if (!sphere.ray_intersect(orig, dir, sphere_dist)) {
        return Vec3f(0.2, 0.7, 0.8);
    }
    return Vec3f(0.4, 0.4, 0.3);
}

void render() {
    const int width = 1024;
    const int height = 768;
    std::vector<Pixel> framebuffer(width*height);
    float fov = 108 * M_PI / 180;
    Sphere sphere(Vec3f(0,0,-2),1);

    for(size_t j = 0; j < height; j++){
        for(size_t i = 0; i < width; i++){
            float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i+j*width] = Pixel(cast_ray(Vec3f(0,0,0), dir, sphere).multiply(255));
        }
    }
    stbi_write_bmp("out.bmp", width, height, 3, framebuffer.data());
}

int main(void) {
    render();
    return 0;
}