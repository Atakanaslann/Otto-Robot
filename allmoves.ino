#include <Servo.h>
#include "pitches.h"


// Happy Birthday Melodisi
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

int noteDurations[] = {
  8, 8, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 2
};

// Nokia Tune Melodisi (Açılış için)
int nokiaMelody[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4,
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4,
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
  NOTE_A4, NOTE_E4, NOTE_FS4, NOTE_GS4
};

int nokiaNoteDurations[] = {
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8
};


// Servo motorlar
Servo servo1; // Sağ bacak
Servo servo2; // Sol bacak
Servo servo3; // Sağ ayak
Servo servo4; // Sol ayak

// Servo pinleri
#define SERVO1_PIN 2
#define SERVO2_PIN 3
#define SERVO3_PIN 4
#define SERVO4_PIN 5

// Bluetooth verileri için
String bluetoothData = "";


void setup() {
  pinMode(13, OUTPUT);
   for (int thisNote = 0; thisNote < sizeof(nokiaMelody) / sizeof(nokiaMelody[0]); thisNote++) {
    int noteDuration = 1000 / nokiaNoteDurations[thisNote];
    tone(13, nokiaMelody[thisNote], noteDuration);

    // Notalar arasında boşluk bırak
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // Sesi kapat
    noTone(13);
  }

  // Servo motorları başlat
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);

  // Bluetooth seri iletişimini başlat
  Serial.begin(9600); // HM-10 için genelde 9600 baud hızı kullanılır

  // Başlangıç pozisyonları
  servo1.write(85); // Sağ bacak sabit duruş
  servo2.write(90); // Sol bacak sabit duruş
  servo3.write(85); // Sağ ayak sabit duruş
  servo4.write(90); // Sol ayak sabit duruş

}

void loop() {
  // Bluetooth veri kontrolü
  if (Serial.available()) {
    char receivedChar = Serial.read();
    bluetoothData += receivedChar;

    // Komutlar arasında sonlandırıcı olarak '\n' kullanıyoruz
    if (receivedChar == '\n') {
      bluetoothData.trim();

      if (bluetoothData == "forward") {
        moveForward();
      } else if (bluetoothData == "stop") {
        stopMovement();
      } else if (bluetoothData == "backward") {
        moveBackward();
      } else if (bluetoothData == "rahat") {
        Rahat();
      } else if (bluetoothData == "hazir") {
        hazirol();
      } else if (bluetoothData == "yuru") {
        walk();
        delay(100);
        walk();
        delay(100);
        walk();
        delay(100);
        walk();
        delay(100);
      }
      else if (bluetoothData == "sag") {
        sagaDon();
      }
      else if (bluetoothData == "sol") {
        solaDon();
      }
      else if (bluetoothData == "dans") {
        dance();
      }
      else if (bluetoothData == "geri") {
        GeriYuru();
        delay(100);
        GeriYuru();
        delay(100);
        GeriYuru();
        delay(100);
        GeriYuru();
        delay(100);
      }

      // Komut işlendi, buffer sıfırla
      bluetoothData = "";
    }
  }

  // Ana döngü devam eder
}

void moveForward() {
  // İleri hareket için temel fonksiyon
  servo1.write(60);
  servo2.write(120);
  servo3.write(40);
  servo4.write(135);
  delay(500);
  stopMovement();
}

void moveBackward() {
  // Geri hareket için temel fonksiyon
  servo1.write(120);
  servo2.write(60);
  servo3.write(135);
  servo4.write(40);
  delay(500);
  stopMovement();
}

void stopMovement() {
  // Tüm motorları durdur
  servo1.write(85);
  servo2.write(90);
  servo3.write(85);
  servo4.write(90);
}

void Rahat() {
    servo3.write(40);
    servo4.write(135);
    delay(1500);

}
void hazirol() {
    servo3.write(90);
    servo4.write(90);
    delay(1500);

}
void walk() {
  // Sağ adım
  servo1.write(60);  // Sağ ayağı kaldır
  servo2.write(70); // Sağ bacağı ileri at
  delay(250);
  servo3.write(70);  // Sağ ayağı indir
  servo4.write(65);
  delay(250);

  servo1.write(110);  // Sağ ayağı kaldır
  servo2.write(120); // Sağ bacağı ileri at
  delay(250);
  servo3.write(110);  // Sağ ayağı indir
  servo4.write(105);
  delay(250);  
  
  // Tekrar başlangıç pozisyonuna dön
  stopMovement();
}

void sagaDon(){

  servo3.write(65);
  servo4.write(65);
  delay(250);

  servo1.write(0);  
  servo2.write(0);
  delay(250);

  servo1.write(85);
  servo2.write(95);
  servo3.write(85);
  servo4.write(80);
}
void solaDon(){

  servo4.write(100);
  servo3.write(105);
  delay(250);

  servo2.write(180);
  servo1.write(180);  
  delay(250);

  servo1.write(85);
  servo2.write(95);
  servo3.write(85);
  servo4.write(80);
}

void dance() {
    // Happy Birthday Melodisi eşliğinde dans
    for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
        // Notanın süresini hesapla
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(13, melody[thisNote], noteDuration);

        // Notalar arasında bir hareket ekleyin
        if (thisNote % 4 == 0) {
            // Sağ adım hareketi
            servo1.write(60);  // Sağ bacağı kaldır
            servo2.write(120); // Sol bacağı indir
            servo3.write(40);  // Sağ ayağı kaldır
            servo4.write(135); // Sol ayağı indir
        } else if (thisNote % 4 == 1) {
            // Sol adım hareketi
            servo1.write(120); // Sağ bacağı indir
            servo2.write(60);  // Sol bacağı kaldır
            servo3.write(135); // Sağ ayağı indir
            servo4.write(40);  // Sol ayağı kaldır
        } else if (thisNote % 4 == 2) {
            // Twist hareketi
            servo1.write(70);
            servo2.write(110);
            delay(100);
            servo1.write(110);
            servo2.write(70);
        } else if (thisNote % 4 == 3) {
            // Dalga hareketi
            servo3.write(40);
            servo4.write(135);
            delay(100);
            servo3.write(135);
            servo4.write(40);
        }

        // Notalar arasında boşluk bırak
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        // Sesi kapat
        noTone(13);
    }

    // Dans bitince motorları durdur
    stopMovement();
}

void GeriYuru() {
  // Sol adım geri
  servo2.write(120);  // Sol bacak yukarı
  servo4.write(110);  // Sol ayak yukarı
  delay(250);
  servo2.write(80);   // Sol bacak geri
  servo4.write(85);   // Sol ayak indir
  delay(250);

  // Sağ adım geri
  servo1.write(50);   // Sağ bacak yukarı
  servo3.write(40);   // Sağ ayak yukarı
  delay(250);
  servo1.write(90);   // Sağ bacak geri
  servo3.write(85);   // Sağ ayak indir
  delay(250);

  // Tekrar başlangıç pozisyonuna dön
  stopMovement();
}




