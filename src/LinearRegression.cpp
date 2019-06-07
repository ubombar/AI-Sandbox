#include "LinearRegression.hpp"

#include <vector>
#include <iostream>

const double 
bombar::HFunction::function(const double x)
{
    return Omega0 + Omega1 * x;
}

const double 
bombar::CostFunction::function(bombar::HFunction& hfunc, const bombar::Table& dataset)
{
    double total = 0;
    int m2 = 0;

    for (const double* e : dataset)
    {
        // We assert that table has only 2 columns, first is x and second is y
        double x = e[0];
        double y = e[1];
        double h = hfunc.function(x);

        double cost = (h - y);

        total += cost * cost;
        m2 += 2;
    }

    return total / m2;
}

const double 
bombar::CostFunction::functionPrime0(bombar::HFunction& hfunc, const bombar::Table& dataset)
{
    double total = 0;
    int m = 0;

    for (const double* e : dataset)
    {
        // We assert that table has only 2 columns, first is x and second is y
        double x = e[0];
        double y = e[1];
        double h = hfunc.function(x);

        double cost = (h - y);

        total += cost;
        m += 1;
    }

    return total / m;
}

const double 
bombar::CostFunction::functionPrime1(bombar::HFunction& hfunc, const bombar::Table& dataset)
{
    double total = 0;
    int m = 0;

    for (const double* e : dataset)
    {
        // We assert that table has only 2 columns, first is x and second is y
        double x = e[0];
        double y = e[1];
        double h = hfunc.function(x);

        double cost = (h - y) * x;

        total += cost;
        m += 1;
    }

    return total / m;
}

bombar::LinearRegression::LinearRegression(Table& dataset)
: learningRate(0.001), dataset(dataset)
{
    // We give a appropriate learning rate, later implementations 
    // will decide the learning rate by examining the data.
}

bombar::HFunction 
bombar::LinearRegression::fit(const int id, double maxError)
{
    switch (id)
    {
        case GRADIENT_DESCENT:
        {
            int maxIter = 100000; // We want to have 0.01% maximum error to stop execution at 100000 iterations

            int iter = 0;
            double error = 1;

            while (iter < maxIter && error > maxError)
            {
                gradientDescent();
                iter++;
                error = costfunc.function(hfunc, dataset);
            }

            // std::cout << error << std::endl;
        }
        break;
    
        case LEAST_SQUARES:
        {
            double sumXY = 0;
            double sumX = 0;
            double sumY = 0;
            double sumX2 = 0;

            for (const double* e : dataset)
            {
                double x = e[0];
                double y = e[1];

                sumXY += x * y;
                sumX += x;
                sumY += y;
                sumX2 += x * x;
            }

            hfunc.Omega1 = (dataset.size() * sumXY - sumX * sumY) / (dataset.size() * sumX2 - sumX * sumX);
            hfunc.Omega0 = (sumY - hfunc.Omega1 * sumX) / (dataset.size());
        }
        break;
    }

    return hfunc;
}

void
bombar::LinearRegression::printHFunc()
{
    std::cout << "error: %" << costfunc.function(hfunc, dataset) * 100 << "\t h(x) = " << hfunc.Omega0 << " + " << hfunc.Omega1 << " * x" << std::endl;
}

void 
bombar::LinearRegression::gradientDescent()
{
    double nOmega0 = hfunc.Omega0 - learningRate * costfunc.functionPrime0(hfunc, dataset) * costfunc.function(hfunc, dataset);
    double nOmega1 = hfunc.Omega1 - learningRate * costfunc.functionPrime1(hfunc, dataset) * costfunc.function(hfunc, dataset);
    hfunc.Omega0 = nOmega0;
    hfunc.Omega1 = nOmega1;
    // Performs simontaneous gradient descent
}