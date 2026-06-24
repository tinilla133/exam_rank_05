/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 22:19:32 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/14 00:36:41 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"
#include <sstream>

bigint& bigint::reverse()
{	
	for (size_t i = 0, j = nbr.size() - 1; i < j; i++, j--) {
		char swap = nbr[i];
		nbr[i] = nbr[j];
		nbr[j] = swap;		
	}

	return *this;
}

bigint& bigint::pad(size_t _size)
{
	// std::cout << "Not padded: " << *this << std::endl;
	
	if (_size > nbr.size()) {
		nbr.append(_size - nbr.size(), '0');
	}

	// std::cout << "Padded: " << *this << std::endl;
		
	return *this;
}

bigint::bigint() : nbr("0") 
{

}

bigint::bigint(unsigned int _nbr)
{
	std::stringstream ss;

	ss << _nbr;
	
	nbr = ss.str();
}

bigint::bigint(const bigint& _bigint)
{
	*this = _bigint;
}

bigint::~bigint()
{
	
}

bigint& bigint::operator=(const bigint& _bigint)
{
	nbr = _bigint.nbr;

	return *this;
}

std::string bigint::getNbrStr() const
{
	return nbr;
}

unsigned int bigint::getNbrUint() const
{
	unsigned int res;
	std::stringstream ss(nbr);

	ss >> res;

	return res;
}

bigint bigint::operator+(const bigint& _bigint) const
{
	bigint sum1 = *this;
	bigint sum2 = _bigint;

	size_t _size = sum1.nbr.size() > sum2.nbr.size() ? sum1.nbr.size() : sum2.nbr.size();
	char tmp;
	int carry = 0;
	
	sum1.reverse().pad(_size);
	sum2.reverse().pad(_size);

	for (size_t i = 0; i < _size; i++) {
		tmp = sum1.nbr[i] - '0' + sum2.nbr[i] - '0' + carry;
		if (tmp > 9) {
			carry = tmp / 10;
			tmp = tmp % 10;
		}
		else {
			carry = 0;
		}
		sum1.nbr[i] = tmp + '0';
	}
	if (carry) {
		sum1.nbr.push_back('1');
	}
	
	return sum1.reverse();
}

bigint& bigint::operator+=(const bigint& _bigint)
{
	*this = *this + _bigint;

	return *this;
}

bigint bigint::operator++(int)
{
	bigint res = *this;

	*this = *this + bigint(1);

	return res;
}

bigint& bigint::operator++()
{
	*this = *this + bigint(1);

	return *this;
}

bigint bigint::operator<<(unsigned int _nbr) const
{
	bigint res = *this;
	
	res.nbr.append(_nbr, '0');

	return res;
}

bigint& bigint::operator<<=(unsigned int _nbr)
{
	*this = *this << _nbr;

	return *this;
}

bigint bigint::operator>>(unsigned int _nbr) const
{
	bigint res = *this;
	
	if (res.nbr.size() < _nbr) {
		return bigint();
	}
	res.nbr.erase(res.nbr.size() - _nbr, _nbr);

	return res;
}

bigint& bigint::operator>>=(unsigned int _nbr)
{
	*this = *this >> _nbr;

	return *this;
}

bigint bigint::operator<<(const bigint& _bigint) const
{
	bigint res = *this;
	
	res.nbr.append(_bigint.getNbrUint(), '0');

	return res;
}

bigint& bigint::operator<<=(const bigint& _bigint)
{
	*this = *this << _bigint.getNbrUint();
	
	return *this;
}

bigint bigint::operator>>(const bigint& _bigint) const
{
	bigint res = *this;
	
	if (res.nbr.size() < _bigint.getNbrUint()) {
		return bigint();
	}
	res.nbr.erase(res.nbr.size() - _bigint.getNbrUint(), _bigint.getNbrUint());

	return res;
}

bigint& bigint::operator>>=(const bigint& _bigint)
{
	*this = *this >> _bigint.getNbrUint();

	return *this;
}

bool bigint::operator==(const bigint& _bigint) const
{
	return nbr == _bigint.nbr;
}

bool bigint::operator!=(const bigint& _bigint) const
{
	return !(nbr == _bigint.nbr);
}

bool bigint::operator<(const bigint& _bigint) const
{
	if (nbr.size() != _bigint.nbr.size()) {
		return nbr.size() < _bigint.nbr.size();
	}
	return nbr < _bigint.nbr;
}

bool bigint::operator>(const bigint& _bigint) const
{
	if (*this != _bigint) {
		return !(*this < _bigint);
	}
	return false;
}

bool bigint::operator<=(const bigint& _bigint) const
{
	return (*this < _bigint) || (*this == _bigint);
}

bool bigint::operator>=(const bigint& _bigint) const
{
	return (*this > _bigint) || (*this == _bigint);
}

std::ostream& operator<<(std::ostream& _output, const bigint& _bigint)
{
	std::cout << _bigint.getNbrStr();

	return _output;
}





