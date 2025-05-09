/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:13:29 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/26 18:48:30 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft.h"
#include "ft_string.h"
#include <stdlib.h>

//error
static char	**error(char **strs, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

//count the number of word
static size_t	ft_nb_word(char const *s, char c)
{
	size_t	nb_word;
	size_t	i;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
			if (!s[i])
				return (nb_word);
		}
		while (!(s[i] == c) && s[i])
			i++;
		nb_word++;
	}
	return (nb_word);
}

//len of word
static size_t	ft_strlen_word(const char *s, char c)
{
	size_t	i;
	size_t	lettre;

	i = 0;
	lettre = 0;
	while (s[i] && !(s[i] == c))
	{
		lettre++;
		i++;
	}
	return (lettre);
}

//duplicate the word
static char	*ft_strdup_split(const char *s, size_t len)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

//split the str
char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	j;

	strs = (char **)malloc(sizeof(char *) * (ft_nb_word(s, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_nb_word(s, c))
	{
		if (!(s[i] == c) && s[i])
		{
			strs[j] = ft_strdup_split(&s[i], ft_strlen_word(&s[i], c));
			if (!strs)
				return (error(strs, j));
			i += ft_strlen_word(&s[i], c);
			j++;
		}
		i++;
	}
	strs[j] = 0;
	return (strs);
}
