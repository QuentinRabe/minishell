/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:39 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/16 09:35:51 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# define SPACES "\t\n\v\f\r "
# define PIPENCO ">|<"

typedef struct s_var_env	t_var_env;
typedef struct s_token		t_token;
typedef struct s_var		t_var;
typedef struct s_msh		t_msh;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;
typedef enum e_type			t_type;

enum	e_type
{
	WORD,
	TRUNC,
	APPEND,
	INFILE,
	OUTFILE,
	EOF_HD,
	HEREDOC,
	REDIR_IN
};

struct s_var_env
{
	char		*key;
	char		*value;
	t_var_env	*next;
};

struct s_var
{
	char	*varname;
	char	*value;
	int		index;
	t_var	*next;
};

struct s_token
{
	char	*value;
	t_type	type;
	t_token	*next;
};

struct s_cmd
{
	char	*value;
	t_token	*token_list;
	t_redir	*redir_list;
	int		heredoc_fd[2];
	char	**argv;
	t_cmd	*next;
};

struct s_msh
{
	t_cmd		*cmds;
	t_var_env	*env;
	t_var_env	*exp;
};
#endif
