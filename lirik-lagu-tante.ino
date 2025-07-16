#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

struct TeksBeat {
  String atas;
  String bawah;
  int delayKata1;
  int delayKata2;
};

TeksBeat data[] = {
  {"","",800,0},
  {"Tante...", "", 2100, 0},
  {"Sudah", "terbiasa", 600, 1100},
  {"terjadi", "tante...", 800, 1000},
  {"teman", "datang", 700, 400},
  {"ketika", "lagi", 800, 400},
  {"butuh", "saja...", 500, 1000},
  {"coba", "kalau", 1100, 400},
  {"lagi", "susah...", 500, 900},
  {"mereka", "semua", 1600, 300},
  {"menghilang...^_^", "last", 1700, 200}
};

const int JUMLAH_INDEX = sizeof(data) / sizeof(data[0]);

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
}

void loop() {
  for (int i = 0; i < JUMLAH_INDEX; i++) {
    lcd.clear();

    // Tampilkan baris atas
    int posAtas = (16 - data[i].atas.length()) / 2;
    lcd.setCursor(posAtas, 0);
    lcd.print(data[i].atas);
    delay(data[i].delayKata1);

    // Khusus index terakhir -> running text di baris 1
    if (i == JUMLAH_INDEX - 1 && data[i].bawah == "last") {
      String scrollText = "Apakah spek standar seperti ini yang para pemirsa inginkan?";
      for (int j = 0; j <= scrollText.length(); j++) {
        String window = scrollText.substring(j, j + 16);
        lcd.setCursor(0, 1);
        lcd.print(window);

        delay(200);
      }
    } else {
      // Tampilkan baris bawah jika ada
      if (data[i].bawah != "") {
        int posBawah = (16 - data[i].bawah.length()) / 2;
        lcd.setCursor(posBawah, 1);
        lcd.print(data[i].bawah);
      }
      delay(data[i].delayKata2);
    }
  }

  delay(3000); // jeda sebelum ulang
}
