#pragma once

#ifndef FRACTION_H
#define FRACTION_H

#include "Fraction_global.h"
#include <iostream>
using namespace std;

// An exception that is thrown if an attempt is made to create a
// Fraction with a zero value denominator.
class FRACTION_EXPORT FractionException {
public:
    FractionException(const string&);
    string& what();
private:
    string message;
};

class FRACTION_EXPORT Fraction
{
public:
    // Constructs a fraction with numerator 0 and denominator 1.
    Fraction();

    // Constructs a fraction with numerator t and denominator 1.
    Fraction(int t);

    // Constructs a fraction with given numerator and denominator.
    Fraction(int t, int b);

    // Returns the numerator.
    int numerator() const;

    // Returns the denominator.
    int denominator() const;

    // Updates a fraction by adding in another fraction value.
    Fraction& operator+=(const Fraction& right);

    // Increment fraction by 1.
    Fraction& operator++(); 			// Preincrement form
    Fraction operator++(int unused); // Postincrement form

    // Compare one fraction value to another.
    // Result is negative if less than right, zero if equal, and
    // positive if greater than right.
    int compare(const Fraction& right) const;

private:
    // Place the fraction in lowest common denominator form.
    FRACTION_EXPORT void normalize();

    // Compute the greatest common denominator of two integer values.
    FRACTION_EXPORT int gcd(int n, int m);

    int top;			// numerator
    int bottom;		// denominator
};

// Non-member overloaded arithmetic operators
FRACTION_EXPORT Fraction operator+(const Fraction& left, const Fraction& right);
FRACTION_EXPORT Fraction operator-(const Fraction& left, const Fraction& right);
FRACTION_EXPORT Fraction operator*(const Fraction& left, const Fraction& right);
FRACTION_EXPORT Fraction operator/(const Fraction& left, const Fraction& right);
FRACTION_EXPORT Fraction operator-(const Fraction& value);

// Non-member overloaded boolean operators
FRACTION_EXPORT bool operator<(const Fraction& left, const Fraction& right);
FRACTION_EXPORT bool operator<=(const Fraction& left, const Fraction& right);
FRACTION_EXPORT bool operator==(const Fraction& left, const Fraction& right);
FRACTION_EXPORT bool operator!=(const Fraction& left, const Fraction& right);
FRACTION_EXPORT bool operator>=(const Fraction& left, const Fraction& right);
FRACTION_EXPORT bool operator>(const Fraction& left, const Fraction& right);

// Non-member stream operators
FRACTION_EXPORT ostream& operator<<(ostream& out, const Fraction& value);
FRACTION_EXPORT istream& operator>>(istream& in, Fraction& retFrac);


#endif // FRACTION_H
