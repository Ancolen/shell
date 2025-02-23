/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerturk <myerturk@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:13:31 by myerturk          #+#    #+#             */
/*   Updated: 2024/05/23 00:13:33 by myerturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_exit_status_position(char *input)
{
	while (input && *input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && input[1] == '?')
					return (input);
				input++;
			}
		}
		if (*input == '$' && input[1] == '?')
			return (input);
		input++;
	}
	return (NULL);
}

static void	update_input(char **input, char *exit_code, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	first_part = ft_strjoin(*input, exit_code);
	updated_input = ft_strjoin(first_part, second_part);
	free(*input);
	*input = NULL;
	free(first_part);
	first_part = NULL;
	*input = updated_input;
}

void	expand_exit_status(char **input, int exit_status)
{
	char	*exit_status_position;
	char	*exit_status_str;

	exit_status_position = find_exit_status_position(*input);
	if (exit_status_position)
	{
		*exit_status_position = '\0';
		exit_status_str = ft_itoa(exit_status);
		update_input(input, exit_status_str, (exit_status_position + 2));
		free(exit_status_str);
		exit_status_str = NULL;
		expand_exit_status(input, exit_status);
	}
}
