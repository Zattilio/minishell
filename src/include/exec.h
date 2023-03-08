/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:58:37 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/03 15:20:46 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/*import wait*/
# include <sys/wait.h>
/*import read*/
# include <fcntl.h>

typedef struct s_param	t_param;
typedef struct s_node	t_node;
typedef struct s_pipe	t_pipe;
typedef struct s_fd		t_fd;

int		exec_root(t_param *prm, t_node *root);
int		exec_pipe(t_param *prm, t_node *root);
int		exec_cmd(t_pipe *args, char *path, char *arg[]);


int		get_path_name(t_pipe *args, char **path_cmd1, char **cmd);

void	ft_wait(t_pipe *args, int *pids);

int		execute_cmd(t_pipe *args, int n_cmd);
//int		execute_last_cmd(t_pipe *args, t_fd *fd_list);
int		execute_all_cmds(t_pipe *args, int *pids, t_fd *fd_list);
//int		execute_first_cmd(t_pipe *args, t_fd *fd_lst);

int		is_parent_process(int *pids, int n);
int		ft_error(int n, t_pipe *args, t_fd *fd_list);
void	close_fd(t_pipe *args, t_fd *fd_list);

void	ft_put2str_fd(char *s1, char *s2, int fd);
void	ft_put3str_fd(char *s1, char *s2, char *s3, int fd);
char	*ft_strjoin3(char *str1, char *str2, char *str3);

int		permission_denied(char **cmd);
int		command_not_found(char **path_tab, char **cmd);
int		path_not_found(char **path_tab, char **cmd);
int		error_ft_strjoin3(char **path_tab, char **cmd);

void	init_pipex(t_pipe *args, int **pids, t_fd **fd_list);
void	init_pipes(t_pipe *args, t_fd *fd_list);
void	init_fork(t_pipe *args, int *pids, t_fd *fd_list);
int		init_fork_heredoc(t_pipe *args, int *pids, t_fd *fd_list);

void	init_signal_child(void);
void	init_signal_parent(void);
void	init_signal_parent_during_heredoc(void);
void	init_signal_parent_during_exec(void);
void	init_signal_heredoc(void);

#endif
