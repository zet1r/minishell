/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createWords.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:46 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/13 11:09:09 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* check for operators */
int	findOperator(char c)
{
	if (c == 60)  /* < */
		return (1);
	if (c == 62)  /* > */
		return (1);
	if (c == 124) /* | */
		return (1);
	return (0);
}

/* separa palavra antes de operador e o operador */
void	lexOp(t_sh *f)
{
	if (f->parser->pos - f->parser->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->parser->str, f->parser->wd_begin, f->parser->pos - f->parser->wd_begin)); //palavra ate operator
	f->parser->wd_begin = f->parser->pos;
	if (f->parser->str[f->parser->pos] == 60 || f->parser->str[f->parser->pos] == 62) /* << >> */
	{
		if (f->parser->str[f->parser->pos + 1] == f->parser->str[f->parser->pos])
			f->parser->pos += 2;
		else
			f->parser->pos++;
	}
	else
		f->parser->pos++;

	append_dll(f, &(f->token), ft_substr(f->parser->str, f->parser->wd_begin, f->parser->pos - f->parser->wd_begin)); //operator
	f->parser->wd_begin = f->parser->pos;
	addType_ll(f, 'O');
}

/* separa palavra normal + espacos entre palavras */
void	lexWdend(t_sh *f)
{
	if (f->parser->pos - f->parser->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->parser->str, f->parser->wd_begin, f->parser->pos - f->parser->wd_begin));
	while (f->parser->str[f->parser->pos] == ' ')
		f->parser->pos++;
	f->parser->wd_begin = f->parser->pos;
}

/* separa desde 1a aspa ate proxima aspa*/
void	lexQuote(t_sh *f)
{
	if (f->parser->str[f->parser->pos] == 34)
	{
		f->parser->pos++;
		while (f->parser->str[f->parser->pos] != 34)
		{
			if (f->parser->str[f->parser->pos] == '\0')
				{printf("err quotes");exit(-1);}
			f->parser->pos++;
		}
	}
	else if (f->parser->str[f->parser->pos] == 39)
	{
		f->parser->pos++;
		while (f->parser->str[f->parser->pos] != 39)
		{
			if (f->parser->str[f->parser->pos] == '\0')
				{printf("err quotes");exit(-1);}
			f->parser->pos++;
		}
	}
	f->parser->pos++;
}

/* separa input por palaras; se algum par de quotes não fechar da erro */
void	createWords(t_sh *f)
{
	while (f->parser->str[f->parser->pos] != '\0')
	{
		if (f->parser->str[f->parser->pos] == '\'' || f->parser->str[f->parser->pos] == '\"') /* errno */
			lexQuote(f);
		else if (findOperator(f->parser->str[f->parser->pos]))
			lexOp(f);
		else if (f->parser->str[f->parser->pos] == ' ')
			lexWdend(f);
		else
			f->parser->pos++;
	}
	if (f->parser->pos - f->parser->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->parser->str, f->parser->wd_begin, f->parser->pos - f->parser->wd_begin)); //ultima palavra
	printf("current f->parser->pos: %i - %c\n", f->parser->pos, f->parser->str[f->parser->pos]);
}