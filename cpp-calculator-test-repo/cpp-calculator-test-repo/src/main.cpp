#include <cstdlib>
#include <iostream>

#include "calculator.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: calculator <number> <operator> <number>\n";
        return 1;
    }

    const double a = std::atof(argv[1]);
    const char operation = argv[2][0];
    const double b = std::atof(argv[3]);

    std::cout << calculate(a, operation, b) << '\n';
    return 0;
}
