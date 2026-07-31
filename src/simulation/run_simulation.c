/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:22:05 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 17:22:54 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	join_coder_threads(t_engine *engine, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(engine->coders[i].thread, NULL);
		i++;
	}
}

static int	create_coder_threads(t_engine *engine, int *created)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		if (pthread_create(&engine->coders[i].thread, NULL,
				coder_routine, &engine->coders[i]) != 0)
			return (*created = i, 0);
		i++;
	}
	*created = i;
	return (1);
}

static int	create_monitor(t_engine *engine)
{
	if (pthread_create(&engine->monitor_thread, NULL,
			monitor_routine, engine) != 0)
		return (0);
	return (1);
}

int	run_simulation(t_engine *engine)
{
	int	created;

	reset_simulation_time(engine);
	created = 0;
	if (!create_coder_threads(engine, &created))
	{
		stop_simulation(engine);
		join_coder_threads(engine, created);
		return (0);
	}
	if (!create_monitor(engine))
	{
		stop_simulation(engine);
		join_coder_threads(engine, created);
		return (0);
	}
	pthread_join(engine->monitor_thread, NULL);
	join_coder_threads(engine, created);
	return (1);
}
