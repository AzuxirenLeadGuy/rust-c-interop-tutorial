#include <sample_clib.h>
#include <stdint.h>

int main(void) {
  // ordered_struct
  if (sum_of_least_two(2, 3, 7) != 5) {
    return 1;
  }

  uint16_t x = 10, y = 20, z = 35;
  uint32_t result = add_to_least_two(4, &x, &y, &z);
  if (result != 38 || x != 14 || y != 24 || z != 35) {
    return 2;
  }

  uint16_t *ptr = reference_to_largest(&x, &y, &z);
  if (ptr != &z || *ptr != 35 || x != 14 || y != 24) {
    return 3;
  }

  struct version_t given_value = {10, 20};
  if (print_version(given_value) != 30) {
    return 4;
  }

  struct version_t *heap_version = create(40, 50);
  if (heap_version == 0) {
    return 5;
  }
  if (print_version(*heap_version) != 90) {
    return 6;
  }
  if (destroy(heap_version) == 0) {
    return 7;
  }

  struct opaque_version *obj = create_opaque(50, 60, 80);
  if (obj == 0) {
    return 9;
  }
  if (print_opaque(obj) != 190) {
    return 10;
  }
  if (delete_opaque(obj) == 0) {
    return 11;
  }

  if (get_libtype() == 0){
    return 12;
  }

  return 0;
}
