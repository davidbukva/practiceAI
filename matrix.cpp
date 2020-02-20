


struct matrix{

    int n;
    int m;

    int **data;
    int data[n][m];
    matrix(int _n, int _m): m(_m), n(_n){
        data = (int **)malloc(n*m*sizeof(int));
    }
    



};
