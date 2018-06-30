/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:25:25 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/29 16:35:12 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "twenty_one.h"

void	signal_inh(int sign)
{
	if (!g_with_termcap)
	{
		if (sign == SIGINT)
			ft_printf("\n$> ");
		if (sign == SIGQUIT)
			exit(0);
	}
}
