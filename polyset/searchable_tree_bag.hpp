/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:34:49 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/18 00:51:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "subject/searchable_bag.hpp"
#include "subject/tree_bag.hpp"

class searchable_tree_bag : public searchable_bag, public tree_bag
{
	public:
		searchable_tree_bag();
		searchable_tree_bag(const searchable_tree_bag& stb);
		searchable_tree_bag& operator=(const searchable_tree_bag& stb);
		~searchable_tree_bag();
		virtual bool has(int) const;
};