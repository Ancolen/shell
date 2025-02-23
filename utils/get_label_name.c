/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerturk <myerturk@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:20:20 by myerturk          #+#    #+#             */
/*   Updated: 2024/05/23 00:20:21 by myerturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_name_end(char *name)
{
	int	name_end;

	name_end = 0;
	while (name[name_end] && !is_name_delimeter(name[name_end]))
	{
		if (name[name_end] == '\'')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '\'')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] == '"')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '"')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] && !is_name_delimeter(name[name_end]))
			name_end++;
	}
	return (name_end);
}

char	*get_label_name(char *redirect_str)
{
	int		name_start;
	int		name_end;
	char	*name;
	char	*remaining_cmd;

	name_start = 0;
	move_one_forward(redirect_str);
	if (redirect_str[name_start] == '>')
		move_one_forward(&redirect_str[name_start]);
	while (redirect_str[name_start] == ' ' || redirect_str[name_start] == '\t')
		name_start++;
	name_end = get_name_end(&redirect_str[name_start]);
	name = ft_substr(&redirect_str[name_start], 0, name_end);
	remaining_cmd = &redirect_str[name_start + name_end];
	ft_memmove(redirect_str, remaining_cmd, ft_strlen(remaining_cmd) + 2);
	return (name);
}
