/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:24:50 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:24:56 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	reset_simulation_time(t_engine *engine)
{
	int	i;

	engine->start_time = get_time_ms();
	i = 0;
	while (i < engine->config.num_coders)
	{
		pthread_mutex_lock(&engine->coders[i].state_mutex);
		engine->coders[i].last_compile_start = engine->start_time;
		pthread_mutex_unlock(&engine->coders[i].state_mutex);
		i++;
	}
}
