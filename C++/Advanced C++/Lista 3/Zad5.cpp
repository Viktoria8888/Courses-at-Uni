#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void FillMatrixWithRandomValues(std::vector<std::vector<double>>& matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.5, 2.0);

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            matrix[i][j] = dis(gen);
        }
    }
}

void SquareMatrix(std::vector<std::vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    std::vector<std::vector<double>> result(rows, std::vector<double>(cols, 0.0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < rows; k++) {
                result[i][j] += matrix[i][k] * matrix[k][j];
            }
        }
    }

    matrix = result;
}

int main() {
    std::vector<std::vector<double>> matrix10(10, std::vector<double>(10, 0.0));
    std::vector<std::vector<double>> matrix100(100, std::vector<double>(100, 0.0));
    std::vector<std::vector<double>> matrix1000(1000, std::vector<double>(1000, 0.0));
    FillMatrixWithRandomValues(matrix10);
    FillMatrixWithRandomValues(matrix100);
    FillMatrixWithRandomValues(matrix1000);


    auto start = std::chrono::high_resolution_clock::now();
    SquareMatrix(matrix1000);
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Execution time for a " << 1000<< "x" << 1000 << " matrix: " << duration << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    SquareMatrix(matrix100);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Execution time for a " << 100<< "x" << 100 << " matrix: " << duration << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    int repetitions = 100;
    for (int i = 0; i < repetitions; ++i) {
        SquareMatrix(matrix10);
    }
    end = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / static_cast<double>(repetitions);

    std::cout << "Average execution time for a " << 10 << "x" << 10 << " matrix: " << duration << " microseconds" << std::endl;

    return 0;
}

/*
Execution time for a 1000x1000 matrix: 8.77637e+06 microseconds
Execution time for a 100x100 matrix: 7711 microseconds
Average execution time for a 10x10 matrix: 8.99 microseconds*/
