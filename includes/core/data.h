/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:17:26 by chbravo-          #+#    #+#             */
/*   Updated: 2017/05/17 16:47:50 by chbravo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <logger.h>
# include <types/bool.h>

/*
** @file data.h
**
** @brief Contains the data structure used throughout the program
**
** This contains eventually any macros, constants,
** or global variables you will need.
*/

typedef struct s_sh_opt		t_sh_opt;
typedef struct s_sh_data	t_sh_data;

/*
** @struct sh_sh_opt
**
** @brief TODO
**
** @param TODO
*/

struct						s_sh_opt
{
	unsigned		verbose:1;
	unsigned		dbg:1;
	enum e_d_lvl	dbg_lvl;
	BOOL			tcaps;
};

/*
** @struct s_sh_data
**
** @brief TODO
**
** @param TODO
*/

struct						s_sh_data
{
	t_sh_opt			opts;
	char				*cwd;
	struct termios		*tattr;

};

#endif
