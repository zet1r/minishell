/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/10 23:49:14 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parseCmds(t_frame *f)
{
	printf("...Parser...\n");
	append_dll_cmd(f, &(f->cmds));
	int	i = 0;
	while (f->token->next != NULL)
	{
		if (f->token->token_type == 'O' && ft_strcmp(f->token->token_str, "| "))
		{
			parsePipes(f);	
			i = 0;
		}
		else
		{
			addStrCmd(f);
			printf("cmd/arg~%i: %s\n",i, f->cmds->full_cmd[i]);i++;
		}
	}
	if (f->token->token_type == 'O' && ft_strcmp(f->token->token_str, "| "))
	{
		parsePipes(f);	
		i = 0;
	}
	else
	{
		addStrCmd(f);
		printf("cmd/arg~%i: %s\n",i, f->cmds->full_cmd[i]);i++;
	}
}

/* return em caso de !str */
int	lexer(t_frame *f)
{
	printf("..lexer..\n");
	printList(f->token);
	while (f->token->next != NULL)
	{
		if (lexWord(f))
			remove_dll(f);
		else
			f->token = f->token->next;
	}
	if (lexWord(f))
		remove_dll(f);
	if (f->token == NULL)
	{	
		printf("\nNo match found\n");
		return (1);
	}
	while (f->token->prev != NULL) /*man de dll*/
		f->token = f->token->prev;
	return (0);
}

/*  */
void	createWords(t_frame *f) //os operadores definem o resto dos tokens!!
{
	while (f->str[f->pos] != '\0')
	{
		if (f->str[f->pos] == '\'' || f->str[f->pos] == '\"') //dentro de quotes 
			lexQuote(f);
		else if (findOperator(f->str[f->pos])) //operador
			lexOp(f);
		else if (f->str[f->pos] == ' ') //final de word
			lexWdend(f);
		else //args
			f->pos++;
	}
	if (f->pos - f->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
}

/* return se input acabar por ser nulo */
void	sortInput(t_frame *f)
{
	createWords(f);
	printf("\n##########################################################\n");
	if (lexer(f))
		return ;
	printf("\n##########################################################\n");
	printf("\nBEFORE PARSER\n");
	printList(f->token);
	free(f->str); // DAR FREE A STR DO READLINE!
	printf("\n##########################################################\n");
	parseCmds(f);
	printf("\n##########################################################\n");
}