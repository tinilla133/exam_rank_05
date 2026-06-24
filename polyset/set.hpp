/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:34:55 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/18 01:09:50 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "subject/searchable_bag.hpp"

class set
{
	private:
		searchable_bag *sb;
		
	public:
		set(searchable_bag& _sb);
		set(const set& _set);
		set& operator=(const set& set);
		~set();
		virtual void insert (int);
		virtual void insert (int *, int);
		virtual void print() const;
		virtual void clear();
		virtual bool has(int) const;
};
