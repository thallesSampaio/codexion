/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:20:13 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:20:19 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_state(t_coder *coder, const char *message)
{
	t_engine	*engine;
	long long	timestamp;

	engine = coder->engine;
	if (simulation_should_stop(engine))
		return ;
	pthread_mutex_lock(&engine->log_mutex);
	if (!simulation_should_stop(engine))
	{
		timestamp = get_time_ms() - engine->start_time;
		printf("%lld %d %s\n", timestamp, coder->id, message);
	}
	pthread_mutex_unlock(&engine->log_mutex);
}

void	log_burnout(t_coder *coder)
{
	t_engine	*engine;
	long long	timestamp;

	engine = coder->engine;
	pthread_mutex_lock(&engine->log_mutex);
	timestamp = get_time_ms() - engine->start_time;
	printf("%lld %d burned out\n", timestamp, coder->id);
	pthread_mutex_unlock(&engine->log_mutex);
}
