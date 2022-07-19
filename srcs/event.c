/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:33:42 by ydumaine          #+#    #+#             */
/*   Updated: 2022/07/18 18:29:13 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_use(t_data *data, t_ray *ray)
{
	if (data->key.use == 1 && ray->walldistance < 1 && ray->text_select == 4)
		ray->map[ray->map_y][ray->map_x] = '/'; 
}

void	ft_event(t_ray *ray)
{
	if (ray->map[(int)ray->pos_y][(int)ray->pos_x] == '/' && ray->door_open == 0)
	{
		ray->pos_door_y = (int)ray->pos_y;
		ray->pos_door_x = (int)ray->pos_x;
		ray->door_open = 1;
	}
	if (ray->map[(int)ray->pos_y][(int)ray->pos_x] != '/' && ray->door_open == 1)
	{
		ray->door_open = 0;
		ray->map[(int)ray->pos_door_y][(int)ray->pos_door_x] = '2';
	}
}