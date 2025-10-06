/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:04:13 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/06 22:32:56 by thde-sou         ###   ########.fr       */
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

char    *ft_itoa(long num, char *buffer)
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

char    *strjoin(char *s1, char *s2)
{
    char    *result;
    int len;
    int i;
    int j;

    len = str_len(s1) + str_len(s2) + 1;
    result = malloc(sizeof(char) * len);
    if(!result)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        result[j + i] = s2[j];
        j++;
    }
    result[len - 1] = '\0';
    return (result);
}
