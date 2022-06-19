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
#include <stdbool.h>
#include <errno.h>

# define MAX_BUF 200
# define ERROR	-1
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

struct s_builtins
{
	char	*name;
	int		(*func)(int argc, char **argv);
};

/*
my global variables
*/
char	                **g_env;
// pid_t				g_pid;
// int					g_error;
int						g_status;
int                     g_exit_value;
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
    struct s_redirection* next;
} t_redirection;

typedef struct s_command
{
	char	**cmd; //cmd
    int     num_cmds;
    int     num_of_args;
    int     pipe_fd[2];
    int     fork;
    int     is_builtin_in;
    struct s_redirection *redirect;
}		t_command;

t_list *ft_lexer(char *line , char **env);
t_list	*ft_add(char *line, int start, int end, int type);
int search_token(char token);
int	ft_strlen(char *s);
int ft_check(t_list** head, char *line);
t_command *ft_parser(t_list** head, char *line , char **env);
char	**ft_split(char const *s, char c);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup_n(char *src);
//char    *find_commande(char *cmd, char **envp);
char	*ft_strjoin_n(char *s1, char *s2);
char *expander(char *var, char **envp);
void    ft_lstadd_back(t_list **lst, t_list *new);
void serach_dollar(t_list** head, char **envp);
char *fill_array(char *line, int start, int end);
int search_token(char token);
void open_files(t_command *cmd, int leng);
int cherche_symbol(char c, char *str);
void deleteList(t_list** head_ref);
void free_all(t_command *cmd);
/////////////////
// ===== builtin functions ====== //
int    builtin_root(char **argv);
int     builtin_cd(int argc, char **argv);
int     builtin_echo(int argc __attribute((unused)), char **argv);
int     builtin_env(int argc __attribute((unused)),
    char **argv __attribute((unused)));
int     builtin_exit(int argc, char **argv);
int     builtin_export(int argc, char **argv);
void    exported_vars(void);
int     builtin_check(char  *str);
int     builtin_pwd(int argc __attribute((unused)), 
    char **argv __attribute((unused)));
int     builtin_unset(int argc __attribute((unused)), char **argv);


//======================================
// ==== ENV ===== //
int     env_init(char **env);
bool    check_var_is_char(char c);
char    *search_env(char *name);
char    *get_value(char *name);
bool    check_var_is_char(char c);

// ==== ENV MODIFY ====//
int unset_the_var(char  *name);
int put_the_var(char *str);
int set_the_env(char *name, char *value);

//=======================================
//======= Execute utils ===== //
char    *get_path(char **envp,  t_command *data, int index);
void    ft_command_not_found(char **paths, char *cmd);
int     open_file(t_redirection *redirect);

//====== execute function =====//
void execute_root(t_command *data, char **envp);
char    **execute_command(t_command *data, char **envp, int index);
char    **exec_1(t_command *data, int index, char **envp);
int     ft_pipe_built(t_command *data, int pid, int index);

//========================================
// ===== builtin_utils ==== //
int     replace_str_env(char ***env, char *old_str, char *new_str);
int     env_count(char **env);
int     add_to_env(char ***env, char *str);
int     remove_from_env(char ***env, char *str);
void	ft_free_env(char ***env);


//=========================================
// ======== libft ============ //
void	freememory(char **mem);
int	wordlen(char const *s, char c);
int	ft_wordcount(char const *s, char c);

int	    ft_isalnum(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char*s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char *s, unsigned int start, size_t len);

//====== Error === //
int ft_error(char *shell_name, char *s1, char *message);

#endif