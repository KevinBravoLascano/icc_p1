int resoltrisup(int n, double **a, double *b, double *x, double tol){
    for(int i=n-1; i>=0; i--){
        x[i] = b[i];
        for(int k=i+1; k<n; k++){
            x[i] -= a[i][k] * x[k];
        }
        x[i] /= a[i][i];
    }
    return 0; // Èxit

}