/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:39 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 23:30:42 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# define SPACES "\t\n\v\f\r "
# define PIPENCO ">|<"

typedef struct s_token	t_token;
typedef enum e_type		t_type;

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

struct s_token
{
	char	*value;
	t_type	type;
	t_token	*next;
};

// enum e_token_kind
// {
// 	WORD,
// 	TRUNC,
// 	APPEND,
// 	INFILE,
// 	OUTFILE,
// 	EOF_HD,
// 	HEREDOC,
// 	REDIR_IN
// }	t_token_kind;

#endif
