/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 22:19:28 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/13 23:44:30 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class bigint
{
	private:
		std::string nbr;
		bigint& reverse();
		bigint& pad(size_t _size);

	public:
		bigint();
		bigint(const bigint& _bigint);
		bigint(unsigned int _nbr);
		bigint& operator=(const bigint& _bigint);
		~bigint();
		std::string getNbrStr() const;
		unsigned int getNbrUint() const;
		bigint operator+(const bigint& _bigint) const;
		bigint& operator+=(const bigint& _bigint);
		bigint operator++(int);
		bigint& operator++();
		bigint operator<<(unsigned int _nbr) const;
		bigint& operator<<=(unsigned int _nbr);
		bigint operator>>(unsigned int _nbr) const;
		bigint& operator>>=(unsigned int _nbr);
		bigint operator<<(const bigint& _bigint) const;
		bigint& operator<<=(const bigint& _bigint);
		bigint operator>>(const bigint& _bigint) const;
		bigint& operator>>=(const bigint& _bigint);
		bool operator==(const bigint& _bigint) const;
		bool operator!=(const bigint& _bigint) const;
		bool operator<(const bigint& _bigint) const;
		bool operator>(const bigint& _bigint) const;
		bool operator<=(const bigint& _bigint) const;
		bool operator>=(const bigint& _bigint) const;	
};

std::ostream& operator<<(std::ostream& _output, const bigint& _bigitn);