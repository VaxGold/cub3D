/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <omercade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:37:32 by omercade          #+#    #+#             */
/*   Updated: 2021/04/21 18:54:37 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

t_img		face_save(t_data *gd, char *r)
{
	t_texture	tex;

	tex.img = mlx_xpm_file_to_image(gd->mlx, r,
			&tex.width, &tex.height);
	secure_free(r);
	tex.addr = (int *)mlx_get_data_addr(tex.img,
			&tex.bits, &tex.line, &tex.endian);
	return (tex);
}

t_skybox	skybox_save(t_data *gd, char *line)
{
	int 			i;
	int				len;
	char			*r;
	unsigned int	init;
	t_texture		tex;

	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'S' && ft_isspace(line[i + 1]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	init = (unsigned int)i;
	while (!ft_isspace(line[i + len]) && line[i + len] != '\0')
		len++;
	r = ft_substr(line, init, (size_t)len);
	free(r);
	while (ft_isspace(line[i]))
		i++;
	init = (unsigned int)i;
	while (!ft_isspace(line[i + len]) && line[i + len] != '\0')
		len++;
	r = ft_substr(line, init, (size_t)len);
	

}