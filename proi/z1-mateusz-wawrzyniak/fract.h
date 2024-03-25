#include <iostream>

class fract
{
    int numerator = 0;
    unsigned int denominator = 1;
public:
    fract() = default;
    fract(int num, unsigned int denom);

    int num() const;
    unsigned int denom() const;

    bool equal(const fract& right) const;

    fract neg() const;

    void add(const fract& right);
    fract sum(const fract& right) const;

    void mul(const fract& right);
    fract prod(const fract& right) const;

    void print(std::ostream& os) const;
};

unsigned int gcd(unsigned int a, unsigned int b);
