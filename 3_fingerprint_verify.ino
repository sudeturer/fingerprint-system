#include <Adafruit_Fingerprint.h>

HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);

  finger.begin(57600);
  if (!finger.verifyPassword()) {
    Serial.println("Sensor yok");
    while (1);
  }

  Serial.println("Dogrulama hazir");
}

void loop() {
  int id = getFingerprintID();
  if (id >= 0) {
    Serial.print("Dogru parmak ID: ");
    Serial.println(id);
  } else {
    Serial.println("Eslesme yok");
  }
  delay(2000);
}

int getFingerprintID() {
  if (finger.getImage() != FINGERPRINT_OK) return -1;
  if (finger.image2Tz() != FINGERPRINT_OK) return -1;
  if (finger.fingerFastSearch() != FINGERPRINT_OK) return -1;
  return finger.fingerID;
}
