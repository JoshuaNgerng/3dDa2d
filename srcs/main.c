/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/22 14:52:34 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	make_setting(t_set *s)
{
	s->move_speed = 10;
	s->rotation_speed = 11;
	s->fov = 90;
	s->win_width = MAX_WIDTH;
	s->win_height = MAX_HEIGHT;
}

static int	check_setting(t_set *s, t_ply *p)
{
	double	rotate_speed;

	if (s->move_speed > 50 || s->rotation_speed > 45)
		return (1);
	if (s->fov > 120 || s->fov < 30)
		return (1);
	p->fov = (double)s->fov / 90;
	p->move_speed = (double)s->move_speed / 100;
	p->depth_of_focus = (double)MAX_HEIGHT * 1.5;
	rotate_speed = (double)s->rotation_speed / 100;
	p->rotate_sin[0] = sin(rotate_speed);
	p->rotate_sin[1] = sin(-rotate_speed);
	p->rotate_cos[0] = cos(rotate_speed);
	p->rotate_cos[1] = cos(-rotate_speed);
	return (0);
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
	g->ply.move_options ^= map_option;
	create_minimap(g);
	mlx_hook(g->mlx.win, esc_key, (1L << 0), &free_exit, g);
	mlx_hook(g->mlx.win, key_press, 0, &set_ply_mov, g);
	mlx_hook(g->mlx.win, key_release, 0, &unset_ply_mov, g);
	mlx_hook(g->mlx.win, mouse_press, 0, &mouse_set_ply, g);
	mlx_hook(g->mlx.win, mouse_release, 0, &mouse_unset_ply, g);
	mlx_loop_hook(g->mlx.mlx, &animation, g);
	mlx_loop(g->mlx.mlx);
}

int	main(int ac, char **av)
{
	char			*ptr;
	static t_game	g;

	if (ac != 2)
		return (errmsg_prog(0), 1);
	errmsg_file_errno(0, av[1]);
	ptr = check_extent(av[1]);
	if (!ptr)
		return (errmsg_prog(1), 1);
	make_setting(&g.setting);
	if (check_setting(&g.setting, &g.ply))
		return (1);
	g.ply.pos = (t_point){.x = -1, .y = -1};
	g.mlx.mlx = mlx_init();
	if (!g.mlx.mlx)
		return (errmsg_config_errno(0), 1);
	if (read_file(&g, av[1]))
		return (free_game(&g), 1);
	*ptr = '\0';
	if (load_mlx_img(&g, av[1]))
		return (free_game(&g), 1);
	game_loop(&g);
	return (free_game(&g), 0);
}
