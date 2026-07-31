/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:34:00 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:34:04 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coder_start_compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->state_mutex);
	coder->last_compile_start = get_time_ms();
	coder->compiles_done++;
	pthread_mutex_unlock(&coder->state_mutex);
}

long long	coder_get_deadline(t_coder *coder)
{
	long long	deadline;

	pthread_mutex_lock(&coder->state_mutex);
	deadline = coder->last_compile_start
		+ coder->engine->config.time_to_burnout;
	pthread_mutex_unlock(&coder->state_mutex);
	return (deadline);
}

int	coder_get_compiles(t_coder *coder)
{
	int	compiles;

	pthread_mutex_lock(&coder->state_mutex);
	compiles = coder->compiles_done;
	pthread_mutex_unlock(&coder->state_mutex);
	return (compiles);
}
