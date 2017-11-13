/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 20:30:58 by gpouyat           #+#    #+#             */
/*   Updated: 2017/10/14 12:33:20 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array/array.h>
#include <automaton/automaton.h>
#include <lexer/lexer.h>
#include <ftprintf.h>
#include <btree/ft_btree.h>
#include <environ/environ.h>
#include <builtins/builtin_utils.h>
#include <history/history.h>
#include <expand/expand.h>
#include <ast/ast.h>
#include <exec/exec.h>
#include <secure_memory/ft_secu_malloc.h>


t_array init_tests_exec(char *input)
{
	t_automaton	automaton;
	t_array		tokens;

	if (lexer_init(&tokens) == NULL)
	{
		ft_dprintf(2, "Error initialising tokens");
		exit (1);
	}
	else if (automaton_init(&automaton) == NULL)
	{
		ft_dprintf(2, "Error Initialising automaton");
		exit (1);
	}
	else if (lexer_lex(&tokens, input))
	{
		if (automaton.stack)
			stack_destroy(&(automaton.stack), NULL);
		return (tokens);
	}
	else
	{
		ft_dprintf(2, "Fatal -c error : Couldn't Catch the error.\n");
    ft_dprintf(2, "Maybe arg is NULL\n");
		exit (1);
	}
}

void sh_testing_exec(char *const *av, char **environ)
{
	t_array		expands;
	t_array		tokens;
	t_btree		*ast;

	ast = NULL;
	init_environ(environ);
  	sh_builtins_init();
	sh_history_init(sh_history_get());
	tokens = init_tests_exec(av[2]);
	if (expand_init(&expands) == NULL)
		exit (1);
	expand(&tokens, &expands);
	ast_create(&ast, &expands);
	exec_exec(NULL, ast);
	array_reset(&expands, NULL);
  ft_secu_free_all();
	exit (0);
}
