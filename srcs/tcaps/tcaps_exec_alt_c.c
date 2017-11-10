#include <core/tcaps.h>
#include <core/input.h>
#include <history/history.h>

static	void	alt_c_end(t_input *tmp, char *str, size_t start, size_t end)
{
	if (tmp && tmp->select_pos.is_set)
	{
		start = tmp->select_pos.cur_start;
		end = tmp->select_pos.cur_end;
		if (start < end)
			str = ft_strjoincl(str, ft_strsub(tmp->str->s,
										  (unsigned int)start, end - start), 3);
		else if (start > end)
			str = ft_strjoincl(str, ft_strsub(tmp->str->s,
										  (unsigned int)end, start - end), 3);
	}
	ft_strdel(&get_select()->str);
	get_select()->str = str;
	log_info("copie str =[%s]", str);
}

static	t_input	*alt_c_mid(t_input *tmp, char **str, size_t start, size_t end)
{
	if (tmp->next && tmp->next->select_pos.is_set && tmp->next->str->len)
		*str = ft_strjoincl(*str, "\\\n", 1);
	tmp = tmp->next;
	while (tmp && tmp->select_pos.is_set && tmp->next &&
			tmp->next->select_pos.is_set)
	{
		if ((start - end))
		{
			if (!(*str = ft_strjoincl(*str, tmp->str->s, 1)))
				return (NULL);
			if ((tmp->next && tmp->next->str->len)
				&& !(*str = ft_strjoincl(*str, "\\\n", 1)))
				return (NULL);
			tmp = tmp->next;
		}
	}
	return (tmp);
}

BOOL	exec_alt_c(const t_key *key, t_input *input)
{
	t_input		*tmp;
	char		*str;
	size_t		start;
	size_t		end;

	(void)input;
	(void)key;
	str = NULL;
	if (!get_select()->is)
		return (false);
	tmp = get_windows(0)->cur_head;
	while (tmp && !tmp->select_pos.is_set)
		tmp = tmp->next;
	if (!tmp)
		return (false);
	start = tmp->select_pos.cur_start;
	end = tmp->select_pos.cur_end;
	if (start < end)
		str = ft_strsub(tmp->str->s, (unsigned int)start, end - start);
	else if (start > end)
		str = ft_strsub(tmp->str->s, (unsigned int)end, start - end);
	tmp = alt_c_mid(tmp, &str, start, end);
	alt_c_end(tmp, str, start, end);
	return (false);
}