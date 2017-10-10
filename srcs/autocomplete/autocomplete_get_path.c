/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_get_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:37:14 by gpouyat           #+#    #+#             */
/*   Updated: 2017/10/09 17:56:51 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <autocomplete/autocomplete.h>

char		*autocomplete_get_path(char *s)
{
	char *ret;
	char *tmp;

	if (!s)
		return (".");
	if (ft_strchr(s, '/'))
	{
		ret = ft_strdup_secu(s, M_LVL_AUTOC);
		tmp = ft_strrchr(ret, '/');
		*++tmp = 0;
		return (ret);
	}
	return (".");
}

t_array		*autocomplete_get_content_paths(char *path)
{
	t_array			*content;
	DIR				*dir;
	struct dirent	*file;
	t_string		*tmp;

	content = array_create(sizeof(t_string));
	dir = opendir(path);
	tmp = NULL;
	if (dir != NULL)
	{
		while ((file = readdir(dir)) && content->used <= 3000)
		{
			if (!autocomplete_is_dots(file->d_name))
				tmp = string_dup_secu(file->d_name, M_LVL_AUTOC);
			if (tmp && path && !ft_strequ(path, "."))
				tmp = string_insert_front_secu(tmp, path, M_LVL_AUTOC);
			if (tmp && tmp->s && autocomplete_is_directory(tmp->s))
				tmp = string_insert_back_secu(tmp, "/", M_LVL_AUTOC);
			if (tmp)
				array_push(content, (void *)tmp);
		}
		closedir(dir);
	}
	return (content);
}
