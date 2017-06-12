/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_research_start_end.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 11:42:12 by gpouyat           #+#    #+#             */
/*   Updated: 2017/06/07 15:31:55 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <history/history.h>

void	history_research_exit(char *result, char *line, BOOL fail, t_input *input)
{
	unsigned int len;

	len = (fail == true ? 32 : 18);
	sh_history_clear_line(len + ft_strlen(line) + ft_strlen(result));
	if (line)
		ft_strdel(&line);
	reset_input(input);
	sh_print_prompt();
	if(result)
	{
		string_replace(input->str, result);
		ft_strdel(&result);
	}
	redraw_line(input);
}

void	history_research_start(char **line, char **result, BOOL *fail)
{
	*line = NULL;
	*result = NULL;
	*fail = false;
	sh_history_clear_len(*line, *result, *fail);
	history_research_prompt(*line, "" ,*fail);
}
