#include <stdio.h>
#include "linalg.h"
int main(void) {
    int n;
    scanf("%d", &n);
    double *b, **A;

    b= ( double *) malloc (n*sizeof(double) );
    A= ( double **) malloc (n*sizeof(double *) );
    for(int i=0; i<n; i++) {
        A[i]= ( double *) malloc (n*sizeof(double) );
    }


    
    //lectura
    printf("Introdueix el vector b\n");
    for(int i=0; i<n;i++){
        scanf("%lf", &b[i]);
    }
    printf("Introdueix la matriu A\n");
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%lf", &A[i][j]);
        }
    }
    return 0;
}
tol = 1e-12;