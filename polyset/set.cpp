/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:34:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/18 01:14:01 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"

set::set(searchable_bag& _sb) : sb(&_sb)
{
	
}

set::set(const set& _set)
{
	*this = _set;	
}

set& set::operator=(const set& set)
{
	sb = set.sb;

	return *this;
}

set::~set()
{
	
}
void set::insert (int nbr)
{
	sb->insert(nbr);
}

void set::insert (int *data, int size)
{
	for (int i = 0; i < size; i++) {
		sb->insert(data[i]);
	}
}

void set::print() const
{
	sb->print();
}

void set::clear()
{
	sb->clear();
}

bool set::has(int nbr) const
{
	return(sb->has(nbr));
}