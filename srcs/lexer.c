#include "../include/minishell.h"

void printList(t_token *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->token_str);
		head = head->next;
	}
}

void	ft_ll_free(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	ft_ll_append(t_token **head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->token_str = ft_strdup(s);
	free(s);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}

/* espera pela " ou ' para fechar  */
static char	*ft_wait_match(char c)
{
	char 	*str;

	//handle_sig();
	str = get_str();
	while (!(ft_strchr(str, c)))
	{
		free(str);
		str = get_str();
	}
	free(str);
	return ()
}

/* calcula tamanho palavra e adiciona a lista */
int	ft_token_word(t_frame *main_f, char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (c != ' ' && s[i] != c)
		s = ft_wait_match(c);
	ft_ll_append(&(main_f->token_f), ft_substr(s, 0, i));
	return (i);
}

/* lê input do readline, separa palavra a palavra a não ser que encontre " ou ' */
void	ft_tokenizer(t_frame *main_f, char *line_r)
{
	int	i;
	int	wsize;

	main_f->token_f = NULL;
	i = 0;
	while (line_r[i] != '\0')
	{
		if (line_r[i] == '\"')
			wsize = ft_token_word(main_f, line_r + i + 1, '\"') + 2;
		else if (line_r[i] == '\'')
			wsize = ft_token_word(main_f, line_r + i + 1, '\'') + 2;
		else
			wsize = ft_token_word(main_f, line_r + i, ' ') + 1;
		printf("i = %i\n", i);
		i += wsize;
		printf("i = %i\n", i);
	}
	printList(main_f->token_f);
	ft_ll_free(main_f->token_f);
}
