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

static t_coder	*find_burned_out(t_engine *engine)
{
	int			i;
	long long	now;

	i = 0;
	now = get_time_ms();
	while (i < engine->config.num_coders)
	{
		if (now >= coder_get_deadline(&engine->coders[i]))
			return (&engine->coders[i]);
		i++;
	}
	return (NULL);
}

static int	all_coders_completed(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		if (coder_get_compiles(&engine->coders[i])
			< engine->config.num_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

static int	check_simulation_end(t_engine *engine)
{
	t_coder	*burned_out;

	burned_out = find_burned_out(engine);
	if (burned_out)
	{
		if (stop_simulation(engine))
			log_burnout(burned_out);
		return (1);
	}
	if (all_coders_completed(engine))
	{
		stop_simulation(engine);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_engine	*engine;

	engine = (t_engine *)arg;
	while (!simulation_should_stop(engine))
	{
		if (check_simulation_end(engine))
		{
			wake_all_coders(engine);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
