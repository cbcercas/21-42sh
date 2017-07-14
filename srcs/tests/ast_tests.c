/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 09:59:15 by gpouyat           #+#    #+#             */
/*   Updated: 2017/07/14 17:47:30 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/ast_tests.h>

void test_aff(t_cmd *cmd)
{
	static int i = 0;
	ft_printf("[%d]{%s} ", i, cmd->exp->str);
	i++;
}

t_array init_tests_ast(char *input)
{
	t_automaton	automaton;
	t_array		tokens;

	if (lexer_init(&tokens) == NULL)
	{
		ft_printf("Error initialising tokens");
		exit (1);
	}
	else if (automaton_init(&automaton) == NULL)
	{
		ft_printf("Error Initialising automaton");
		exit (1);
	}
	else if (lexer_lex(&tokens, &automaton, input))
	{
		if (automaton.stack)
			stack_destroy(&(automaton.stack), NULL);
		return (tokens);
	}
	else
	{
		ft_printf("Fatal testing error : Couldn't Catch the error.");
		exit (1);
	}
}

void sh_testing_ast(char *const *av, char **environ)
{
	t_btree	*ast;
	t_array		expands;
	t_array		tokens;
	char *input;

	input = ft_strclean(av[3]);//TODO à faire pour le main ;)
	ast = NULL;
	sh_init_environ(environ);
	sh_history_init(NULL);
	tokens = init_tests_ast(input);
	if (expand_init(&expands) == NULL)
		exit (1);
	expand(&tokens, &expands);
	if (!(ast = ast_create(&expands)))
		ft_printf("AST NULL\n");
	else if (!av[4] || ft_strequ(av[4], "tree"))
		btree_print(ast, (char * (*)(void*))&ast_aff);
	else if (ft_strequ(av[4], "line"))
		btree_apply_prefix(ast, (void (*)(void*))&test_aff);
	btree_destroy(&ast, (void (*) (void*))&ast_del_cmd);
	free(input);
	array_reset(&expands, NULL);
	exit (0);
}
