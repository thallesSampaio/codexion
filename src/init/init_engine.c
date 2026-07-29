/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:14:42 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:14:46 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_engine_mutexes(t_engine *engine)
{
	if (pthread_mutex_init(&engine->log_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&engine->state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&engine->log_mutex);
		return (0);
	}
	return (1);
}

static int	allocate_engine_data(t_engine *engine)
{
	int	count;

	count = engine->config.num_coders;
	engine->coders = malloc(sizeof(t_coder) * count);
	engine->dongles = malloc(sizeof(t_dongle) * count);
	if (!engine->coders || !engine->dongles)
	{
		free(engine->coders);
		free(engine->dongles);
		engine->coders = NULL;
		engine->dongles = NULL;
		return (0);
	}
	memset(engine->coders, 0, sizeof(t_coder) * count);
	memset(engine->dongles, 0, sizeof(t_dongle) * count);
	return (1);
}

static void	clean_engine_init(t_engine *engine)
{
	free(engine->coders);
	free(engine->dongles);
	engine->coders = NULL;
	engine->dongles = NULL;
	pthread_mutex_destroy(&engine->state_mutex);
	pthread_mutex_destroy(&engine->log_mutex);
}

int	init_engine(t_engine *engine, t_config config)
{
	memset(engine, 0, sizeof(t_engine));
	engine->config = config;
	engine->start_time = get_time_ms();
	if (!init_engine_mutexes(engine))
		return (0);
	if (!allocate_engine_data(engine))
	{
		pthread_mutex_destroy(&engine->state_mutex);
		pthread_mutex_destroy(&engine->log_mutex);
		return (0);
	}
	if (!init_dongles(engine))
		return (clean_engine_init(engine), 0);
	init_coders(engine);
	return (1);
}
