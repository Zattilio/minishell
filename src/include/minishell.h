/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:07:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/13 11:46:18 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/src/libft.h"
# include "./minishell_struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

# define VERT "\033[0;32m"
# define ROUGE "\033[0;31m"
# define CYAN "\033[0;36m"
# define GRAS_START "\e[1m"
# define GRAS_END "\e[0m"
# define RESET_COLOR "\033[0m"

extern unsigned char	g_return_value;

/*	alloc_garbage	*/
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

/*	alloc_garbage -> garbage_2.c */
void	garbage_split(t_param *prm, int id, char **strs);

/*	builtins	*/
/*	builtins -> echo.c	*/
int		exec_echo(char **cmd);

/*	builtins -> env_utils.c	*/
int		print_env(t_param *prm);
void	garbage_env(t_param *prm);
void	clone_env(t_param *prm, char **env);
int		check_valid_export(char *str);

/*	builtins -> env.c	*/
char	*get_env_var(t_param *prm, char *name);
int		export_env(t_param *prm, char *str);
int		pos_in_env(t_param *prm, char *str);
int		unset_env(t_param *prm, char *str);

/*	builtins -> exec_builtins.c	*/
void	exec_builtins(t_pipe *pipe, char *arg[]);
int		check_is_builtin(char *cmd);
int		exec_cmd(t_pipe *pipe, char *path, char *arg[]);

/*	builtins -> exec_cd.c	*/
int		exec_cd(t_param *prm, char *arg[]);

/*	builtins -> exec_env.c	*/
int		exec_env(t_param *prm, char **cmd);
int		exec_export(t_param *prm, char **cmd);
int		exec_unset(t_param *prm, char **cmd);

/*	builtins -> exec_exit.c	*/
int		exec_exit(t_param *prm, char *arg[]);

/*	builtins -> exec_pwd.c	*/
int		exec_pwd(void);

/*	command_line_interface	*/
/* command_line_interface -> command_line_interface.c */
void	print_minishell_title(void);
void	readline_new_prompt(char **cmd_buf);
void	printf_new_prompt(void);

/*	excec	*/
/*	excec -> close_fd.c	*/
void	close_fd(t_pipe *args, t_fd *fd_list);

/*	excec -> error_cmd.c	*/
int		permission_denied(char **cmd);
int		command_not_found(char **cmd);
int		not_a_command(char **cmd);
int		no_such_file_or_directory(char **cmd);
int		error_ft_strjoin3(char **path_tab, char **cmd);

/*	excec -> exec_pipe.c	*/
int		exec_pipe(t_param *prm, t_node *root);

/*	excec -> exec_root.c	*/
int		exec_root(t_param *prm, t_node *root);

/*	excec -> execute_cmd.c	*/
int		execute_cmd(t_pipe *args, int n_cmd);

/*	excec -> execute_n_cmd.c	*/
int		redir_in(t_node *redir);
int		redir_out(t_node *redir);
int		redirection(t_pipe *args, t_node *redir, int i, t_fd *fd_list);
int		execute_all_cmds(t_pipe *args, int *pids, t_fd *fd_list);

/*	excec -> ft_error.c	*/
int		ft_error(int n, t_pipe *args, t_fd *fd_list);

/*	excec -> ft_putnstr_fd.c	*/
void	ft_put2str_fd(char *s1, char *s2, int fd);
void	ft_put3str_fd(char *s1, char *s2, char *s3, int fd);

/*	excec -> ft_wait.c	*/
void	ft_wait(t_pipe *args, int *pids);

/*	excec -> get_path_name.c	*/
char	*ft_strjoin3(char *str1, char *str2, char *str3);
int		get_path_name(t_pipe *args, char **path_cmd, char **cmd);

/*	excec -> here_doc_utils.c	*/
void	ft_lstprint(t_list *lst, char *stop, t_fd *fd_list, int i);
void	do_heredoc(t_pipe *args, t_fd *fd_list, t_node *node, int i);

/*	excec -> here_doc.c	*/
void	fake_heredoc(t_node *node);
int		is_there_another_heredoc(t_node *node);
int		redirection_heredoc(t_pipe *args, t_node *redir,
			int i, t_fd *fd_list);
void	clean_heredoc(t_pipe *args, t_fd *fd_list);
int		init_heredoc(t_pipe *args, t_fd *fd_list);

/*	excec -> init.c	*/
void	init_pipex(t_pipe *args, int **pids, t_fd **fd_list);
void	init_pipes(t_pipe *args, t_fd *fd_list);

/*	excec -> is_parent_process.c	*/
int		is_parent_process(int *pids, int n);

/* lexer	*/
/* lexer -> lexer.c	*/
char	*get_token(t_param *prm);
t_token	peek_tk(t_param *prm);
t_token	get_t_token(char *token);

/*	parser	*/
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

/*	signals	*/
/*	signals -> signal_child.c	*/
void	handle_sigint_child(int sig);
void	handle_sigquit_child(int sig);
void	init_signal_child(void);

/*	signals -> signal_command_line_interface.c	*/
void	handle_sigint(int sig);
void	init_signal(void);

/*	signals -> signal_heredoc.c	*/
void	handle_sigint_heredoc(int sig);
void	init_signal_heredoc(void);

/*	signals -> signal_parent_during_exec.c	*/
void	handle_sigint_parent_during_exec(int sig);
void	handle_sigquit_parent_during_exec(int sig);
void	init_signal_parent_during_exec(void);

/*	signals -> signal_parent_during_heredoc.c	*/
void	handle_sigint_parent_during_heredoc(int sig);
void	init_signal_parent_during_heredoc(void);

/*	signals -> signal_parent.c	*/
void	handle_sigint_parent(int sig);
void	handle_sigquit_parent(int sig);
void	reset_ret_val_and_init_signal_parent(void);

/*	utils	*/
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
