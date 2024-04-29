/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:10 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/29 17:04:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	make_setting(t_set *s, t_ply *p, int *ptr)
{
	double	rotate_speed;

	s->cell_width = 64;
	*ptr = s->cell_width;
	s->depth_of_focus = 100;
	s->move_speed = 5;
	s->rotation_speed = 11;
	s->fov = 90;
	p->fov = s->fov / 90;
	s->win_width = MAX_WIDTH;
	s->win_height = MAX_HEIGTH;
	rotate_speed = s->rotation_speed / 100;
	p->rotate_sin[0] = sin(rotate_speed);
	p->rotate_sin[1] = sin(- rotate_speed);
	p->rotate_cos[0] = cos(rotate_speed);
	p->rotate_cos[1] = cos(- rotate_speed);
}

static char	*check_extent(const char *file)
{
	char	*ptr;

	ptr = ft_strchr(file, '.');
	if (!ptr)
		return (NULL);
	if (ft_strncmp(ptr, ".cub", 5))
		return (NULL);
	return (ptr);
}

static void	game_loop(t_game *g)
{
	generate_scene(g);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->scene.img, 0, 0);
	mlx_hook(g->mlx.win, 17, (1L << 0), &free_exit, g);
	mlx_hook(g->mlx.win, X_EVENT_KEY_PRESS, 0, &set_ply_mov, g);
	mlx_hook(g->mlx.win, X_EVENT_KEY_RELEASE, 0, &unset_ply_mov, g);
	mlx_loop_hook(g->mlx.mlx, &animation, g);
	mlx_loop(g->mlx.mlx);
}

int	main(int ac, char **av)
{
	char			*ptr;
	static t_game	g;

	if (ac != 2)
		return (1);
	ptr = check_extent(av[1]);
	if (!ptr)
		return (errmsg(1), 1);
	make_setting(&g.setting, &g.ply, &g.map.unit_size);
	g.ply.pos = (t_point){.x = -1, .y = -1};
	g.mlx.mlx = mlx_init();
	if (!g.mlx.mlx)
		return (1); // cannot load mlx
	if (read_file(&g, av[1]))
		return (free_game(&g), 1);
	// system("leaks cub3D");
	*ptr = '\0';
	g.mlx.win = mlx_new_window(g.mlx.mlx, MAX_WIDTH, MAX_HEIGTH, av[1]);
	if (!g.mlx.win)
		return (free_game(&g), 1); // cannot load win
	// system("leaks cub3D");
	if (load_art_n_mlx(&g))
		return (free_game(&g), 1);
	// printf("testing ply pos x(%lf) y(%lf)\n", g.ply.pos.x, g.ply.pos.y);
	// print_map(&g.map);
	// system("leaks cub3D");
	game_loop(&g);
	return (free_game(&g), 0);
}
