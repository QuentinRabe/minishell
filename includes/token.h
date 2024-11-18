/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:33:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/18 13:33:26 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <t_bool.h>

char	check_for_delimiter(char *str);
char	find_arrow(char *str);
t_bool	is_there_arrow(char *str);
int		count_arrow(char *str, char arrow);
t_token	*find_last_token(t_token *token_lst);
#endif //TOKEN_H
