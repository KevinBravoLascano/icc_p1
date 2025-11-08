#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.h"
int main(void){
    int n;
    double tol;
    //lectura de datos

    printf("Introduce la dimenmsion n:\n");
    scanf("%d", &n);

    double **a = malloc(n * sizeof(double *));
    double **a2 = malloc(n * sizeof(double *));
    double *b = malloc(n * sizeof(double));
    double *x = malloc(n * sizeof(double));
    double *r = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        a[i] = malloc(n * sizeof(double));
        a2[i] = malloc(n * sizeof(double));
    }

    printf("Introduce la tolerancia:\n");
    scanf("%lf", &tol);

    printf("Introduce la matriz A:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%lf", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++) //copiando matriz a para el calculo de residuo
        for (int j = 0; j < n; j++)
            a2[i][j] = a[i][j];


    printf("Introdueix el vector b:\n");
    for(int i = 0; i < n; i++){
        scanf("%lf", &b[i]);
    }

    //calculos
    gausspiv(n,a,b,tol);
    resoltrisup(n,a,b,x,tol);
    residuo(n, a2, b, x, r);

    // Calcular norma-2 del residuo
    double norma2 = sqrt(prod_esc(n, r, r));

    // Mostrar resultados
    printf("\nSolució x:\n");
    for(int i = 0; i < n; i++)
        printf("%lf\n", x[i]);

    printf("\nNorma-2 del residu: %e\n", norma2);

    for(int i = 0; i < n; i++){
        free(a[i]);
        free(a2[i]);
    }
    free(a);
    free(a2);
    free(b);
    free(x);
    free(r);
    return 0;
}