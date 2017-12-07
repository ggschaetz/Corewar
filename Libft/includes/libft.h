/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 20:33:07 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/01 14:47:44 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 128

# include "macro.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef	struct		s_gnl
{
	int				fd;
	char			*buff;
}					t_gnl;

/*
 **	String Functions
*/

void				concat_bit(unsigned char c, char *str);
void				del_space(char **str);
void				str_search_and_replace(char *str, char *pattern,
					char *replace);
size_t				ft_strlen_c(char *str, char c);
char				*ft_strdup_c(char *str, char c);
char				*ft_strndup(const char *str, size_t n);
char				*ft_strjoin_free(char const *s1, char const *s2);
char				*ft_strdup(const char *str);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
size_t				ft_strlen(const char *str);
char				*ft_strnstr(const char *big, const char *little
						, size_t len);
char				**ft_strsplit(char const *s, char c);
size_t				ft_sstrlen(char **sstr);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strrev(char *s);
char				*ft_str_resize(char *str, int start, int end);
char				*ft_str_resize_nf(char *str, int start, int end);
int					ft_next_char(char const *s, char c, int index, int w_c);
int					ft_word_count(char const *s, char c);
int					ft_char_count(char const *s, char c, int index);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_cp_new_elem(char const *s, int len, int index1);
int					ft_char_count(char const *s, char c, int index);
int					ft_next_char(char const *s, char c, int index, int w_c);
int					ft_word_count(char const *s, char c);
char				*ft_strpbrk(const char *str, const char *c);
char				**ft_sstradd(char **dest, char **src, char *to_add);
char				*ft_strmaj(char *str);
char				*cut_str(char *str, int cut);

/*
 **	Memory Functions
*/

void				*secure_malloc(size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
 **	GNL Functions
*/

int					get_next_line(const int fd, char **line);
ssize_t				gnl_readoneline(t_gnl *file);
t_gnl				*gnl_findorcreate_file(const int fd, t_list **my_list);

/*
 **	Character_is_? Functions
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isblank(int c);
int					ft_isxdigit(int c);

/*
 **	Modification Caracter Functions
*/

int					ft_toupper(int c);
int					ft_tolower(int c);
char				ft_converttochar(int c);

/*
 **	Numbers Functions
*/

int					ft_atoi(const char *str);
long				ft_atoi_base(char *str, int base);
int					ft_num_count(unsigned long int n);
int					ft_pow10(int pw);
int					ft_pow10(int pw);
double				ft_pow(double n, double p);
float				ft_powf(float n, float p);
char				*ft_itoa(int n);
char				*ft_itoabase(unsigned int c, size_t base);
char				*ft_itoabase_uint(uintmax_t c, size_t base);
char				*ft_itoa_base(intmax_t value, int base);
/*
 **	Printing Functions
*/

void				ft_putlong(long nb);
void				ft_putchar(unsigned char c);
void				ft_putstr(char *str);
void				ft_putendl(char const *s);
void				ft_putnbr(long int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
 **	List Functions
*/

void				ft_lstdelone(t_list **alst, void (*del)(void
						*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *,
						size_t));
void				ft_lstadd(t_list **alst, t_list *create);
void				ft_lstiter(t_list *lst, void (*f)(t_list
						*elem));
t_list				*ft_lstmap(t_list *lst, t_list *
						(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t
						content_size);

#endif
