/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 21:07:36 by chbravo-          #+#    #+#             */
/*   Updated: 2017/10/09 18:00:42 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec/check_path.h>
#include <core/main.h>

char		*makefilepath(char const *path, char const *filename)
{
	char	*filepath;

	if (path)
	{
		if (path[ft_strlen(path) - 1] != '/')
		{
			filepath = ft_strjoin(path, "/");
			filepath = ft_strjoincl(filepath, (char *)filename, 1);
		}
		else
			filepath = ft_strjoin(path, filename);
	}
	else
		filepath = ft_strdup(filename);
	return (filepath);
}

/*
** return string malloc filename with path
*/
char	*sh_check_path(char const *cmd_name)
{
	char	**env_path;
	char	*file;
	int		ret;
	int		tmp;

	env_path = ft_strsplit_secu(sh_getenv_value("PATH"), ':', M_LVL_FUNCT);
	ret = 0;
	while (env_path && *env_path)
	{
		if (!(file = makefilepath(*env_path, cmd_name)))
			break;
		if ((tmp = sh_test_access(file)) == 1)
			return (file);
		else if (tmp == -1)
			ret = -1;
		ft_strdel(&file);
		env_path++;
	}
	if (ret == -1)
		ft_dprintf(STDERR_FILENO, "%s: permission denied: %s\n", PROGNAME, cmd_name);
	else if (ret == 0)
		ft_dprintf(STDERR_FILENO, "%s: command not found: %s\n", PROGNAME, cmd_name);
	ft_secu_free_lvl(M_LVL_FUNCT);
	return (NULL);
}

/*
** return string malloc filename
*/

char *get_filename(char *av)
{
	int		tmp;
	char	*ret;

	tmp = 0;
	ret = NULL;
	if (ft_strchr(av, '/'))
		{
			if ((tmp = sh_test_access(av)) == 1)
				return (ft_strdup(av));
			ft_printf("%s: permission denied: %s\n", PROGNAME, av);
		}
	else
		ret = sh_check_path(av);
	ft_secu_free_lvl(M_LVL_FUNCT);
	return (ret);
}
