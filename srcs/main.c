/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:50:07 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/31 23:18:25 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// put all the pointer inside the struct at NULL
t_cub	*init_struct(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		ft_putstr_fd("Error\nFailed to init struct\n", 2);
		return (NULL);
	}
	cub->has_door = FALSE;
	cub->g_height = GRAPH_HEIGHT;
	cub->g_width = GRAPH_WIDTH;
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	cub->minimap = NULL;
	cub->no_xpm = NULL;
	cub->so_xpm = NULL;
	cub->we_xpm = NULL;
	cub->ea_xpm = NULL;
	cub->do_xpm = NULL;
	cub->init_ptr = NULL;
	cub->img_ptr = NULL;
	cub->map = NULL;
	return (cub);
}

/**
 * @brief Free all mlx structs and exit the program.
 * @param cub the t_cub struct containing the game state.
 */
void	free_struct(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->img_ptr)
		mlx_delete_image(cub->init_ptr, cub->img_ptr);
	if (cub->minimap)
		mlx_delete_image(cub->init_ptr, cub->minimap);
	if (cub->no_xpm)
		mlx_delete_texture(cub->no_xpm);
	if (cub->ea_xpm)
		mlx_delete_texture(cub->ea_xpm);
	if (cub->so_xpm)
		mlx_delete_texture(cub->so_xpm);
	if (cub->we_xpm)
		mlx_delete_texture(cub->we_xpm);
	if (cub->do_xpm)
		mlx_delete_texture(cub->do_xpm);
	if (cub->init_ptr)
		mlx_terminate(cub->init_ptr);
	if (cub->map)
		free_tab(cub->map);
	free(cub);
	exit (0);
}

/**
 * @brief Check if the given string is a .cub file.
 * @return TRUE if .cub, FALSE if not with an error message.
 */
t_bool	is_cub(char *argv)
{
	argv += ft_strlen(argv) - 4;
	if (!ft_strcmp(argv, ".cub"))
		return (TRUE);
	else
	{
		ft_putstr_fd("Error\nThe map is not a .cub", 2);
		return (FALSE);
	}
}

/**
 * @brief Get the max string length in a 2D array.
 * @param map 2D string array
 * @return Max string length or -1 if NULL.
 */
int	find_max_len(char **map)
{
	int	i;
	int	len;
	int	tmp_len;

	len = 0;
	i = 0;
	if (!map)
		return (-1);
	while (map[i])
	{
		tmp_len = ft_strlen(map[i]);
		if (tmp_len > len)
			len = tmp_len;
		i++;
	}
	return (len);
}

/**
 * @brief Entry point of the program.
 * The program takes one argument, a path to a .cub file.
 * The program parse the .cub file and make a raycasting of the map.
 * The program then launch a window with the raycasting of the map.
 * @param argc The number of argument passed to the program.
 * @param argv The argument passed to the program.
 * @return 0 if the program succeed, 127 if there is an error.
 */
int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nYou need to pass one map.\n", 2);
		return (127);
	}
	if (!is_cub(argv[1]))
		return (127);
	cub = parse_struct(argv[1]);
	if (!cub)
		return (127);
	cub->player.map_height = tab_size(cub->map);
	cub->player.map_width = find_max_len(cub->map);
	if (cub->player.map_width == -1 || cub->player.map_height == -1)
	{
		free_struct(cub);
		ft_putstr_fd("Error while calculating map size\n", 2);
		return (127);
	}
	print_struct(cub);
	open_window(cub);
	return (0);
}
