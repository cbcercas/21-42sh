/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 21:07:36 by chbravo-          #+#    #+#             */
/*   Updated: 2017/08/03 17:58:35 by gpouyat          ###   ########.fr       */
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

static int	sh_test_access(char const *filename)
{
	struct stat *buf;
	int		ret;

	if (!(buf = ft_secu_malloc_lvl(sizeof(*buf), 3)))
		return (-2);
	ret = 0;
	ft_bzero(buf, sizeof(*buf));
	if (stat(filename, buf) == 0)
	{
		if (buf->st_mode & S_IXUSR)
			ret = 1;
		else
			ret = -1;
	}
	ft_secu_free(buf);
	return (ret);
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

	env_path = ft_strsplit_secu(get_var_value(get_envs(), "PATH"), ':', M_LVL_FUNCT); //TODO check if PATH is in envs or in local var
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
