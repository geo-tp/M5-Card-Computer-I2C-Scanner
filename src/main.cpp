#include <Arduino.h>
#include <M5Cardputer.h> // Include the M5Cardputer library
#include <Wire.h>

std::vector<byte> i2cAddresses; // Tableau pour stocker les adresses I2C détectées

void setup()
{
  auto cfg = M5.config(); // Get the M5 configuration
  M5.begin(cfg); // Initialize the M5
  M5.Power.begin(); // Initialize the M5 power

  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(1);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(55, 60);
  M5.Lcd.printf("I2C Scanner\n");

  delay(1000); // Delay to show the initial message

  Wire.begin();
}

void loop()
{
  byte error, address;
  int nDevices;
  
  i2cAddresses.clear(); // Erase previous adresses
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(60, 40);
  M5.Lcd.println("Loading...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmission to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    M5.Lcd.clear();
    M5.Lcd.setCursor(100, 80);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print(address);

    if (error == 0)
    {
      if (address < 16)
          M5.Lcd.print("0");

      i2cAddresses.push_back(address); // add adsress
      nDevices++;
    }
    else if (error == 4)
    {
      M5.Lcd.print("Error at address 0x");

      if (address < 16)
        M5.Lcd.print("0");

      M5.Lcd.println(address, HEX);
    }
  }

  M5.Lcd.setCursor(35, 10);
  if (nDevices == 0)
    M5.Lcd.println("No I2C devices\n");
  else
    {
        M5.Lcd.clear();
        M5.Lcd.printf("%d I2C devices\n", nDevices);
        M5.Lcd.println("");
        
        for (byte addr : i2cAddresses)
        {
            M5.Lcd.print("0x");
            if (addr < 16)
                M5.Lcd.print("0");
            M5.Lcd.println(addr, HEX);
        }
    }
  delay(8000); // wait 8 seconds for next scan
}
