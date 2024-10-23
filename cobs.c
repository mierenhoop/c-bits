#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define CobsMaxOverhead(n) (1 + ((n) + 253) / 254)

/**
 * Encode COBS.
 *
 * @returns length of COBS encoded bytes
 */
size_t cobs(uint8_t *d, const uint8_t *s, size_t n) {
  uint8_t l, *b = d, *back = d++;
  for (l = 1; n--; s++) {
    if (*s)
      *d++ = *s, l++;
    if (*s == 0 || l == 255) {
      *back = l, l = 1, back = d;
      if (*s == 0 || n)
        d++;
    }
  }
  *back = l;
  *d++ = 0;
  return d - b;
}

/**
 * Decode COBS.
 *
 * @returns true if successful and false if data is corrupt
 */
bool uncobs(uint8_t *d, const uint8_t *s, size_t n) {
  const uint8_t *e = s + n;
  uint8_t prv = 255;
  uint8_t cur;
  while (s < e && (cur = *s++) && s + cur <= e) {
    if (cur && prv != 255)
      *d++ = 0;
    prv = cur;
    while (--cur)
      *d++ = *s++;
  }
  return s == e;
}
