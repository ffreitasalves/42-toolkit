/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_list_splice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/07 04:18:37 by irabeson          #+#    #+#             */
/*   Updated: 2013/10/07 11:57:43 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** <This file contains s_list_splice method>
** < splice >
** Copyright (C) <2013>  Iohann Rabeson <irabeson42@gmail.com>
**
** This file is part of 42-toolkit.
**
** 42-toolkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <s_list.h>
#include <m_error.h>

static void	f_list_pick_cells_imp(t_list *const v_this,
								  t_list_cell * const begin,
								  t_list_cell *const end)
{
	t_list_cell	*cell_before;
	t_list_cell	*cell_after;

	cell_before = begin->v_prev;
	cell_after = end->v_next;
	if (cell_before == NULL)
	{
		v_this->v_begin = cell_after;
		if (cell_after)
			cell_after->v_prev = NULL;
	}
	else
		cell_before->v_next = cell_after;
	if (cell_after == NULL)
	{
		if (v_this->v_begin)
			v_this->v_end = v_this->v_begin->v_next;
		else
			v_this->v_end = v_this->v_begin;
	}
	else
		cell_after->v_prev = cell_before;
}

static ui	f_list_pick_cells(t_list *v_this, t_list_cell *begin,
							  t_list_cell *end)
{
	ui			cell_count;
	
	if (D_LIST(empty)(v_this))
		return (0);
	if (end == NULL)
		end = D_LIST(end)(v_this);
	cell_count = D_LIST_CELL(count)(begin, end);
	D_LIST(pick_cells_imp)(v_this, begin, end);
	v_this->v_size = v_this->v_size - cell_count;
	begin->v_prev = NULL;
	end->v_next = NULL;
	return (cell_count);
}

static void	f_list_splice_imp(t_list *v_this, t_list_cell * const position,
							  t_list_cell *const other_begin,
							  t_list_cell *const other_end)
{
	t_list_cell	*before;

	before = position->v_prev;
	if (before == NULL)
	{
		v_this->v_begin = other_begin;
		v_this->v_begin->v_prev = NULL;
	}
	else
	{
		before->v_next = other_begin;
		other_begin->v_prev = before;
	}
	position->v_prev = other_end;
	other_end->v_next = position;
}

void		f_list_splice(t_list *v_this, t_list_cell *position,
						  t_list *other_list, t_list_cell *other_begin,
						  t_list_cell *other_end)
{
	ui			cell_count;
	
	cell_count = D_LIST(pick_cells)(other_list, other_begin, other_end);
	if (cell_count == 0)
		return ;
	if (D_LIST(empty)(v_this))
	{
		v_this->v_size = cell_count;
		v_this->v_begin = other_begin;
		v_this->v_end = other_end;
		return ;
	}
	if (position == NULL)
	{
		position = D_LIST(end)(v_this);
		position->v_next = other_begin;
		other_begin->v_prev = position;
	}
	else
	{
		D_LIST(splice_imp)(v_this, position, other_begin, other_end);
	}
	v_this->v_size = v_this->v_size + cell_count; 
}
