/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:37:54 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/06 15:50:12 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../libft/src/libft.h"
# include "../include/minishell.h"
# define PARSING_STOPPER "|<>$\'\""

/*
	TK_WILDCARD,
	TK_AMP,
	TK_DPIPE,
	TK_DAMP,
*/

typedef enum e_token {
	TK_ERROR = -1,
	TK_WORD,
	TK_PIPE,
	TK_EXEC,
	TK_INF,
	TK_SUP,
	TK_DINF,
	TK_DSUP,
	TK_DOLLAR,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_DAMP,
	TK_DPIPE,
	TK_EOF
}			t_token;

enum e_error_parsing {
	ERR_SQUOTE_CLOSE,
	ERR_DQUOTE_CLOSE
};

typedef enum e_bool {
	TRUE = 1,
	FALSE = 0
}				t_bool;

typedef struct s_node {
	int				id;
	t_token			token_type;
	char			*token;
	char			*file_name;
	int				flags_open;
	mode_t			mode_open;
	char			**cmd;
	t_bool			conv_dol;
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*redir;
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
	char			***env;
}					t_param;

/*	alloc_garbage -> ft_alloc_gc.c */
void	*ft_malloc_gc(t_param *prm, int id, size_t size);
void	*ft_calloc_gc(t_param *prm, int id, size_t nmemb, size_t size);
char	*ft_substr_gc(t_param *prm, char *s, unsigned int start, size_t len);
char	*ft_strdup_gc(t_param *prm, const char *s);

/*	alloc_garbage -> garbage.c */
int		garbage_col(t_param *prm, int id, void *ptr);
void	empty_all_garbage(t_param *prm);
void	empty_garbage(t_param *prm, int id);
void	print_garbage(t_param *prm);
void	remove_from_garb(t_param *prm, void *ptr);

/*	builtins -> env.c	*/
int		clone_env(t_param *prm, char **env);
char	*get_env_var(t_param *prm, char *name);
void	print_env(t_param *prm);

/* lexer -> lexer.c	*/
char	*get_token(t_param *prm);
t_token	peek_tk(t_param *prm);
t_token	get_t_token(char *token);

/*	parser -> make_node.c	*/
t_node	*make_node(t_param *prm, int id, int token_type, char *token);
t_node	*make_pipe_node(t_param *prm, t_node *left, t_node *right);
t_node	*make_redir_node(t_param *prm, t_node *left,
			int token_type, char *file_name);
t_node	*make_exec_node(t_param *prm, char **cmd);

/*	parser -> parser.c	*/
t_node	*parsing(t_param *prm);
t_node	*parse_pipe(t_param *prm);
t_node	*parse_exec(t_param *prm);
t_node	*parse_redir(t_param *prm);

/*	parser -> parser_utils.c	*/
void	add_last_left(t_node **root, t_node *node);
char	**add_cmd_arg(t_param *prm, char **cmd, char *arg);
char	*get_word(t_param *prm);
char	*get_word_squote(t_param *prm);
char	*get_word_dquote(t_param *prm);

/*	utils -> print_ast.c	*/
void	print_ast(t_node *root);
char	*get_tk_str(int tk_type);

/*	utils -> utils.c	*/
int		is_redir(int token_type);
int		is_word(t_token token_type);
void	print_space(int space);
int		get_pos_in_str(char *str, char c);
int		get_nb_str(char **strs);

#endif
