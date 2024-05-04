/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 06:00:52 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:12:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static inline int	is_separator(char c, const char *sep)
{
	int	i;

	i = 0;
	while (sep[i] && sep[i] != c)
		++i;
	return (sep[i]);
}

static size_t	word_count(const char *s, const char *c)
{
	size_t	words;
	size_t	inword;

	words = 0;
	inword = 0;
	while (*s)
	{
		if (!is_separator(*s++, c))
			++inword;
		else if (inword && ++words)
			inword = 0;
	}
	if (inword)
		++words;
	return (words);
}

static void	word_copy(char *cpy, const char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i + sizeof(size_t) <= len)
	{
		((size_t *)cpy)[i / sizeof(size_t)] = ((size_t *)s)[i / sizeof(size_t)];
		i += sizeof(size_t);
	}
	while (i < len)
	{
		cpy[i] = s[i];
		++i;
	}
	cpy[i] = 0;
}

static inline void	*cleanup(char **spl, size_t idx)
{
	while (idx--)
		free(spl[idx]);
	free(spl);
	return (NULL);
}

char	**ft_splits(const char *s, const char *sep)
{
	size_t const	words = word_count(s, sep);
	size_t			idx;
	size_t			wordlen;
	char			**spl;

	spl = malloc(sizeof(char *) * (words + 1));
	if (!spl)
		return (NULL);
	idx = 0;
	while (idx < words)
	{
		while (*s && is_separator(*s, sep))
			++s;
		wordlen = 0;
		while (s[wordlen] && !is_separator(s[wordlen], sep))
			++wordlen;
		spl[idx] = malloc(wordlen + 1);
		if (!spl[idx])
			return (cleanup(spl, idx));
		word_copy(spl[idx], s, wordlen);
		s += wordlen;
		++idx;
	}
	spl[words] = 0;
	return (spl);
}
