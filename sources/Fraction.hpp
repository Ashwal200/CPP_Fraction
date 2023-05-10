#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;




namespace ariel {


class Fraction
{
// Private members
private:
    int numerator;
    int denominator;

public:
    // Constructor

    // We have here constructors that 
    // can create a new fraction object default or from an integer, 
    // two integers, or a float. 
    // And we have a copy constructor and move constructor 
    // that help us when we need to copy large data.
    Fraction();
    Fraction(const Fraction& frac);
    Fraction(Fraction&& frac) noexcept;
    //Fraction(int number);
    Fraction(int , int);
    Fraction(float number);

    // Descructor

    // The descructor is default because we didn't allocate data.
    ~Fraction() = default;
    
    // Operators

    // Copy assignment operator that take a new value of fraction
    // to existing fraction.
    Fraction& operator=(const Fraction& frac);

    // The move assignment operator that take the value of a temp fraction.
    Fraction& operator=(Fraction&& frac) noexcept;
    
    // - PLUS
    const friend Fraction operator+(const Fraction& frac1, const Fraction& frac2);

    // - MINUS
    const friend Fraction operator-(const Fraction& frac1, const Fraction& frac2);
 
    // - MULT
    const friend Fraction operator*(const Fraction& frac1, const Fraction& frac2);

    // - DIVID
    const friend Fraction operator/(const Fraction& frac1, const Fraction& frac2);


    // Comparisons
    friend bool operator==(const Fraction& frac1, const Fraction& frac2);

    friend bool operator!=(const Fraction& frac1, const Fraction& frac2);
    
    friend bool operator>=(const Fraction& frac1, const Fraction& frac2);

    friend bool operator<=(const Fraction& frac1, const Fraction& frac2);

    friend bool operator>(const Fraction& frac1, const Fraction& frac2);

    friend bool operator<(const Fraction& frac1, const Fraction& frac2);


    // increment and decrement
    Fraction& operator++(); // ++i
    const Fraction operator++(int); // i++
    Fraction& operator--(); // --i
    const Fraction operator--(int); // i--

    friend ostream& operator<<(ostream& oss, const Fraction& fraction);
    friend istream& operator>>(istream& iss, Fraction& fraction);
    
    // Getter & Setter
    int getNumerator();
    
    int getDenominator();

    // Some help function
    void reduce_init();
};

}

#endif


