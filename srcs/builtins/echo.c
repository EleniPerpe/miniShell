/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:56:41 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/31 20:29:41 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
int     check_for_ns(char **args, int count);
void    print_echo(char **args, int i);

int    ft_echo(char **args)
{
    int i;
    i = 1;
    if (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
    {
        while (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
            i++;
        i = check_for_ns(args, i);
        if (i > 1)
            print_echo(args, i);
    }
    else
    {
        print_echo(args, i);
        if (args[1] != NULL)
            printf("\n");
    }
	return (0);
}
void    print_echo(char **args, int i)
{
    while (args[i] != NULL)
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
}
int check_for_ns(char **args, int count)
{
    int i;
    int j;
    i = 1;
    while (i < count)
    {
        j = 1;
        while (args[i][j] != '\0')
        {
            if (args[i][j] != 'n')
                return (i);
            j++;
        }
        i++;
    }
    return (i);
}
