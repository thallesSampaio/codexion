/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:37:21 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/24 16:37:24 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	get_smallest_child(t_heap *heap, int i, t_sched sched)
{
	int	left;
	int	right;
	int	smallest;

	left = 2 * i + 1;
	right = 2 * i + 2;
	smallest = left;
	if (right < heap->size && is_higher_priority(heap->data[right],
			heap->data[left], sched))
		smallest = right;
	return (smallest);
}

t_request	heap_pop(t_heap *heap, t_sched sched)
{
	t_request	top;
	int			i;
	int			smallest;

	top = heap->data[0];
	heap->size--;
	heap->data[0] = heap->data[heap->size];
	i = 0;
	while (2 * i + 1 < heap->size)
	{
		smallest = get_smallest_child(heap, i, sched);
		if (is_higher_priority(heap->data[smallest], heap->data[i], sched))
		{
			swap_req(&heap->data[i], &heap->data[smallest]);
			i = smallest;
		}
		else
			break ;
	}
	return (top);
}
