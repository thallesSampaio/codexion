/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:19:49 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:20:02 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	move_up(t_heap *heap, int index, t_sched sched)
{
	int	parent;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!request_has_priority(heap->data[index],
				heap->data[parent], sched))
			break ;
		swap_requests(&heap->data[index], &heap->data[parent]);
		index = parent;
	}
}

int	heap_push(t_heap *heap, t_request request, t_sched sched)
{
	int	index;

	if (!heap || heap->size >= heap->capacity)
		return (0);
	index = heap->size;
	heap->data[index] = request;
	heap->size++;
	move_up(heap, index, sched);
	return (1);
}
