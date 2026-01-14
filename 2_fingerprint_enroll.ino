#include <Adafruit_Fingerprint.h>

HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id = 1;

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);

  finger.begin(57600);
  if (!finger.verifyPassword()) {
    Serial.println("Sensor bulunamadi");
    while (1);
  }

  Serial.println("Parmak izi kaydi basliyor");
  enrollFingerprint(id);
}

void loop() {}

uint8_t enrollFingerprint(uint8_t id) {
  int p = -1;

  Serial.println("Parmaginizi okutun");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  finger.image2Tz(1);
  delay(2000);

  while (finger.getImage() != FINGERPRINT_NOFINGER);

  Serial.println("Tekrar okutun");
  while (finger.getImage() != FINGERPRINT_OK);

  finger.image2Tz(2);
  finger.createModel();
  finger.storeModel(id);

  Serial.println("Kayit tamamlandi");
  return true;
}
