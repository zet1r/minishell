/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:06 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/18 22:36:26 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_list(t_token *head)
{
	printf("\n                                          Mem                                    \n");
	while (head != NULL)
	{
		printf("word: %s | ", head->word);
		printf("type: %c\n", head->type);
		head = head->next;
	}
	printf("\n                                      Mem END                                    \n");
}

void	print_listcmd(t_cmd *head)
{
	int	i;


	printf("\n                                          Mem                                    \n");
	if (!(head->full_cmd))
		return ;
	while (head != NULL)
	{
		i = 0;
		while (head->full_cmd[i])
		{
			if (i == 0)
				printf("Command: %s | ADRESS: %p\n", head->full_cmd[i], head);
			else
				printf("Arg[%i]: %s\n", i - 1, head->full_cmd[i]);
			i++;
		}
		head = head->next;
	}
	printf("\n                                      Mem END                                    \n");
}

void	initcmd(t_cmd *node)
{
	node->full_cmd = NULL;
	node->path = NULL;
	node->in_file= STDIN_FILENO;
	node->out_file = STDOUT_FILENO;
}

void ddl_append(t_cmd **head)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = NULL;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));

	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

/* adiciona tipo de token */
void	addType_ll(t_sh *f, char type)
{
	t_token	*head;

	head = f->token;
	while (head->next != NULL)
		head = head->next;
	head->type = type;
}

/* adiciona mais um node (do tipo neutro) a lista de tokens */
void append_dll(t_sh *f, t_token **head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	(void)f;
	new_node = NULL;
	new_node = (t_token *)malloc(sizeof(t_token));

	new_node->word = s;
	new_node->type = 'N';
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}
