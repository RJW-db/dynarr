testcase:

#include <dynarr.h>
#include <stdio.h>
void	showcase(t_dynarr myArray)
{
	for (size_t i = 0; i < myArray.length; i++)
	{
		printf("%d ", ((int *)myArray.arr)[i]);
	}
	printf("\n");
}
int	main()
{
	t_dynarr myArray;
	int initialSize = 5;
	int dataSize = sizeof(int);

	if (!dynarr_create(&myArray, initialSize, dataSize))
	{
		return (1);
	}
	for (int i = 1; i <= 15; i++)
	{
		dynarr_insert(&myArray, &i);
	}
	showcase(myArray);
	printf("myArray.capacity %zu\n", myArray.capacity);
	dynarr_shrink_to_fit(&myArray);
	printf("myArray.capacity %zu\n", myArray.capacity);

	int cpy_value = ((int *)myArray.arr)[5];
	int	*arr = dynarr_take_arr(&myArray);
	printf("copied value = %d\n", cpy_value);
	printf("set to 0 %ld\n", myArray.capacity);
	printf("set to 0 %ld\n", myArray.elem_size);
	printf("set to 0 %ld\n", myArray.length);

	printf("extracted array from dynarr %d\n", arr[0]);
	free(arr);
	return (0);
}