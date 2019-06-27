#ifndef __NEURAL_NETWORK_HPP
#define __NEURAL_NETWORK_HPP

#include <stdlib.h>
#include <list>
#include <vector>

namespace bombar
{
    class matrix
    {
        public:
            matrix(const uint N = 1, const uint M = 1, const double value = 1);
            matrix(const matrix& mat);

            ~matrix();

            void print() const;
            
            double get(const int& row, const int& column) const;
            void set(const int& row, const int& column, const double& num);

            void size(uint& row, uint& column) const;

            matrix& operator=(const matrix& mat);

            matrix& operator+(const double& num);
            matrix& operator-(const double& num);
            matrix& operator*(const double& num);
            matrix& operator/(const double& num);

            matrix& operator*(const matrix& mat);
            matrix& operator+(const matrix& mat);
            matrix& operator-(const matrix& mat);

        private:
            uint N;
            uint M;
            double** data;

            void createEmpty(const double value);
            void createMatrix(const matrix& mat);
            void destroy();
    };

    class BasicNeuralNet
    {
        public:
            BasicNeuralNet(
                const uint input, 
                const uint outut, 
                uint lrate = 0.01);

            void run(const matrix& I, matrix& O);
            void train(const uint iter = 10000);
            
        private:
            double gradientDescent();
            double cost();

            matrix W1;
            matrix B1;
            uint lrate;
    };
}

#endif