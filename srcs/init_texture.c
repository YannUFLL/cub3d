/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 19:18:52 by ydumaine          #+#    #+#             */
/*   Updated: 2022/07/18 19:22:46 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_texture(t_texture *tex)
{
	int	x;
	x = 0;
	while(x < 5)
	{
		tex[x].path = NULL;
		tex[x].mlx_img = NULL;
		tex[x].addr = NULL;
		tex[x].img_width = 0;
		tex[x].img_height = 0;
		tex[x].lenght = 0;
		tex[x].bit_per_pixel = 0;
		tex[x].endian = 0;
		x++;
	}
}

int	ft_init_text(t_data *data)
{
	int			x;
	t_texture	*text;

	x = 0;

	text = data->texture; 
	while (x < data->textures_nb)
	{
		ft_printf("path : %s \n", text[x].path);
		text[x].mlx_img = mlx_xpm_file_to_image(data->mlx,
			text[x].path, &text[x].img_width, &text[x].img_height);
		text[x].addr = (int *)mlx_get_data_addr(text[x].mlx_img,
			&text[x].bit_per_pixel, &text[x].lenght, &text[x].endian);
		x++; 
	}
	return (0);
}