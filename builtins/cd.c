/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerturk <myerturk@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:59:59 by myerturk          #+#    #+#             */
/*   Updated: 2024/05/23 00:00:01 by myerturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(void)
{
	print_error_msg("cd", "");
	return (EXIT_SUCCESS);
}

int	cd(char **args, t_env *minienv)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (args[1] && args[2])
		return (cd_error());
	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = minienv_value("__HOME", minienv);
	if (chdir(path) != 0)
	{
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	pwd = minienv_value("PWD", minienv);
	oldpwd = minienv_value("OLDPWD", minienv);
	if (oldpwd && pwd && *pwd)
		minienv_update("OLDPWD", pwd, minienv);
	if (pwd && *pwd)
		minienv_update("PWD", getcwd(cwd, PATH_MAX), minienv);
	return (EXIT_SUCCESS);
}
