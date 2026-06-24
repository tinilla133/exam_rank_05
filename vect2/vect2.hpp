/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:41:56 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/14 01:22:27 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class vect2
{
	private:
		int x, y;
		
	public:
		vect2();
		vect2(int _x, int _y);
		vect2(const vect2& _vect);
		~vect2();
		vect2& operator=(const vect2& _vect);
		vect2 operator+(const vect2& _vect) const;
		vect2& operator+=(const vect2& _vect);
		vect2 operator-(const vect2& _vect) const;
		vect2& operator-=(const vect2& _vect);
		vect2 operator-() const;
		vect2 operator*(int nbr) const;
		vect2& operator*=(int nbr);
		friend vect2 operator*(int nbr, const vect2& _vect);
		vect2 operator++(int);
		vect2& operator++();
		vect2 operator--(int);
		vect2& operator--();
		int operator[](unsigned int pos) const;
		int& operator[](unsigned int pos);
		bool operator==(const vect2& _vect) const;
		bool operator!=(const vect2& _vect) const;
};

std::ostream& operator<<(std::ostream& _output, const vect2& _vect);