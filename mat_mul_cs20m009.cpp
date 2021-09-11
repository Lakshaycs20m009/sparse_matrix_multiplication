#include <iostream>
#include<time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

int main(int args, char **argv) {
    int t1 = 0, t2 = 0;
    int m, n, x, y;
    m = atoi(argv[1]);
    n = x = atoi(argv[2]);
    y = atoi(argv[3]);
    float spf_1, spf_2;
    spf_1 = atof(argv[4]);
    spf_2 = atof(argv[5]);


    clock_t starta, enda, startb, endb;
    cout << "Enter the number of rows and columns of Matrix A-->" << "\n";
    cout << "number of rows of Matrix A-->" << m << endl;
    cout << "number of columns of Matrix A-->" << n << endl;
    vector<vector<int> > A(m, vector<int> (n, 0));
    cout << "Enter the number of rows and columns of Matrix B-->" << "\n";

    cout << "number of rows of Matrix B-->" << x << endl;
    cout << "number of columns of Matrix B-->" << y << endl;
    vector<vector<int> > B(x, vector<int> (y, 0));
    cout << "Sparse Factor for Matrix A and Matrix B-->" << "\n";

    cout << "Sparse factor of Matrix A-->" << spf_1 << "\n";
    cout << "Sparse factor of Matrix B-->" << spf_2 << "\n";

    if (n != x)
    {
        cout << "Please give valid inputs cannot perform multiplication" << "\n";
        return -1;
    }
    srand(time(0));
    t1 = spf_1 * m * n;
    t2 = spf_2 * x * y;


    for (int i = 0; i < t1; ++i)
    {
        int index = (int) (m * ((double) rand() / (RAND_MAX + 1.0)));
        int index_2 = (int) (n * ((double) rand() / (RAND_MAX + 1.0)));
        if (A[index][index_2] == 0)
            A[index][index_2] = rand() % 10;
        else
            i--;

    }
    for (int i = 0; i < t2; ++i)
    {
        int index = (int) (m * ((double) rand() / (RAND_MAX + 1.0)));
        int index_2 = (int) (n * ((double) rand() / (RAND_MAX + 1.0)));
        if (B[index][index_2] == 0)
            B[index][index_2] = rand() % 10;
        else
            i--;
    }
    cout << "********************************************************";
    cout << " Dense Matrix A" << "\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }

    cout << " Dense Matrix B" << "\n";
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }

    starta = clock();
    vector<vector<int> > result_dense(m, vector<int> (y, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result_dense[i][j] = 0;

            for (int k = 0; k < x; k++) {
                result_dense[i][j] += A[i][k] * B[k][j];
            }
        }
    }





    cout << "******result by dense matrix********" << "\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < y; j++)
        {
            cout << result_dense[i][j] << " ";
        }
        cout << "\n";
    }

    enda = clock();
    double time_taken_a = double(enda - starta) / double(CLOCKS_PER_SEC);
    cout << "Time taken by dense multiplication: " << fixed
         << time_taken_a << setprecision(5);
    cout << " sec " << endl;
    /////////////////squeezing matrix////////////////
    int size_1 = 0;// number of non-zero elements in matrix A
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0)
                size_1++;
    int compactMatrix_A[3][size_1];
    int k1 = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0)
            {
                compactMatrix_A[0][k1] = i;
                compactMatrix_A[1][k1] = j;
                compactMatrix_A[2][k1] = A[i][j];
                k1++;
            }

    int size_2 = 0;// number of non-zero elements in matrix B
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (B[i][j] != 0)
                size_2++;
        }
    }
    int compactMatrix_B[3][size_2];
    int k2 = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (B[i][j] != 0)
            {
                compactMatrix_B[0][k2] = i;
                compactMatrix_B[1][k2] = j;
                compactMatrix_B[2][k2] = B[i][j];
                k2++;
            }
        }
    }


    vector<vector<int> > result;
    vector<int>temp;

    startb = clock();

    for (int i = 0; i < k1; i++) {
        cout << compactMatrix_A[0][i] << " " << compactMatrix_A[1][i] << " " << compactMatrix_A[2][i] << endl;
    }

    cout << "-------------------------------" << endl;

    for (int i = 0; i < k2; i++) {
        cout << compactMatrix_B[0][i] << " " << compactMatrix_B[1][i] << " " << compactMatrix_B[2][i] << endl;
    }

    cout << "------------------Csd---------------------" << endl;

    for (int i = 0; i < k1; i++) {
        int row = compactMatrix_A[0][i];
        int col = compactMatrix_A[1][i];
        for (int j = 0; j < k2; j++) {
            if (compactMatrix_B[0][j] == col) {
                int nCol = compactMatrix_B[1][j];
                int nVal = compactMatrix_A[2][i] * compactMatrix_B[2][j];

                int size;
                if (result.empty())
                    size = 0;
                else
                    size =  result[0].size();
                int flag = 0;
                for (int k = 0; k < size; k++) {
                    if (result[0][k] == row && result[1][k] == nCol) {
                        result[2][k] += nVal;
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    if (result.empty()) {
                        vector<int> ro = {row};
                        // ro.push_back(row);
                        vector<int> co = {nCol};
                        // ro.push_back(nCol);
                        vector<int> va = {nVal};
                        // ro.push_back(nVal);
                        result.push_back(ro);
                        result.push_back(co);
                        result.push_back(va);
                    }
                    else {
                        result[0].push_back(row);
                        result[1].push_back(nCol);
                        result[2].push_back(nVal);
                    }
                }

            }

        }
    }



    endb = clock();
    double time_taken_b = double(endb - startb) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program csr representation : " << fixed
         << time_taken_b << setprecision(5);
    cout << " sec " << endl;
    cout << "****result by csr***" << "\n";
    for (int i = 0; i < result[0].size(); i++) {
        cout << result[0][i] << " " << result[1][i] << " " << result[2][i] << endl;
    }

    return 0;
}