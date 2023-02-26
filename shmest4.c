// Define the cylinder's center point, radius, and central axis direction vector
vec3 center = {1.0, 2.0, 3.0};
float radius = 2.0;
vec3 axis = {0.0, 1.0, 0.0};

// Define the ray's origin and direction vectors
vec3 origin = {4.0, 5.0, 6.0};
vec3 direction = {-1.0, -1.0, -1.0};

// Step 1: Calculate the direction vector of the cylinder's central axis
vec3 axis_direction = normalize(axis);

// Step 2: Project the direction vector of the ray onto the cylinder's central axis
float ray_projection = dot(direction, axis_direction);
vec3 ray_component = scalar_multiply(ray_projection, axis_direction);

// Step 3: Calculate the vector from the cylinder's center to the ray's origin
vec3 center_to_ray = subtract(origin, center);

// Step 4: Calculate the vector perpendicular to the cylinder's axis that points from the cylinder's center to the closest point on the ray to the cylinder's axis
vec3 perpendicular = subtract(center_to_ray, ray_component);

// Step 5: Calculate the distance between the closest point on the ray to the cylinder's axis and the center of the cylinder
float distance = length(perpendicular);

// Step 6: Calculate the point where the ray intersects the plane of the cylinder's circular cross-sections
vec3 intersection = add(origin, scalar_multiply(distance/ray_projection, direction));
