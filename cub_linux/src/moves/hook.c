/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:57:35 by nsoares-          #+#    #+#             */
/*   Updated: 2023/12/03 01:33:36 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * @brief Updates the player's position and orientation based on 
 * rotation and movement.
 *
 * This function updates the player's direction, plane, and position 
 * based on the specified rotation angle and checks for collisions with 
 * walls in the game. The player's position is adjusted accordingly, 
 * ensuring that it does not intersect with walls.
 *
 * @param data A pointer to the game data structure.
 * @param rot The rotation angle.
 */
void update_moves(t_data *data, double rot)
{
    double olddir_x;
    double oldplane_x;
    double margin;

    margin = 0.1;
    olddir_x = data->dir_x;
    data->dir_x = data->dir_x * cos(rot) - data->dir_y * sin(rot);
    data->dir_y = olddir_x * sin(rot) + data->dir_y * cos(rot);
    oldplane_x = data->plane_x;
    data->plane_x = data->plane_x * cos(rot) - data->plane_y * sin(rot);
    data->plane_y = oldplane_x * sin(rot) + data->plane_y * cos(rot);
    if (!ft_strchr("1", data->map->worldmap[(int)(data->pos_x + \
    data->dir_x * data->dey)][(int)(data->pos_y)]))
        data->pos_x += (data->dir_x * data->dey) * (1.0 - margin);
    if (!ft_strchr("1", data->map->worldmap[(int)(data->pos_x)]\
    [(int)(data->pos_y + data->dir_y * data->dey)]))
        data->pos_y += (data->dir_y * data->dey) * (1.0 - margin);
    if (!ft_strchr("1", data->map->worldmap[(int)(data->pos_x + \
    data->plane_x * data->dex)][(int)data->pos_y]))
        data->pos_x += (data->plane_x * data->dex) * (1.0 - margin);
    if (!ft_strchr("1", data->map->worldmap[(int)data->pos_x][(int)\
    (data->pos_y + data->plane_y * data->dex)]))
        data->pos_y += (data->plane_y * data->dex) * (1.0 - margin);
}

int	keyboard_hook(int keycode, t_mlx *m)
{
	if (keycode == XK_Escape)
		mlx_exit(m);
	if (keycode == XK_S || keycode == XK_s)
		m->data->dey = -0.03;
	if (keycode == XK_W || keycode == XK_w)
		m->data->dey = 0.03;
	if (keycode == XK_A || keycode == XK_a)
		m->data->dex = -0.03;
	if (keycode == XK_D || keycode == XK_d)
		m->data->dex = 0.03;
	if (keycode == XK_Left)
		m->data->rot = 0.01;
	if (keycode == XK_Right)
		m->data->rot = -0.01;
	return (0);
}

int	keyboard_keyrelease(int keycode, t_mlx *m)
{
	if (keycode == XK_S || keycode == XK_s)
		m->data->dey = 0;
	if (keycode == XK_W || keycode == XK_w)
		m->data->dey = 0;
	if (keycode == XK_A || keycode == XK_a)
		m->data->dex = 0;
	if (keycode == XK_D || keycode == XK_d)
		m->data->dex = 0;
	if (keycode == XK_Left)
		m->data->rot = 0;
	if (keycode == XK_Right)
		m->data->rot = 0;
	return (0);
}
