/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_coder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:44:34 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:44:42 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	run_single_coder(t_coder *coder)
{
	t_dongle	*dongle;

	dongle = coder->left_dongle;
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_in_use = 1;
	pthread_mutex_unlock(&dongle->mutex);
	log_state(coder, "has taken a dongle");
	while (!simulation_should_stop(coder->engine))
		usleep(200);
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_in_use = 0;
	dongle->last_released_time = get_time_ms();
	pthread_mutex_unlock(&dongle->mutex);
}
