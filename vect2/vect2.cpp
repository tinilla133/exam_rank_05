/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:41:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/14 01:28:42 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2() : x(0), y(0)
{
	
}

vect2::vect2(int _x, int _y) : x(_x), y(_y)
{
	
}

vect2::vect2(const vect2& _vect)
{
	*this = _vect;
}

vect2::~vect2()
{

}

vect2& vect2::operator=(const vect2& _vect)
{
	x = _vect.x;
	y = _vect.y;

	return *this;
}

vect2 vect2::operator+(const vect2& _vect) const
{
	return vect2(x + _vect.x, y + _vect.y);
}

vect2& vect2::operator+=(const vect2& _vect)
{
	x = x + _vect.x;
	y = y + _vect.y;

	return *this;
}

vect2 vect2::operator-(const vect2& _vect) const
{
	return vect2( x - _vect.x, y - _vect.y);
}

vect2& vect2::operator-=(const vect2& _vect)
{
	x = x -_vect.x;
	y = y -_vect.y;

	return *this;
}

vect2 vect2::operator-() const
{
	return vect2(-x, -y);
}

vect2 vect2::operator*(int nbr) const
{
	return vect2(x * nbr, y * nbr);
}

vect2& vect2::operator*=(int nbr)
{
	x = x * nbr;
	y = y * nbr;

	return *this;
}

vect2 vect2::operator++(int)
{
	x = x + 1;
	y = y + 1;
	
	return vect2(x - 1, y - 1);
}

vect2& vect2::operator++()
{
	x = x + 1;
	y = y + 1;

	return *this;
}

vect2 vect2::operator--(int)
{
	x = x - 1;
	y = y - 1;
	
	return vect2(x + 1, y + 1);
}

vect2& vect2::operator--()
{
	x = x - 1;
	y = y - 1;

	return *this;
}

int vect2::operator[](unsigned int pos) const
{
	return !pos ? x : y;
}

int& vect2::operator[](unsigned int pos)
{
	return !pos ? x : y;
}

bool vect2::operator==(const vect2& _vect) const
{
	return (x == _vect.x) && (y == _vect.y);
}

bool vect2::operator!=(const vect2& _vect) const
{
	return !(*this == _vect);
}

vect2 operator*(int nbr, const vect2& _vect)
{
	return vect2(_vect.x * nbr, _vect.y * nbr);
}

std::ostream& operator<<(std::ostream& _output, const vect2& _vect)
{
	_output << "{" << _vect[0] << ", " << _vect[1] << "}" << std::endl;

	return _output;
}