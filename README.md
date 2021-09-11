Aim of this experiment is to compare runtime of Dense Matrix Representation vs Sparse Matrix Representation while performing basic operation such as Multiplication
Simply converted the given matrix to Compressed Sparse Row(CSR) and then performed the multiplication compared it with dense multiplication for the same set of matrices
This experiment is performed for the matrices A:500x500 B:500x500 with different sparse factors (randomness) and observed that for lesser sparse factor CSR took less time as compared to Dense(Normal) representation. 
