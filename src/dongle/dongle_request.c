/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_request.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:42:43 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:42:46 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_request	create_request(t_coder *coder)
{
	t_request	request;

	request.coder_id = coder->id;
	request.arrival_time = get_time_ms();
	request.deadline = coder_get_deadline(coder);
	return (request);
}

static int	queues_have_space(t_coder *coder)
{
	if (coder->left_dongle->queue->size
		>= coder->left_dongle->queue->capacity)
		return (0);
	if (coder->right_dongle->queue->size
		>= coder->right_dongle->queue->capacity)
		return (0);
	return (1);
}

int	request_coder_dongles(t_coder *coder)
{
	t_request	request;
	t_sched		scheduler;

	request = create_request(coder);
	scheduler = coder->engine->config.scheduler;
	lock_coder_dongles(coder);
	if (!queues_have_space(coder))
	{
		unlock_coder_dongles(coder);
		return (0);
	}
	heap_push(coder->left_dongle->queue, request, scheduler);
	heap_push(coder->right_dongle->queue, request, scheduler);
	unlock_coder_dongles(coder);
	return (1);
}
