/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:54:26 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/03 07:11:02 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_var_env	*get_last_node(t_var_env *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	add_new_env(t_var_env *env, char *key, char *value)
{
	t_var_env	*tmp;
	t_var_env	*new;
	t_var_env	*last;
	t_var_env	*prev;

	last = env;
	prev = env;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			tmp = env->next;
			free(env->key);
			free(env->value);
			free(env);
			prev->next = tmp;
			env = tmp;
			break ;
		}
		prev = env;
		env = env->next;
	}
	env = last;
	last = get_last_node(env);
	new = (t_var_env *) malloc(sizeof(t_var_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->is_new = true;
	new->next = NULL;
	last->next = new;
}

char	*var_value(char *str)
{
	int		index;
	char	*value;

	index = ft_strlen_set(str, '=');
	if (str[index])
		index++;
	else
		return (NULL);
	if (str[index])
	{
		value = ft_substr(str, index, ft_strlen(str + index));
		return (value);
	}
	return (NULL);
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

bool	export_process(char **argv, t_var_env *env, t_var_env *exp)
{
	char	*key;
	char	*value;
	int		i;
	bool	error;
	bool	eq;
	int		rm;

	i = 0;
	error = false;
	while (argv[++i])
	{
		eq = false;
		key = var_name(argv[i], &eq);
		if (!key && !eq)
		{
			if (!error)
				error = true;
			continue ;
		}
		value = var_value(argv[i]);
		rm = remove_var_exp(exp, key, value);
		if (value || (!value && eq))
			add_new_env(env, key, value);
		if (!value && !rm)
			add_new_env(exp, key, NULL);
		sort_new_exp(exp);
		free(key);
		free(value);
	}
	return (error);
}

void	print_env(t_var_env *env, int fd)
{
	while (env)
	{
		ft_putstr_fd(env->key, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(env->value, fd);
		env = env->next;
	}
}

int	execute_export(t_cmd *cmd, int fd)
{
	bool	error;
	t_ppx	*data;
	t_msh	*msh;

	error = false;
	data = get_data(1, NULL);
	msh = get_msh(1, NULL);
	/*if (fd < 0)
	{
		fd = 1;
		ft_redir_out(cmd, &fd);
	}*/
	if (!cmd->argv[1])
	{
		print_env(msh->exp, fd);
		if (fd != 1)
			close(fd);
	}
	else
		error = export_process(cmd->argv, msh->env, msh->exp);
	if (error)
	{
		child_exit_process(data, 1);
		return (1);
	}
	child_exit_process(data, 0);
	return (0);
}
