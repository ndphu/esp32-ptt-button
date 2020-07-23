#include <Arduino.h>
#include <BleKeyboard.h>

#define BUTTON_PIN 15

BleKeyboard bleKeyboard;
bool isPressed = false;

void setup()
{
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  char *bleName = new char[32];
  uint64_t chipid = ESP.getEfuseMac();
  sprintf(bleName, "ESP32-%04X", (uint32_t)(chipid >> 32));
  bleKeyboard.deviceName = bleName;
  bleKeyboard.deviceManufacturer = "DYI Products";
  bleKeyboard.begin();
}
void loop()
{
  if (bleKeyboard.isConnected())
  {    
    if (digitalRead(BUTTON_PIN) == LOW) {
      if (isPressed) {
       // pressed. do nothing        
      } else {
        Serial.println("Press button");
        bleKeyboard.press(KEY_RIGHT_CTRL);
        isPressed = true;
      }
    } else {
      if (isPressed) {
        // release
        Serial.println("Release button");
        bleKeyboard.release(KEY_RIGHT_CTRL);
        isPressed = false;
      } else {
        // not pressed. do nothing
      }
    }
  }
  delay(100);
}