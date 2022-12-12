/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_unset_echo_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:56:42 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/12 12:09:00 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*pwd with no options*/
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);//
	ft_putendl_fd(pwd, 1);
	free (pwd);
	return (0);
}

/*unset with no options*/
int	ft_unset(t_sh *sh)
{
	int		i;
	int		n;

	n = mtr_len(sh->test);
	if (n > 1)
	{
		i = 0;
		while (sh->test[++i])
			rmv_env(sh->test[i], sh);
	}
	return (0);
}

/*echo with option -n*/
int	ft_echo(t_sh *sh)
{
	int	i;
	int	n;
	int	opt;

	i = 0;
	n = mtr_len(sh->test);
	opt = ft_strncmp(sh->test[1], "-n", 2);
	if (n < 2 || (!opt && n < 3))
		return (0);
	if (!opt)
		i++;
	while (sh->test[++i])
	{
		ft_putstr_fd(sh->test[i], 1);
		if (sh->test[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (opt)
		ft_putchar_fd('\n', 1);
	return (0);
}

/*cd with only a relative or absolute path*/
int	ft_cd(t_sh *sh)
{
	int		n;
	char	*pwd;
	char	*oldpwd;

	n = mtr_len(sh->test);
	if (n > 2)
	{
		perror("cd error too many args");//
		return (0);//
	}
	if (n == 1)
		cd_home(sh);
	if(chdir(sh->test[1]) == -1)
	{
		perror("cd error wrong path");//
		return (0);//
	}
	pwd = getcwd(NULL, 0);
	oldpwd = get_env("PWD", sh);
	set_env("OLDPWD", oldpwd, sh);
	set_env("PWD", pwd, sh);
	free(pwd);
	free(oldpwd);
	return (0);
}

int	cd_home(t_sh *sh)
{
	char	*home;

	home = get_env("HOME", sh);
	if(!home)
	{
		perror("cd error setting home");
		return (0);//
	}
	sh->test = mtr_add(home, sh->test);
	free(home);
	if (!sh->test)
	{
		perror("cd error setting home");//
		return (0);//
	}
	return (0);
}
