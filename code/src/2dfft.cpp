float ** 2d_transform(float ** mat, int m, int n){
    complex mat[m][n];
    for(int r = 0; r < m){
        fft(mat[r]);
    }
    complex t[m];
    for(int c = 0;c < n;c++){

        for(int r = 0;r < m;r++){
            t[r] = mat[r][c];
        }

        fft(t, m);
        
        for(int r = 0;r < m;r++){
            mat[r][c] = t;
        }
    }
}

int main(){
    float ** matrix;
}
