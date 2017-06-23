/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 10:51:56 by gpouyat           #+#    #+#             */
/*   Updated: 2017/06/15 17:53:55 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins/builtins_utils.h>

extern char const	*g_optarg;
extern int				g_optind;

void	get_opt_reset(void)
{
	g_optarg = NULL;
	g_optind = 1;
	opterr = 0;
	optopt = 0;
}

void	sh_history_help(char *arg)
{
	//ft_printf("history: %s: invalid option\n", arg);
	ft_printf("history: usage: history [-c] [-d offset] [n] or history");
 	ft_printf("-awrn [filename] or history -ps arg [arg...]\n");
}


int sh_history(t_sh_data *data, char **argv)
{
	(void)data;
	int		opt;

	//TODO : reset get_opt
	get_opt_reset();

	opt = ft_getopt(ft_tablen(argv), argv, "cd:arwsnp");//TODO: mettre ft_getopt quand il y'aura un reset
	if (opt == 'c')
		sh_history_builtin_c();
	else if (opt == 'd')
		sh_history_builtin_d(optarg);
	else if(opt == 'a')
		sh_history_builtin_a(argv[optind]);
	else if(opt == 'n')
		sh_history_builtin_n(argv[optind]);
	else if(opt == 'r')
		sh_history_builtin_r(argv[optind]);
	else if(opt == 'w')
		sh_history_builtin_w(argv[optind]);
	else if(opt == 's')
		sh_history_builtin_s(argv, optind);
	else if(opt == 'p')
		sh_history_builtin_p(argv);
	else if (opt == -1)
		sh_history_builtin_print(argv[optind]);
	else if (opt == '?')
		sh_history_help(argv[1]);
		//TODO : reset get_opt
		get_opt_reset();
	return (0);
}
