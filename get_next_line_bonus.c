/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 02:31:32 by lucia-ma          #+#    #+#             */
/*   Updated: 2022/10/11 01:01:45 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lstadd_back(t_list **lst, void *content)
{
	t_list	*last;
	t_list	*new;

	new = (void *)malloc(sizeof(t_list));
	new->content = content;
	new->next = NULL;
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	if (last == NULL)
		return ;
	while (last->next != NULL)
		last = last -> next;
	last -> next = new;
}

void	ft_lstiter(t_list *ls, size_t (*ft_len)(const char *)
, char *ft_p, char	**s, int *l)
{
	char	*cont;

	while (ls)
	{
		if (ft_p == NULL)
		{
			*l += ft_len(ls->content);
		}
		if (ft_len == NULL)
		{
			cont = (char *) ls->content;
			while (*cont)
			{
				*(*s) = *(cont++);
				(*s)++;
			}
		}
		ls = ls->next;
	}
}

void	iterador(char **st, char **s, int *i)
{
	int	e;
	int	x;

	x = 0;
	e = 0;
	while ((*s)[*i])
	{
		if ((*s)[*i] == '\n')
		{
			x = *i + 1;
			*st = ft_calloc(ft_strlen(&(s[0][*i])), 1);
			while ((*s)[++(*i)])
				(*st)[e++] = (*s)[*i];
			(*s)[x] = 0;
			*i = x - 1;
			break ;
		}
		*i = *i + 1;
	}			
}

char	*ft_copy(char *str)
{
	char		*ret;
	int			counter;

	ret = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!ret)
		return (NULL);
	counter = 0;
	while (str[counter])
	{
		ret[counter] = str[counter];
		counter ++;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	char			*s;
	static char		*st[4096];
	t_list			*ls;
	int				i;

	if (fd < 0)
		return (NULL);
	s = ((i = ((ls = NULL), 0)), ft_calloc(BUFFER_SIZE + 1, 1));
	while (s[i] != '\n')
	{
		ft_bzero((i = 0, s), BUFFER_SIZE + 1);
		if (st[fd])
			st[fd] = ((s = (free(s), ft_copy(st[fd]))), free(st[fd]), NULL);
		else
			if (read(fd, s, BUFFER_SIZE) <= 0)
				break ;
		ft_lstadd_back((iterador(&st[fd], &s, &i), &ls), ft_strdup(s));
	}
	if (ls == NULL)
		return (free(s), ft_freelist(ls), free(st[fd]), NULL);
	ft_lstiter((i = (free(s), 0), ls), &ft_strlen, NULL, NULL, &i);
	ft_lstiter((s = ft_calloc(i + 1, 1), ls), NULL, "ft_put", &s, NULL);
	if (ft_freelist(ls), !*(s - i))
		return (free(s - i), NULL);
	return (s - i);
}
