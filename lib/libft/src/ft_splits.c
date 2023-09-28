/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:46 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/06 18:21:46 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	includes(char const *set, char c)
{
	if (!c)
		return (1);
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

static size_t	word_counter(char const *str, char const *set)
{
	size_t	words;
	size_t	inword;

	words = 0;
	inword = 0;
	while (*str)
	{
		if (!includes(set, *str++))
			++inword;
		else if (inword && ++words)
			inword = 0;
	}
	if (inword)
		++words;
	return (words);
}

static void	gtfo(char **s, size_t i)
{
	while (i--)
		free(s[i]);
	free(s);
}

char	**ft_splits(char const *str, char const *set)
{
	char	**spl;
	size_t	words;
	size_t	idx;
	size_t	wordlen;

	words = word_counter(str, set);
	spl = malloc(sizeof(char *) * (words + 1));
	if (!spl)
		return (NULL);
	idx = 0;
	while (idx < words)
	{
		wordlen = 0;
		while (includes(set, *str))
			++str;
		while (!includes(set, str[wordlen]))
			++wordlen;
		spl[idx] = ft_substr(str, 0, wordlen);
		if (!spl[idx++])
			gtfo(spl, idx);
		str += wordlen;
	}
	spl[idx] = NULL;
	return (spl);
}
