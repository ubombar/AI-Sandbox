#ifndef __LINEAR_REGRESSION_HPP
#define __LINEAR_REGRESSION_HPP

#define GRADIENT_DESCENT    0
#define LEAST_SQUARES       2

#include <vector>

namespace bombar
{
    typedef std::vector<double*> Table;

    struct HFunction
    {
        double Omega0 = 0;
        double Omega1 = 0;

        const double function(const double x);
    };

    struct CostFunction
    {
        const double function(HFunction& hfunc, const Table& dataset);
        const double functionPrime0(HFunction& hfunc, const Table& dataset);
        const double functionPrime1(HFunction& hfunc, const Table& dataset);
    };

    class LinearRegression
    {
        public:
            LinearRegression(Table& dataset);
            HFunction fit(const int id, double maxError = 0.0001);
            void printHFunc();

        private:
            HFunction hfunc;
            CostFunction costfunc;
            Table dataset;
            double learningRate;

            void gradientDescent();
    };
}


#endif