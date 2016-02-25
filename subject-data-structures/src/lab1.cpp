#include "stdio.h"
#include <math.h>

struct Data
{
	double a;
	double b;
	double x1;
	double x2;
	double dx;
	double* f;
};

int main()
{
	#define SIZE 100
	static double source[SIZE];
	static double results[SIZE];
	static Data d = { 1, 5, -2, -0.1, 0.1, results };

	printf("Iteration from %.2f to %.2f with step %.2f\n", d.x1, d.x2, d.dx);

	int cnt = 0;
	if (d.x1 < d.x2)
		for (double i = d.x1; i < d.x2; i+=d.dx) {
			source[cnt] = i;
			d.f[cnt] = sin(i);
			++cnt;
		}
	else
		for (double i = d.x1; i > d.x2; i-=d.dx) {
			source[cnt] = i;
			d.f[cnt] = sin(i);
			++cnt;
		}

	printf(" x         f(x)\n");
	for (int i = 0; i < cnt; ++i)
	{
		printf("%.2f     %.2f\n", source[i], d.f[i]);
	}
	return 0;
}
