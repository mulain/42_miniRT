/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:48:03 by wmardin           #+#    #+#             */
/*   Updated: 2023/02/11 20:05:00 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_appendbuffertoline(char *line, char *readbuffer, int readreturn);
int		ft_findnewline(const char *line);
char	*ft_makeremainder_returnoutput(char *line, char **remainder, int fd);
int		ft_strlen_gnl(const char *s);
char	*ft_strdup_gnl(const char *source);

#endif