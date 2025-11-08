#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.h"

int main(void) {
    int n;
    printf("Introduce el tamaño n:\n");
    scanf("%d", &n);

    double **A = malloc(n * sizeof(double *));
    double *b = malloc(n * sizeof(double));
    double *x = malloc(n * sizeof(double));
    double *r = malloc(n * sizeof(double));

    for(int i = 0; i < n; i++)
        A[i] = malloc(n * sizeof(double));

    // Lectura
    printf("Introdueix el vector b:\n");
    for(int i = 0; i < n; i++)
        scanf("%lf", &b[i]);

    printf("Introdueix la matriu A:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    // Tolerancia
    double tol;
    printf("Introduce la tolerancia (1e-x):\n");
    scanf("%d", &tol);

    // Resolver sistema triangular superior
    resoltrisup(n, A, b, x, tol);

    // Calcular residuo r = A*x - b
    residuo(n, A, b, x, r);

    // Calcular norma-2 del residuo
    double norma2 = sqrt(prod_esc(n, r, r));

    // Mostrar resultados
    printf("\nSolució x:\n");
    for(int i = 0; i < n; i++)
        printf("%lf\n", x[i]);

    printf("\nNorma-2 del residu: %e\n", norma2);

    // Liberar memoria
    for(int i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(b);
    free(x);
    free(r);

    return 0;
}

