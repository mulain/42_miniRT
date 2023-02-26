#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

typedef struct {
    Vec3 center;
    float radius;
    Vec3 axis;
} Cylinder;

// Calculate the intersection of a ray with a cylinder
// Returns the distance to the intersection point along the ray, or -1 if there is no intersection
float intersect_cylinder(Ray r, Cylinder c) {
    // Compute the direction vector of the ray projected onto the cylinder's axis
    Vec3 axis = c.axis;
    float r_dot_axis = r.direction.x * axis.x + r.direction.y * axis.y + r.direction.z * axis.z;
   
    Vec3 ray_dir_axis = {r_dot_axis * axis.x, r_dot_axis * axis.y, r_dot_axis * axis.z};

    // Compute the direction vector of the ray perpendicular to the cylinder's axis
    Vec3 ray_dir_perp = {r.direction.x - ray_dir_axis.x, r.direction.y - ray_dir_axis.y, r.direction.z - ray_dir_axis.z};

    // Compute the origin vector of the ray projected onto the cylinder's axis
    Vec3 oc = {r.origin.x - c.center.x, r.origin.y - c.center.y, r.origin.z - c.center.z};
    float oc_dot_axis = oc.x * axis.x + oc.y * axis.y + oc.z * axis.z;
    Vec3 ray_orig_axis = {oc_dot_axis * axis.x, oc_dot_axis * axis.y, oc_dot_axis * axis.z};

    // Compute the origin vector of the ray perpendicular to the cylinder's axis
    Vec3 ray_orig_perp = {oc.x - ray_orig_axis.x, oc.y - ray_orig_axis.y, oc.z - ray_orig_axis.z};

    // Compute the coefficients of the quadratic equation
    float a = ray_dir_perp.x * ray_dir_perp.x + ray_dir_perp.y * ray_dir_perp.y + ray_dir_perp.z * ray_dir_perp.z;
    float b = 2 * (ray_dir_perp.x * ray_orig_perp.x + ray_dir_perp.y * ray_orig_perp.y + ray_dir_perp.z * ray_orig_perp.z);
    float c1 = ray_orig_perp.x * ray_orig_perp.x + ray_orig_perp.y * ray_orig_perp.y + ray_orig_perp.z * ray_orig_perp.z - c.radius * c.radius;

    // Solve the quadratic equation
    float discriminant = b * b - 4 * a * c1;
    if (discriminant < 0) {
        // no intersection
        return -1;
    } else {
        // find the distance to the intersection point along the ray
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        if (t1 > 0 && t2 > 0) {
            return fmin(t1, t2) / r_dot_axis;
        } else if (t1 > 0) {
            return t1 / r_dot_axis;
        } else if (t2 > 0) {
            return t2 / r_dot_axis;
        } else {
            // both intersection distances are negative, no intersection
            return -1;
        }



#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

typedef struct {
    Vec3 center;
    float radius;
    Vec3 axis;
} Cylinder;

// Calculate the intersection of a ray with a cylinder
// Returns the distance to the intersection point along the ray, or -1 if there is no intersection
float intersect_cylinder(Ray r, Cylinder c) {
    // Compute the direction vector of the ray projected onto the cylinder's axis
    Vec3 axis = c.axis;
    float r_dot_axis = r.direction.x * axis.x + r.direction.y * axis.y + r.direction.z * axis.z;
    Vec3 ray_dir_axis = {r_dot_axis * axis.x, r_dot_axis * axis.y, r_dot_axis * axis.z};

    // Compute the direction vector of the ray perpendicular to the cylinder's axis
    Vec3 ray_dir_perp = {r.direction.x - ray_dir_axis.x, r.direction.y - ray_dir_axis.y, r.direction.z - ray_dir_axis.z};

    // Compute the origin vector of the ray projected onto the cylinder's axis
    Vec3 oc = {r.origin.x - c.center.x, r.origin.y - c.center.y, r.origin.z - c.center.z};
    float oc_dot_axis = oc.x * axis.x + oc.y * axis.y + oc.z * axis.z;
    Vec3 ray_orig_axis = {oc_dot_axis * axis.x, oc_dot_axis * axis.y, oc_dot_axis * axis.z};

    // Compute the origin vector of the ray perpendicular to the cylinder's axis
    Vec3 ray_orig_perp = {oc.x - ray_orig_axis.x, oc.y - ray_orig_axis.y, oc.z - ray_orig_axis.z};

    // Compute the coefficients of the quadratic equation
    float a = ray_dir_perp.x * ray_dir_perp.x + ray_dir_perp.z * ray_dir_perp.z;
    float b = 2 * (ray_dir_perp.x * ray_orig_perp.x + ray_dir_perp.z * ray_orig_perp.z);
    float c1 = ray_orig_perp.x * ray_orig_perp.x + ray_orig_perp.z * ray_orig_perp.z - c.radius * c.radius;

    // Solve the quadratic equation
    float discriminant = b * b - 4 * a * c1;
    if (discriminant < 0) {
        // no intersection
        return -1;
    } else {
        // find the distance to the intersection point along the ray
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        if (t1 > 0 && t2 > 0) {
            return fmin(t1, t2) / r_dot_axis;
        } else if (t1 > 0) {
            return t1 / r_dot_axis;
        } else if (t2 > 0) {
            return t2 / r_dot_axis;
        } else {
            // both intersection distances are negative, no intersection
            return -1;
        }
    }
}

int main() {
    // set up the ray and cylinder
    Ray r = {{0, 1, 0}, {1, 
