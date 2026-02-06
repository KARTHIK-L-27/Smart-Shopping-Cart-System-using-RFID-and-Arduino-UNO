#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int buzzer = 8;
int total = 0;

void setup() {
  SPI.begin();
  rfid.PCD_Init();
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);

  lcd.print("Smart Cart");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  // Demo: every product = ₹50
  total += 50;

  lcd.clear();
  lcd.print("Item Added");
  lcd.setCursor(0, 1);
  lcd.print("Total: Rs ");
  lcd.print(total);

  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);

  rfid.PICC_HaltA();
}
