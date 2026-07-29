/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:33:37 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:33:40 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_heap	*heap_create(int capacity)
{
	t_heap	*heap;

	if (capacity <= 0)
		return (NULL);
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

void	heap_destroy(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->data);
	free(heap);
}

int	heap_peek(t_heap *heap, t_request *request)
{
	if (!heap || !request || heap->size == 0)
		return (0);
	*request = heap->data[0];
	return (1);
}
