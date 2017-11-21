/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:16:16 by gpouyat           #+#    #+#             */
/*   Updated: 2017/10/11 15:39:25 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals/signals.h>

/*
** @brief Exits the program and displays a message
**
** @param sig The signal you want the program to exit with
*/

void	signals_quit(int sig)
{
	default_terminal_mode();
	if (sig == SIGSEGV)
		ft_putstr_fd("\nShell Segfault !\n", 2);
	else if (sig == SIGABRT)
		ft_putstr_fd("Shell Abort", 2);
	else
		ft_dprintf(STDERR_FILENO, "\nShell quit with signal: %d\nGoodbye, "
				"see-you! :)\n", sig);
	log_fatal("Signals: Shell quit with signal: %d", sig);
	kill_childs(SIGTERM);
	exit(128 + (sig % 32));
}

/*
** @brief SIGWINCH signal handler
*/

void	signals_sigwinch(void)
{
	size_t	pos;
	t_input	*input;
	t_input	*tmp;

	if (!isatty(STDOUT_FILENO))
		return ;
	input = input_get_cur();
	pos = pos_in_str(input);
	tmp = input;
	input = input_back_to_writable(input);
	get_windows(1);
	get_windows(0)->cur = input;
	get_select()->is = false;
	reset_select_pos();
	tputs(tgetstr("cr", NULL), 0, &ft_putchar2);
	sh_print_prompt(input, NULL, E_RET_REDRAW_PROMPT);
	redraw_input(input);
	//TODO refactor using tgoto
	input = goto_input(input, tmp);
	while (pos != pos_in_str(input) && pos_in_str(input) < input->str->len)
		move_cursor_right(&input->cpos, get_ts());
	get_windows(0)->cur = input;
}

/*
** @brief Signal handler for each `sig`
** @param sig signal
*/

void	signals_handler(int sig)
{
	log_info("Signals:Shell cath signal:%d", sig);
	if (sig == SIGTSTP)
		tcaps_bell();
	else if (sig == SIGINT)
	{
		ft_putchar('\n');
		log_info("Signal: User pressed Ctrl+C.");
	}
	else if (sig == SIGWINCH)
		signals_sigwinch();
	else if (sig == SIGUSR1 || sig == SIGTERM)
		sh_exit(NULL, NULL);
	else if (sig == 13)
	{
		if (get_pid_child(-1))
			kill(get_pid_child(-1), SIGKILL);
		exit(EXIT_SUCCESS);
	}
	else if (((sig >= 1 && sig < 17) || sig == 23 || sig == 24 ||\
					(sig >= 26 && sig <= 31)) && sig != SIGWINCH && sig != 28)
		signals_quit(sig);
}

BOOL	*is_in_pipe(void)
{
	static BOOL		stop = true;

	return (&stop);
}
