/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:21:32 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:21:35 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long long	get_coder_deadline(t_coder *coder)
{
	long long	deadline;

	pthread_mutex_lock(&coder->state_mutex);
	deadline = coder->last_compile_start
		+ coder->engine->config.time_to_burnout;
	pthread_mutex_unlock(&coder->state_mutex);
	return (deadline);
}

static t_coder	*find_burned_out_coder(t_engine *engine)
{
	int			i;
	long long	now;

	i = 0;
	now = get_time_ms();
	while (i < engine->config.num_coders)
	{
		if (now >= get_coder_deadline(&engine->coders[i]))
			return (&engine->coders[i]);
		i++;
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_engine	*engine;
	t_coder		*burned_out;

	engine = (t_engine *)arg;
	while (!simulation_should_stop(engine))
	{
		burned_out = find_burned_out_coder(engine);
		if (burned_out)
		{
			if (stop_simulation(engine))
				log_burnout(burned_out);
			wake_all_coders(engine);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
