/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:19:33 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/28 23:23:48 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "twenty_one.h"

static int		unset_sub_env(char **paras, char **env, char **new_env)
{
	char	**cp;
	int		index;

	cp = env;
	index = 0;
	paras++;
	while (*cp && !(!ft_strncmp(*paras, *cp, ft_strlen(*paras)) \
				&& ft_strlen(*paras) < ft_strlen(*cp) && \
				(*cp)[ft_strlen(*paras)] == '='))
		new_env[index++] = *cp++;
	new_env[index] = NULL;
	if (*cp)
	{
		cp++;
		while (cp && *cp)
			new_env[index++] = *cp++;
		new_env[index] = NULL;
		return (0);
	}
	put2_str_fd(*paras, " :no such variable \n", 2);
	return (1);
}

static void		pro_for_env(char **paras, char **new_env, t_sh *table)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		ft_putendl_fd("fork failled", 2);
	else if (pid == 0)
	{
		if (is_buildin(*paras))
		{
			do_build(paras, &new_env, table);
			exit(0);
		}
		else
			child_pro_bin(paras, new_env, table);
	}
	else
		waitpid(0, NULL, 0);
}

static int		env_iu(char **paras, char **new_env, char ***env, t_sh *table)
{
	char	**cp;
	int		i;

	i = 0;
	cp = NULL;
	if ((*paras)[1] == 'i')
	{
		paras++;
		while (*paras && ft_strstr(*paras, "="))
			new_env[i++] = *paras++;
		new_env[i] = NULL;
		cp = new_env;
		(!*paras) ? put_strstr(cp) : pro_for_env(paras, cp, table);
	}
	else if ((*paras)[1] == 'u')
	{
		unset_sub_env(paras, *env, new_env);
		paras = paras + 2;
		!*paras ? put_strstr((char **)new_env) : pro_for_env(paras, cp, table);
	}
	else
		return (return_message("Usage: env [-u name] [-i] [utlity]\n", 1, 2));
	return (0);
}

static int		othercase_env(char **env, char **newe, char **pa, t_sh *table)
{
	int		i;

	i = 0;
	while (*pa && ft_strstr(*pa, "="))
		newe[i++] = *pa++;
	while (env && *env)
		newe[i++] = *env++;
	newe[i] = NULL;
	if (!*pa)
		put_strstr(newe);
	else
		pro_for_env(pa, newe, table);
	return (0);
}

int				put_env(char **env, char **paras, t_sh *table)
{
	char	**new_env;
	int		i;
	int		j;
	int		res;

	paras++;
	i = -1;
	j = -1;
	res = 0;
	new_env = malloc(sizeof(char *) * MAX_BUF);
	if (!*paras)
		put_strstr(env);
	else if (*paras && **paras == '-')
		res = env_iu(paras, new_env, &env, table);
	else
		othercase_env(env, new_env, paras, table);
	free(new_env);
	return (res);
}
