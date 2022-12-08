#include "../include/minishell.h"

void	handleDollar(t_frame *f)
{
	int	dollar;
	t_token *node;
	char	*tmp;
	char	*expand;
	char	*tmp2;

	node = f->token;
	dollar = f->pos;
	tmp = ft_substr(node->token_str, f->wd_begin, (f->pos - 1) - f->wd_begin);
	while (node->token_str[f->pos] != '\"' && node->token_str[f->pos] != ' ' && node->token_str[f->pos])
		f->pos++;
	tmp2 = ft_strjoin(tmp, getenv("USER"/*ft_substr(node->token_str, dollar, f->pos - dollar)*/));
	free(tmp);
	expand = ft_substr(node->token_str, f->pos, ft_strlen(node->token_str) - f->pos);
	free(node->token_str);
	node->token_str = ft_strjoin(tmp2, expand);
	free(tmp2);
	free(expand);
	printf("expand$: %s\n", node->token_str);
}

/* lida com '$' e '=' */
void	tokenizeWord(t_frame *f)
{
	t_token *node;

	node = f->token;
	f->pos = 0;
	f->wd_begin = 0;
	if (ft_strlen(node->token_str) < 2 && node->token_str[0] == '$')
		return ;
	while (node->token_str[f->pos])
	{
		//dentro de '' passa so a frente;
		if (node->token_str[f->pos] == 39)
		{
			f->pos++;
			printf("dentro de \' \n");
			while (node->token_str[f->pos] != 39)
				f->pos++;
			f->pos++;
		}
		//se dentro de aspas:
			// '$' //pega na palavra a direita para com aspas ou final de palavra; retira a var e insere o value; se n der match delete_ll
		else if (node->token_str[f->pos] == 34)
		{
			f->pos++;
			printf("fora de \" \n");
			while (node->token_str[f->pos] != 34 && node->token_str[f->pos])
			{
				if (node->token_str[f->pos] == '$')
				{
					handleDollar(f);
					f->pos++;
				}
				else
					f->pos++;
			}
			f->pos++;
		}
		else
			f->pos++;
		//se fora de aspas:
			// '$' //palavra a direita para com aspas ou final de palavra;
			// '=' //palavra a esquerda n pode ter aspas; insert(pesq) atras, insert(token) atras, continua 
		//retirar aspas
	}
}
