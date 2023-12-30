/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:36:00 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/02 17:36:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	read_wav_header(char const *path, int *size)
{
	int		fd;
	char	buffer[44];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (throw_error("Failed opening sound file"));
	if (read(fd, buffer, 44) < 44)
		return (close(fd), throw_error("Failed to read sound file header"));
	*size = *(int *)(buffer + 4) + 8;
	if (close(fd) || *size < 1)
		return (throw_error("Unrecognized sound file"));
	return (0);
}

int	load_sound(char const *path, char **data, size_t *bytes)
{
	int		fd;
	int		size;
	ssize_t	r;

	size = 0;
	if (read_wav_header(path, &size))
		return (1);
	*data = malloc(size);
	if (!*data)
		return (throw_error("Memory allocation failed"));
	fd = open(path, O_RDONLY);
	*bytes = size - 44;
	r = read(fd, *data, size);
	while (r > 0)
	{
		if (r < size)
			size -= r;
		if (!size)
			break ;
		r = read(fd, *data + r, size);
	}
	close(fd);
	if (r < 0)
		return (throw_error("Failed reading sound file"));
	return (0);
}

int	play_sound(char const *raw, size_t bytes)
{
	pa_simple		*s;
	pa_sample_spec	ss;

	ss.format = PA_SAMPLE_S16NE;
	ss.channels = 2;
	ss.rate = 44100;
	s = pa_simple_new(NULL, "Cub3D", PA_STREAM_PLAYBACK, NULL, \
						"PeerOfDestiny_intro", &ss, NULL, NULL, NULL);
	if (pa_simple_write(s, raw, bytes, NULL) < 0)
		(void)throw_error("PulseAudio playback failed");
	pa_simple_drain(s, NULL);
	pa_simple_free(s);
	return (0);
}

void	*play_intro_sound(void *ignore)
{
	char		*sound;
	size_t		sound_bytes;

	if (load_sound(INTRO_RIFF, &sound, &sound_bytes))
		return (NULL);
	play_sound(sound, sound_bytes);
	free(sound);
	return (ignore);
}

int	init_sound_thread(void)
{
	
	pthread_t	sound_thread;

	if (pthread_create(&sound_thread, NULL, play_intro_sound, NULL))
	{
		return (throw_error("Failed creating thread"));
	}
	return (0);
}
