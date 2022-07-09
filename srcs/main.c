/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:38:35 by ydumaine          #+#    #+#             */
/*   Updated: 2022/07/08 19:52:16 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int	ft_test_color(int color, t_data *data)
{
	int x; 
	int y; 

	y = 0; 
	while (y < 800)
	{
		x = 0;
		y++; 
		while (x < 800)
		{
			x++;
			mlx_pixel_put(data->mlx, data->mlx_win, x, y, color);
		}
	}	
	return (0);
}
*/

int	ft_init_data(t_data *data)
{
	data->mlx_win = NULL;
	data->mlx = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor = -1;
	data->ceiling = -1;
	data->player_spawn_dir = 0;
	data->player_spawn_pos[0] = 0; 
	data->player_spawn_pos[1] = 0; 
	data->edge_size = 16;
	data->fov = 80; 
	data->resolution_x = 1920;
	data->resolution_y = 1080;
	return (0);
}

int	ft_init_display(t_data *data) 
{
	data->display = mlx_new_image(data->mlx, data->resolution_x, data->resolution_y);
	data->display_add = mlx_get_data_addr(data->display, 
		&data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}

int ft_free(t_data *data)
{
	if (data->no != NULL)
		free(data->no);
	if (data->so != NULL)
		free(data->so);
	if (data->we != NULL)
		free(data->we);
	if (data->ea != NULL)
		free(data->ea);
	return (0);

}
int	main(int argc, char **argv)
	{
	(void)argc; 
	(void)argv;
	t_data data; 

	if (argc > 2)
	{
		printf("Error\nToo Much arguments");
		return (0);
	}
	if (argc < 2)
	{
		printf("Error\nNeed 2 arguments");
		return (0);
	}
	ft_init_data(&data);
	data.mlx = mlx_init(); 
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "LE MEILLEUR JEU AU MONDE ");
	ft_init_display(&data);
	if (ft_parsing(&data, argv[1]) == 1)
		return (ft_free(&data));
	mlx_loop_hook(data.mlx_win, ft_render_next_frame, &data);
	mlx_loop(data.mlx);
	}