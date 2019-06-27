#include <iostream>
#include "LinearRegression.hpp"
#include "NeuralNetwork.hpp"

using namespace std;
using namespace bombar;

void testLinearRegression()
{
    cout << "Linear Regression Testing" << endl;

    Table dataset;

    double datas[][2] = {{0, 0}, {1.4, 3}, {6.2, 7}, {9.52, 12.1}};

    for (int i = 0; i < 4; i++)
        dataset.push_back(datas[i]);
    
    LinearRegression reg(dataset);

    cout << "Initial          \t: ";
    reg.printHFunc();
    reg.fit(GRADIENT_DESCENT);

    cout << "Gradient Descent  \t: ";
    reg.printHFunc();
    reg.fit(LEAST_SQUARES);

    cout << "Least Squares      \t: ";
    reg.printHFunc();

    cout << endl << endl;
}

int main()
{
    // testLinearRegression();

    vector<matrix> vec;
    matrix input(4, 1);
    matrix output(2, 1);

    cout << "lol" << endl;

    BasicNeuralNet net(4, 2);

    net.run(input, output);

    // output.print();
}
