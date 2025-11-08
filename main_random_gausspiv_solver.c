#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.h"

/* Se generan valores reales aleatorios en un intervalo real */
#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* rand, srand, RAND_MAX */
#include <time.h> /* time */


int main(void){
    int n;
    double tol=1e-12;
    int k;
    double max_norma=0.0;
    double a, z;
    double **A;
    double **a2;
    double *b;
    double *x;
    double *r;
    FILE *fp = fopen("residuos.txt", "w");
    if (!fp) {
        printf("Error al abrir archivo.\n");
        return 1;
    }
    

   
    a=-1.0;
    z=1.0;

    srand(time(NULL)); /* genera la semilla inicial */
    for(n=1;n<=100;n++){
        max_norma=0.0;
        A = malloc(n * sizeof(double *));
        a2 = malloc(n * sizeof(double *));
        b = malloc(n * sizeof(double));
        x = malloc(n * sizeof(double));
        r = malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) {
            A[i] = malloc(n * sizeof(double));
            a2[i] = malloc(n * sizeof(double));
        }

         
        

        for(int i=0;i<1000;i++){//generador de 1000 equaciones lineales
            for(int j = 0; j < n; j++){//Generador de A
                for (k = 0; k < n; k++) {
                    A[j][k] = a + (z - a) * ((1.0 * rand()) / RAND_MAX);
                
                }
                //generador de b
                b[j]=a + (z - a) * ((1.0 * rand()) / RAND_MAX);
            }
            for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                a2[i][j] = A[i][j];
            }
         } //copiando matriz a para el calculo de residuo
            //calculos por cada equacion
            if (gausspiv(n,A,b,tol) != 0) continue;
            resoltrisup(n,A,b,x,tol);
            residuo(n, a2, b, x, r);
            
            
            // Calcular max norma-2 del residuo
            
            double norma2 = sqrt(prod_esc(n, r, r));
            if (norma2 > max_norma)
                max_norma = norma2;

           

        }
         //impresion ne el archivo
        fprintf(fp, "%d %e\n", n, max_norma);
        printf("n=%d terminado, max_norma=%e\n", n, max_norma);

        //liberacion
        for (int i = 0; i < n; i++) {
            free(A[i]);
            free(a2[i]);
        }
        free(A); free(a2); free(b); free(x); free(r);   
    }
    

}