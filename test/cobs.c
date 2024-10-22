#include "../cobs.c"

#include <stdio.h>

void DumpHex(const uint8_t *p, int n) {
  for (int i = 0; i < n; i++)
    printf("%02x ", p[i]);
  puts("");
}

#define Test(...)                                                              \
  do {                                                                         \
    const uint8_t data[] = {__VA_ARGS__};                                      \
    uint8_t d[255], d2[sizeof(data)];                                          \
    Cobs(d, data, sizeof(data));                                               \
    DumpHex(d, sizeof(data) + 2);                                              \
    assert(UnCobs(d2, d, sizeof(data) + 2));                                   \
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
  puts("All tests passed");
}
