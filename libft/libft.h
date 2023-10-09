/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:13:05 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/30 10:11:56 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_bzero(void *s, unsigned int n);
void	*ft_calloc(size_t numcarac, size_t size);
int		ft_atoi(const char *str);
char	*ft_itoa(int nb);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, unsigned int n);
void	*ft_memset(void *b, int c, int len);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dest, char *src, unsigned int size);
int		ft_strlcpy(char *dest, char *src, unsigned int size);
size_t	ft_strlen(char *str);
char	*ft_strmapi(char const	*s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(char *str, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_memcpy(void *dest, const void *tocpy, int sizetocpy);
void	*ft_memmove(void *dst, const void *src, int len);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	*ft_itoa_base(unsigned long long n, char *base);
int		ft_decimal(int nb);
int		ft_decimal_unsig(unsigned int nb);
int		ft_hexa(unsigned int nb);
int		ft_hexamayus(unsigned int nb);
int		ft_char(int c);
int		ft_void(void *ptr_address);
int		ft_printpercent(void);
int		ft_types(va_list args, const char format);
int		ft_printf(const char *str, ...);
int		ft_putstr(char *str);
void	ft_putchar(char c);
char	*ft_strjoin_2(char *s1, char *s2);
char	*ft_strchr_2(const char *s, int c);
char	*get_line(char *buff);
char	*next_line(char *buff);
char	*ft_read_content(int fd, char *content);
char	*get_next_line(int fd);
char	*frees(char *buffer, char *buf);
void	byte_check(int byte, char *content);
#endif
