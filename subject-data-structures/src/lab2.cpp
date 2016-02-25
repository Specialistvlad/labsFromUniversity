#include "stdio.h"
#include <math.h>


int scale(double source) {
	return source;
}

int main()
{

	int cnt = 0;
	if (d.x1 < d.x2)
		for (double i = d.x1; i < d.x2+d.dx; i+=d.dx) {
			source[cnt] = i;
			d.f[cnt] = f(i);
			++cnt;
		}
	else
		for (double i = d.x1; i > d.x2+d.dx; i-=d.dx) {
			source[cnt] = i;
			d.f[cnt] = f(i);
			++cnt;
		}

	printf(" x         f(x)\n");
	for (int i = 0; i < cnt; ++i)
	{
		printf("%.2f     %.2f\n", source[i], d.f[i]);
	}
	return 0;
}
