# dynarr – Generic Dynamic Array for C

A small, header-based dynamic array library for C. Stores elements by value (copies `elem_size` bytes per insert), supports generic types, and provides simple memory management utilities.

## Table of Contents

- [Features](#features)
- [Repository Layout](#repository-layout)
- [Build](#build)
- [Integration](#integration)
- [Example](#example)
- [API Overview](#api-overview)
- [Notes](#notes)

## Features

- Generic storage using `void *arr` and `elem_size`
- Append insertion with automatic growth (`dynarr_insert`)
- Optional memory reclaim (`dynarr_shrink_to_fit`)
- Transfer ownership of the backing array (`dynarr_take_arr`)

## Repository Layout

- Public header: [`include/dynarr.h`](include/dynarr.h)
- Sources:
  - [`src/dynarr.c`](src/dynarr.c)
  - [`src/dynarr_insert.c`](src/dynarr_insert.c)
  - [`src/dynarr_utils.c`](src/dynarr_utils.c)
- Build script: [`Makefile`](Makefile)
- Output: `dynarr.a`

## Build

```sh
make          # build dynarr.a
make clean    # remove build artifacts
make fclean   # clean + remove push_swap checker (and extern deps)
make re       # fclean + build
make valgrind # debug flags
make debug    # debug flags + sanitizers (per Makefile)
```

All targets and flags are defined in the [`Makefile`](Makefile).

## Integration
Build and link the static library:

```sh
cc -I include main.c dynarr.a -o demo
```

## Example

This example shows:
- Growing past the initial capacity by inserting 15 ints
- Printing `length` items from the backing array
- Shrinking capacity to `length`
- Taking ownership of the internal array with `dynarr_take_arr`

```c
#include <stdio.h>
#include <stdlib.h>
#include "dynarr.h"

static void showcase(const t_dynarr a)
{
    const int *p = (const int *)a.arr;

    for (size_t i = 0; i < a.length; i++)
        printf("%d ", p[i]);
    printf("\n");
}

int main(void)
{
    t_dynarr a;

    if (!dynarr_create(&a, 5, sizeof(int)))
        return 1;

    for (int i = 1; i <= 15; i++)
    {
        if (!dynarr_insert(&a, &i))
        {
            dynarr_free(&a);
            return 1;
        }
    }

    showcase(a);

    printf("capacity before shrink: %zu\n", a.capacity);
    if (!dynarr_shrink_to_fit(&a))
        return 1;
    printf("capacity after shrink:  %zu\n", a.capacity);

    dynarr_free(&a);
    return 0;
}
```

## API Overview

```c
typedef struct s_dynarr {
    void      *arr;
    size_t     elem_size;
    size_t     capacity;
    size_t     length;
} t_dynarr;

bool   dynarr_create(t_dynarr *ptr, size_t init_size, size_t data_size);
bool   dynarr_insert(t_dynarr *a, const void *element);
bool   dynarr_shrink_to_fit(t_dynarr *a);
void  *dynarr_take_arr(t_dynarr *a);
void   dynarr_free(t_dynarr *a);
```

## Notes

- `dynarr_insert` copies `elem_size` bytes from `element` into the backing array.
- `dynarr_take_arr` returns the internal `arr` pointer and clears the `dynarr` struct. The caller owns the returned pointer and must `free()` it.
- `dynarr_shrink_to_fit` tries to realloc the backing storage down to `length * elem_size`.


