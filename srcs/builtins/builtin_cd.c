/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:25:11 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/16 16:28:01 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char     *get_the_print_working_dir(int argc, char **argv);
static int      update_pwd(void);

int builtin_cd(int argc, char **argv)
{
    char    *dir;

    dir = get_the_print_working_dir(argc, argv);
    if (dir == NULL)
        return (EXIT_FAILURE);
    if (chdir(dir) == -1)
    {
        ft_error("minishell", "cd", dir);
        return (ERROR);
    }
    if (argv[1] && ft_strncmp(argv[1], "-", 2))
        ft_putendl_fd(dir, STDOUT_FILENO);
    if (update_pwd() == ERROR)
        return (EXIT_FAILURE);
    return (0);
}

static char    *get_the_print_working_dir(int argc, char **argv)
{
    char    *dir;

    if (argc == 1)
    {
        dir = get_value("HOME");
        if (dir == NULL)
            ft_error("minishell", "cd", " HOME not set");
    }
    else if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0) // "cd -"
    {
        dir = get_value("OLDPWD");
        if (dir == NULL)
            ft_error("minishell", "cd", "OLDPWD not set");
    }
    else
        dir = get_value(argv[1]);
    return (dir);
}

static int update_pwd(void)
{
    char    path[MAX_BUF];
    if (get_value("PWD")) // check if PWD exists for real in g_env ---- to handle weird cases
    { // like "cd dlfkdsf" so if yes then i need to compare between OLDPWD and PWD 
        // if nothing changed that means bli rah trat chi haja b7al dik command liwrit  
        if (set_the_env("OLDPWD", get_value("PWD")) == ERROR)
            return (ERROR);
    }
    else // if no then i need to remove OLDPWD content and replace it 
        unset_the_var("OLDPWD"); // with the previous one before using cd
    if (getcwd(path, MAX_BUF) == NULL)
    {
        ft_error("minishell", "cd", strerror(ENOMEM));
        return (ERROR);
    }
    if (set_the_env("PWD", path) == ERROR)
        return (ERROR);
    return (0);
}
