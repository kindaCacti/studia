#include "fract.h"


fract::fract(int num, unsigned int denom)
    : numerator(num), denominator(denom)
{
    unsigned int divisor = gcd(numerator, denominator);
    if (divisor > 1)
    {
        numerator /= divisor;
        denominator /= divisor;
    }
}

int fract::num() const
{
    return numerator;
}

unsigned int fract::denom() const
{
    return denominator;
}

void fract::print(std::ostream& os) const
{
    os << num();
    if (denom() != 1)
        os << '/' << denom();
}

bool fract::equal(const fract& right) const{
    int vgcd = gcd(denom(), right.denom());
    int leftNumerator = num() * (right.denom() / vgcd);
    int rightNumerator = right.num() * (denom() / vgcd);
    return (leftNumerator == rightNumerator);
}

fract fract::neg() const{
    return fract(-num(), denom());
}

void fract::add(const fract& right){
    int vgcd = gcd(denom(), right.denom());
    int leftNumerator = num() * (right.denom() / vgcd);
    int rightNumerator = right.num() * (denom() / vgcd);
    this->numerator = leftNumerator + rightNumerator;
    this->denominator = denom() * (right.denom() / vgcd);
}

fract fract::sum(const fract& right) const{
    /*int vgcd = gcd(denom(), right.denom());
    int leftNumerator = num() * (right.denom() / vgcd);
    int rightNumerator = right.num() * (denom() / vgcd);
    int nume = leftNumerator + rightNumerator;
    int deno = denom() * (right.denom() / vgcd);*/

    fract tmp(num(), denom());
    tmp.add(right);
    return tmp;
}

void fract::mul(const fract& right){
    int gcd1 = gcd(num(), right.denom());
    int gcd2 = gcd(denom(), right.num());
    this->numerator = (right.num() / gcd2) * (num() / gcd1);
    this->denominator = (denom() / gcd2) * (right.denom() / gcd1);
}

fract fract::prod(const fract& right) const{
    fract tmp(denom(), num());
    tmp.mul(right);
    fract out(tmp.denom(), tmp.num());
    return out;
}

unsigned int gcd(unsigned int a, unsigned int b)
{
    while (a > 0 && b > 0)
    {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return std::max(a, b);
}
