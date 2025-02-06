/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:39 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/06 09:13:18 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# define SPACES "\t\n\v\f\r "
# define PIPENCO ">|<"
# define DIGITS "0123456789"

typedef struct s_var_env	t_var_env;
typedef struct s_token		t_token;
typedef struct s_var		t_var;
typedef struct s_msh		t_msh;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_ppx		t_ppx;
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
	REDIR_IN,
	IN,
	OUT
};

struct s_var_env
{
	char		*key;
	char		*value;
	bool		is_new;
	t_var_env	*next;
};

struct s_var
{
	char	*varname;
	char	*value;
	int		index;
	t_var	*next;
};

struct s_redir
{
	t_type	type;
	t_type	absolute_type;
	char	*filename;
	int		heredoc_fd[2];
	bool	is_last;
	bool	expand;
	bool	in_dq;
	t_redir	*next;
};

struct s_token
{
	char	*value;
	bool	in_dq;
	t_type	type;
	t_token	*next;
};

struct s_cmd
{
	char	*value;
	t_token	*token_list;
	t_redir	*redir_list;
	char	**argv;
	t_cmd	*next;
};

struct s_msh
{
	t_cmd		*cmds;
	t_var_env	*env;
	t_var_env	*exp;
	int			hd_fd_write;
	int			hd_fd_read;
	int			status;
	int			historic_fd;
};

struct s_ppx
{
	pid_t	pid;
	int		**fd;
	int		idx;
	int		nb_cmd;
};

#endif
