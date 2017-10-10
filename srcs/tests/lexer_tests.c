#include <tests/lexer_tests.h>

void sh_testing_lexer(char *const *av)
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
    else if (lexer_lex(&tokens, &automaton, av[3]))
    {
        lexer_print_tokens(&tokens);
        exit (1);
    }
    else
    {
        ft_dprintf(2, "Fatal testing error : Couldn't Catch the error.");
        exit (1);
    }
}
