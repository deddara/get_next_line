/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:23:19 by deddara           #+#    #+#             */
/*   Updated: 2020/07/25 14:28:30 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	clear(t_list **list, int fd, int code)
{
	t_list *tmp;
	t_list	*var;

	if(*list)
	{
		tmp = *list;
		if(tmp->fd == fd)
			*list = tmp->next;
		else
		{
			while (tmp->next->fd != fd)
				tmp = tmp->next;
			var = tmp->next;
			tmp->next = var->next;
			tmp = var;
		}
		free(tmp->rest_buf);
		free(tmp->line_back);
		free(tmp);
	}
	if (code == -1)
		return(-1);
	return (0);
}

static char *check_buf(t_list *list, char **line)
{
	char *new_liner;
	char *new_line;

	if((list)->rest_buf == NULL)
	{
		if(!(new_liner = (char *)malloc(sizeof(char) * 1)))
			return(NULL);
		new_liner[0] = '\0';
		return(new_liner);
	}
	if ((new_line = ft_strchr((list)->rest_buf, '\n')))
	{
		*new_line++ = '\0';
		if(!((*line) = ft_strdup((list)->rest_buf)))
			return (NULL);
		(list)->rest_buf = new_line;
		return(*line);
	}
	if(!((*line) = ft_strdup((list)->rest_buf)))
		return (NULL);
	(list)->rest_buf = NULL;
	return(*line);
}

t_list	*get_fd(t_list **list, int fd)
{
	t_list *tmp;
	t_list	*tmp1;
	if ((*list) == NULL)
		return((*list = ft_lstnew(fd)));
	tmp = (*list);
	while ((tmp->fd != fd && tmp->next != 0))
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	else
	{
		tmp1 = ft_lstnew(fd);
		tmp->next = tmp1;
		free(tmp1);
		return(tmp->next);
	}
}

static int	reader_mn(char *buf, t_list *list, char **line)
{
	char *new_line;

	if ((new_line = ft_strchr(buf, '\n')))
	{
		*new_line = '\0';
		new_line++;
		if(!((list)->rest_buf = ft_strdup(new_line)))
			return (-1);
	}
	list->line_back = (*line);
	if(!((*line) = ft_strjoin(*line, buf)))
		return (-1);
	free(list->line_back);
	list->line_back = NULL;
	return (0);
}

static int	read_line(t_list **list, char **line, int fd, t_list *ptr)
{
	char buf[BUFFER_SIZE + 1];
	int		ret;
	int		result;

	result = 0;
	ret = -1;
	while (((ptr)->rest_buf == NULL) && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret < 0)
			return (clear(list, fd,-1));
		buf[ret] = '\0';
		result = reader_mn(buf, ptr, line);
		if (result == -1)
			return (clear(list, fd, -1));
	}
	if (ret < BUFFER_SIZE && ((ptr)->rest_buf) == NULL)
	{
		return (clear(list, fd, 0));
	}
	return (1);
}

int get_next_line(int fd, char **line)
{
	static t_list *list;
	t_list			*list_ptr;
	char			test[1];

	if (fd < 0 || !line || read(fd, test, 0) < 0 || !(list_ptr = get_fd(&list, fd)))
		return (-1);
	if(!((*line) = check_buf(list_ptr, line)))
		return (clear(&(list), fd, -1));
	return (read_line(&(list), line, fd, list_ptr));
}
