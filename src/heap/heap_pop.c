/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:21:17 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:21:20 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	priority_child(t_heap *heap, int index, t_sched sched)
{
	int	left;
	int	right;

	left = index * 2 + 1;
	right = index * 2 + 2;
	if (right < heap->size
		&& request_has_priority(heap->data[right],
			heap->data[left], sched))
		return (right);
	return (left);
}

static void	move_down(t_heap *heap, int index, t_sched sched)
{
	int	child;

	while (index * 2 + 1 < heap->size)
	{
		child = priority_child(heap, index, sched);
		if (!request_has_priority(heap->data[child],
				heap->data[index], sched))
			break ;
		swap_requests(&heap->data[index], &heap->data[child]);
		index = child;
	}
}

int	heap_pop(t_heap *heap, t_sched sched, t_request *request)
{
	if (!heap || !request || heap->size == 0)
		return (0);
	*request = heap->data[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->data[0] = heap->data[heap->size];
		move_down(heap, 0, sched);
	}
	return (1);
}

static int	find_request(t_heap *heap, int coder_id)
{
	int	index;

	index = 0;
	while (index < heap->size)
	{
		if (heap->data[index].coder_id == coder_id)
			return (index);
		index++;
	}
	return (-1);
}

int	heap_remove_coder(t_heap *heap, int coder_id, t_sched sched)
{
	int	index;

	if (!heap || heap->size == 0)
		return (0);
	index = find_request(heap, coder_id);
	if (index == -1)
		return (0);
	heap->size--;
	if (index < heap->size)
	{
		heap->data[index] = heap->data[heap->size];
		while (index > 0 && request_has_priority(heap->data[index],
				heap->data[(index - 1) / 2], sched))
		{
			swap_requests(&heap->data[index],
				&heap->data[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
		move_down(heap, index, sched);
	}
	return (1);
}
