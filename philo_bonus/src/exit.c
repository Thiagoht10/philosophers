/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:46:26 by thde-sou          #+#    #+#             */
/*   Updated: 2025/10/05 02:58:38 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void    wait_children(t_app app, t_data *data)
{
    pid_t   pid;
    
    data->all_satisfied = 0;
    while(1)
    {
        pid = waitpid(-1, &data->status, 0);
        if(pid == -1)
        {
            break;
        }
        if(WIFEXITED(data->status))
        {
            data->code = WEXITSTATUS(data->status);
            if(!check_exit(data, app))
            {
                break;
            }
        }
        else if(WIFSIGNALED(data->status))
        {
            kill_process(data, app);
            sem_post(data->print);
            break;
        }
    }
}

int check_exit(t_data *data, t_app app)
{
    if(data->code == 0)
    {
        data->all_satisfied++;
        if(data->all_satisfied == app.num_philo)
            return (FALSE);
    }
    else
    {
        kill_process(data, app);
        return (FALSE);
    }
    return (TRUE);
}

void kill_process(t_data *data, t_app app)
{
    int i;

    i = 0;
    while (i < app.num_philo)
    {
        if (data->pid[i] > 0)
        {
            kill(data->pid[i], SIGKILL);
            waitpid(data->pid[i], NULL, 0);
        }
        i++;
    }
}
