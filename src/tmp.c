#include <stdio.h>

double f( double num, double num2, double num3, double num4 ) {
    return 5.4 + num*7.5 + num2*-12.8 + num3*31.3 + num4*-122.45; // in5
}

int main()
{
	int i, n = 14;
    int v[] = { -1, -2, -3 , -4, 0, 1, 2 ,3 ,4 ,5 ,6 ,7 ,8, 9 };
    int v2[] = { -5, -3, 0 , 2, 5, 7, 10 ,11 ,25 ,28 ,29 ,30 ,35, 38 };
    int v3[] = { -20, -13, -10 , -7, 0, 3, 10 ,11 ,21 ,23 ,27 ,29 ,31, 34 };
    int v4[] = { -23, -18, -14 , -13, -10, 3, 10 ,12 ,15 ,19 ,25 ,29 ,34, 37 };

    for ( i = 0; i < n; i++ ) {
        printf("%d %d %d %d %lf\n", v[i], v2[i], v3[i], v4[i], f(v[i],v2[i],v3[i], v4[i]) );
    }

}
