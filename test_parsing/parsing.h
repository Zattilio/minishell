/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:37:54 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 11:40:09 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# define TK_WORD 1
# define TK_PIPE 2
# define TK_AMP 3
# define TK_INF 4
# define TK_SUP 5
# define TK_DOLLAR 6
# define TK_SQUOTE 7
# define TK_DQUOTE 8
# define TK_WILDCARD 9

typedef struct s_node {
	int				id;
	int				token_type;
	char			*token;
	struct s_node	*right;
	struct s_node	*left;
}					t_node;

#endif