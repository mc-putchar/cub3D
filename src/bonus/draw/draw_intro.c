/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_intro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:11:57 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 09:11:57 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	generate_storyline(t_cub *cub, t_point *origin)
{
	char	**story;
	char	**ptr;

	story = malloc(11 * sizeof(*story));
	if (!story)
		return ;
	ptr = story;
	*ptr++ = ft_strdup(".....");
	*ptr++ = ft_strdup("Manual override required");
	*ptr++ = ft_strdup("Providing support ..... YOU CAN DO IT!");
	*ptr++ = ft_strdup("Generating background story ..... DONE");
	*ptr++ = ft_strdup("STORY:");
	*ptr++ = ft_strdup("    Berlin FireWall has fallen");
	*ptr++ = ft_strdup("    Internet Trollz are flooding in");
	*ptr++ = ft_strdup("    It's only a matter of time");
	*ptr++ = ft_strdup("    when 42 will also fall");
	*ptr++ = ft_strdup("    Now, our only hope is");
	*ptr = NULL;
	typewrite(cub, origin, FONT, story);
	free_arr(story);
	origin->y += 18 * 10;
}

static void	blink_text(t_cub *cub, t_point *p, char *text, int color)
{
	mlx_string_put(cub->mlx, cub->win, p->x, p->y, color, text);
	ft_sleep(400);
	mlx_string_put(cub->mlx, cub->win, p->x, p->y, FONT_BLACK, text);
	ft_sleep(400);
	mlx_string_put(cub->mlx, cub->win, p->x, p->y, color, text);
	ft_sleep(400);
	mlx_string_put(cub->mlx, cub->win, p->x, p->y, FONT_BLACK, text);
	ft_sleep(400);
	mlx_string_put(cub->mlx, cub->win, p->x, p->y, color, text);
	ft_sleep(400);
	mlx_string_put(cub->mlx, cub->win, p->x, p->y, FONT_BLACK, text);
	ft_sleep(400);
	mlx_string_put(cub->mlx, cub->win, p->x, p->y, color, text);
}

static void	boot_system(t_cub *cub, t_point *origin)
{
	char	**boot;
	char	**ptr;

	boot = malloc(6 * sizeof(*boot));
	if (!boot)
		return ;
	ptr = boot;
	*ptr++ = ft_strdup("Booting project ..... OK");
	*ptr++ = ft_strdup("Reading subject.pdf ..... OK");
	*ptr++ = ft_strdup("Evaluating bonus parts ..... OK");
	*ptr++ = ft_strdup("Plugging memory leaks ..... OK");
	*ptr++ = ft_strdup("Raising FireWall ..... KO");
	*ptr = NULL;
	typewrite(cub, origin, FONT, boot);
	origin->y += 18 * 5;
	blink_text(cub, origin, "ERROR Catastrophic failure encountered", FONT_ERROR);
	origin->y += 18;
	free_arr(boot);
}

static void	draw_bios(t_cub *cub)
{
	int		fd;
	int		y;
	char	*line;

	y = 100;
	mlx_put_image_to_window(cub->mlx, cub->win, cub->logo->img, 200, y);
	fd = open(INFO_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	mlx_set_font(cub->mlx, cub->win, FONT3);
	line = get_next_line(fd);
	y += 16;
	while (line)
	{
		mlx_string_put(cub->mlx, cub->win, 460, y, FONT_COLOR, line);
		y += 16;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	draw_intro(t_cub *cub)
{
	t_point		origin;

	origin.x = 200;
	origin.y = 360;
	draw_bios(cub);
	ft_sleep(2000);
	boot_system(cub, &origin);
	generate_storyline(cub, &origin);
	ft_sleep(2000);
	mlx_set_font(cub->mlx, cub->win, FONT2);
	origin.x = 270;
	blink_text(cub, &origin, "PEER OF DESTINY", FONT_COLOR);
	mlx_set_font(cub->mlx, cub->win, FONT);
	ft_sleep(4000);
	return (0);
}
