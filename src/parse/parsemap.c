/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:15 by adgutier          #+#    #+#             */
/*   Updated: 2023/11/25 14:22:04 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_top_map(t_map *map)
{
    int i;
    int j;
    int k;
    // int mapheight;
    
    i = 0;
    j = 0;
    k = 0;
    // mapheight = map_height(map->map);
    
    while (map->map[i] != NULL)
    {
        if (ft_strncmp(map->map[i], "NO", 2) == 0)
        {
            j = 3;
            k = 0;
            while (map->map[i][j] != '\0' && map->map[i][j] != '\n' && map->map[i][j] != ' ' && map->map[i][j] != '\t' && map->map[i][j] != '\r')
            {
                map->no[k] = map->map[i][j];
                k++;
                j++;
            }
            map->no[k] = '\0';
        }
        else if (ft_strncmp(map->map[i], "SO", 2) == 0)
        {
            j = 3;
            k = 0;
            while (map->map[i][j] != '\0' && map->map[i][j] != '\n' && map->map[i][j] != ' ' && map->map[i][j] != '\t' && map->map[i][j] != '\r')
            {
                map->so[k] = map->map[i][j];
                k++;
                j++;
            }
            map->so[k] = '\0';
        }
        else if (ft_strncmp(map->map[i], "WE", 2) == 0)
        {
            j = 3;
            k = 0;
            while (map->map[i][j] != '\0' && map->map[i][j] != '\n' && map->map[i][j] != ' ' && map->map[i][j] != '\t' && map->map[i][j] != '\r')
            {
                map->we[k] = map->map[i][j];
                k++;
                j++;
            }
            map->we[k] = '\0';
        }
        else if (ft_strncmp(map->map[i], "EA", 2) == 0)
        {
            j = 3;
            k = 0;
            while (map->map[i][j] != '\0' && map->map[i][j] != '\n' && map->map[i][j] != ' ' && map->map[i][j] != '\t' && map->map[i][j] != '\r')
            {
                map->ea[k] = map->map[i][j];
                k++;
                j++;
            }
            map->ea[k] = '\0';
        }
        else if (ft_strncmp(map->map[i], "F", 1) == 0)
        {
            j = 2;
            k = 0;
            while (map->map[i][j] != '\0' && map->map[i][j] != '\n' && map->map[i][j] != '\r' && map->map[i][j] != ' ' && map->map[i][j] != '\t')
            {
                map->fr = ft_atoi(&map->map[i][j]);
                while (map->map[i][j] != ',' && map->map[i][j] != '\0')
                    j++;
                if (map->map[i][j] == ',')
                    j++;
                map->fg = ft_atoi(&map->map[i][j]);
                while (map->map[i][j] != ',' && map->map[i][j] != '\0')
                    j++;
                if (map->map[i][j] == ',')
                    j++;
                map->fb = ft_atoi(&map->map[i][j]);
            }
        }
        else if (ft_strncmp(map->map[i], "C", 1) == 0)
        {
            j = 2;
            k = 0;
            while (map->map[i][j] != '\0' && map->map[i][j] != '\n' && map->map[i][j] != '\r' && map->map[i][j] != ' ' && map->map[i][j] != '\t')
            {
                map->cr = ft_atoi(&map->map[i][j]);
                while (map->map[i][j] != ',' && map->map[i][j] != '\0')
                    j++;
                if (map->map[i][j] == ',')
                    j++;
                map->cg = ft_atoi(&map->map[i][j]);
                while (map->map[i][j] != ',' && map->map[i][j] != '\0')
                    j++;
                if (map->map[i][j] == ',')
                    j++;
                map->cb = ft_atoi(&map->map[i][j]);
            }
        }
        i++;
    }
}


int find_first_map_row(t_map *map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(map->map[i])
    {
        if(map->map[i][0] == ' ')
        {
            while (map->map[i][j] && (map->map[i][j] != '1' || map->map[i][j] != '0'))
                j++;
            if(map->map[i][j] == '1' || map->map[i][j] == '0')
                return(i);
            
        }
        else if(map->map[i][0] == '1' || map->map[i][0] == '0')
            return(i);
        i++;
    }
    return(0);
}