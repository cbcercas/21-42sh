/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:26:15 by chbravo-          #+#    #+#             */
/*   Updated: 2017/02/26 15:07:45 by chbravo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <core/command.h>

int	sh_command(t_sh_data *data, char **command)
{
	t_builtin_e	*e;
	char		**cmd;

	while (*command)
	{
		if ((e = sh_is_builtin(data->builtins, *command)))
		{
			if (e->fn(data, *command + e->len + 1))
				return (1);
		}
		else
		{
			if ((cmd = sh_get_command(*command)))
				sh_exec_command(cmd);
		}
		command++;
	}
	return (0);
}

char **sh_get_command(char *input)
{
	return (ft_strsplit(input, ' '));
}

int	sh_exec_command(char **command)
{
	char	*cmd;
	char	**envtab;
	pid_t	pid;
	int		status;

	status = 0;
	envtab = sh_tenv_to_tab();
	if ((cmd = sh_check_path(command[0])))
	{
		if ((pid = fork()) == -1)
			ft_printf("fork error");
		else if (pid == 0)
		{
			execve(cmd, command, envtab);
			exit(0);
		}
		else
			wait(&status);
	}
	return (0);
}