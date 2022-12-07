#include "../include/minishell.h"

int	findOperator(char c)
{
	if (c == 61)  /* = */
		return (1);
	if (c == 60)  /* < */
		return (1);
	if (c == 62)  /* > */
		return (1);
	if (c == 124) /* | */
		return (1);
	if (c == 36)  /* $ */
		return (1);
	return (0);
}

void	lexDollar(t_frame *f)
{
	f->pos++;
	while (f->str[f->pos] != ' ' && f->str[f->pos])
		f->pos++;
	if (f->pos - f->wd_begin)
		append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //palavra ate operator
	f->wd_begin = f->pos;
}

void	lexOp(t_frame *f)
{
	
	if (f->pos - f->wd_begin)
		append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //palavra ate operator
	f->wd_begin = f->pos;
	if (f->str[f->pos] == 60 || f->str[f->pos] == 62) /* >> << */
	{
		if (f->str[f->pos + 1] == f->str[f->pos])
			f->pos += 2;
		else
			f->pos++;
	}
	else
		f->pos++;
	append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //operator
	f->wd_begin = f->pos;
}

void	lexer(t_frame *f) //os operadores definem o resto dos tokens!!
{
	while (f->str[f->pos] != '\0')
	{
		if (f->str[f->pos] == '\'' || f->str[f->pos] == '\"') //dentro de quotes 
			next_quote(f);
		else if (findOperator(f->str[f->pos])) //operador
		{
			if (f->str[f->pos] == 36)
				lexDollar(f);
			else
				lexOp(f);
		}
		else if (f->str[f->pos] == ' ') //final de word
		{
			if (f->pos - f->wd_begin)
				append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin));
			while (f->str[f->pos] == ' ')
				f->pos++;
			f->wd_begin = f->pos;
		}
		else //args
			f->pos++;
	}
	if (f->pos - f->wd_begin)
		append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
	printList(f->token);
}
