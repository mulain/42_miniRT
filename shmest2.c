#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y, z;
} Vec3;

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

double intersectCylinder(Ray ray) {
    // Transform the ray to the cylinder's local coordinate system
    ray.origin.y -= 1; // Translate the origin to the top of the cylinder
    ray.direction.y = -ray.direction.y; // Invert the y-component of the direction

    // Calculate the coefficients of the quadratic equation for t
    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2 * (ray.direction.x * ray.origin.x + ray.direction.z * ray.origin.z);
    double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;

    // Solve the quadratic equation for t
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // The ray does not intersect the cylinder
        return -1;
    }
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);

    // Check if the intersection point is within the height of the cylinder
    double y1 = ray.origin.y + t1 * ray.direction.y;
    double y2 = ray.origin.y + t2 * ray.direction.y;
    if (y1 < -1 || y1 > 1) {
        t1 = -1;
    }
    if (y2 < -1 || y2 > 1) {
        t2 = -1;
    }

    // Return the closest intersection point
    if (t1 < 0 && t2 < 0) {
        // The cylinder is behind the ray
        return -1;
    } else if (t1 < 0) {
        return t2;
    } else if (t2 < 0) {
        return t1;
    } else {
        return fmin(t1, t2);
    }
}

int main() {
    // Example usage
    Ray ray = { {0, 0, -5}, {0, 0, 1} };
    double t = intersectCylinder(ray);
    if (t >= 0) {
        Vec3 intersection = {
            ray.origin.x + t * ray.direction.x,
            ray.origin.y + t * ray.direction.y,
            ray.origin.z + t * ray.direction.z
        };
        printf("Intersection at (%f, %f, %f)\n", intersection.x, intersection.y, intersection.z);
    } else {
        printf("No intersection\n");
    }
    return 0;
}