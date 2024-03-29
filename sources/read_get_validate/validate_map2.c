/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femarque <femarque@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:00:39 by femarque          #+#    #+#             */
/*   Updated: 2023/07/05 14:02:30 by femarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*ft_strdup_map(const char *s1, t_map *map, int spaces_flag)
{
	int		i;
	char	*map_line;

	map_line = (char *) ft_calloc((map->map_width + 2), sizeof(char));
	if (!map_line)
		return (NULL);
	i = 0;
	while (i < map->map_width)
		map_line[i++] = ' ';
	map_line[i + 1] = '\0';
	if (spaces_flag)
		return ((char *)(map_line));
	i = -1;
	while (++i < (int)ft_strlen(s1))
	{
		map_line[i + 2] = s1[i];
	}
	return ((char *)(map_line));
}

void	get_map_width(t_map *map)
{
	int	i;

	i = 0;
	map->map_width = ft_strlen(map->map[0]);
	while (map->map[i] != NULL)
	{
		if (ft_strlen(map->map[i]) > (size_t)map->map_width)
			map->map_width = ft_strlen(map->map[i]);
		i++;
	}
	map->map_width += 4;
}

void	fill_out_spaces(t_map *map)
{
	int	i;

	map->map_height += 4;
	map->remap = (char **)ft_calloc(sizeof(char *), (map->map_height + 1));
	i = -1;
	map->remap[0] = ft_strdup_map(NULL, map, 1);
	map->remap[1] = ft_strdup_map(NULL, map, 1);
	map->remap[map->map_height - 1] = ft_strdup_map(NULL, map, 1);
	map->remap[map->map_height - 2] = ft_strdup_map(NULL, map, 1);
	while (map->map[++i])
		map->remap[i + 2] = ft_strdup_map(map->map[i], map, 0);
	map->remap[map->map_height] = NULL;
}

int	is_valid_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (2);
	else if (c != '0' && c != '1' && c != ' ')
		return (1);
	return (0);
}

int	validade_char(t_map *map)
{
	int	flag_error;
	int	i;
	int	j;

	flag_error = 0;
	i = 1;
	while (i < map->map_height - 1)
	{
		j = 1;
		while (j < map->map_width - 1)
		{
			if (is_valid_char(map->remap[i][j]) == 2 && flag_error == 0)
				flag_error = 1;
			else if (is_valid_char(map->remap[i][j]) == 2 && flag_error == 1)
				return (write(2, "cub3d: Error: Invalid map\n", 26));
			else if (is_valid_char(map->remap[i][j]) == 1)
				return (write(2, "cub3d: Error: Invalid map\n", 26));
			j++;
		}
		i++;
	}
	if (flag_error != 1)
		return (write(2, "cub3d: Error: Invalid map\n", 26));
	return (0);
}
