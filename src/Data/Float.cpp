#include "Float.h"
#include <cmath>

NL_NAMEUSING

Float::Float()
{
	n = 0.00000f;
}

Float::Float(float _n)
{
	n = _n;
}

Float::Float(int _n)
{
	n = float(_n);
}

Float::Float(double _n)
{
	n = float(_n);
}
Float::Float(const Float & copy)
{
	this->n = copy.n;
}
float Float::getNative()
{
	return n;
}
float Float::getRound(int numberfloat)
{
	ASSERT(numberfloat > 0)
    int nPow = pow(10, numberfloat);
    return static_cast<double>(static_cast<int>(n*nPow)) / nPow;
}
float Float::getDecimal()
{
	return n - (int)n;
}

NString Float::toString()
{
	NString str = NString::fromDouble(this->n);
	if (str[str.getLength()-1] == '.')
		str.Replace(".", "");

	return str;
}

int Float::toInt()
{
    return (int)n;
}
void Float::operator*=(Float addMe)
{
	this->n = this->getNative() * addMe.getNative();
}
void Float::operator*=(float addMe)
{
	this->n = this->getNative() * addMe;
}
void Float::operator/=(Float addMe)
{
	this->n = this->getNative() / addMe.getNative();
}
void Float::operator/=(float addMe)
{
	this->n = this->getNative() / addMe;
}
void Float::operator+=(Float addMe)
{
	this->n = this->getNative() + addMe.getNative();
}
void Float::operator+=(float addMe)
{
	this->n = this->getNative() + addMe;
}
void Float::operator-=(Float addMe)
{
	this->n = this->getNative() - addMe.getNative();
}
void Float::operator-=(float addMe)
{
	this->n = this->getNative() - addMe;
}
void Float::operator=(Float addMe)
{
	this->n = addMe.getNative();
}
void Float::operator=(float addMe)
{
	this->n = addMe;
}
Float Float::operator+(Float addMe)
{
	return this->getNative() + addMe.getNative();
}
Float Float::operator+(float addMe)
{
	return this->getNative() + addMe;
}
Float Float::operator-(Float addMe)
{
	return this->getNative() - addMe.getNative();
}
Float Float::operator-(float addMe)
{
	return this->getNative() - addMe;
}
Float Float::operator*(Float addMe)
{
	return this->getNative() * addMe.getNative();
}
Float Float::operator*(float addMe)
{
	return this->getNative() * addMe;
}
Float Float::operator/(Float addMe)
{
	return this->getNative() / addMe.getNative();
}
Float Float::operator/(float addMe)
{
	return this->getNative() / addMe;
}

bool Float::operator<(Float addMe)
{
	return this->getNative() < addMe.getNative();
}
bool Float::operator<(float addMe)
{
	return this->getNative() < addMe;
}
bool Float::operator>(Float addMe)
{
	return this->getNative() > addMe.getNative();
}
bool Float::operator>(float addMe)
{
	return this->getNative() < addMe;
}
bool Float::operator<=(Float addMe)
{
	return this->getNative() <= addMe.getNative();
}
bool Float::operator<=(float addMe)
{
	return this->getNative() <= addMe;
}
bool Float::operator>=(Float addMe)
{
	return this->getNative() >= addMe.getNative();
}
bool Float::operator>=(float addMe)
{
	return this->getNative() >= addMe;
}
bool Float::operator==(Float addMe)
{
	return this->getNative() == addMe.getNative();
}
bool Float::operator==(float addMe)
{
	return this->getNative() == addMe;
}
