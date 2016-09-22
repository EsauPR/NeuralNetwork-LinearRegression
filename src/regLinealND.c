/*
    Implementation of Multiple Linear Regression

    @author Oscar Esaú Peralta Rosales
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(x) (((x) < 0) ? -(x) : (x))

#define MAX_DIMENSION 50  // Max dimension of the data matrix
#define MAX_DATA_SAMPLE 800 // Number of data samples
#define STR_DIMENSION 500 // Max dimension of string for process de input


void readInput( const char *fname, double x[][MAX_DIMENSION], int *n, int *p );  // Process the input file
void createMatrixR( double x[][MAX_DIMENSION], double R[][MAX_DIMENSION], int n, int p );  // Create the matrix R to solve the equation P = R*W
void createVectorP( double x[][MAX_DIMENSION], double *P, int n, int p );  // Create the vector P to solve the equation P = R*W
void setIdentityMatrix( double I[][MAX_DIMENSION], int p );  // Set the identity matrix
void solve( double Rinv[][MAX_DIMENSION], double *P, double *W, int p );  // Solve the equation P = R*W using the inverse matrix of R, Rinv*P = Rinv*R*W
void printSol( double *W, int p );  // Show the function solution
void help();  // Show the program help

int inverseMatrix( double R[][MAX_DIMENSION], double I[][MAX_DIMENSION], int p );  // Compute the inverse Matrix of R by Gauss-Jordan method


int main( int argc, char const *argv[] ) {
    int n = 0, p = 0;

    double x[MAX_DIMENSION][MAX_DATA_SAMPLE];  // Data input, the las element of the each row i represents the value di
    // Values for P = R*W
    double R[MAX_DIMENSION][MAX_DIMENSION];
    double P[MAX_DIMENSION];
    double W[MAX_DIMENSION];
    double Rinv[MAX_DIMENSION][MAX_DIMENSION];  // Inverse matrix of R

    if ( argc < 2 ) {
        printf("Error: Enter a input file as argument\n");
        help();
        exit( EXIT_FAILURE );
    }

    // Processing input datas and computing solution
    readInput( argv[1], x, &n, &p );
    createMatrixR( x, R, n, p );
    createVectorP( x, P, n, p );
    setIdentityMatrix(Rinv, p);
    inverseMatrix(R, Rinv, p);

    solve( Rinv, P, W, p );

    printSol( W, p );

    exit(EXIT_SUCCESS);
}

// Create the matrix R to solve the ecuation P = R*W
void createMatrixR( double x[][MAX_DIMENSION], double R[][MAX_DIMENSION], int n, int p ) {
    int i, j, k;

    /*
        R[k][j] = 1/N * [i = 1 to N]Σ( x[i][j] * x[i][k] )
        k = 0,1,2,...,p
        j = 0,1,2,...,p
    */
    for ( k = 0; k < p; k++ ) {
        // R is a symmetric matrix calculate only the half
        for ( j = k; j < p; j++ ) {
            R[k][j] = 0.0;
            for ( i = 0; i < n; i++ ) {
                R[k][j] += x[i][j] * x[i][k];
            }
            R[k][j] /= n;
            R[j][k] = R[k][j];
        }
    }
}

// Create the vector P to solve the ecuation P = R*W
void createVectorP( double x[][MAX_DIMENSION], double *P, int n, int p ) {
    int i, j;

    /*
        P[j] = 1/N * [i = 1 to N]Σ( x[i][j] * d[i] )
        j = 0,1,2,...,p
    */
    for ( j = 0; j < p; j++ ) {
        P[j] = 0;
        for ( i = 0; i < n; i++) {
            P[j] += x[i][j] * x[i][p];
        }
        P[j] /= n;
    }
}

// Set the identity matrix
void setIdentityMatrix( double I[][MAX_DIMENSION], int p ) {
    int i;
    for ( i = 0; i < p; i++ ) {
        memset( I[i], 0, p);
        I[i][i] = 1.0;
    }
}

// Compute the inverse Matrix of R by Gauss-Jordan method
int inverseMatrix( double R[][MAX_DIMENSION], double I[][MAX_DIMENSION], int p ) {
    int pivot, j, k;
    double factor, acum;

    for ( pivot = 0; pivot < p; pivot++ ) {
        // Became one the cell R[pivot][pivot];
        factor = R[pivot][pivot];
        for ( k = 0; k < p; k++ ) {
            I[pivot][k] /= factor;
            R[pivot][k] /= factor;
        }
        // Become zero the column R[j][pivot]
        for ( j = 0; j < p; j++ ) {
            // except the cell R[pivot][pivot]
            if( j != pivot ) {
                // Factor to become zero the cell R[j][pivot]
                factor = R[j][pivot];
                acum = 0.0;
                for ( k = 0; k < p; k++ ) {
                    I[j][k] -= I[pivot][k] * factor;
                    R[j][k] -= R[pivot][k] * factor;
                    acum += abs( R[j][k] );
                }
                if ( acum == 0.0 ) {
                    printf("Does not exist inverse matrix for R\n");
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}

// Solve the equation P = R*W using the inverse matrix of R, Rinv*P = Rinv*R*W
void solve( double Rinv[][MAX_DIMENSION], double *P, double *W, int p ) {
    int i, j;
    /*
        W = Rinv * P
    */
    for ( i = 0; i < p; i++ ) {
        W[i] = 0.0;
        for ( j = 0; j < p; j++ ) {
            W[i] += Rinv[i][j] * P[j];
        }
    }
}

// Show the function solution
void printSol( double *W, int p ) {
    int i;
    printf("d = ");
    for ( i = 0; i < p; i++ ) {
        if ( i != 0 ) {
            if ( W[i] >= 0 ) {
                printf(" + ");
            }
            else {
                printf(" - ");
            }
            printf("%.4lfX%d", abs( W[i] ), i );
        }
        else {
            printf("%.4lf", W[i] );
        }
    }
    puts("");
}

// Process the input file
void readInput( const char *fname, double x[][MAX_DIMENSION], int *n, int *p ) {
    int nTmp = 0, pTmp = 0;
	char str[STR_DIMENSION], *token, *delim = " \n";

    FILE *file = NULL;
    file = fopen( fname, "r");

	if( file == NULL ) {
		printf("Error: The file does not exist: %s\n", fname);
        help();
		exit(EXIT_FAILURE);
	}

    // Processing input data line by line
    while( fgets( str, STR_DIMENSION, file ) != NULL ) {
        pTmp = 1;

        /*
            d = b + [k = 1 to p]Σ( w[k] * x[k] )

            Adding b to the the sum:
                Becoming b = w[0] and x[0] = 1, then
                d = [k = 0 to p]Σ( w[k] * x[k] )
        */
        x[nTmp][0] = 1.0;

        token = strtok(str, delim);
        while( token != NULL ) {
            x[nTmp][pTmp] = atof( token );
            token = strtok(NULL, delim);
            pTmp++;
        }
        nTmp++;
        *p = pTmp - 1;
    }
    *n = nTmp;

	fclose(file);
}

// Show the program help
void help() {
    printf("\nHow to use:\n");
    printf("\n\tregLinealND [file_input]\n" );
    printf("\nThe input file must have the following format:\n");
    printf("\n\tFor each row must be \"p + 1\" elements,\n");
    printf("\tp real numbers \"x1, x2, ..., xp\" followed by one real number d,\n");
    printf("\twhere \"xi\" represents the values for the function\n");
    printf("\t\"d = w1*xi + w2*x2 + ... + wp*xp + b\"\n");
    printf("\tand d is the result of the function for xi\n\n");
}
