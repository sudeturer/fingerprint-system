#include <Adafruit_Fingerprint.h>

HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t nextID = 1;

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);

  finger.begin(57600);
  if (!finger.verifyPassword()) {
    Serial.println("Sensor bulunamadi");
    while (1);
  }

  Serial.println("K: Kayit | O: Okutma");
}

void loop() {
  if (Serial.available()) {
    char secim = Serial.read();

    if (secim == 'K' || secim == 'k') {
      enrollFingerprint(nextID);
      nextID++;
    }

    if (secim == 'O' || secim == 'o') {
      int id = getFingerprintID();
      if (id >= 0) {
        Serial.print("Giris basarili ID: ");
        Serial.println(id);
      } else {
        Serial.println("Giris reddedildi");
      }
    }
  }
}

uint8_t enrollFingerprint(uint8_t id) {
  finger.getImage();
  finger.image2Tz(1);
  delay(2000);
  finger.getImage();
  finger.image2Tz(2);
  finger.createModel();
  finger.storeModel(id);
  Serial.println("Kayit alindi");
  return true;
}

int getFingerprintID() {
  if (finger.getImage() != FINGERPRINT_OK) return -1;
  if (finger.image2Tz() != FINGERPRINT_OK) return -1;
  if (finger.fingerFastSearch() != FINGERPRINT_OK) return -1;
  return finger.fingerID;
}
