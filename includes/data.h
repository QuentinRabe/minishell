/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:39 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 10:03:51 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_msh		t_msh;
typedef struct s_env		t_env;
typedef struct s_cmd		t_cmd;
typedef struct s_token		t_token;
typedef enum e_token_kind	t_token_kind;

enum e_token_kind
{
	WORD,
	TRUNC,
	APPEND,
	INFILE,
	OUTFILE,
	HEREDOC,
	REDIR_IN
};

struct s_env
{
	char	**path;
	char	**dup_env;
};

struct s_token
{
	t_token_kind	kind;
	char			*value;
};

struct s_cmd
{
	struct s_token	*tokens;
};

struct s_msh
{
	char			*cmd;
	struct s_env	env_data;
	struct s_cmd	*cmd_arr;
};

#endif
