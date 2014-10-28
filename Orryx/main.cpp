#include <iostream>

#include "OrryxMath.h"

using namespace orx;

int main(int argc, char* argv[])
{
    Vector3 test(1.f, 0.f, 0.f);
    Matrix rot = Matrix::fromRotateY(1.f);
    test.transform(rot);
    std::cout << rot.toString() << std::endl << std::endl << test.toString();
    std::cin.get();

    return 0;
}