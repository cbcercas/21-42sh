/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 09:24:48 by chbravo-          #+#    #+#             */
/*   Updated: 2017/01/16 11:47:36 by chbravo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "env_list_utils.h"

char	*ms_getenv_name(char *env)
{
	char	*sep;
	char	*name;

	sep = ft_strchr(env, '=');
	name = ft_strsub(env, 0, sep - env);
	return (name);
}

char	*ms_getenv_value(char *env)
{
	char	*sep;
	char	*value;

	sep = ft_strchr(env, '=') + 1;
	value = ft_strsub(sep, 0, ft_strlen(sep));
	return (value);
}

t_env	*ms_new_env(char *env)
{
	t_env	*e;

	e = ft_memalloc(sizeof(*e));
	if (!e)
		return (NULL);
	e->next = NULL;
	if (!(e->name = ms_getenv_name(env)))
		ft_memdel((void **)&e);
	else if (!(e->value = ms_getenv_value(env)))
	{
		ft_strdel(&e->name);
		ft_memdel((void **)&e);
	}
	return (e);
}