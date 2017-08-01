/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:25:01 by chbravo-          #+#    #+#             */
/*   Updated: 2017/07/29 23:21:40 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/prompt.h>

size_t get_prompt(BOOL print)
{
	char		*path;
	char		*tmp;
	size_t	len;
	char		*ret;

	path = NULL;
	ret = (!g_ret ? "\033[92m" : "\033[91m");
	(tmp = sh_getenv_value("USER")) ? 0 : (tmp = "???");
	print ? ft_printf("\033[94m[%s] \033[0m", tmp) : 0;
	len = (ft_strlen(tmp) + 3);
	path = getcwd(path, 0);
	tmp = (path ? ft_strrchr(path, '/') : NULL);
	if (print && tmp && tmp[1])
		ft_printf("\033[93m➜ %s\033[0m %s🎩\033[0m ", &tmp[1], ret);
	else if (print && tmp)
		ft_printf("\033[93m➜ %s\033[0m %s🎩\033[0m ", tmp, ret);
	else if (print)
		ft_printf("\033[93m➜ \033[0m %s🎩\033[0m ", ret);
	len += (tmp ? ft_strlen(tmp) + 5 : 5);
	ft_strdel(&path);
	return (len);
}

void	sh_print_prompt(void)
{
	get_prompt(true);
}

size_t sh_len_prompt(void)
{
	return (get_prompt(false));
}
