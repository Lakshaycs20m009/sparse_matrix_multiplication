Aim of this experiment is to compare runtime of Dense Matrix Representation vs Sparse Matrix Representation while performing basic operation such as Multiplication
Simply converted the given matrix to Compressed Sparse Row(CSR) and then performed the multiplication compared it with dense multiplication for the same set of matrices
This experiment is performed for the matrices A:500x500 B:500x500 with different sparse factors (randomness) and observed that for lesser sparse factor CSR took less time as compared to Dense(Normal) representation. 
Which can be seen on this link- https://github.com/Lakshaycs20m009/sparse_matrix_multiplication/blob/main/comparison_graph.png
Instruction to run code:
1.After cloning this repo , you can run this -> g++ -std=c++11 mat_mul_cs20m009.cpp -o main.out in the respective directory.
2. ./main.out m n p spf_1 spf_2
3. where m=number of rows of A, n = number of columns of A which is equal to number of rows of B , p = number of columns of B , spf_1= sparse factor of A , spf_2=sparse factor of B.

