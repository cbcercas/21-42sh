#include <expand/expand.h>

t_array *expand(t_array *tokens, t_array *array_exp)
{
  t_exp   *exp;
  size_t  i;

  i = 0;
  if (!tokens || !array_exp || i >= tokens->used)
    return (NULL);
  while (tokens && i < tokens->used)// dans tous les tokens
  {
    exp = exp_create_new((t_token *)array_get_at(tokens, i));// etape 1
    if (exp->type != E_TOKEN_SQUOTE)
    {
        expand_dol(exp);//expand les dollards
        if(expand_hist(exp) == NULL)//expand les !
        {
            ft_printf("event not found\n");
            return (NULL);
        }
    }
    expand_remove_quote(exp);
    // merge_token_word(exp);
    array_push(array_exp, (void *)exp);// push dans notre t_array
    i++;
  }
  return(array_exp);
}