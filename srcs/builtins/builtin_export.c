/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:54:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/24 21:09:03 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **sort_env(char **env);
static bool check_arg(char *argv);

static char *skip_symbol(char *argv)
{
    int i;
    int j;
    char    *str;

    //printf("%s\n",argv);
    str = malloc(ft_strlen(argv));
    i = 0;
    j = 0;
    while (argv[i] != '\0')
    {
        if (argv[i + 1] == '=' && cherche_symbol(argv[i],"+"))
        {
            i++;
            continue;
        }
       // printf("%c\n",argv[i]);
        str[j++] = argv[i];
        i++;
    }
   
    return (str);
}

static bool error_symbol(char *argv)
{
    int i;

    i = 0;
    while (argv[i] != '\0'  && argv[i] != '=')
    {
        if (cherche_symbol(argv[i],"!$%'()*+,-./:;<>?@[]^`{|}~"))
            return (false);
        i++;
    }
    return (true);
}

int builtin_export(int argc, char **argv)
{
    int status;
    int  i;
    char *new;
    int test = 0;

    status = EXIT_SUCCESS;
    if (argc == 1)
        exported_vars();
    if (argc > 1)
    {
        i = 1;
        while (argv[i])
        {
            new  =  skip_symbol(argv[i]);
            if (ft_strcmp(new, argv[i]))
                test = 1;             
            if (check_arg(new) == false || error_symbol(new) == false)
            {
                ft_error("minishell", argv[i], "not a valid identifier\n");
                status = EXIT_FAILURE;
            }
            else if (ft_strchr(new, '='))
                status = put_the_var(new, test);
            i++;
        }
    }
    return (status);
}

void exported_vars(void)
{
    char    **dup_env;
    int     i;
    
    dup_env = (char **)malloc((env_count(g_env) + 1) * sizeof(char *)); // +1 for NULL
    if (dup_env == NULL)
    {
        ft_error("minishell", NULL, strerror(ENOMEM)); // "Cannot allocate memory" message
        return ;
    }
    if (g_env == NULL)
        return ;
    ft_memcpy(dup_env, g_env, (env_count(g_env) + 1) * sizeof(char *));
    i = 0;
    dup_env = sort_env(dup_env);
    i = 0;
    while (dup_env[i])
    {
        g_env[i] = ft_strdup(dup_env[i]);
        i++;
    }
    i = 0;
    while (g_env[i])
	{
        ft_putendl_fd(g_env[i], 1);
		i++;
	}
    free(dup_env);
}

static char **sort_env(char **env)
{
    int     i;
    int     j;
    char    *tmp;
    int     count;
    
    count = env_count(env);
    i = 0;
    while(i < count - 1)
    {
        j = 0;
        while (j < (count - 1))
        {
            if (ft_strcmp(env[j], env[j + 1]) > 0)
            {
                tmp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
    return (env);
}

static bool check_arg(char *argv)
{
    int i;

    i = 0;
    if (argv[0] == '\0' || argv[0] == '=')
        return (false);
    while (argv[i] != '\0'  && argv[i] != '=')
        i++;
    if (argv[i] == '=' || argv[i] == '\0')
        return (true);
    else
        return (false);
    
}