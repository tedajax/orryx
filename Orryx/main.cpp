#include <iostream>

#include "OrryxMath.h"

using namespace orx;

int main(int argc, char* argv[])
{
    Vector2 test(20.f, 10.f);
    std::cout << "vector <" << test.getX() << ", " << test.getY() << "> length is " << test.length() << std::endl;
    std::cin.get();
    return 0;
}