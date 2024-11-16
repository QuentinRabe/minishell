/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:39 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/11 10:48:51 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# define TRUE 1
# define FALSE 0

typedef struct s_msh		t_msh;
typedef struct s_env		t_env;
typedef struct s_cmd		t_cmd;
typedef struct s_token		t_token;
typedef struct s_e_env		t_e_env;
typedef enum e_token_kind	t_token_kind;
typedef int					t_bool;

enum e_token_kind
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

struct s_e_env
{
	struct s_e_env	*prev;
	char			*key;
	char			*value;
	struct s_e_env	*next;
};

struct s_env
{
	char	**path;
	t_e_env	*env;
	t_e_env	*ex_env;
};

struct s_token
{
	struct s_token	*prev;
	t_token_kind	kind;
	t_bool			in_d_quote;
	t_bool			in_s_quote;
	char			*value;
	struct s_token	*next;
};

struct s_cmd
{
	char			*value;
	struct s_token	*token_lst;
	struct s_cmd	*next;
};

struct s_msh
{
	char			*cmd;
	int				*pipe_pos;
	int				quoted_pipe;
	int				i_qut_pipe;
	struct s_env	env_data;
	struct s_cmd	*cmd_lst;
};

#endif
