#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

// #include "vector.h" // lmao i do not need your bitchass
typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Sphere {
    Vec3 center;
    float radius;
} Sphere;

typedef struct Ray {
    Vec3 origin;
    Vec3 direction;
} Ray;

static inline float lerp(float v0, float v1, float t);
static inline Vec3 unit_vector(Vec3 u);
static inline Vec3 ray_at(Vec3 origin, Vec3 direction, float t);
static inline float dot(Vec3 u, Vec3 v);
static inline bool ray_hits_sphere(Ray ray, Sphere sphere);

int main()
{
    size_t width = 640;
    size_t height = 480;

    float viewport_height = 2;
    float viewport_width = viewport_height * ((double) width/height);

    float focal_length = 1;
    Vec3 camera_center = {0, 0, 0};
    Vec3 viewport_u = {viewport_width, 0, 0}; // relative
    Vec3 viewport_v = {0, -viewport_height, 0}; // relative

    Vec3 pixel_delta_u = {
        (float) viewport_u.x/width,
        (float) viewport_u.y/width,
        (float) viewport_u.z/width,
    }; // relative

    Vec3 pixel_delta_v = {
        (float) viewport_v.x/height,
        (float) viewport_v.y/height,
        (float) viewport_v.z/height,
    }; // relative

    Vec3 viewport_topleft = {
        camera_center.x - 0            - 0.5f * (viewport_u.x + viewport_v.x),
        camera_center.y - 0            - 0.5f * (viewport_u.y + viewport_v.y),
        camera_center.z - focal_length - 0.5f * (viewport_u.z + viewport_v.z),
    }; // absolute

    Vec3 pixel00 = {
        viewport_topleft.x + 0.5f * (pixel_delta_u.x + pixel_delta_v.x),
        viewport_topleft.y + 0.5f * (pixel_delta_u.y + pixel_delta_v.y),
        viewport_topleft.z + 0.5f * (pixel_delta_u.z + pixel_delta_v.z),
    }; // absolute

    Sphere sphere = {
        .center = {0, 0, -1},
        .radius = 0.3f,
    };

    printf("P3\n");
    printf("%zu %zu\n", width, height);
    printf("255\n");
    for (size_t i = 0; i < height; i++) {
        fprintf(stderr, "\rProgress: %.0f%%", 100 * ((float)i / (height-1)));
        for (size_t j = 0; j < width; j++) {
            Vec3 pixel_center = {
                (pixel00.x + (i * pixel_delta_v.x) + (j * pixel_delta_u.x)),
                (pixel00.y + (i * pixel_delta_v.y) + (j * pixel_delta_u.y)),
                (pixel00.z + (i * pixel_delta_v.z) + (j * pixel_delta_u.z)),
            }; // absolute

            // camera_center + ray_dir = pixel_center
            Vec3 ray_dir = {
                pixel_center.x - camera_center.x,
                pixel_center.y - camera_center.y,
                pixel_center.z - camera_center.z,
            };

            Vec3 ray_origin = camera_center;
            Ray ray = {
                .origin = ray_origin,
                .direction = ray_dir,
            };

            Vec3 color = {0};

            if (ray_hits_sphere(ray, sphere)) {
                color = (Vec3) {0, 0, 1};
            } else {
                // draw gradient based on y of the ray
                Vec3 unit_ray_dir = unit_vector(ray_dir);
                float normalised_y = 0.5f * (unit_ray_dir.y + 1.0);

                color = (Vec3) {
                    lerp(1, 0.5, normalised_y),
                    lerp(1, 0.7, normalised_y),
                    lerp(1, 1.0, normalised_y),
                };
            }

            int r = 255 * color.x;
            int g = 255 * color.y;
            int b = 255 * color.z;
            printf("%d %d %d\n", r, g, b);
        }
    }

    fputc('\n', stderr);
    return 0;
}

// source: wikipedia
static inline float lerp(float v0, float v1, float t) {
  return v0 + t * (v1 - v0);
}

static inline Vec3 unit_vector(Vec3 u)
{
    float inv_distance = (float) 1/sqrtf(u.x*u.x + u.y*u.y + u.z*u.z);
    return (Vec3) {
        u.x * inv_distance,
        u.y * inv_distance,
        u.z * inv_distance,
    };
}

static inline Vec3 ray_at(Vec3 origin, Vec3 direction, float t)
{
    return (Vec3) {
        origin.x + t * direction.x,
        origin.y + t * direction.y,
        origin.z + t * direction.z,
    };
}

static inline float dot(Vec3 u, Vec3 v)
{
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

static inline bool ray_hits_sphere(Ray ray, Sphere sphere)
{
    Vec3 c_minus_p = {
        sphere.center.x - ray.origin.x,
        sphere.center.y - ray.origin.y,
        sphere.center.z - ray.origin.z,
    };

    float a = dot(ray.direction, ray.direction);
    float b = -2 * dot(ray.direction, c_minus_p);
    float c = dot(c_minus_p, c_minus_p) - sphere.radius * sphere.radius;

    float determinant = b*b - 4*a*c;
    return determinant >= 0;
}
