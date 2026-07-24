#include <stdint.h>

// ------------------------------------------------
// purely value-based function with fundamental types

uint8_t get_libtype(void);

uint32_t sum_of_least_two(uint16_t a, uint16_t b, uint16_t c);

// ------------------------------------------------
// pointer-based function with fundamental types

uint32_t add_to_least_two(uint8_t add, uint16_t* a, uint16_t* b, uint16_t *c);

uint16_t* reference_to_largest(uint16_t* x, uint16_t*y, uint16_t* z);

// ------------------------------------------------
// purely value-based function with custom types

struct version_t{
  uint8_t major;
  uint8_t minor;
};

int print_version(struct version_t object);

// ------------------------------------------------
// pointer-based function with custom types

struct version_t* create(uint8_t major, uint8_t minor);

int destroy(struct version_t* object);

// ------------------------------------------------
// purely value-based function with opaque types

struct opaque_version;

struct opaque_version* create_opaque(uint8_t major, uint8_t minor, uint8_t patch);

int print_opaque(struct opaque_version* version);

int delete_opaque(struct opaque_version* version);

