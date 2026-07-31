/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_acquire.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:43:38 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:43:41 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	claim_dongles(t_coder *coder)
{
	t_request	request;
	t_sched		scheduler;

	scheduler = coder->engine->config.scheduler;
	heap_pop(coder->left_dongle->queue, scheduler, &request);
	heap_pop(coder->right_dongle->queue, scheduler, &request);
	coder->left_dongle->is_in_use = 1;
	coder->right_dongle->is_in_use = 1;
}

static int	try_take_dongles(t_coder *coder)
{
	int	success;

	success = 0;
	lock_coder_dongles(coder);
	if (coder_can_take_dongles(coder))
	{
		claim_dongles(coder);
		success = 1;
	}
	unlock_coder_dongles(coder);
	return (success);
}

int	acquire_coder_dongles(t_coder *coder)
{
	if (!request_coder_dongles(coder))
		return (0);
	while (!simulation_should_stop(coder->engine))
	{
		if (try_take_dongles(coder))
		{
			log_state(coder, "has taken a dongle");
			log_state(coder, "has taken a dongle");
			return (1);
		}
		usleep(200);
	}
	return (0);
}
