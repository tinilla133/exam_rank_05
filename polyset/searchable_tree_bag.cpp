/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:34:46 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/18 01:10:51 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag()
{
	
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& stb) : tree_bag(stb)
{
	
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& stb)
{
	tree_bag::operator=(stb);

	return *this;
}

searchable_tree_bag::~searchable_tree_bag()
{
	
}

bool searchable_tree_bag::has(int nbr) const
{
	node *tree_aux= tree;
	
	while (tree_aux) {
		if (tree_aux->value < nbr) {
			tree_aux = tree_aux->r;
		}
		else if (tree_aux->value > nbr) {
			tree_aux = tree_aux->l;
		}
		else {
			return true;
		}
	}
	return false;
}
