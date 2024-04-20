/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:37:50 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/20 17:43:35 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

//we use substr to grab what was in stash and fill the line
// static char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	i;
// 	size_t	j;

// 	i = start;
// 	if (!s[0]) /* another protection from "s" read */
// 		return (NULL);
// 	j = 0;
// 	if (start > ft_strlen(s))
// 		return (NULL);
// 	j = ft_strlen(s + start);
// 	if (len > j)
// 		len = j;
// 	substr = malloc((len + 1) * sizeof(char));
// 	if (!s || !substr)
// 		return (NULL);
// 	j = 0;
// 	while (i < ft_strlen(s) && j < len)
// 		substr[j++] = s[i++];
// 	substr[j] = '\0';
// 	return (substr);
// }

//this function helps us to complete the line up to the '\n' character is found 
char	*ft_strchr(char *s, int c) /* SEEM OK */
{
	int	i;

	i = 0;
	if (!s)
		return (free(s), s = NULL, NULL); /* MISSING PROTECTION */
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *) &s[i]);
	return (0); /* 0 instead of NULL means OK end */
}

char	*clean_stash(char *line_buf) /* SEEM OK*/
{
	size_t	i;
	size_t	j;  /* you need to avoid substring */
	char	*stash;

	i = 0;
	while (line_buf[i] != '\0' && line_buf[i] != '\n')
		i++;
	if (!line_buf[i]) /* just deny the existence !line_buff */
		return (free(line_buf), line_buf = NULL, NULL);
	// stash = ft_substr(line_buf, i + 1, ft_strlen(line_buf) - i); /* AVOID SUBSTRING, ITS JUST ANOTHER MEM PROBLEM TO HANDLE */
	stash = malloc(sizeof(char) * (ft_strlen(line_buf) + 1));
	// if (*stash == 0)
	// {
	// 	free(stash);
	// 	stash = NULL;
	// }
	if(!stash)
		return (free(stash), stash = NULL, NULL);
	i++;
	j = 0; /* initialize j */
	while (line_buf[i] != '\0')
		stash[j++] = line_buf[i++];
	stash[j] = '\0';
	return (free(line_buf), line_buf = NULL, stash);
}

char	*complete_line_2(char *stash) /* SEEM OK */
{
	size_t	nbr;
	char	*tmp;

	if (!stash[0])
		return (NULL);	
	nbr = 0;
	while (stash[nbr] != '\0')
	{
		if (stash[nbr++] == '\n')
			break ;
	}
	tmp = malloc(sizeof(char) * (nbr + 1));
	if (!tmp)
		return (NULL);
	nbr = -1;
	while (stash[nbr++] != '\0' && stash[nbr] != '\n')
		tmp[nbr] = stash[nbr];
	if (stash[nbr] == '\n')
		tmp[nbr++] = '\n';
	tmp[nbr] = '\0';	
	return (tmp);
}

char	*complete_line(int fd, char *stash) /* ft_read_fd  CHECKED OK */ 
{
	char	*tmp;
	int		nbr;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	nbr = 1;
	if (!tmp)
		return (free(stash), stash = NULL, NULL);
	while (nbr > 0 && !ft_strchr(stash, '\n'))
	{
		nbr = read(fd, tmp, BUFFER_SIZE);
		if (nbr > 0)
		{
			tmp[nbr] = '\0';
			stash = ft_strjoin(stash, tmp);
		}
	}
	free(tmp);
	if (nbr < 0)
		return (free(stash), stash = NULL, NULL);
	return (stash);
}




char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	// char		*buf = NULL; /* No needed, actually */

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = complete_line(fd, stash);
	if (!stash)
		return (free(stash), stash = NULL, NULL);
	line = complete_line_2(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = clean_stash(stash);
	return (line);
}
