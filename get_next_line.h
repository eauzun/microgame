#ifndef GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
#  endif
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
char *get_all_line(int fd, char *all_line);
char *till_nl(char *all_line);
char *return_rest(char *all_line);
char *get_next_line(int fd);
char *ft_strjoin(char *s1, char *s2);
size_t  ft_strnl(char *s);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
#endif