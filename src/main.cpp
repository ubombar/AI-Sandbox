#include <iostream>
#include "LinearRegression.hpp"

using namespace std;
using namespace bombar;

int main()
{
    cout << "Linear Regression Example" << endl;

    Table dataset;
    size_t n = 100;
    double** doo = new double*[4];

    double datas[][2] = {{0, 0}, {1.4, 3}, {6.2, 7}, {9.52, 12.1}};

    for (int i = 0; i < 4; i++)
        dataset.push_back(datas[i]);
    
    LinearRegression reg(dataset);

    cout << "Initialized at zero: \t";
    reg.printHFunc();
    reg.fit(GRADIENT_DESCENT);

    cout << "Gradient Descent: \t";
    reg.printHFunc();
    reg.fit(LEAST_SQUARES);

    cout << "Least Squares:   \t";
    reg.printHFunc();   
}
