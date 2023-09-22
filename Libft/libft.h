/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:38:49 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/09 12:32:19 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strclen(const char *s, char c);
size_t	ft_strchrlen(const char *str, char *set);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_s1(char *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_intlen(long long n, int base);
void	ft_puthex_fd(unsigned int num, const char c, int fd);
char	*ft_itoapositive(long long n);
void	ft_free_array(char **array);
void	ft_free_array_size(void **array, int size);

// printf functions

# ifndef BUFFER_SIZE
#  define HEXBASE "0123456789abcdef"
# endif

int		ft_printf(const char *format, ...);
int		print_chr(char c, int *flags);
int		print_str(char *s, int *flags);
int		print_nbr(int n, int *flags);
int		print_hex(unsigned int nbr, int *flags, const char c);
int		print_unsigned(unsigned int n, int *flags);
int		print_pointer(unsigned long long addr, int *flags);

// get_next_line functions

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef MAX_FILES
#  define MAX_FILES 500
# endif

char	*get_next_line(int fd);

// Colors

# ifndef RESET
#  define RESET "\033[0m"
# endif
# ifndef BLACK
#  define BLACK "\033[0;30m"
# endif
# ifndef RED
#  define RED "\033[0;31m"
# endif
# ifndef GREEN
#  define GREEN "\033[0;32m"
# endif
# ifndef YELLOW
#  define YELLOW "\033[0;33m"
# endif
# ifndef BLUE
#  define BLUE "\033[0;34m"
# endif
# ifndef MAGENTA
#  define MAGENTA "\033[0;35m"
# endif
# ifndef CYAN
#  define CYAN "\033[0;36m"
# endif
# ifndef WHITE
#  define WHITE "\033[0;37m"
# endif
# ifndef BOLDBLACK
#  define BOLDBLACK "\033[1;30m"
# endif
# ifndef BOLDRED
#  define BOLDRED "\033[1;31m"
# endif
# ifndef BOLDGREEN
#  define BOLDGREEN "\033[1;32m"
# endif
# ifndef BOLDYELLOW
#  define BOLDYELLOW "\033[1;33m"
# endif
# ifndef BOLDBLUE
#  define BOLDBLUE "\033[1;34m"
# endif
# ifndef BOLDMAGENTA
#  define BOLDMAGENTA "\033[1;35m"
# endif
# ifndef BOLDCYAN
#  define BOLDCYAN "\033[1;36m"
# endif
# ifndef BOLDWHITE
#  define BOLDWHITE "\033[1;37m"
# endif

#endif
