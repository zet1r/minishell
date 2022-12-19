/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/19 12:40:44 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* return 1 se input acabar por ser nulo */
int	sort_input(t_sh *f)
{
	if (create_words(f))
		return (1);
//	print_list(f->token);
//	printf("\n\n                                       ### LEXER ###                         \n\n");
	if (_expander(f))
		return (1);
//	print_list(f->token);
//	printf("\n\n                                       ### PARSER ###                        \n\n");
	if (parsecmd(f) != 0)
		return (1);
//	printf("\n\n                                       ### NO FINAL ###                      \n\n");
//	print_listcmd(f->cmd);
//	printf("\n                                        ...free...                              \n");
	return (0);
}