typedef struct{
unsigned int * ptr;
 int size;
} set_t;

set_t set;
set.ptr = malloc(3 * sizeof(unsigned int));
set.size = 3;

*(set.ptr + 2) = 54;
*(set.ptr + 1) = 42;
*(set.ptr + 0) = 69;

printf("%d\n", set.ptr[2]);