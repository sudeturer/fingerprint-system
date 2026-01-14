#include <Adafruit_Fingerprint.h>

HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);

  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Parmak izi sensörü bulundu");
  } else {
    Serial.println("Sensör bulunamadı");
    while (1);
  }
}

void loop() {
}
