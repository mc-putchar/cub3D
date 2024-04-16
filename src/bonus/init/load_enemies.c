/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:43:04 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/30 13:43:04 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define FRAME0	"res/enemies/enemy_1/idle_0.xpm"
#define FRAME1	"res/enemies/enemy_1/idle_1.xpm"
#define FRAME2	"res/enemies/enemy_1/idle_2.xpm"
#define FRAME3	"res/enemies/enemy_1/idle_3.xpm"
#define FRAME4	"res/enemies/enemy_1/idle_4.xpm"
#define FRAME5	"res/enemies/enemy_1/idle_5.xpm"

#define ENEMY_MOVE_SPEED	0.02
#define ENEMY_RANGE			30
#define ENEMY_DIST			0.4

static void	converge(t_vector target, t_vector *me)
{
	if (((target.x - me->x) * (target.x - me->x) \
	+ (target.y - me->y) * (target.y - me->y)) > ENEMY_RANGE) {
		return;
	}
	if (me->x > target.x + ENEMY_DIST)
	{
		me->x -= ENEMY_MOVE_SPEED;
	}
	else if (me->x + ENEMY_DIST < target.x)
	{
		me->x += ENEMY_MOVE_SPEED;
	}
	if (me->y > target.y + ENEMY_DIST)
	{
		me->y -= ENEMY_MOVE_SPEED;
	}
	else if (me->y + ENEMY_DIST < target.y)
	{
		me->y += ENEMY_MOVE_SPEED;
	}
}

void	enemy_turn(t_cub *cub)
{
	t_basic_enemy	*nmy;

	nmy = cub->bonus;
	converge(cub->player->position, &nmy->idle->position);
}

static int	animate_enemy(t_cub *cub, t_animation *anim)
{
	anim->frames = malloc(sizeof(t_mlx_image *) * 6);
	if (!anim->frames)
		return (throw_error("Memory allocation failed"));
	anim->frames[0] = malloc(sizeof(t_mlx_image));
	anim->frames[1] = malloc(sizeof(t_mlx_image));
	anim->frames[2] = malloc(sizeof(t_mlx_image));
	anim->frames[3] = malloc(sizeof(t_mlx_image));
	anim->frames[4] = malloc(sizeof(t_mlx_image));
	anim->frames[5] = malloc(sizeof(t_mlx_image));
	if (tex_load(cub->mlx, anim->frames[0], FRAME0)
	|| tex_load(cub->mlx, anim->frames[1], FRAME1)
	|| tex_load(cub->mlx, anim->frames[2], FRAME2)
	|| tex_load(cub->mlx, anim->frames[3], FRAME3)
	|| tex_load(cub->mlx, anim->frames[4], FRAME4)
	|| tex_load(cub->mlx, anim->frames[5], FRAME5))
		return (1);
	anim->n_frames = 6;
	anim->current_frame = 0;
	anim->iter = 0;
	anim->delay = ANIMATION_FRAME_DELAY;
	return (0);
}

int	load_basic_enemy(t_cub *cub)
{
	t_basic_enemy	*enemy;
	t_sprite		*idle_sprite;

	enemy = malloc(sizeof(t_basic_enemy));
	if (!enemy)
		return (throw_error("Memory allocation failed"));
	idle_sprite = malloc(sizeof(t_sprite));
	if (!idle_sprite)
		return (throw_error("Memory allocation failed"));
	idle_sprite->anim = malloc(sizeof(t_animation));
	if (!idle_sprite->anim)
		return (throw_error("Memory allocation failed"));
	if (animate_enemy(cub, idle_sprite->anim))
		return (1);
	idle_sprite->isloaded = 1;
	idle_sprite->position.x = 15.5;
	idle_sprite->position.y = 15.5;
	idle_sprite->hdiv = 0;
	idle_sprite->vdiv = 0;
	idle_sprite->z = 100.0;
	idle_sprite->on_pickup = NULL;
	idle_sprite->collectable = 0;
	enemy->idle = idle_sprite;
	cub->bonus = enemy;

	t_sprite	*node;
	node = cub->scene->sprites;
	while (node->next)
		node = node->next;
	node->next = idle_sprite;
	++(cub->scene->n_sprites);
	return (0);
}
