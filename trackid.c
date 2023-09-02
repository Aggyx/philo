/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:53:09 by smagniny          #+#    #+#             */
/*   Updated: 2023/07/21 18:05:59 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	get_next_id(t_var *var, int *id)
{
	pthread_mutex_lock(&var->idwrap);
	*id = var->id;
	var->id++;
	pthread_mutex_unlock(&var->idwrap);
}
