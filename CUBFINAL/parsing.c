/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:58:03 by azaimi            #+#    #+#             */
/*   Updated: 2025/09/26 17:14:05 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int isnum(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int getceiling(t_data *data)
{
    int	i;
    int	j;
    int	k;
    int	result;

    i = 0;
    k = 0;
    result = 0;
    while (data->cubfile[i])
    {
        if (!ft_strncmp(data->cubfile[i], "C", 1))
        {
            j = 1;
            while (data->cubfile[i][j])
            {
                if (isnum(data->cubfile[i][j]))
                    result = result * 10 + (data->cubfile[i][j] - '0');
                if (data->cubfile[i][j] == ',' || data->cubfile[i][j + 1] == '\0')
                {
                    data->ceiling[k++] = result;
                    result = 0;
                }
                j++;
            }
            break ;
        }
        i++;
    }
    return (1);
}

int getfloor(t_data *data)
{
    int	i;
    int	k;
    int	result;
    int	j;

    i = 0;
    k = 0;
    result = 0;
    while (data->cubfile[i])
    {
        if (!ft_strncmp(data->cubfile[i], "F", 1))
        {
            j = 1;
            while (data->cubfile[i][j])
            {
                if (isnum(data->cubfile[i][j]))
                    result = result * 10 + (data->cubfile[i][j] - '0');
                if (data->cubfile[i][j] == ',' || data->cubfile[i][j + 1] == '\0')
                {
                    data->floor[k++] = result;
                    result = 0;
                }
                j++;
            }
            break ;
        }
        i++;
    }
    return (1);
}

int isconfig(char *str)
{
    if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) ||
        !ft_strncmp(str, "WE", 2)|| !ft_strncmp(str, "EA", 2) ||
        !ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
        return (1);
    return (0);
}

int getmap(t_data *data)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    j = 0;
    data->map = malloc(sizeof(char *) * (data->len + 1));
    if (!data->map)
        return (0);
    while (data->cubfile[i])
    {
        if (isconfig(data->cubfile[i]) == 1)
            j++;
        i++;
        if (j == 6)
            break ;
    }
    while (data->cubfile[i])
    {
        data->map[k] = ft_strdup(data->cubfile[i]);
        k++;
        i++;
    }
    data->map[k] = NULL;
    data->k = k;
    return (1);
}

int longestline(t_data *data)
{
    int i;
    size_t len;

    i = 0;
    len = 0;
    while (data->map[i])
    {
        if (ft_strlen(data->map[i]) > len)
            len = ft_strlen(data->map[i]);
        i++;
    }
    return (len);
}

int validatepadding(t_data *data)
{
    int		i;
    char	*tmp;
    char	*updated;
    size_t	j;
    size_t	len;

    i = 0;
    len = longestline(data);
    data->longestline = len;
    while (data->map[i])
    {
        if (len > ft_strlen(data->map[i]))
        {
            tmp = data->map[i];
            updated = malloc(len + 1);
            if (!updated)
                return (0);
            j = ft_strlen(data->map[i]);
            ft_strlcpy(updated, data->map[i], len + 1);
            while (j < len)
                updated[j++] = ' ';
            updated[j] = '\0';
            data->map[i] = updated;
            free(tmp);
        }
        i++;
    }
    return (1);
}

int isvalid(char c)
{
    if (c == '0' || c == '1' || c == 'N' ||
        c == 'S' || c == 'E' || c == 'W' ||
            c == ' ')
            return (1);
    return (0);
}

int isplayer(char c)
{
    if (c == 'N' || c == 'S' ||
        c == 'E' || c == 'W')
            return (1);
    return (0);
}

int validatemap(t_data *data)
{
    int    i;
    int j;
    int flag;

    i = 0;
    flag = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (!isvalid(data->map[i][j]))
                return (0);
            if (isplayer(data->map[i][j]) && flag == 0)
                flag = 1;
            else if (isplayer(data->map[i][j]) && flag == 1)
                return (0);
            j++;
        }
        i++;
    }
    if (flag == 0)
        return (0);
    return (1);
}

int validateinside(t_data *data)
{
    size_t y;
    size_t x;
    char    c;
    
    x = 0;
    while (data->map[x])
    {
        y = 0;
        while (data->map[x][y])
        {
            c = data->map[x][y];
            if (c == '0' || isplayer(c))
            {
                if ((x > 0 && data->map[x - 1][y] == ' ')
                    || (x < data->k - 1 && data->map[x + 1][y] == ' ')
                    || (y > 0 && data->map[x][y - 1] == ' ')
                    || (!data->map[x][y + 1] || data->map[x][y + 1] == ' '))
                    return (0);
            }
            y++;
        }
        x++;
    }
    return (1);
}
