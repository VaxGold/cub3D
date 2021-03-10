/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omercade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:05:55 by omercade          #+#    #+#             */
/*   Updated: 2021/01/25 19:02:06 by omercade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int     main(void)
{
    void    *mlx_ptr;
	void	*win_ptr;

    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test");
	mlx_loop(mlx_ptr);
	
	return (0);
}
