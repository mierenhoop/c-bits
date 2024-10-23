#include "../cobs.c"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void DumpHex(const uint8_t *p, int n) {
  for (int i = 0; i < n; i++)
    printf("%02x ", p[i]);
  puts("");
}

#define Test(...)                                                              \
  do {                                                                         \
    const uint8_t data[] = {__VA_ARGS__};                                      \
    uint8_t d[sizeof(data) + CobsMaxOverhead(sizeof(data))], d2[sizeof(data)]; \
    size_t n = cobs(d, data, sizeof(data));                                    \
    DumpHex(d, n);                                                             \
    assert(uncobs(d2, d, n));                                                  \
    assert(!memcmp(data, d2, sizeof(data)));                                   \
  } while (0)

int main() {
  Test();
  Test(0x00);
  Test(0x00, 0x00);
  Test(0x00, 0x11, 0x00);
  Test(0x11, 0x22, 0x00, 0x33);
  Test(0x11, 0x22, 0x33, 0x44);
  Test(0x11, 0x00, 0x00, 0x00);
  Test([0 ... 253] = 254);
  Test([0 ... 254] = 255);
  Test([0 ... 500] = 0xcc);
  Test([0 ... 1000] = 0xcc);
  Test([0 ... 253] = 0);
  Test([0 ... 254] = 0);
  Test([0 ... 500] = 0);
  Test([0 ... 1000] = 0);
  puts("All tests passed");
}
