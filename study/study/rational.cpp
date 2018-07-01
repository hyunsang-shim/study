#include "Rational.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

Rational::Rational()	// 문제 14.2 풀이 적용됨
{
	r[0] = 0;
	r[1] = 1;
}

Rational::Rational(int numerator, int denominator)	// 문제 14.2 풀이 적용됨
{
	int factor = gcd(numerator, denominator);
	this->r[0] = ((denominator > 0) ? 1 : -1) * numerator / factor;
	this->r[1] = abs(denominator) / factor;
}

Rational::Rational(double input)
{
	int divider = 1;
	int tmp = (int)input;

	//소수를 완전히 정수로 만든다 (소수 밑을 소수점 왼쪽으로 옮긴다)
	while (1)
	{
		divider *= 10;

		tmp = input * divider;

		if ((tmp % 10 == 0))
			break;
	}

	//정수 계산하듯 기약분수 만든다.
	int factor = gcd(tmp, divider);
	this->r[0] = ((divider > 0) ? 1 : -1) * tmp / factor;
	this->r[1] = abs(divider) / factor;
}

int Rational::getNumerator() const	// 문제 14.2 풀이 적용됨
{
	return r[0];
}

int Rational::getDenominator() const	// 문제 14.2 풀이 적용됨
{
	return r[1];
}

Rational Rational::add(const Rational& secondRational) const	// 문제 14.2 풀이 적용됨
{
	int n = r[0] * secondRational.getDenominator() + r[1] * secondRational.getNumerator();
	int d = r[1] * secondRational.getDenominator();

	return Rational(n, d);
}

Rational Rational::subtract(const Rational& secondRational) const
{
	int n = r[0] * secondRational.getDenominator() - r[1] * secondRational.getNumerator();
	int d = r[1] * secondRational.getDenominator();
	
	return Rational(n, d);
}

Rational Rational::multiply(const Rational& secondRational) const	// 문제 14.2 풀이 적용됨
{
	int n = r[0] * secondRational.getNumerator();
	int d = r[1] * secondRational.getDenominator();

	return Rational(n, d);
}

Rational Rational::divide(const Rational & secondRational) const	// 문제 14.2 풀이 적용됨
{
	int n = r[0] * secondRational.getDenominator();
	int d = r[1] * secondRational.r[0];

	return Rational(n,d);
}

int Rational::compareTo(const Rational & secondRational) const
{
	Rational temp = subtract(secondRational);
	if (temp.getNumerator() < 0)
		return -1;
	else if (temp.getNumerator() == 0)
		return 0;
	else 
		return 1;	
}

bool Rational::equals(const Rational & secondRational) const
{
	if (compareTo(secondRational) == 0)
		return true;
	else
		return false;
}

bool Rational::operator<(const Rational & secondRational) const
{
	if (compareTo(secondRational) < 0)
		return true;
	else
		return false;
}

bool Rational::operator<=(const Rational & secondRational) const
{
	if (compareTo(secondRational) <= 0)
		return true;
	else
		return false;
}

bool Rational::operator>(const Rational & secondRational) const
{
	if (compareTo(secondRational) > 0)
		return true;
	else
		return false;
}

bool Rational::operator>=(const Rational & secondRational) const
{
	if (compareTo(secondRational) >= 0)
		return true;
	else
		return false;
}

Rational Rational::operator+(const Rational & secondRational) const
{
	return this->add(secondRational);
}


Rational Rational::operator-(const Rational & secondRational) const
{
	return this->subtract(secondRational);
}

Rational &Rational::operator+=(const Rational & secondRational)
{
	*this = add(secondRational);

	return *this;
}

Rational &Rational::operator-=(const Rational & secondRational)
{
	*this = subtract(secondRational);
	return *this;
}

Rational & Rational::operator++()	// 문제 14.2 풀이 적용됨
{
	r[0] += r[1];
	return *this;
}
Rational Rational::operator++(int dummy)	// 문제 14.2 풀이 적용됨
{
	Rational temp(r[0], r[1]);
	r[0] += r[1];
	return temp;
}
Rational & Rational::operator--()	// 문제 14.2 풀이 적용됨
{
	r[0] -= r[1];
	return *this;
}
Rational Rational::operator--(int dummy)
{
	Rational temp(*this);
	add(Rational(-1, 0));
	return temp;

	return Rational();
}

Rational::operator double()
{
	return doubleValue();
}
int Rational::intValue() const
{
	return getNumerator() / getDenominator();
}

double Rational::doubleValue() const
{
return 1.0 * getNumerator() / getDenominator();
}

string Rational::toString() const	// 문제 14.2 풀이 적용됨
{
	stringstream ss;
	ss << r[0];

	if (r[1] > 1)
		ss << "/" << r[1];

	return ss.str();
}


int Rational::gcd(int n, int d)
{
	int n1 = abs(n);
	int n2 = abs(d);
	int gcd = 1;

	for (int k = 1; k <= n1 && k <= n2; k++)
	{
		if (n1 %k == 0 && n2%k == 0)
			gcd = k;
	}

	return gcd;
}

ostream & operator<<(ostream & out, const Rational & rational)	// 문제 14.2 풀이 적용됨
{
	
	if (rational.r[1] == 1)
		cout << rational.r[0];
	else
		out << rational.r[0] << "/" << rational.r[1];
	return out;
}
