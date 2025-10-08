/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:04:13 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/08 00:11:29 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int str_len(const char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

int ft_itoa_rec(long num, char *buffer, int i)
{
    if(num >= 10)
        i = ft_itoa_rec(num / 10, buffer, i);
    buffer[i++] = (num % 10) + '0';
    return (i);
}

void    ft_itoa(long num, char *buffer)
{
    int i;

    i = 0;
    if(num < 0)
    {
        buffer[0] = '-';
        num *= -1;
        i++;
    }
    i = ft_itoa_rec(num, buffer, i);
    buffer[i] = '\0';
}

void    strjoin(char *s1, char *s2, char *buffer)
{
    int len;
    int i;
    int j;

    len = str_len(s1) + str_len(s2) + 1;
    i = 0;
    while (s1[i])
    {
        buffer[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        buffer[j + i] = s2[j];
        j++;
    }
    buffer[len - 1] = '\0';
}
