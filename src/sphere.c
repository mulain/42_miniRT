#include <stdio.h>
#include <math.h>

//gcc sphere.c -lm && ./a.out

typedef struct {
    double x;
    double y;
    double z;
} Vector3;

double dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double distance(Vector3 a, Vector3 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

Vector3 Vector3Subtract(Vector3 a, Vector3 b)
{
	return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

void Vector3Normalize(Vector3 *v)
{
	double len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

int sphere_intersection(Vector3 center, double radius, Vector3 ray_origin, Vector3 ray_direction, double* t1, double* t2) {
    double a = dot(ray_direction, ray_direction);
    double b = 2 * dot(ray_direction, Vector3Subtract(ray_origin, center));
    double c = dot(Vector3Subtract(ray_origin, center), Vector3Subtract(ray_origin, center)) - pow(radius, 2);
    double discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0) {
        return 0; // no intersection
    } else if (discriminant == 0) {
        *t1 = -b / (2 * a);
        return 1;
    } else {
        double t_min = (-b - sqrt(discriminant)) / (2 * a);
        double t_max = (-b + sqrt(discriminant)) / (2 * a);
        if (t_max < 0) {
            return 0; // sphere behind the ray
        } else if (t_min >= 0) {
            *t1 = t_min;
            *t2 = t_max;
            return 2;
        } else {
            *t1 = 0;
            *t2 = t_max;
            return 1;
        }
    }
}

int main() {
    Vector3 center = {1.0, 2.0, 3.0};
    double radius = 4.0;
    Vector3 ray_origin = {0.0, 0.0, 0.0};
    Vector3 ray_direction = {1.0, 1.0, 1.0};
    Vector3Normalize(&ray_direction);
    double t1, t2;
    int num_intersections = sphere_intersection(center, radius, ray_origin, ray_direction, &t1, &t2);
    if (num_intersections == 0) {
        printf("No intersection.\n");
    } else if (num_intersections == 1) {
        printf("One intersection at distance %lf.\n", t1);
    } else {
        printf("Two intersections at distances %lf and %lf.\n", t1, t2);
    }
    return 0;
}