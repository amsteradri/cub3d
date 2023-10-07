/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:51:20 by adgutier          #+#    #+#             */
/*   Updated: 2023/03/16 12:12:34 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(char *buff)
{
	int		i;
	char	*mem;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
	i++;
	mem = ft_calloc(i + 2, sizeof(char));
	if (!mem)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		mem[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		mem[i] = buff[i];
		i++;
	}
	return (mem);
}

char	*next_line(char *buff)
{
	int		i;
	int		j;
	char	*memo;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	memo = ft_calloc((ft_strlen(buff) - i + 1), sizeof(char));
	if (!memo)
		return (NULL);
	i++;
	j = 0;
	while (buff[i])
		memo[j++] = buff[i++];
	free(buff);
	return (memo);
}

char	*frees(char *buffer, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin_2(buffer, buf);
	return (tmp);
}

char	*ft_read_content(int fd, char *content)
{
	int		byte;
	char	*buff;

	if (!content)
		content = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	byte = read(fd, buff, BUFFER_SIZE);
	while (byte > 0)
	{
		buff[byte] = 0;
		content = frees(content, buff);
		if (ft_strchr_2(buff, '\n'))
			break ;
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
	}
	free(buff);
	byte_check (byte, content);
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*cont;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = ft_read_content(fd, buff);
	if (!buff)
		return (NULL);
	cont = get_line(buff);
	buff = next_line(buff);
	return (cont);
}

/*
int		main(void)
{
	int		fd;

	fd = open("prueba", O_RDONLY);
	
	printf("%s", get_next_line(fd));
}*/