/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:34:38 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/18 01:11:32 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() : array_bag()
{
	
}
searchable_array_bag::searchable_array_bag(const searchable_array_bag& sab) : array_bag(sab)
{
	
}
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& sab)
{
	array_bag::operator=(sab);

	return *this;
}

searchable_array_bag::~searchable_array_bag()
{

}

bool searchable_array_bag::has(int nbr) const
{
	for (int i = 0; i < size; i++) {
		if (data[i] == nbr) {
			return true;
		}
	}
	return false;
}
