/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:46:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/30 13:46:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_DATA_H
# define BONUS_DATA_H

enum e_enemy_state
{
	DECOMPOSED,
	DEAD,
	IDLE,
	PATROL,
	AGGRO
};

typedef struct s_basic_enemy
{
	int				n_frames;
	int				current_frame;
	t_sprite		*idle;
}	t_basic_enemy;

#endif // BONUS_DATA_H
