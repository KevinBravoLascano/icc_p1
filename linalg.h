int resoltrisup(int n, double **a, double *b, double *x, double tol);
int resoltriinf(int n, double **a, double *b, double *x);
int gausspiv(int n, double**a,double*b,double tol);
void prodMatVec(int n, double **a, double *u, double *v);
void prodMatMat(int n,int p,int m, double** a, double** b,double** c);
int prod_esc (int n,double*x,double* y);
void residuo(int n, double **a, double *b, double *x, double *r);
int lu(int n, double **a, double tol);