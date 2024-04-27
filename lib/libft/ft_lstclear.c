/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:18:57 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/18 11:29:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nex;

	if (!del || !lst || !*lst)
		return ;
	while (*lst && lst)
	{
		nex = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = nex;
	}
}
