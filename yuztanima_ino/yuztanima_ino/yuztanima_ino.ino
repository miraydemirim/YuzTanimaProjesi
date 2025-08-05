const int hataButonPin = 10;
const int onayButonPin = 11;
const int onayRolePin = 12;
const int hataRolePin = 13;
const int buzzerPin = 9;

// Röle durumları
bool hataRoleDurum = false;
bool onayRoleDurum = false;

// Önceki buton durumları
bool oncekiHataButonDurum = HIGH;
bool oncekiOnayButonDurum = HIGH;

void setup() {
  pinMode(hataButonPin, INPUT_PULLUP);
  pinMode(onayButonPin, INPUT_PULLUP);

  pinMode(hataRolePin, OUTPUT);
  pinMode(onayRolePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(hataRolePin, LOW);
  digitalWrite(onayRolePin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.begin(9600);  // Seri iletişimi başlat
}

void loop() {
  bool hataButon = digitalRead(hataButonPin);
  bool onayButon = digitalRead(onayButonPin);

  // Hata butonuna basıldıysa
  if (oncekiHataButonDurum == HIGH && hataButon == LOW) {
    hataRoleDurum = !hataRoleDurum;
    digitalWrite(hataRolePin, hataRoleDurum ? HIGH : LOW);
    redSesi();
    delay(200);
  }

  // Onay butonuna basıldıysa
  if (oncekiOnayButonDurum == HIGH && onayButon == LOW) {
    onayRoleDurum = !onayRoleDurum;
    digitalWrite(onayRolePin, onayRoleDurum ? HIGH : LOW);
    onaySesi();
    delay(200);
  }

  // Python'dan gelen seri komutlar
  if (Serial.available() > 0) {
    char komut = Serial.read();

    if (komut == 'O') {  // Onay sinyali
      digitalWrite(onayRolePin, HIGH);
      onaySesi();
      delay(500);
      digitalWrite(onayRolePin, LOW);
    }
    else if (komut == 'H') {  // Hata sinyali
      digitalWrite(hataRolePin, HIGH);
      redSesi();
      delay(500);
      digitalWrite(hataRolePin, LOW);
    }
  }

  oncekiHataButonDurum = hataButon;
  oncekiOnayButonDurum = onayButon;
}

// 🔴 RED sesi (düşük ton)
void redSesi() {
  tone(buzzerPin, 300, 300); // 300 Hz, 300 ms
  delay(300);
  noTone(buzzerPin);
}

// ✅ ONAY sesi (yüksek ton bip bip)
void onaySesi() {
  tone(buzzerPin, 1000, 150); // 1000 Hz, 150 ms
  delay(150);
  tone(buzzerPin, 1200, 150); // 1200 Hz, 150 ms
  delay(150);
  noTone(buzzerPin);
}
