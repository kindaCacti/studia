#include "fract.h"
#include <iostream>


int main()
{
    {
        fract f(1, 3);
        if (f.num() != 1 || f.denom() != 3)
            std::cerr << "Error in values after fract(1, 3) ctor\n";
        f.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f(2, 4);
        if (f.num() != 1 || f.denom() != 2)
            std::cerr << "Error in values after fract(2, 4) ctor\n";
        f.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f(0, 500);
        if (f.num() != 0 || f.denom() != 1)
            std::cerr << "Error in values after fract(0, 1) ctor\n";
        f.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(0, 500);
        fract f2(100, 500);
        f2.add(f1);
        if (f2.num() != 1 || f2.denom() != 5)
            std::cerr << "Error in values after f2.add(f1) ctor\n";
        f2.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(3, 500);
        f1 = f1.sum(f1);
        if (f1.num() != 6 || f1.denom() != 500)
            std::cerr << "Error in values after f1.sum(f1) ctor\n";
        f1.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(3, 500);
        f1.mul(f1);
        if (f1.num() != 9 || f1.denom() != 250000)
            std::cerr << "Error in values after f1.mul(f1) ctor\n";
        f1.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(3, 500);
        f1.mul(f1);
        if (f1.num() != 9 || f1.denom() != 250000)
            std::cerr << "Error in values after f1.mul(f1) ctor\n";
        f1.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(3, 500);
        bool tmp = f1.equal(f1);
        if (!tmp)
            std::cerr << "Error in values after f1.equal(f1) ctor\n";
        f1.print(std::cout);
        std::cout << " is equal to ";
        f1.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(3, 500);
        fract f2(4, 500);
        bool tmp = f1.equal(f2);
        if (tmp)
            std::cerr << "Error in values after f1.equal(f1) ctor\n";
        f1.print(std::cout);
        std::cout << " is not equal to ";
        f2.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(3, 500);
        f1 = f1.prod(f1);
        if (f1.num() != 1 || f1.denom() != 1)
            std::cerr << "Error in values after f1.prod(f1) ctor\n";
        f1.print(std::cout);
        std::cout << std::endl;
    }

    {
        fract f1(10, 20);
        fract f2(100, 500);
        f2 = f2.prod(f1);
        if (f2.num() != 2 || f2.denom() != 5)
            std::cerr << "Error in values after f2.prod(f1) ctor\n";
        f2.print(std::cout);
        std::cout << std::endl;
    }

    std::cout << std::endl;
    return 0;
}