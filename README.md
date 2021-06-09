# BastWAN_SHA2

cf [this thread](https://twitter.com/Kongduino/status/1402420169826127872).

I need to add MAC to my [LoRa messaging code](https://github.com/Kongduino/BastWAN_Minimal_LoRa), to authenticate the messages. On WisBlock, the Adafruit nRFCrypto library provides SHA-1, SHA-224, SHA-256 and SHA-512, but there's no such luxury on ATSAMR34 (that powers the RAK4260 & BastWAN). So there you go.

Sample code does just a couple of tests. Feel free to enhance it. SHA and HMAC implementation by [Olivier Gay](https://github.com/ogay/hmac/).