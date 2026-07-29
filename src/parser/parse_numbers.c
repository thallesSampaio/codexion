/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:55:56 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 15:56:02 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_positive_ll(const char *str, long long *value)
{
	long long	result;
	int			digit;
	int			i;

	if (!str || !str[0])
		return (0);
	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit = str[i] - '0';
		if (result > (LLONG_MAX - digit) / 10)
			return (0);
		result = result * 10 + digit;
		i++;
	}
	*value = result;
	return (1);
}

int	parse_positive_int(const char *str, int *value)
{
	long long	number;

	if (!parse_positive_ll(str, &number))
		return (0);
	if (number > INT_MAX)
		return (0);
	*value = (int)number;
	return (1);
}
