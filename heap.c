/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:35:03 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/24 16:37:56 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

#include "codexion.h"

t_heap	*heap_create(int capacity)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->data = malloc(sizeof(t_request) * capacity);
	if (!heap->data)
	{
		free(heap);
		return (NULL);
	}
	heap->capacity = capacity;
	heap->size = 0;
	return (heap);
}

int	is_higher_priority(t_request a, t_request b, t_sched sched)
{
	if (sched == CX_SCHED_FIFO)
	{
		if (a.arrival_time != b.arrival_time)
			return (a.arrival_time < b.arrival_time);
		return (a.coder_id < b.coder_id);
	}
	else
	{
		if (a.deadline != b.deadline)
			return (a.deadline < b.deadline);
		return (a.coder_id < b.coder_id);
	}
}

void	swap_req(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heap_push(t_heap *heap, t_request req, t_sched sched)
{
	int	i;
	int	parent;

	if (heap->size >= heap->capacity)
		return ;
	i = heap->size;
	heap->data[i] = req;
	heap->size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (is_higher_priority(heap->data[i], heap->data[parent], sched))
		{
			swap_req(&heap->data[i], &heap->data[parent]);
			i = parent;
		}
		else
			break ;
	}
}

void	heap_destroy(t_heap *heap)
{
	if (!heap)
		return ;
	if (heap->data)
		free(heap->data);
	free(heap);
}
