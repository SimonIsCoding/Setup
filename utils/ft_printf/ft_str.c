/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:13:27 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/20 16:50:04 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_putstr(char *s)
{
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	if (write(1, s, ft_strlen(s)) == -1)
		return (-1);
	return (ft_strlen(s));
}

int	ft_putchar(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}
