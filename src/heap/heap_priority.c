/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_priority.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:19:31 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:19:34 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	request_has_priority(t_request a, t_request b, t_sched sched)
{
	if (sched == CX_SCHED_FIFO)
	{
		if (a.arrival_time != b.arrival_time)
			return (a.arrival_time < b.arrival_time);
		return (a.coder_id < b.coder_id);
	}
	if (a.deadline != b.deadline)
		return (a.deadline < b.deadline);
	if (a.arrival_time != b.arrival_time)
		return (a.arrival_time < b.arrival_time);
	return (a.coder_id < b.coder_id);
}

void	swap_requests(t_request *a, t_request *b)
{
	t_request	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
