/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:58:37 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/01 18:47:39 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

/*import wait*/
# include <sys/wait.h>
/*import read*/
# include <fcntl.h>

typedef struct s_fd
{
	int	fd[2];
}				t_fd;

typedef struct s_arg
{
	int		argc;
	char	**argv;
	char	**env;
}				t_arg;

int		main_pipex(int argc, char *argv[], char *env[]);

int		get_path_name(t_arg *args, char **path_cmd1, char **cmd);

void	ft_wait(t_arg *args, int *pids);

int		execute_cmd(t_arg *args, int n_cmd);
int		execute_last_cmd(t_arg *args, t_fd *fd_list);
void	execute_middle_cmd(t_arg *args, int *pids, t_fd *fd_list);
int		execute_first_cmd(t_arg *args, t_fd *fd_lst);

int		is_parent_process(int *pids, int n);
int		ft_error(int n, t_arg *args, int *pids, t_fd *fd_list);
void	close_fd(t_arg *args, t_fd *fd_list);

void	ft_heredoc(t_arg *args, t_fd *fd_list);
int		check_heredoc(t_arg *args);
void	fork_heredoc(t_arg *args, int *pids, t_fd *fd_list);

int		permission_denied(char **cmd);
int		command_not_found(char **path_tab, char **cmd);
int		error_ft_strjoin3(char **path_tab, char **cmd);

void	init_pipex(t_arg *args, int **pids, t_fd **fd_list);
void	init_pipes(t_arg *args, int *pids, t_fd *fd_list);
void	init_fork(t_arg *args, int *pids, t_fd *fd_list);
t_arg	*init_arg(int *argc, char **argv[], char **env[]);

#endif
