/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:35:40 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/24 16:35:42 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	log_state(t_coder *coder, const char *state)
{
	t_engine	*engine;
	long long	timestamp;
	int			stop;

	engine = coder->engine;
	pthread_mutex_lock(&engine->log_mutex);
	pthread_mutex_lock(&engine->state_mutex);
	stop = engine->simulation_stop;
	pthread_mutex_unlock(&engine->state_mutex);
	if (!stop)
	{
		timestamp = get_time_ms() - engine->start_time;
		printf("%lld %d %s\n", timestamp, coder->id, state);
	}
	pthread_mutex_unlock(&engine->log_mutex);
}
