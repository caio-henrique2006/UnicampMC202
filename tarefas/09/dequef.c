#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"

int df_copy(dequef *origin, long new_cap)
{
   dequef *new_D = df_alloc(new_cap, origin->factor);
   if (new_D == NULL)
   {
      return 0;
   }
   // Copy origin into new_D
   for (long k = 0; k < origin->size; k++)
   {
      new_D->data[k] = origin->data[(origin->first + k) % origin->cap];
   }
   free(origin->data);
   origin->data = new_D->data;
   origin->first = 0;
   origin->cap = new_cap;
   free(new_D);
   return 1;
}

/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef *df_alloc(long capacity, double factor)
{
   dequef *D = malloc(sizeof(dequef));
   if (D == NULL || capacity <= 0)
   {
      return NULL;
   }
   float *data = malloc(capacity * sizeof(float));
   if (data == NULL)
   {
      free(D);
      return NULL;
   }
   D->data = data;
   D->first = 0;
   D->size = 0;
   D->cap = capacity;
   D->mincap = capacity;
   D->factor = factor;

   return D;
}

/**
  Release a dequef and its data.
**/
void df_free(dequef *D)
{
   if (!(D == NULL))
   {
      free(D->data);
      free(D);
   }
}

/**
   The size of the deque.
**/
long df_size(dequef *D)
{
   return D->size;
}

/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef *D, float x)
{
   if (D->cap == D->size)
   {
      long new_cap = (long)(D->cap * D->factor);
      if (!df_copy(D, new_cap))
      {
         return 0;
      }
   }
   long i = (D->first + D->size) % D->cap;
   D->data[i] = x;
   D->size++;

   return 1;
}

/**
   Remove a float from the end of D and return it.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_pop(dequef *D)
{
   if (D->size == 0)
   {
      return 0;
   }
   long end = (D->first + D->size - 1) % D->cap;
   float removed = D->data[end];
   D->size--;

   // Resize
   if (D->size == D->cap / (D->factor * D->factor))
   {
      long new_cap = (long)(D->cap / D->factor);
      if (new_cap < D->mincap)
      {
         new_cap = D->mincap;
      }
      if (!df_copy(D, new_cap))
      {
         return removed;
      }
   }

   return removed;
}

/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef *D, float x)
{
   if (D->cap == D->size)
   {
      long new_cap = (long)(D->cap * D->factor);
      if (!df_copy(D, new_cap))
      {
         return 0;
      }
   }
   D->first = (D->first - 1 + D->cap) % D->cap;
   D->data[D->first] = x;
   D->size++;
   return 1;
}

/**
   Remove a float from the beginning of D and return it.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_eject(dequef *D)
{
   if (D->size == 0)
   {
      return 0;
   }
   float removed = D->data[D->first];
   D->first = (D->first + 1 + D->cap) % D->cap;
   D->size--;

   if (D->size == (long)(D->cap / (D->factor * D->factor)))
   {
      long new_cap = (long)(D->cap / D->factor);
      if (new_cap < D->mincap)
      {
         new_cap = D->mincap;
      }
      if (!df_copy(D, new_cap))
      {
         return removed;
      }
   }
   return removed;
}

/**
   Return D[i].

   If i is not in [0,|D|-1]] what happens then?
**/
float df_get(dequef *D, long i)
{
   long index = (D->first + i) % D->cap;
   return D->data[index];
}

/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] what happens then?
**/
void df_set(dequef *D, long i, float x)
{
   if (!(i < 0 || i >= D->size))
   {
      long index = (D->first + i) % D->cap;
      D->data[index] = x;
   }
}

/**
   Print the elements of D in a single line.
**/
void df_print(dequef *D)
{
   if (D == NULL)
   {
      return;
   }
   printf("deque (%ld): ", D->size);
   for (long i = 0; i < D->size; i++)
   {
      long index = (D->first + i) % D->cap;
      printf("%.1f ", D->data[index]);
   }
   printf("\n");
}