#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define CobsMaxOverhead(n) (1 + ((n) + 253) / 254)

/**
 * Encode COBS.
 *
 * @param d is the destination buffer with a size of at least `n +
 * CobsMaxOverhead(n)`
 * @returns length of COBS encoded bytes
 */
size_t cobs(uint8_t *d, const uint8_t *s, size_t n) {
  uint8_t l = 1, *b = d, *back;
  if (n > 0) {
    for (back = d++; n--; s++) {
      if (*s)
        *d++ = *s, l++;
      if (*s == 0 || l == 255) {
        *back = l, l = 1, back = d;
        if (*s == 0 || n)
          d++;
      }
    }
    *back = l;
  }
  *d++ = 0;
  return d - b;
}

/**
 * Decode COBS.
 *
 * @param d is the destination buffer with a size of at least `n`
 * @returns true if successful and false if data is corrupt
 */
size_t uncobs(uint8_t *d, const uint8_t *s, size_t n) {
  const uint8_t *b = d, *e = s + n;
  uint8_t cur, prv = 255;
  while (s < e && (cur = *s++) && s + cur <= e) {
    if (cur && prv != 255)
      *d++ = 0;
    prv = cur;
    while (--cur)
      *d++ = *s++;
  }
  return s == e ? d - b : 0;
}
