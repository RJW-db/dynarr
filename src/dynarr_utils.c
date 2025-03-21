/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/03/21 19:18:17 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>	//	MIN()
#include <dynarr.h>

//	Static Functions
static void	*da_memmove(void *dest, const void *src, size_t n);

void	*da_calloc(size_t nmemb, size_t size)
{
	unsigned char	*char_ptr;
	size_t			t;
	void			*ptr;

	t = nmemb * size;
	if (nmemb != 0 && size != 0 && t / nmemb != size)
		return (NULL);
	ptr = malloc(t);
	if (ptr == NULL)
		return (NULL);
	char_ptr = (unsigned char *)ptr;
	while (t != 0)
	{
		*char_ptr++ = '\0';
		--t;
	}
	return (ptr);
}

void	*da_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*tmp_src;
	unsigned char		*tmp_dest;

	if (!dest && !src)
		return (NULL);
	tmp_dest = (unsigned char *)dest;
	tmp_src = (const unsigned char *)src;
	while (n--)
		*tmp_dest++ = *tmp_src++;
	return (dest);
}

void	*da_free_ptr(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

void	*da_realloc(void **ptr, const size_t new_size, const size_t old_size)
{
	void	*new;

	if (new_size == 0 && ptr != NULL)
	{
		da_free_ptr(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	if (ptr != NULL && *ptr != NULL)
	{
		da_memmove(new, *ptr, MIN(new_size, old_size));
		da_free_ptr(ptr);
	}
	return (new);
}

static void	*da_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (src > dest)
		while (n--)
			*tmp++ = *(char *)src++;
	if (dest > src)
		while (n--)
			*((char *)dest + n) = *((char *)src + n);
	return (dest);
}