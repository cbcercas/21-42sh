/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 17:34:35 by chbravo-          #+#    #+#             */
/*   Updated: 2017/02/15 11:01:20 by chbravo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <builtins/chdir.h>

int sh_classic_chdir(t_sh_data *data, char *arg)
{
	(void)data;
	char cwd[1024];
	char *tmp;
	if (arg == NULL)
	{
		sh_setenv("OLDPWD", sh_getenv_value("PWD"));
		if (chdir(sh_getenv_value("HOME")) == -1)
			ft_printf("cd: HOME not set\n");
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		tmp = sh_getenv_value("PWD");
		chdir(sh_getenv_value("OLDPWD"));
		sh_setenv("OLDPWD", tmp);
	}
	else
	{
		sh_setenv("OLDPWD", sh_getenv_value("PWD"));
		if (chdir(arg) == -1)
			ft_printf("cd: no such file or directory: %s\n", arg);
	}
	getcwd(cwd, sizeof(cwd));
	sh_setenv("PWD", cwd);
	return (0);
}

int	sh_chdir(t_sh_data *data, char **arg)
{
	(void)data;
	struct stat sb;
	int buffer = 1024;
	ssize_t len;
	char buf[buffer];

	if ((ft_strequ(arg[0], "-P")) || (ft_strequ(arg[0], "-L")))
	{
		if (arg[1] == NULL)
		{
			ft_dprintf(1, "cd: error, option requires an argument\n");
			return (1);
		}
		else
		{
			if(lstat(arg[1], &sb) != -1)
			{
				if (S_ISLNK(sb.st_mode))
				{
					if (ft_strequ(arg[0], "-P"))
					{
						len = readlink(arg[1], buf, sizeof(buf) - 1);
						if (len != -1)
						{
							buf[len] = '\0';
							sh_classic_chdir(data, buf);
						}
						else
							ft_printf("ERROR");
					}
					else if (ft_strequ(arg[0], "-L"))
						sh_classic_chdir(data, arg[1]);
				}
				else
					sh_classic_chdir(data, arg[1]);
			}
			return (0);
		}
	}
	else
		return (sh_classic_chdir(data, arg[0]));
}