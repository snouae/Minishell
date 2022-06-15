# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

enum tokens
{
    pipe_token = '|',
    redirect_out = '>',
    redirect_in = '<',
    dollar = '$',
    tab = '\t',
    single_quo = '\'',
    double_quo = '\"',
    white_space = ' ',
    char_null = 0,
    new_lin = '\n'
};
// typedef struct s_token
// {
//     int len;
//     //int type;
//     char *str;
// }   t_token;

enum s_fileType
{
    NONE,
    IN,
    OUT,
    HEREDOC,
    APPEND
}   t_filetype;

typedef struct s_list
{
    int len;
    int type;
    char *str;
    struct s_list* next;
} t_list;

typedef struct s_redirection
{
    char *file;
    int type;
    int fd;
    //int tartib;
    struct s_redirection* next;
} t_redirection;

typedef struct s_command
{
	char	**envp; //cmd
    int     num_of_args;
    struct s_redirection *redirect;
    //char    *executable;
}		t_command;

void ft_lexer(char *line, char **env);
t_list	*ft_add(char *line, int start, int end, int type);
int search_token(char token);
int	ft_strlen(char *s);
void ft_check(t_list** head, char *line);
void ft_parser(t_list** head, char *line, char **env);
char	**ft_split(char const *s, char c);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);
char    *find_commande(char *cmd, char **envp);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
char *expander(char *var, char **envp);
void    ft_lstadd_back(t_list **lst, t_list *new);
void serach_dollar(t_list** head, char **envp);
char *fill_array(char *line, int start, int end);
int search_token(char token);
void open_files(t_command *cmd, int leng);
int cherche_symbol(char c, char *str);

#endif