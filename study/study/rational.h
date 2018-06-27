#pragma once

#include <string>

using namespace std;

class Rational
{
public:
	Rational();
	Rational(int numerator, int denominator);
	int getNumerator() const;
	int getDenominator() const;
	Rational add(const Rational& secondRational) const;
	Rational subtract(const Rational& secondRational) const;
	Rational multiply(const Rational& secondRational) const;
	Rational divide(const Rational& secondRational) const;
	int compareTo(const Rational& secondRational) const;
	bool equals(const Rational& secondRational) const;
	bool operator<(const Rational& secondRational) const;
	bool operator<=(const Rational& secondRational) const;
	bool operator>(const Rational& secondRational) const;
	bool operator>=(const Rational& secondRational) const;
	Rational operator+(const Rational& secondRational) const;
	Rational operator-(const Rational& secondRational) const;
	Rational &operator+=(const Rational& secondRational);
	Rational &operator-=(const Rational& secondRational);
	Rational &operator++();
	Rational operator++(int dummy);
	Rational &operator--();
	Rational operator--(int dummy);
	friend ostream& operator<<(ostream & out, const Rational & rational);
	operator double();



	int intValue() const;
	double doubleValue() const;
	string toString() const;
	

private:
	//int numerator;		// 원본
	//int denominator;		// 원본
	static int gcd(int n, int d);
	int r[2];	// 문제 14.2번 풀이용
};
