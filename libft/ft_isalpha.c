/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:12:05 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/25 16:45:14 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalpha(int c)
{
	return ((((char)c >= 65 && (char)c <= 90)
				|| ((char)c >= 97 && (char)c <= 122))
			&& ((c < 256) && (c > 0)) ? (1) : (0));
}
