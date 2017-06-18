//
//  Complex.hpp
//  Complex
//
//  Copyright © 2017 Xavier Merino. All rights reserved.
//

#ifndef Complex_hpp
#define Complex_hpp

#include <iostream>

class Complex {
public:
    Complex(double re = 0, double im = 0);
    double getReal() const;
    double getImaginary() const;
    Complex& setReal(const double re);
    Complex& setImaginary(const double im);
    Complex operator+(const Complex& number) const;
    Complex operator-(const Complex& number) const;
    Complex operator*(const Complex& number) const;
    Complex operator/(const Complex& number) const;
    std::string toPolarForm() const;
    friend std::ostream& operator<<(std::ostream&, const Complex&);
    
private:
    double re;
    double im;
    Complex add(const Complex& number) const;
    Complex subtract(const Complex& number) const;
    Complex multiply(const Complex& number) const;
    Complex divide(const Complex& number) const;
};

#endif /* Complex_hpp */
