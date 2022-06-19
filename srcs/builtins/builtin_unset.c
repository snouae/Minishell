/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:38:49 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/17 04:05:27 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_unset(int argc , char **argv)
{
    int i;
    int j;
    int status;
    
    status = EXIT_SUCCESS;
    i = 1;
    while (--argc)
    {
        j = 0;
        while (argv[i][j] && check_var_is_char(argv[i][j]))
            j++;
        if (argv[i][j] != '\0' || argv[i][0] == '\0')
        {
            ft_error("minishell", "unset", " not a valid identifier"); 
            status = EXIT_FAILURE;
            break;
        }
        else
            unset_the_var(argv[i]);
        i++;
    }
    return (status);
}

