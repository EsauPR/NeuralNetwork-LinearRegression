/*
    Implementation of Linear Regression for one variable

    @author Oscar Esaú Peralta Rosales
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

void help();  // Show the program help

int main(int argc, char const *argv[]) {

    int N = 0;  // Number of samples [x, d]

    double w, b;  // Values of the lineal ecuation " d = w*x + b"
    double xi = 0.0, di = 0.0;  // Samples [x,d]
    double X = 0.0, X2 = 0.0, D = 0.0, XD = 0.0;  // Average of x, average of x², average of d, average of x*d

    FILE *file = NULL;

    if ( argc < 2 ) {
        printf("Error: Enter input file as argument\n");
        help();
        exit( EXIT_FAILURE );
    }

    file = fopen( argv[1], "r");

    if( file == NULL ) {
		printf("Error: The file does not exist: %s\n", argv[1]);
        help();
		exit(EXIT_FAILURE);
	}

    // Processing input datas and computing averages
    while ( fscanf( file, "%lf %lf", &xi, &di ) != EOF ) {
        X += xi;
        D += di;
        X2 += xi * xi;
        XD += di * xi;
        N++;
    }

    fclose( file );

    X /= N;
    D /= N;
    X2 /= N;
    XD /= N;

    // Obtaining the values w and b of the function
    w = ( XD - D * X ) / ( X2 - X * X );
    b = ( D * X2 - XD * X ) / ( X2 - X * X );

    printf("d = %.4lf + %.4lfx\n", b, w );

    exit(EXIT_SUCCESS);
}

// Show the program help
void help() {
    printf("\nHow to use:\n");
    printf("\n\tregLineal2D [file_input]\n" );
    printf("\nThe input file must have the following format:\n");
    printf("\n\tFor each row must be two real numbers \"x\" and \"d\"\n");
    printf("\twhere \"x\" represents the value for the function \"d = w*x + b\"\n");
    printf("\tand \"d\" is the result of the function for \"x\"\n\n");
}
