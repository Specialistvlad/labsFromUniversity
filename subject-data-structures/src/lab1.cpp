#include "stdio.h"
#include <math.h>
#include <cmath>

struct Data
{
	double a;
	double b;
	double x1;
	double x2;
	double dx;
	double* f;
};

#define SIZE 100
static double source[SIZE];
static double results[SIZE];
static double results2[SIZE];
static double results4[SIZE];
static Data d = { 1, 5, -2, -0.1, 0.1, results };

double f(double x) {
	double result;
	if (x <= -0.7) {
		result = -1 * d.a * x * x;
	} else {
		result = (d.a - x) / (d.b * x);
	}
	return result;
}

double scale(double x, double min, double from, double to) {
	min = std::abs(min);
	from = std::abs(from + min);
	x = std::abs(x+min);
	double scaleFactor = to / from;
	return scaleFactor * x;
}

double printVertical(double* f, int size) {
	printf("\n\n\n3.\n");
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < f[i]; ++j) {
			printf(" ");
		}
		printf("*\n");
	}
}

float randomFloat(float a, float b) {
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

int main()
{
	//1111111111111111111111111111111111111111111111111
	printf("Iteration from %.2f to %.2f with step %.2f\n", d.x1, d.x2, d.dx);

	int cnt = 0;
	if (d.x1 < d.x2)
		for (double x = d.x1; x < d.x2+d.dx; x+=d.dx) {
			source[cnt] = x;
			if (d.a - x == 0)
				d.f[cnt] = 0;
			else
				d.f[cnt] = f(x);
			++cnt;
		}
	else
		for (double x = d.x1; x > d.x2+d.dx; x-=d.dx) {
			source[cnt] = x;
			if (d.a - x == 0)
				d.f[cnt] = 0;
			else
				d.f[cnt] = f(x);
			++cnt;
		}

	printf(" x         f(x)\n");
	for (int i = 0; i < cnt; ++i)
	{
		printf("%.2f     %.2f\n", source[i], d.f[i]);
	}

	//222222222222222222222222222222222222222222222222
	double min = d.f[0];
	double max = d.f[0];
	double scaleA = 70;

	for (int i = 0; i < cnt; ++i)
		if (min > d.f[i])
			min = d.f[i];

	for (int i = 0; i < cnt; ++i)
		if (max < d.f[i])
			max = d.f[i];

	printf("\n\n\nscale from [%.2f, %.2f] to [%d, %.2f]\n",
		min, max, 0, scaleA);
	printf("source    result\n");
	for (int i = 0; i < cnt; ++i)
	{
		results2[i] = scale(d.f[i], min, max, scaleA);
		printf("%.2f     %.2f\n", d.f[i], results2[i]);
	}

	//3333333333333333333333333333333333333333333333333
	printVertical(results2, cnt);

	//4444444444444444444444444444444444444444444444444
	// printVertical(d.f, cnt);
	double s1 = d.f[1];

	for (int i = 0; i < cnt; ++i)
		if (i+1 % 2 == 0)
			if (s1 > d.f[i])
				s1 = d.f[i];

	double s2 = d.f[0];
	for (int i = 0; i < cnt; ++i)
		if (s2 > d.f[i])
			s2 = d.f[i];

	printf("\n4. S1=%.2f S2=%.2f\n", s1, s2);
	for (int i = 0; i < cnt; ++i) {
		results4[i] = randomFloat(s1, s2);
		printf("random in range %.2f\n", results4[i]);
	}
	return 0;
}
