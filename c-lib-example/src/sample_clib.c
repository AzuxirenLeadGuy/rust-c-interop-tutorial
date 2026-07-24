#include <sample_clib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LIBTYPE
#define LIBTYPE 0
#endif

uint8_t get_libtype(void) {
  return LIBTYPE;
}

uint16_t *reference_to_largest(uint16_t *a, uint16_t *b, uint16_t *c) {
  if (*a > *b && *a > *c) {
    return a;
  } else if (*b > *c) {
    return b;
  } else {
    return c;
  }
}

uint32_t add_to_least_two(uint8_t add, uint16_t *a, uint16_t *b, uint16_t *c) {
  uint16_t *max_ptr = reference_to_largest(a, b, c);
  if (b == max_ptr || c == max_ptr) {
    *a += add;
  }
  if (a == max_ptr || c == max_ptr) {
    *b += add;
  }
  if (a == max_ptr || b == max_ptr) {
    *c += add;
  }
  return *a + *b + *c - *max_ptr;
}

uint32_t sum_of_least_two(uint16_t a, uint16_t b, uint16_t c) {
  return add_to_least_two(0, &a, &b, &c);
}

int print_version(struct version_t object) {
  printf("Obtained struct object in %d <%d.%d>\n", LIBTYPE, object.major,
         object.minor);
  return object.major + object.minor;
}

struct version_t *create(uint8_t major, uint8_t minor) {
  struct version_t *ptr = malloc(sizeof(struct version_t));
  if (ptr == 0)
    return 0;
  ptr->major = major;
  ptr->minor = minor;
  return ptr;
}

int destroy(struct version_t *object) {
  if (object == 0)
    return 0;
  free(object);
  return 1;
}

struct opaque_version {
  uint8_t major, minor, patch;
};

struct opaque_version *create_opaque(uint8_t major, uint8_t minor,
                                     uint8_t patch){
  struct opaque_version* ptr = malloc(sizeof(struct opaque_version));
  if(ptr != 0)
  {
    ptr->major = major;
    ptr->minor = minor;
    ptr->patch = patch;
  }
  return ptr;
}

int print_opaque(struct opaque_version *version) {
  printf("Obtained struct object in %d <%d.%d.%d>\n", LIBTYPE, version->major,
         version->minor, version->patch);
  return version->major + version->minor + version->patch;
}

int delete_opaque(struct opaque_version *version) {
  if (version == 0)
    return 0;
  free(version);
  return 1;
}
