/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/29 15:31:02 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "twenty_one.h"

int			delete_at_position(t_line *line)
{
	if (line->pos < line->buf_len)
	{
		move_right(line);
		delete_key(line);
		move_left(line);
	}
	return (0);
}

int			ctrl_d(t_line *line)
{
	if (g_with_termcap && (line->pos < line->buf_len) && line->buf_len)
		delete_at_position(line);
	else
	{
		if (g_inside_doc_quote)
		{
			g_end_line = 1;
			g_inside_doc_quote = 0;
			return (0);
		}
		else
		{
			init_attr(SETOLD);
			ft_printf("exit");
			exit(0);
		}
	}
	return (0);
}

int			ctrl_c(t_line *line)
{
	(void)line;
	init_attr(SETOLD);
	ft_printf("\n$> ");
	ft_bzero(g_new_line, MAX_BUF);
	init_line("$> ", &g_line);
	init_attr(SETNEW);
	g_inside_doc_quote = 0;
	g_clc = 1;
	return (0);
}
