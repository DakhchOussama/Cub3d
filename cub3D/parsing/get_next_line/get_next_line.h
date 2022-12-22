/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 03:02:00 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/19 22:57:33 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

// # ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

char	*ft_lecture(int fd, char *buffers);
char	*ft_strchr_my(char *s, int c);
size_t	ft_strleen(char *s);
char	*ft_strjoineb(char *s1, char *s2);
void	*ft_memcpy(void *dst, void *src, size_t n);
char	*lire_ligne(char *buffers);
char	*rest(char *buffers);
char	*get_next_line(int fd);

//  #endif
