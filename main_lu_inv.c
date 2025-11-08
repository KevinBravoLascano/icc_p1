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
    double **inversa= malloc(n * sizeof(double *));
    double **identitat = malloc(n * sizeof(double *));
    double *y = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(n * sizeof(double));
        a2[i] = malloc(n * sizeof(double));
        identitat[i] = malloc(n * sizeof(double));
        inversa[i] = malloc(n * sizeof(double));
    }


    printf("Introduce la tolerancia:\n");
    scanf("%lf", &tol);

    printf("Introduce la matriz A:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%lf", &a[i][j]);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            a2[i][j]=a[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) //definicion de la matriz identidad
        for (int j = 0; j < n; j++)
            if(i==j){
                identitat[i][j]=1;
            }else{
                identitat[i][j]=0;
            }

    

    lu(n,a,tol);//sacamos LU

    double *col = malloc(n * sizeof(double));

    for(int i=0;i<n;i++){
        // resolvemos A * x = columna i de la identidad
        for(int j=0;j<n;j++)
            col[j] = identitat[j][i]; // tomar columna i de la identidad

        resoltriinf(n,a,col,y);       // resolver Ly = b
        resoltrisup(n,a,y,col,tol);   // resolver Ux = y

    // Guardar la columna resultante en inversa
    for(int j=0;j<n;j++)
        inversa[j][i] = col[j];  // nota: loo hice asi porq en mi pensamiwento original me daba la inversa traspuesta y queria tener bien
    }
    
    prodMatMat(n,n,n,a,inversa,a2);    //calculo AA^-1
    // Calcular norma-2 del residuo
    double normaInf = 0.0;
    for(int i = 0; i < n; i++) {
        double fila = 0.0;
        for(int j = 0; j < n; j++) {
            fila += fabs(a2[i][j] - identitat[i][j]);
        }
        if(fila > normaInf) normaInf = fila;
    }

    // Mostrar resultados
    printf("\nMatriz A^-1:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%lf ", inversa[i][j]);
        }
        printf("\n");
    }


    printf("\nNorma-2 del residu: %e\n", normaInf);

    for(int i = 0; i < n; i++){
        free(a[i]);
        free(identitat[i]);
        free(a2[i]);
        free(inversa[i]);
    }
    free(a);
    free(a2);
    free(inversa);
    free(identitat);
    free(y);
    return 0;
}