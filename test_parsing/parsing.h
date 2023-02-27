/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:37:54 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 15:44:22 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

enum token { 
	TK_WORD, 
	TK_PIPE,
	TK_AMP,
	TK_INF,
	TK_SUP,
	TK_DOLLAR,
	TK_SQUOTE,
	TK_DQUOTE, 
	TK_WILDCARD	
};

typedef struct s_node {
	int				id;
	int				token_type;
	char			*token;
	struct s_node	*right;
	struct s_node	*left;
}					t_node;

typedef struct s_garb
{
	void			*ptr;
	int				id;
	struct s_garb	*next;
}					t_garb;

typedef struct s_param {
	int				id;
	t_garb			*garb;
}					t_param;

/*	garbage.c	*/
void	*ft_malloc(t_param *prm, size_t size);
void	*ft_calloc_gc(t_param *prm, size_t nmemb, size_t size);
int		garbage_col(t_param *prm, void *ptr); 

/*	print_ast.c	*/
void	print_ast(t_node *root);

/*	lexeur.c	*/
t_node	*make_node(int id, int token_type, char *token);

#endif