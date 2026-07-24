/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:35:56 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/24 16:36:03 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_dongles(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		pthread_mutex_init(&engine->dongles[i].mutex, NULL);
		pthread_cond_init(&engine->dongles[i].cond, NULL);
		engine->dongles[i].queue = heap_create(engine->config.num_coders);
		if (!engine->dongles[i].queue)
			return (0);
		engine->dongles[i].is_in_use = 0;
		engine->dongles[i].last_released_time = 0;
		i++;
	}
	return (1);
}

static void	init_coders(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		engine->coders[i].id = i + 1;
		engine->coders[i].last_compile_start = engine->start_time;
		engine->coders[i].compiles_done = 0;
		engine->coders[i].engine = engine;
		engine->coders[i].left_dongle = &engine->dongles[i];
		engine->coders[i].right_dongle = &engine->dongles[(i + 1)
			% engine->config.num_coders];
		i++;
	}
}

int	init_engine(t_engine *engine, t_config config)
{
	engine->config = config;
	engine->simulation_stop = 0;
	engine->start_time = get_time_ms();
	pthread_mutex_init(&engine->log_mutex, NULL);
	pthread_mutex_init(&engine->state_mutex, NULL);
	engine->coders = malloc(sizeof(t_coder) * config.num_coders);
	engine->dongles = malloc(sizeof(t_dongle) * config.num_coders);
	if (!engine->coders || !engine->dongles)
		return (0);
	if (!init_dongles(engine))
		return (0);
	init_coders(engine);
	return (1);
}

void	cleanup_engine(t_engine *engine)
{
	int	i;

	pthread_mutex_destroy(&engine->log_mutex);
	pthread_mutex_destroy(&engine->state_mutex);
	if (engine->dongles)
	{
		i = 0;
		while (i < engine->config.num_coders)
		{
			pthread_mutex_destroy(&engine->dongles[i].mutex);
			pthread_cond_destroy(&engine->dongles[i].cond);
			heap_destroy(engine->dongles[i].queue);
			i++;
		}
		free(engine->dongles);
	}
	if (engine->coders)
		free(engine->coders);
}
