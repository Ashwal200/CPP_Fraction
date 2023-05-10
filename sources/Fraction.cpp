#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <numeric> // For __gcd; taken from the internet
#include <cmath>
#include <stdexcept>
#include <limits.h> // https://www.geeksforgeeks.org/int_max-int_min-cc-applications/
#
using namespace std;

#include "Fraction.hpp"
using namespace ariel;

namespace ariel
{
    


    void Fraction::reduce_init()
    {
	if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
        int my_gcd = abs(gcd(numerator, denominator));
        numerator = numerator / my_gcd;
        denominator = denominator / my_gcd;
    }

    // Constructors

    Fraction::Fraction() : numerator(0), denominator(1) {}
    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if (den == 0)
        {
            throw invalid_argument("Division by zero!");
        }
        reduce_init();
    }

    Fraction::Fraction(float number)
    {
        Fraction ans(static_cast<int>(number*1000) , 1000);
        numerator = ans.numerator;
        denominator = ans.denominator;
        reduce_init();
    }

    Fraction::Fraction(const Fraction &frac) : numerator(frac.numerator), 
    denominator(frac.denominator) {}

    Fraction::Fraction(Fraction &&frac) noexcept : numerator(frac.numerator), 
    denominator(frac.denominator) {}

    // Operators
    Fraction &Fraction::operator=(const Fraction &frac)
    {
        if (*this == frac)
            return *this;

        this->numerator = frac.numerator;
        this->denominator = frac.denominator;
        return *this;
    }

    Fraction &Fraction::operator=(Fraction &&frac) noexcept
    {
        if (*this == frac)
            return *this;

        this->numerator = frac.numerator;
        this->denominator = frac.denominator;
        return *this;
    }

    bool check_range(long long num)
    {
        return num <= INT_MAX && num >= INT_MIN;
    }



    Fraction check_overflow(int num1, int den1, int num2, int den2, int option) {
	
	long long check_num;
	long long check_den;
        // check the plus operation
	if( option == 0){
            check_den = static_cast<long long>(den1) * static_cast<long long>(den2);
            long long check_num1 = static_cast<long long>(num1) * static_cast<long long>(den2); 
            long long check_num2 = static_cast<long long>(den1) * static_cast<long long>(num2);
            check_num = check_num1 + check_num2;
       
            if (check_range(check_den) && check_range(check_num) && check_range(check_num1) 
            	&& check_range(check_num2))
            {
                return Fraction(check_num , check_den);
            }
            else
                throw overflow_error("The number is out of the range!");
            }
                
        
        // Check the mult operation
        if( option == 1){
            check_den = static_cast<long long>(den1) * static_cast<long long>(den2);
            check_num = static_cast<long long>(num1) * static_cast<long long>(num2);
 
            if (check_range(check_den) && check_range(check_num) )
            {
                return Fraction(check_num , check_den);
            }
            else
                throw overflow_error("The number is out of the range!");    
            }

        return NULL;}


    // Plus

    const Fraction operator+(const Fraction &frac1, const Fraction &frac2)
    {
        Fraction ans = check_overflow(frac1.numerator , frac1.denominator, frac2.numerator , frac2.denominator , 0);
        return ans;
    }

    // Minus

    const Fraction operator-(const Fraction &frac1, const Fraction &frac2)
    {
        Fraction oposite = frac2 * (-1);
        Fraction ans = check_overflow(frac1.numerator , frac1.denominator, 
        oposite.numerator , oposite.denominator , 0);
        return ans;
    }

    // Multiply

    const Fraction operator*(const Fraction &frac1, const Fraction &frac2)
    {
        Fraction ans = check_overflow(frac1.numerator , frac1.denominator, frac2.numerator , frac2.denominator , 1);
        return ans;
    }

    // Divide

const Fraction operator/(const Fraction& frac1, const Fraction& frac2) 
    {
        if (frac2.numerator == 0)
        {
            throw runtime_error("Division by zero!");
        }
        Fraction ans = frac1 * Fraction(frac2.denominator, frac2.numerator);
        return ans;
    }


    // Comparisons

    bool operator==(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.numerator == frac2.numerator && frac1.denominator == frac2.denominator)
        {
            return true;
        }
        return false;
    }

    bool operator!=(const Fraction& frac1, const Fraction& frac2)
    {
        return !(frac1== frac2);
    }
    
    bool operator>=(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1 == frac2)
        {
            return true;
        }
        if (frac1.numerator * frac2.denominator > frac1.denominator * frac2.numerator)
        {
            return true;
        }

        return false;
    }

    bool operator<=(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1 == frac2)
        {
            return true;
        }
        if (frac1.numerator * frac2.denominator < frac1.denominator * frac2.numerator)
        {
            return true;
        }

        return false;
    }

    bool operator>(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.numerator * frac2.denominator > frac1.denominator * frac2.numerator)
        {
            return true;
        }

        return false;
    }

    bool operator<(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.numerator * frac2.denominator < frac1.denominator * frac2.numerator)
        {
            return true;
        }

        return false;
    }

    // increment and decrement
    Fraction &Fraction::operator++()
    {
        this->numerator = this->numerator + this->denominator;
        reduce_init();
        return *this;
    }
    const Fraction Fraction::operator++(int)
    {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }
    Fraction &Fraction::operator--()
    {
        this->numerator = this->numerator - this->denominator;
        reduce_init();
        return *this;
    }
    const Fraction Fraction::operator--(int)
    {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    ostream &operator<<(ostream &oss, const Fraction &fraction)
    {
        return oss << fraction.numerator << '/' << fraction.denominator;
    }

    istream &operator>>(istream &iss, Fraction &fraction)
    {
    	iss >> fraction.numerator >> fraction.denominator;
    	if (iss.fail() || fraction.denominator == 0)
        {
            throw runtime_error("error");
        }
        fraction.reduce_init();
        return iss;
    }

    int Fraction::getNumerator() { return numerator; }

    int Fraction::getDenominator() { return denominator; }




}

