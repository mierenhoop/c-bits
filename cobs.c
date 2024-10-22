#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/**
 * Encode COBS.
 */
void Cobs(uint8_t *d, const uint8_t *s, int n) {
  assert(0 <= n && n <= 253);
  uint8_t l = 1;
  d[n+1] = 0;
  while (n--) {
    if (s[n] == 0)
      d[n+1] = l, l = 0;
    else
      d[n+1] = s[n];
    l++;
  }
  d[0] = l;
}

/**
 * Decode COBS.
 *
 * @returns true if successful and false if data is corrupt
 */
bool UnCobs(uint8_t *d, const uint8_t *s, int n) {
  int l, i = -n;
  if (2 <= n && n <= 255 && s[0] != 0 && s[n-1] == 0) {
    n -= 2;
    memcpy(d, s+1, n);
    for (i = s[0]-1; i < n && (l = d[i]); i += l)
      d[i] = 0;
  }
  return i == n;
}

