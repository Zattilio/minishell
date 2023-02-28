/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:37:54 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/28 14:23:14 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef enum e_token {
	TK_ERROR = -1,
	TK_WORD,
	TK_PIPE,
	TK_AMP,
	TK_DPIPE,
	TK_DAMP,
	TK_INF,
	TK_SUP,
	TK_DINF,
	TK_DSUP,
	TK_DOLLAR,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_WILDCARD,
	TK_EOF
}			t_token;

typedef struct s_node {
	int				id;
	int				token_type;
	char			*token;
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*parent;
}					t_node;

typedef struct s_garb
{
	void			*ptr;
	int				id;
	struct s_garb	*next;
}					t_garb;

typedef struct s_source {
	char			*line;
	size_t			line_size;
	size_t			cur;
}					t_source;

typedef struct s_param {
	int				id;
	t_source		source;
	t_garb			*garb;
}					t_param;

/*	garbage.c	*/
void	*ft_malloc_gc(t_param *prm, size_t size);
void	*ft_calloc_gc(t_param *prm, size_t nmemb, size_t size);
int		garbage_col(t_param *prm, void *ptr);
void	empty_garbage(t_param *prm);

/*	print_ast.c	*/
void	print_ast(t_node *root);

/*	lexeur.c	*/
t_node	*make_node(t_param *prm, int id, int token_type, char *token);
char	*get_token(t_param *prm);
char	*pick_next_token(t_param *prm);
t_token	get_token_type(char *token);

/*	utils.c	*/
char	*ft_substr_gc(t_param *prm, char *s, unsigned int start, size_t len);
char	*ft_strdup_gc(t_param *prm, const char *s);

#endif