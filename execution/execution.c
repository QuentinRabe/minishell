/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:06:08 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/03 09:53:37 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	child_first_process(t_msh *msh, t_cmd *ptr_cmds \
, t_ppx *data, char **env)
{
	int	input;
	int	output;

	input = -1;
	output = -1;
	ft_open_file(ptr_cmds, data, &input, &output);
	if (data->nb_cmd > 1 && data->idx > 0)
		dup2(data->fd[data->idx - 1][0], STDIN_FILENO);
	if (data->nb_cmd > 1 && data->idx < data->nb_cmd - 1)
		dup2(data->fd[data->idx][1], STDOUT_FILENO);
	if (data->idx == 0)
		dup2(input, STDIN_FILENO);
	if (data->idx == data->nb_cmd - 1)
		dup2(output, STDOUT_FILENO);
	if (input >= 0)
		close(input);
	if (output >= 0)
		close(output);
	if (ft_builtins(msh, ptr_cmds, env, STDOUT_FILENO))
		return ;
	close_unused_pipes(data, data->idx);
	execute(ptr_cmds, env);
}

int	**allocate_array(int rows, int cols)
{
	int	**array;
	int	i;

	i = 0;
	array = (int **)malloc(sizeof(int *) * (rows + 1));
	if (array == NULL)
	{
		perror("Erreur d'allocation pour les lignes");
		return (NULL);
	}
	while (i < rows)
	{
		array[i] = (int *)malloc(sizeof(int) * cols);
		if (array[i] == NULL)
		{
			while (i > 0)
				free(array[i--]);
			free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}

int	**create_pipe(t_ppx *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		if (pipe(data->fd[i]) == -1)
			perror("pipe");
		i++;
	}
	return (data->fd);
}

void	init_data(t_ppx *data, t_cmd	*cmds)
{
	data->idx = 0;
	data->nb_cmd = ft_strlen_argv(cmds);
	if (data->nb_cmd > 1)
	{
		data->fd = allocate_array(data->nb_cmd - 1, 2);
		if (data->fd == NULL)
			exit(1);
	}
	data->fd = create_pipe(data);
}

int	ft_execution(t_msh *msh, char **env)
{
	t_cmd	*ptr_cmds;
	t_ppx	data;
	int		status;

	get_data(0, &data);
	ptr_cmds = msh->cmds;
	init_data(&data, msh->cmds);
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, SIG_IGN);
	while (ptr_cmds)
	{
		data.pid = fork();
		if (data.pid == 0)
		{
			config_sig();
			child_first_process(msh, ptr_cmds, &data, env);
			exit(0);
		}
		data.idx++;
		close_heredoc_fd(ptr_cmds);
		ptr_cmds = ptr_cmds->next;
	}
	ft_wait(&data, &status);
	cleanup_data(&data);
	return (1);
}
