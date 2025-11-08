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

int gausspiv(int n, double **a, double *b, double tol) {
    for (int k = 0; k < n - 1; k++) {
        // Buscar pivote máximo en columna 
        int l = k;
        double max = fabs(a[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(a[i][k]) > max) {
                max = fabs(a[i][k]);
                l = i;
            }
        }

    
        if (max < tol) {//si no cumple, fuera, acaba
            printf("Error: pivote demasiado pequeño en columna %d (|a[%d][%d]| = %e)\n", k, l, k, max);
            return -1;
        }

        
        if (l != k) {
            double *temp = a[k]; //hacemos los cambios de filas de lo q toque
            a[k] = a[l];
            a[l] = temp;

            double tmpb = b[k];
            b[k] = b[l];
            b[l] = tmpb;
        }

       
        for (int i = k + 1; i < n; i++) {//hare que deje matriz trriangle superior, es decir bajo ma diagonal todo 0
            double factor = a[i][k] / a[k][k];
            a[i][k] = 0.0; // limpiar elemento

            for (int j = k + 1; j < n; j++) {
                a[i][j] -= factor * a[k][j];
            }

            b[i] -= factor * b[k];
        }
    }

    // Verificar último pivote 
    if (fabs(a[n - 1][n - 1]) < tol) {
        printf("Error: pivote demasiado pequeño en última fila.\n");
        return -1;
    }

    return 0; // Éxito
}

void prodMatVec(int n, double **a, double *u, double *v){
    for(int i=0;i<n;i++){
        v[i]=0.0;
        for(int j=0;j<n;j++)
            v[i] += a[i][j] * u[j];
    }
}

void prodMatMat(int n,int p,int m, double** a, double** b,double **c){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<p;k++){
                c[i][j]+=a[i][k]*b[k][j];//aplicamos la formula d emultiplicar matrices
            }
        }

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
    printf("matriz Ax:\n");
    
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





