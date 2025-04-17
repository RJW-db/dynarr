/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/04/17 15:19:52 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>

bool	dynarr_create(t_dynarr *ptr, size_t init_size, const size_t data_size)
{
	if (ptr == NULL || data_size == 0)
		return (false);
	ptr->arr = da_calloc(init_size, data_size);
	if (ptr->arr == NULL)
		return (false);
	*(size_t *)&ptr->elem_size = data_size;
	ptr->capacity = init_size;
	ptr->length = 0;
	return (true);
}

/**
 * use this function in a if statement and check for ENOMEM.
 */
bool	dynarr_shrink_to_fit(t_dynarr *a)
{
	void	*ar;
	if (a == NULL || a->arr == NULL)
		return (false);
	ar = da_realloc(&a->arr,
			(a->length * a->elem_size), (a->capacity * a->elem_size));
	if (ar == NULL)
	{
		dynarr_free(a);
		return (false);
	}
	a->arr = ar;
	a->capacity = a->length;
	return (true);
}

void	dynarr_free(t_dynarr *a)
{
	da_free_ptr(&a->arr);
	*(size_t *)&a->elem_size = 0;
	a->capacity = 0;
	a->length = 0;
}

void	*dynarr_take_arr(t_dynarr *a)
{
	void	*arr_copy;

	if (a == NULL || a->arr == NULL)
		return (NULL);
	arr_copy = a->arr;
	a->arr = NULL;
	dynarr_free(a);
	return (arr_copy);
}
