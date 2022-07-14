/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:31:47 by ydumaine          #+#    #+#             */
/*   Updated: 2022/07/14 22:56:36 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <sys/time.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst; 

	dst = data->display_add + (y * data->line_length + x * (data->bits_per_pixel / 8)); 
	*(unsigned int*)dst = color; 
}
int	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec)
		* 1000 + ((end->tv_usec - start->tv_usec) / 1000));
}

void	ft_printf_ray(t_ray *ray)
{
	printf("\n\n");
	printf("camera x : %f \n", ray->camera_x);
	printf("plane x : %f \n", ray->plane_x);
	printf("plane y : %f \n", ray->plane_y);
	printf("dir x  : %f \n ", ray->dir_x);
	printf("dir y : %f \n", ray->dir_y);
	printf("raydir x : %f \n", ray->raydir_x);
	printf("raydir y : %f \n", ray->raydir_y);
	printf("pos x : %f \n", ray->pos_x);
	printf("pos y : %f \n", ray->pos_y);
	printf("map x : %d \n", ray->map_x);
	printf("map y : %d \n", ray->map_y);
	printf("ray_side_x : %f \n", ray->ray_side_x);
	printf("ray_side_y : %f \n", ray->ray_side_y);
	printf("ray_delta_x : %f \n", ray->ray_delta_x);
	printf("ray_delta_y : %f \n", ray->ray_delta_y);
	printf("step x : %d \n", ray->step_x);
	printf("step y : %d \n", ray->step_y);
	printf("ray_wall_distance : %f \n", ray->walldistance);
}



void	ft_print_grind(t_data *data, t_ray *ray)
{
	int	x;
	int	y; 
	int	old_x;
	int	old_y; 

	x = 0;
	y = 0; 

	while (ray->map[y])
	{
		x = 0;
		while(ray->map[y][x])
		{
			if (ray->map[y][x] == '1')
			{
				old_y = y * 30; 
				while(old_y <= ((y * 30) + 30))
				{
					old_x = x * 30;
					while(old_x <= ((x * 30) + 30))
					{
							my_mlx_pixel_put(data, old_x, old_y, 16711680);
						old_x++;
					}
					old_y++;
				}
			}
			if (ray->map[y][x] == '0' || ray->map[y][x] == 'N' || ray->map[y][x] == 'S' || ray->map[y][x] == 'W'|| ray->map[y][x] == 'E')
			{
				old_y = y * 30; 
				while(old_y <= ((y * 30) + 30))
				{
					old_x = x * 30;
					while(((old_y == (y * 30)) || (old_y == (y * 30 + 30))) && (old_x <= ((x * 30) + 30)))
					{
						my_mlx_pixel_put(data, old_x, old_y, 16777215);
						old_x++;
					}
					while(((old_y != (y * 30)) || (old_y != (y * 30 + 30))) && (old_x <= ((x * 30) + 30)))
					{
						my_mlx_pixel_put(data, old_x, old_y, 16777215);
						old_x++;
					}
					my_mlx_pixel_put(data, old_x, old_y, 16777215);
					my_mlx_pixel_put(data, old_x + 30, old_y, 16777215);
					old_y++;
				}
			}
			x++;
		}
	y++; 
	}
}

void	ft_print_pos(t_data *data, t_ray *ray)
{
	int x; 
	int y; 

	x = (ray->pos_x * 30) - 5;
	y = (ray->pos_y * 30) - 5;

	while (y <= (ray->pos_y * 30) + 5)
	{
		x = (ray->pos_x * 30) - 5;
		while (x <= ((ray->pos_x * 30) + 5))
		{
				my_mlx_pixel_put(data, x, y, 65280);
			x++; 
		}
		y++;
	}
}

void	ft_print_ray(t_data *data, t_ray *ray, double v_x, double v_y, double norme)
{
	double y1;
	double y2;
	double x1;
	double x2; 
	double a; 
	double b; 
	double x; 
	double y; 
	int	sens;
	

	sens = 0;
	x1 = (ray->pos_x * 30);
	y1 = (ray->pos_y * 30);	
	x2 = x1 + (v_x * 30);
	y2 = y1 + (v_y * 30);
	if (x2 < x1)
		sens = -1;
	if ((x1 - x2) != 0)
		a = (y1 - y2) / (x1 - x2);
	else 
		a = (y1 - y2) / (1000000);
	b = y2 - a * x2; 
	x = x1;
	while ((sens == 0 && x <= (x1 + norme * 30)) || (sens == -1 && x >= (x1 + -norme * 30)))
{
		y = (a*x + b); 
		if ((x < 1920 && y < 980) && ( x > 0 && y > 0))
		my_mlx_pixel_put(data, (int)x, (int)y, 0xFF0CCB);
		if (sens == 0)
		x++;
		else 
		x--;
	}
}


void	ft_print_raydata(t_data *data, t_ray *ray)
{
	ft_print_grind(data, ray);
	ft_print_pos(data, ray);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->display, 0, 0);
}
// calcul of ray vector 

void ft_calc_rayside(t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;  //composante de la direction du rayon (si -1 negative)
		ray->ray_side_x = (ray->pos_x - ray->map_x) * ray->ray_delta_x; 
	}
	else
	{
		ray->step_x = 1;
		ray->ray_side_x = (ray->map_x + 1 - ray->pos_x) * ray->ray_delta_x; 
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->ray_side_y = (ray->pos_y - ray->map_y) * ray->ray_delta_y; 
	}
	else
	{
		ray->step_y = 1;
		ray->ray_side_y = (ray->map_y + 1 - ray->pos_y) * ray->ray_delta_y; 
	}
}

void ft_launch_ray(t_ray *ray)
{
	while (ray->hit == 0) 
	{
		if (ray->ray_side_x < ray->ray_side_y)
		{
			ray->ray_side_x += ray->ray_delta_x; 
			ray->map_x += ray->step_x; 
			ray->side = 0;
		}
		else 
		{
			ray->ray_side_y += ray->ray_delta_y;
			ray->map_y += ray->step_y; 
			ray->side = 1;
		}
		if (ray->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1; 
	}
}

void	ft_calc_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->walldistance = (ray->ray_side_x - ray->ray_delta_x); // on prend la distance dx car c'est le rayon x qui a connecte au mur en premier
	else if (ray->side == 1) 
		ray->walldistance = (ray->ray_side_y - ray->ray_delta_y); // come on est un carre trop loin il faut enlever la distance de 1 carrere

}

void	ft_draw_wall_line(t_ray *ray)
{
	ray->lineheight = (int)(ray->resolution_y / ray->walldistance);
	ray->drawstart = (-ray->lineheight / 2) + (ray->resolution_y / 2);
	ray->drawend = (ray->lineheight / 2) + (ray->resolution_y / 2);
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	if (ray->drawend >= ray->resolution_y)
		ray->drawend = ray->resolution_y - 1;
}

void	ft_calc_ray_dir(t_ray *ray)
{
	ray->raydir_x =	ray->dir_x + ray->plane_x * ray->camera_x;
	ray->raydir_y =	ray->dir_y + ray->plane_y * ray->camera_x;
	if (ray->raydir_x == 0)
		ray->raydir_x = 0.000001;
	if (ray->dir_y == 0)
		ray->raydir_y = 0.000001;
}

void ft_calc_ray_delta(t_ray *ray)
{
		//ay->ray_delta_y = sqrt(1 + ((ray->raydir_x * ray->raydir_x ) / ( ray->raydir_y * ray->raydir_y))); // distance a parcourir pour aller a l'intersection suivante
		//ray->ray_delta_x = sqrt(1 + ((ray->raydir_y * ray->raydir_y ) / ( ray->raydir_x * ray->raydir_x)));  // attention si cette formule fisheyes 
		ray->ray_delta_y = fabs(1 / ray->raydir_y);
		ray->ray_delta_x = fabs(1 / ray->raydir_x);
		//printf("ray->delta_y : %f\n", ray->ray_delta_y);
		//printf("ray->delta_x : %f\n", ray->ray_delta_x);
}


void	ft_put_ceiling_and_roof(t_data *data)
{
	int x; 
	int y;

	x = 0;
	while(x <= data->resolution_x)
	{
		y = 0;
		while (y <= data->resolution_y / 2)
		{
			my_mlx_pixel_put(data, x, y, data->floor);
			y++;
		}
		while (y <= data->resolution_y)
		{
			my_mlx_pixel_put(data, x, y, data->ceiling);
			y++;
		}
	x++;
	}
}

void	ft_fps(void)
{
	static struct timeval time;
	struct timeval actual_time;
	static int	fps; 
	if (fps == 0)
	{
		gettimeofday(&time, NULL);
	}
	fps++;
	gettimeofday(&actual_time, NULL); 
	if (time_diff(&time, &actual_time) > 1000)
	{
		ft_printf("fps : %d\n", fps);
		fps = 0; 
	}
	return ;
}

void	ft_move(t_ray *ray, t_data *data, t_key *key)
{
	double alpha; 
	if (key->move_back == 1)
		{
			if (ray->map[(int)(ray->pos_y - ray->dir_y * data->move_speed)][(int)(ray->pos_x)] != '1') 
				ray->pos_y -= ray->dir_y * data->move_speed;
			if (ray->map[(int)(ray->pos_y)][(int)(ray->pos_x - ray->dir_x * data->move_speed)] != '1')  
				ray->pos_x -= ray->dir_x * data->move_speed;
		}
	if (key->move_forward == 1)
	{
		if (ray->map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_x * data->move_speed)] != '1') // en c l'arrondi ce fait a l'inferieur
			ray->pos_x += ray->dir_x * data->move_speed; 
		if (ray->map[(int)(ray->pos_y + ray->dir_y * data->move_speed)][(int)(ray->pos_x)] != '1') // en c l'arrondi ce fait a l'inferieur
			ray->pos_y += ray->dir_y * data->move_speed; 
	}
	if (key->move_right == 1)
		{
			if (ray->dir_y > 0)
				alpha = acos(ray->dir_x);
			else
				alpha = -acos(ray->dir_x);
			if (ray->map[(int)((sin(alpha + M_PI / 2) * data->move_speed) + ray->pos_y)][(int)(ray->pos_x)] != '1') 
				ray->pos_y = (sin(alpha + M_PI / 2) * data->move_speed) + ray->pos_y;
			if (ray->map[(int)(ray->pos_y)][(int)((cos(alpha + M_PI / 2) * data->move_speed) + ray->pos_x)] != '1')  
				ray->pos_x = (cos(alpha + M_PI / 2) * data->move_speed) + ray->pos_x;
		}
	if (key->move_left == 1)
	{
			if (ray->dir_y > 0)
			alpha = acos(ray->dir_x);
			else 
			alpha = -acos(ray->dir_x);
			if (ray->map[(int)((-sin(alpha + M_PI / 2) * data->move_speed) + ray->pos_y)][(int)(ray->pos_x)] != '1') 
				ray->pos_y = (-sin(alpha + M_PI / 2) * data->move_speed) + ray->pos_y;
			if (ray->map[(int)(ray->pos_y)][(int)((cos(alpha + M_PI / 2) * data->move_speed) + ray->pos_x)] != '1')  
				ray->pos_x = (-cos(alpha + M_PI / 2) * data->move_speed) + ray->pos_x;
	}
}

void	ft_rotate_right(t_ray *ray, t_data *data, t_key *key)
{
	double	old_dir_x;
	double	old_plane_x;


	old_dir_x = ray->dir_x;
	old_plane_x = ray->plane_x;
	if (key->rotate_right == 1)
	{
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(data->rotate_speed) - ray->dir_y * sin(data->rotate_speed);
		ray->dir_y = old_dir_x * sin(data->rotate_speed) + ray->dir_y * cos(data->rotate_speed);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(data->rotate_speed) - ray->plane_y * sin(data->rotate_speed);
		ray->plane_y = old_plane_x  * sin(data->rotate_speed) + ray->plane_y * cos(data->rotate_speed);
	}
}
void	ft_rotate_left(t_ray *ray, t_data *data, t_key *key)
{
	double old_dir_x;
	double	old_plane_x;

	old_dir_x = ray->dir_x;
	old_plane_x = ray->plane_x;
	if (key->rotate_left == 1)
	{
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-data->rotate_speed) - ray->dir_y * sin(-data->rotate_speed);
		ray->dir_y = old_dir_x * sin(-data->rotate_speed) + ray->dir_y * cos(-data->rotate_speed);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-data->rotate_speed) - ray->plane_y * sin(-data->rotate_speed);
		ray->plane_y = old_plane_x  * sin(-data->rotate_speed) + ray->plane_y * cos(-data->rotate_speed);
	}

}
int	ft_action(t_data *data)
{
	
	t_key *key;
	key = &data->key; 
	//ft_printf_ray(&data->ray_data);
	ft_rotate_left(&data->ray_data, data, key);
	ft_rotate_right(&data->ray_data, data, key);
	ft_move(&data->ray_data, data,key );
	return (0);
}

void	ft_calc_x_texture(t_data *data)
{
	double wall_x;
	t_ray *ray;

	ray = &data->ray_data;

		if (ray->side == 0)
			wall_x = ray->pos_y + ray->walldistance * ray->raydir_y;
		else
			wall_x = ray->pos_x + ray->walldistance * ray->raydir_x;	
		wall_x = -floor(wall_x);
	ray->texx = (int)(wall_x * data->texture[0].img_width);
	if (ray->side == 0 && ray->raydir_x > 0)
	ray->texx = data->texture[0].img_width - ray->texx - 1;
	if (ray->side == 1 && ray->raydir_x < 0)
	ray->texx = data->texture[0].img_width - ray->texx - 1;

}

void	ft_calc_y_texture(t_data *data, int x)
{
	double step; 
	double texpos;
	t_ray *ray;

	
	ray = &data->ray_data; 
	step = 1 * data->texture[0].img_height / ray->lineheight;
	texpos = (ray->drawstart - ray->resolution_y + ray->lineheight / 2) * step; 
	while(ray->drawstart < ray->drawend)
	{
		ray->texy = (int)texpos & (data->texture[0].img_height - 1);
		texpos += step; 
		my_mlx_pixel_put(data, x, ray->drawstart, data->texture[0].addr[256 * ray->texy + ray->texx]);
		ray->drawstart++;
	}
}

void	ft_put_without_texture(t_data *data, t_ray *ray, int x)
{
	while(ray->drawstart < ray->drawend)
	{
		my_mlx_pixel_put(data, x, ray->drawstart, ray->color);
		ray->drawstart++;
	}
}
int	ft_render_next_frame(t_data *data)
{
	int	x;
	t_ray *ray;
	ray = &data->ray_data;

	x = 0;
	ft_print_raydata(data, ray);
	ft_put_ceiling_and_roof(data);
	ft_fps();
	ft_action(data);
	while (x < ray->resolution_x)
	{
		ray->hit = 0; 
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		ray->camera_x =  2 * x / ray->resolution_x - 1;
		ft_calc_ray_dir(ray);
		ft_calc_ray_delta(ray);
		ft_calc_rayside(ray);
		ft_launch_ray(ray);
		ft_calc_wall_distance(ray);
		//ft_print_ray(data, ray, ray->raydir_x, ray->raydir_y,ray->walldistance);
		ft_draw_wall_line(ray);
		ft_calc_x_texture(data);
		ft_calc_y_texture(data, x);
		//ft_put_without_texture(data, ray, x); 

		if (x == 0)
			ft_printf_ray(ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->display, 0, 0);
	return (0);
}

int	ft_key_press(int	keycode, t_data *data)
{
	t_key *key;

	key = &data->key; 
	(void)keycode;
	if (keycode == 0)
	key->move_left = 1;
	if (keycode == 2)
	key->move_right = 1;
	if (keycode == 13)
	key->move_forward = 1;
	if (keycode == 1)
	key->move_back = 1;
	if (keycode == 123)
	key->rotate_left = 1;
	if (keycode == 124)
	key->rotate_right = 1;
	data->keycode = keycode;
	return(0);
}

int	ft_key_release(int	keycode, t_data *data)
{
	t_key *key;

	key = &data->key;
	(void)keycode;
	if (keycode == 0)
		key->move_left = 0;
	if (keycode == 2)
		key->move_right = 0;
	if (keycode == 13)
		key->move_forward = 0;
	if (keycode == 1)
		key->move_back = 0;
	if (keycode == 123)
		key->rotate_left = 0;
	if (keycode == 124)
		key->rotate_right = 0;
	return(0);
}



	
	/*if (keycode == 53)
		ft_exit(data->map);*/
