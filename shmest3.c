#include <math.h>
#include <stdio.h>

int main()
{
	int fov = 90;

	double result = tan(fov / 2 * M_PI / 180);
	tan(fov / 2 * M_PI / 180)
	double result2 = tan(fov / 2) * M_PI / 180;
	//tan(fov / 2 * M_PI / 180)
	printf("result:%f\n", result);
	printf("result:%f\n", result2);

}