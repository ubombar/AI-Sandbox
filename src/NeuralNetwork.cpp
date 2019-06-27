#include "NeuralNetwork.hpp"

#include <iostream>

// Begining of Matrix implementations

bombar::matrix::matrix(const uint N, const uint M, const double value)
: N(N), M(M), data(NULL)
{
    // by default it initializes matrix as 1 matrix
    // all weights are initialized as 1.
    // the matrix is imutable by operations
    // can only be muted by set

    // std::cout << "constructor" << std::endl;

    createEmpty(value);
}

bombar::matrix::matrix(const bombar::matrix& mat) 
: N(mat.N), M(mat.M), data(NULL)
{
    // std::cout << "copy constructor" << std::endl;
    createMatrix(mat);
}

bombar::matrix::~matrix()
{
    // std::cout << "destructor" << std::endl;
    destroy();
}

void 
bombar::matrix::print() const
{
    std::cout << std::endl << "matrix " << N << "x" << M << "" << std::endl;

    for (int i = 0; i < N; i++)
    {
        std::cout << "\t";

        for (int j = 0; j < M; j++)
            std::cout << data[i][j] << "\t";

        std::cout << "" << std::endl;
    }
}

double 
bombar::matrix::get(const int& row, const int& column) const
{
    return data[row][column];
}

void 
bombar::matrix::set(const int& row, const int& column, const double& num)
{
    data[row][column] = num;
}

void bombar::matrix::size(uint& row, uint& column) const
{
    row = N;
    column = M;
}

bombar::matrix&
bombar::matrix::operator=(const matrix& mat)
{
    // std::cout << "copy operator" << std::endl;
    destroy();
    createMatrix(mat);
    return *this;
}

bombar::matrix&
bombar::matrix::operator+(const double& num)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            data[i][j] += num;
            
    return *this;
}

bombar::matrix&
bombar::matrix::operator-(const double& num)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            data[i][j] -= num;
            
    return *this;
}

bombar::matrix&
bombar::matrix::operator*(const double& num)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            data[i][j] *= num;
            
    return *this;
}

bombar::matrix&
bombar::matrix::operator/(const double& num)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            data[i][j] /= num;
            
    return *this;
}

bombar::matrix&
bombar::matrix::operator*(const bombar::matrix& mat)
{
    if (mat.N != M)
        throw std::exception();

    

    matrix result(N, mat.M, 0);
    double dot;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            dot = 0;

            for (int k = 0; k < M; k++) // runs for dot product
                dot += data[i][k] * mat.data[k][j];

            result.data[i][j] = dot;
        }
    }

    std::cout << "avrat 1" << std::endl;

    destroy();
    createMatrix(result);

    std::cout << "avrat 2" << std::endl;
        
    return *this;
}

bombar::matrix&
bombar::matrix::operator+(const matrix& mat)
{
    if (mat.N != N || mat.M != M)
        throw std::exception();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            data[i][j] += mat.data[i][j];
            
    return *this;
}

bombar::matrix&
bombar::matrix::operator-(const matrix& mat)
{
    if (mat.N != N || mat.M != M)
        throw std::exception();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            data[i][j] -= mat.data[i][j];
            
    return *this;
}

void bombar::matrix::createEmpty(const double value)
{
    data = new double*[N];

    for (int i = 0; i < N; i++)
    {
        data[i] = new double[M];

        for (int j = 0; j < M; j++)
        {
            data[i][j] = value;
        }
    }
}

void bombar::matrix::createMatrix(const matrix& mat)
{
    data = new double*[N];

    for (int i = 0; i < N; i++)
    {
        data[i] = new double[M];

        for (int j = 0; j < M; j++)
        {
            data[i][j] = mat.data[i][j];
        }
    }
}

void bombar::matrix::destroy()
{
    for (int i = 0; i < N; i++)
        delete[] data[i];

    delete[] data;

    data = NULL;
}

// End of Matrix implementations

// Begining of NeuralNet implementations

bombar::BasicNeuralNet::BasicNeuralNet(const uint input, const uint output, uint lrate)
: lrate(lrate), W1(matrix(output, input)), B1(matrix(output, 1))
{
    // everything is done
}

void
bombar::BasicNeuralNet::run(const matrix& I, matrix& O)
{
    O = (W1 * I) + B1;
}