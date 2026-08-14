# Static Libraries in C

A static library is a library that must be linked during the compile phase. This at first may sound the obvious way to build libraries, but there are certain advantages in building dynamic libraries that are worth checking out. It is detailed in the next chapter.

A static library is made literally by archiving multiple object files together, using the tool `ar`, which is the [GNU archiver](https://en.wikipedia.org/wiki/Ar_(Unix)). It is part of the [GNU binutils](https://www.gnu.org/software/binutils/).

The usage is straightforward as follows:

```
ar <your-static-lib>.a [collection of object files]
```


In the previous example, we were working with the following header file

```c
// veclib.h

struct vector3d_t;

struct vector3d_t* unit_vec_3d();

void sum_vec_3d(struct vector3d_t *a, struct vector3d_t *b);

int sum_components_vec_3d(struct vector3d_t* a);

void free_vec3d(struct vector3d_t* a);

```




<style>
  .expert-blogs { 
      /*We display the buttons when the mouse is hovered near it*/
      display: none;
      /*Highlighting the big links*/ 
      color: yellow;
   }
</style>


For just one source code `veclib.c`, we can prepare an object file `veclib.o` using

```
gcc -c veclib.c -o veclib.o
```


// TODO