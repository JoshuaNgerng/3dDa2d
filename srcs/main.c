/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:10 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/05 17:44:19 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	make_setting(t_set *s, t_ply *p)
{
	double	rotate_speed;

	s->wall_strip_width = MAX_WIDTH / RAY_FREQ;
	s->depth_of_focus = 100;
	s->ray_freq = RAY_FREQ;
	p->move_speed = 0.1;
	rotate_speed = 0.1;
	p->fov = 1;
	p->rotate_sin[0] = sin(rotate_speed);
	p->rotate_sin[1] = sin(- rotate_speed);
	p->rotate_cos[0] = cos(rotate_speed);
	p->rotate_cos[1] = cos(- rotate_speed);
	s->angle_delta = (FOV * M_PI) / (RAY_FREQ * 180);
	s->angle_start = (FOV * M_PI) / (2 * 180);
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

// static void	game_loop(t_game *g)
// {
// 	generate_scene(g);
// 	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->scene.img, 0, 0);
// 	mlx_hook(g->mlx.win, 17, (1L << 0), &free_exit, g);
// 	mlx_key_hook(g->mlx.win, &handle_input, g);
// 	mlx_hook(g->mlx.win, X_EVENT_KEY_PRESS, 0, &set_ply_mov, g);
// 	mlx_hook(g->mlx.win, X_EVENT_KEY_RELEASE, 0, &unset_ply_mov, g);
// 	mlx_loop_hook(g->mlx.mlx, &animation, g);
// 	mlx_loop(g->mlx.mlx);
// }

int	main(int ac, char **av)
{
	char			*ptr;
	static t_game	g;

	if (ac != 2)
		return (1);
	ptr = check_extent(av[1]);
	if (!ptr)
		return (errmsg(1), 1);
	make_setting(&g.setting, &g.ply);
	g.ply.pos = (t_point){.x = -1, .y = -1};
	if (read_file(&g, av[1]))
		return (free_game(&g), 1);
	// system("leaks cub3D");
	*ptr = '\0';
	g.mlx.mlx = mlx_init();
	if (!g.mlx.mlx)
		return (1); // cannot load mlx
	g.mlx.win = mlx_new_window(g.mlx.mlx, MAX_WIDTH, MAX_HEIGHT, av[1]);
	if (!g.mlx.win)
		return (free_game(&g), 1); // cannot load win
	// // system("leaks cub3D");
	// if (load_art_n_mlx(&g))
	// 	return (free_game(&g), 1);
	// printf("testing ply pos x(%lf) y(%lf)\n", g.ply.pos.x, g.ply.pos.y);
	print_map(&g.map);
	create_map(g);
	// system("leaks cub3D");
	// game_loop(&g);
	return (free_game(&g), 0);
}


