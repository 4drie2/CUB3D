/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:48:34 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 23:53:05 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Open a window and start the mlx event loop.
 * @param cub the t_cub struct containing the game state.
 */
void	open_window(t_cub *cub)
{
	cub->img_ptr = mlx_new_image(cub->init_ptr,
			cub->win_width, cub->win_height);
	cub->minimap = mlx_new_image(cub->init_ptr,
			cub->win_width, cub->win_height);
	if (!cub->img_ptr)
	{
		free_struct(cub);
		return ;
	}
	mlx_image_to_window(cub->init_ptr, cub->img_ptr, 0, 0);
	mlx_image_to_window(cub->init_ptr, cub->minimap, 0, 0);
	raycast(cub);
	mlx_set_cursor_mode(cub->init_ptr, MLX_MOUSE_HIDDEN);
	mlx_key_hook(cub->init_ptr, handle_door, cub);
	mlx_loop_hook(cub->init_ptr, handle_move, cub);
	mlx_close_hook(cub->init_ptr, free_struct, cub);
	mlx_loop(cub->init_ptr);
}
