/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:34:43 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/18 01:11:17 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "subject/searchable_bag.hpp"
#include "subject/array_bag.hpp"

class searchable_array_bag : public searchable_bag, public array_bag
{
	public:
		searchable_array_bag();
		searchable_array_bag(const searchable_array_bag& sab);
		searchable_array_bag& operator=(const searchable_array_bag& sab);
		~searchable_array_bag();
		virtual bool has(int) const;
};
