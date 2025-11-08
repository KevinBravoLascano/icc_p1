#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int resoltrisup(int n, double **a, double *b, double *x, double tol){
    
    for(int i=n-1; i>=0; i--){
        if (fabs(a[i][i]) < tol) {
            // Elemento de la diagonal demasiado pequeño
            return 1; 
        }
        x[i] = b[i];
        for(int k=i+1; k<n; k++){
            x[i] -= a[i][k] * x[k];
        }
        x[i] /= a[i][i];
    }
    return 0; // Èxit

}

int resoltriinf(int n, double **a, double *b, double *x){
    for(int i=0; i<n; i++){
        x[i] = b[i];
        for(int k=0; k<i; k++){
            x[i] -= a[i][k] * x[k];
        }
        
    }
    return 0; // Èxit
}

void prodMatVec(int n, double **a, double *u, double *v){
    for(int i=0;i<n;i++){
        v[i]=0.0;
        for(int j=0;j<n;j++)
            v[i] += a[i][j] * u[j];
    }
}


double prod_esc(int n, double *x, double *y){
    double prod = 0.0;
    for(int i=0; i<n; i++)
        prod += x[i]*y[i];
    return prod;
}
void residuo(int n, double **a, double *b, double *x, double *r){
    double *Ax = (double*) malloc(n*sizeof(double));
    prodMatVec(n, a, x, Ax);  // Ax = A*x

    for(int i=0;i<n;i++)
        r[i] = Ax[i] - b[i];  // r = Ax - b

    free(Ax);
}


int lu(int n, double **a, double tol) {
    int i, j, k;
    double m;

    for (k = 0; k < n - 1; k++) {
        // Comprobar que el pivote no sea demasiado pequeño
        if (fabs(a[k][k]) < tol) {
            printf("Error: pivote demasiado pequeño");
            return 1;  
        }

        // Eliminación de Gauss (sin pivoteo)
        for (i = k + 1; i < n; i++) {
            a[i][k] = a[i][k] / a[k][k];  // Guardamos el multiplicador en la parte inferior

            for (j = k + 1; j < n; j++) {
                a[i][j] = a[i][j] - a[i][k] * a[k][j];
            }
        }
    }

    // Comprobación final del último pivote
    if (fabs(a[n - 1][n - 1]) < tol) {
        printf("Error: pivote demasiado pequeño");
        return 1;
    }

    return 0;  // Éxito
}





