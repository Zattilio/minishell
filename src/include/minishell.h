/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:07:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 12:15:46 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/src/libft.h"
# include "./exec.h"
# include "./minishell_struct.h"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define VERT "\033[0;32m"
# define ROUGE "\033[0;31m"
# define CYAN "\033[0;36m"
# define GRAS_START "\e[1m"
# define GRAS_END "\e[0m"
# define RESET_COLOR "\033[0m"

extern unsigned char	g_return_value;

/* command_line_interface */
void	print_minishell_title(void);
void	readline_new_prompt(char **cmd_buf);
void	printf_new_prompt(void);
void	init_signal(void);

/* builtins */
void	ft_cd(char *arg[], char *env[]);
void	ft_pwd(char *arg[], char *env[]);
void	ft_exit(char *arg[], char *env[], char *do_);

/*	alloc_garbage -> ft_alloc_gc.c */
void	*ft_malloc_gc(t_param *prm, int id, size_t size);
void	*ft_calloc_gc(t_param *prm, int id, size_t nmemb, size_t size);
char	*ft_substr_gc(t_param *prm, char *s, unsigned int start, size_t len);
char	*ft_strdup_gc(t_param *prm, int id, const char *s);
char	*ft_strjoin_gc(t_param *prm, int id, char const *s1, char const *s2);

/*	alloc_garbage -> garbage.c */
int		garbage_col(t_param *prm, int id, void *ptr);
void	empty_all_garbage(t_param *prm);
void	empty_garbage(t_param *prm, int id);
void	print_garbage(t_param *prm);
void	remove_from_garb(t_param *prm, void *ptr);

/*	builtins -> env_utils.c	*/
void	print_env(t_param *prm);
void	garbage_env(t_param *prm);

/*	builtins -> env.c	*/
int		clone_env(t_param *prm, char **env);
char	*get_env_var(t_param *prm, char *name);
int		export_env(t_param *prm, char *str);
int		pos_in_env(t_param *prm, char *str);
int		unset_env(t_param *prm, char *str);

/*	builtins -> exec_env.c	*/
void	exec_env(t_param *prm, char **cmd);
void	exec_export(t_param *prm, char **cmd);
void	exec_unset(t_param *prm, char **cmd);

/*	builtins -> echo.c	*/
void	exec_echo(char **cmd);

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

/*	parser -> parser_error.c	*/
int		check_error_parsing(t_param *prm);

/*	parser -> parser.c	*/
t_node	*parse(t_param *prm, char *line);
t_node	*parsing(t_param *prm);
t_node	*parse_pipe(t_param *prm);
t_node	*parse_exec(t_param *prm);
t_node	*parse_redir(t_param *prm);

/*	parser -> parser_utils.c	*/
char	*get_word(t_param *prm);
char	*get_word_squote(t_param *prm);
char	*get_word_dquote(t_param *prm, t_bool sub);
char	*get_endheredoc(t_param *prm);

/*	parser -> parser_utils_2.c	*/
void	add_last_left(t_node **root, t_node *node);
char	**add_cmd_arg(t_param *prm, char **cmd, char *arg);
char	*substitute_word(t_param *prm, char	*word);
char	*get_space(t_param *prm);

/*	utils -> print_ast.c	*/
void	print_ast(t_param *prm, t_node *root);
char	*get_tk_str(int tk_type);

/*	utils -> utils.c	*/
int		is_redir(int token_type);
int		is_word(t_token token_type);
void	print_space(int space);
int		pos_str(char *str, char c);
int		get_nb_str(char **strs);
#endif
