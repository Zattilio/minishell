/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:37:54 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/02 16:10:56 by jlanza           ###   ########.fr       */
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
# define PARSING_STOPPER "|<>$\'\""

typedef enum e_token {
	TK_ERROR = -1,
	TK_WORD,
	TK_PIPE,
	TK_EXEC,
	//TK_AMP,
	TK_DPIPE,
	TK_DAMP,
	TK_INF,
	TK_SUP,
	TK_DINF,
	TK_DSUP,
	TK_DOLLAR,
	TK_SQUOTE,
	TK_DQUOTE,
	//TK_WILDCARD,
	TK_EOF
}			t_token;

enum e_error_parsing {
	ERR_SQUOTE_CLOSE,
	ERR_DQUOTE_CLOSE,
};

typedef struct s_node {
	int				id;
	t_token			token_type;
	char			*token;
	char			*file_name;
	int				flags_open;
	mode_t			mode_open;
	char			**cmd;
	struct s_node	*right;
	struct s_node	*left;
}					t_node;

typedef struct s_garb
{
	void			*ptr;
	int				id;
	struct s_garb	*next;
}					t_garb;

typedef struct s_source {
	int				id;
	char			*line;
	size_t			line_size;
	size_t			cur;
	int				error;
}					t_source;

typedef struct s_param {
	t_source		source;
	t_garb			*garb;
	char			*env[];
}					t_param;

/*	garbage.c	*/
int		garbage_col(t_param *prm, void *ptr);
void	empty_garbage(t_param *prm, int id);
void	print_garbage(t_param *prm);
char	*ft_strjoin_gc(t_param *prm, char const *s1, char const *s2);

/*	garbage_2.c	*/
void	*ft_malloc_gc(t_param *prm, size_t size);
void	*ft_calloc_gc(t_param *prm, size_t nmemb, size_t size);

/*	print_ast.c	*/
void	print_ast(t_node *root);
char	*get_tk_str(int tk_type);

/*	lexeur.c	*/
t_node	*make_node(t_param *prm, int id, int token_type, char *token);
char	*get_token(t_param *prm);
t_token	peek_tk(t_param *prm);
t_token	get_t_token(char *token);
size_t	test_double_token(t_param *prm, size_t cur);

/*	utils.c	*/
char	*ft_substr_gc(t_param *prm, char *s, unsigned int start, size_t len);
char	*ft_strdup_gc(t_param *prm, const char *s);
int		is_redir(int token_type);
void	print_space(int space);

/*	parseur.c	*/
t_node	*make_pipe_node(t_param *prm, t_node *left, t_node *right);
t_node	*make_redir_node(t_param *prm, t_node *left,
			int token_type, char *file_name);
t_node	*make_exec_node(t_param *prm, char **cmd);
t_node	*parsing(t_param *prm);
t_node	*parse_pipe(t_param *prm);
t_node	*parse_exec(t_param *prm);
t_node	*parse_redir(t_param *prm);
char	**add_cmd_arg(t_param *prm, char **cmd, char *arg);
void	add_last_left(t_node **root, t_node *node);
char	*get_word_squote(t_param *prm);
char	*get_word(t_param *prm);

#endif
