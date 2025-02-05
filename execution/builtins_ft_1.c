/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:54:26 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/05 07:32:07 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_new_env(t_var_env *env, char *key, char *value)
{
	t_var_env	*new;
	t_var_env	*prev;

	prev = env;
	free_existent_key(key, env, &prev, value);
	if (prev && !prev->next && !value)
		return ;
	new = (t_var_env *) malloc(sizeof(t_var_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->is_new = true;
	new->next = NULL;
	if (prev)
		prev->next = new;
	else
		env = new;
}

char	*var_name(char *str, bool *eq)
{
	char	*name;
	int		len;

	len = ft_strlen_set(str, '=');
	if (str[len] && str[len] == '=')
		*eq = true;
	name = ft_substr(str, 0, len);
	if ((!ft_isalpha(name[0]) && name[0] != '_')
		|| !export_valid_varname(name))
	{
		ft_putstr_fd("msh: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(name);
		return (NULL);
	}
	return (name);
}

static int	continue_check(char *key, bool eq, bool *error)
{
	if (!key && !eq)
	{
		if (!(*error))
			*error = true;
		return (1);
	}
	return (0);
}

bool	export_process(char **argv, t_var_env *env, t_var_env *exp)
{
	char	*key;
	char	*value;
	int		i;
	bool	error;
	bool	eq;

	i = 0;
	error = false;
	while (argv[++i])
	{
		eq = false;
		key = var_name(argv[i], &eq);
		if (continue_check(key, eq, &error))
			continue ;
		value = var_value(argv[i]);
		if (value || (!value && eq))
			add_new_env(env, key, value);
		add_new_env(exp, key, value);
		sort_new_exp(exp);
		free(key);
		free(value);
	}
	return (error);
}

int	execute_export(t_cmd *cmd, int fd_in, int fd_out)
{
	bool	error;
	t_ppx	*data;
	t_msh	*msh;
	bool	std[2];

	error = false;
	msh = get_msh(1, NULL);
	init_stds(&std[0], &std[1]);
	data = get_data(1, NULL);
	if (check_fd(&fd_in, &fd_out, &std[0], &std[1]) == 1)
		return (1);
	if (!cmd->argv[1])
		print_env(msh->exp, fd_out);
	else
		error = export_process(cmd->argv, msh->env, msh->exp);
	if (ft_strlen_argv(msh->cmds) == 1 && std[1])
		close(fd_out);
	if (error)
		return (child_exit_process(data, 1), 1);
	return (child_exit_process(data, 0), 0);
}
