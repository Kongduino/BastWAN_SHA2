#include "sha2.c"
#undef max
#undef min
#include <string>
#include <vector>

using namespace std;
// Required or the code won't compile!
template class basic_string<char>; // https://github.com/esp8266/Arduino/issues/1136

namespace std _GLIBCXX_VISIBILITY(default) {
_GLIBCXX_BEGIN_NAMESPACE_VERSION
void __throw_length_error(char const*) {}
void __throw_bad_alloc() {}
void __throw_out_of_range(char const*) {}
void __throw_logic_error(char const*) {}
void __throw_out_of_range_fmt(char const*, ...) {}
}

void hexDump(char *mybuf, uint16_t len) {
  string s = "|", t = "| |";
  Serial.println(F("\n  |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f |"));
  Serial.println(F("  +------------------------------------------------+ +----------------+"));
  for (uint16_t i = 0; i < len; i += 16) {
    for (uint8_t j = 0; j < 16; j++) {
      if (i + j >= len) {
        s = s + "   "; t = t + " ";
      } else {
        char c = mybuf[i + j];
        char nn[5];
        sprintf(nn, "%02X ", c);
        s.append(nn);
        if (c < 32 || c > 127) t.append(".");
        else t.append(1, (char)c);
      }
    }
    uint8_t index = i / 16;
    Serial.print(index, HEX); Serial.write('.');
    s.append(t);
    s.append("|");
    Serial.println(s.c_str());
    s = "|"; t = "| |";
  }
  Serial.println(F("  +------------------------------------------------+ +----------------+"));
}

void setup() {
  delay(2000);
  SerialUSB.begin(115200);
  delay(2000);
  SerialUSB.println("\n\n");
  const unsigned char message1[] = "{\"UUID\":\"00D60A54\",\"cmd\":\"ping\",\"from\":\"BastMobile\"}";
  const unsigned char message2[] = "Hi There";
  unsigned char hash0[] = {
    0x42, 0x81, 0x88, 0x40, 0xe4, 0x01, 0xca, 0x59,
    0xfe, 0x1a, 0x02, 0x79, 0x7b, 0x33, 0xe9, 0x66,
    0x7e, 0x4b, 0x8f, 0x9c, 0x43, 0xa6, 0x82, 0xc2,
    0xcf, 0xf6, 0x31, 0x88
  };
  unsigned char hash1[] = {
    0x4c, 0x1f, 0xe4, 0xd5, 0x6a, 0xd6, 0x13, 0xfe,
    0x29, 0x83, 0x3d, 0x3f, 0x2c, 0x10, 0x5e, 0x17,
    0xe6, 0x6b, 0x52, 0x24, 0xe8, 0xeb, 0x71, 0x46,
    0x91, 0xbb, 0xbc, 0x6a, 0x60, 0xc2, 0x2d, 0x62
  };
  unsigned char hash2[] = {
    0x89, 0x6f, 0xb1, 0x12, 0x8a, 0xbb, 0xdf, 0x19,
    0x68, 0x32, 0x10, 0x7c, 0xd4, 0x9d, 0xf3, 0x3f,
    0x47, 0xb4, 0xb1, 0x16, 0x99, 0x12, 0xba, 0x4f,
    0x53, 0x68, 0x4b, 0x22
  };
  unsigned char hash3[] = {
    0xb0, 0x34, 0x4c, 0x61, 0xd8, 0xdb, 0x38, 0x53,
    0x5c, 0xa8, 0xaf, 0xce, 0xaf, 0x0b, 0xf1, 0x2b,
    0x88, 0x1d, 0xc2, 0x00, 0xc9, 0x83, 0x3d, 0xa7,
    0x26, 0xe9, 0x37, 0x6c, 0x2e, 0x32, 0xcf, 0xf7
  };
  unsigned char key[20];
  unsigned char digest[SHA512_DIGEST_SIZE];
  unsigned char mac[SHA512_DIGEST_SIZE];

  SerialUSB.println("\nSHA-224 test");

  sha224(message1, strlen((char *)message1), digest);
  hexDump((char *)digest, SHA224_DIGEST_SIZE);
  hexDump((char *)hash0, SHA224_DIGEST_SIZE);
  if (memcmp(digest, hash0, SHA224_DIGEST_SIZE) == 0) SerialUSB.println(" * test passed");
  else SerialUSB.println(" * test failed");
  SerialUSB.println("\nSHA-256 test");

  sha256(message1, strlen((char *)message1), digest);
  hexDump((char *)digest, SHA256_DIGEST_SIZE);
  hexDump((char *)hash1, SHA224_DIGEST_SIZE);
  if (memcmp(digest, hash1, SHA256_DIGEST_SIZE) == 0) SerialUSB.println(" * test passed");
  else SerialUSB.println(" * test failed");

  SerialUSB.println("\nSHA-HMAC test");

  SerialUSB.println("\nSHA-HMAC-224 test");
  memset(key, 0x0b, 20);
  hmac_sha224(key, 20, (unsigned char *) message2, strlen((char*)message2), mac, SHA224_DIGEST_SIZE);
  hexDump((char *)mac, SHA224_DIGEST_SIZE);
  hexDump((char *)hash2, SHA224_DIGEST_SIZE);
  if (memcmp(mac, hash2, SHA224_DIGEST_SIZE) == 0) SerialUSB.println(" * test passed");
  else SerialUSB.println(" * test failed");

  SerialUSB.println("\nSHA-HMAC-256 test");
  memset(key, 0x0b, 20);
  hmac_sha256(key, 20, (unsigned char *) message2, strlen((char*)message2), mac, SHA256_DIGEST_SIZE);
  hexDump((char *)mac, SHA256_DIGEST_SIZE);
  hexDump((char *)hash3, SHA256_DIGEST_SIZE);
  if (memcmp(mac, hash3, SHA256_DIGEST_SIZE) == 0) SerialUSB.println(" * test passed");
  else SerialUSB.println(" * test failed");
}

void loop() {
}
