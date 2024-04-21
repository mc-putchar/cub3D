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

static size_t	word_count(const char *s, char c)
{
	size_t	words;
	size_t	inword;

	words = 0;
	inword = 0;
	while (*s)
	{
		if (*s++ != c)
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

char	**ft_split(const char *s, char c)
{
	size_t const	words = word_count(s, c);
	size_t			idx;
	size_t			wordlen;
	char			**spl;

	spl = malloc(sizeof(char *) * (words + 1));
	if (!spl)
		return (NULL);
	idx = 0;
	while (idx < words)
	{
		while (*s && *s == c)
			++s;
		wordlen = 0;
		while (s[wordlen] && s[wordlen] != c)
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
