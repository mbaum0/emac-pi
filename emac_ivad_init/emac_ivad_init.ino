/**
 * emac_ivad_init
 * 
 * This sketch initializes the IVAD (CRT display controller) board on
 * an Apple eMac
 * 
 * Adapted from https://github.com/qbancoffee/emac_ivad_board_init
 * 
 * The circuit requires the following connections:
 *    IVAD          Arduino
 *    ---------------------
 *     DDE Clock  => SCL
 *     DDE Data   => SDA
 *     Ground     => Ground
 * 
 * Created 4/7/2020
 * By Michael Baumgarten
 */
#include <Wire.h>

int horizontalPos = 0xcc;
int horizontalSize = 0x86;
int verticalPos = 0x37;
int verticalSize = 0xbc;

int greenBacklight = 0xff;
int blueBacklight = 0xff;
int redBacklight = 0xff;

int contrast = 0x80;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
}

byte x = 0;

void loop() {
  initIvadBoard();
  adjustDisplay();
  changeValue();
  for(;;){}
}


void writeToIvad(int address, int message) {
  Wire.beginTransmission(address);
  Wire.write(message);
  Wire.endTransmission();

}//end method

void writeToIvad(int address, int message1, int message2) {
  Wire.beginTransmission(address);
  Wire.write(message1);
  Wire.write(message2);
  Wire.endTransmission();

}//end method

void  readFromIvad(int address, int bytes) {
  char buf[bytes + 1];
  int bytesRead = 0;
  Wire.requestFrom(address, bytes);
  while (Wire.available())
  {
    char c = Wire.read();
    buf[bytesRead++] = c;
  }
  buf[bytesRead] = '\0';
  //return buf;


}//end method

void changeValue() {
  char rx_byte = 0;
  while(1) {
    if (Serial.available() > 0) {
      rx_byte = Serial.read();
      Serial.println(rx_byte);
      
      if (rx_byte == '1')
      {
        horizontalSize -= 1;
      } else if (rx_byte == '2') {
        horizontalSize += 1;
      } else if (rx_byte == '3')
      {
        horizontalPos += 1;
      } else if (rx_byte == '4') {
        horizontalPos -= 1;
      } else if (rx_byte == '5') {
        verticalSize -=1;
      } else if (rx_byte == '6') {
        verticalSize +=1;
      } else if (rx_byte == '7') {
        verticalPos -=1;
      } else if (rx_byte == '8') {
        verticalPos +=1;
      } else if (rx_byte == 'g') {
        greenBacklight -= 1;
      } else if (rx_byte == 'G') {
        greenBacklight += 1;
      } else if (rx_byte == 'b') {
        blueBacklight -= 1;
      } else if (rx_byte == 'B') {
        blueBacklight += 1;
      } else if (rx_byte == 'r') {
        redBacklight -= 1;
      } else if (rx_byte == 'R') {
        redBacklight += 1;
      } else if (rx_byte == 'c') {
        contrast -= 1;
      } else if (rx_byte == 'C') {
        contrast += 1;
      }
      
      ivadCmd(0x0D, horizontalSize);
      ivadCmd(0x07, horizontalPos);
      ivadCmd(0x08, verticalSize);
      ivadCmd(0x09, verticalPos);

      ivadCmd(0x01, greenBacklight);
      ivadCmd(0x02, blueBacklight);
      ivadCmd(0x03, redBacklight);

      ivadCmd(0x00, contrast);
      
      Serial.print("H-size: 0x");
      Serial.print(horizontalSize, HEX);
      Serial.print(" H-pos: 0x");
      Serial.print(horizontalPos, HEX);
      Serial.print("\r\n");
      
      Serial.print("V-size: 0x");
      Serial.print(verticalSize, HEX);
      Serial.print(" V-pos: 0x");
      Serial.print(verticalPos, HEX);
      Serial.print("\r\n");

      Serial.print("g-backlight: 0x");
      Serial.print(greenBacklight, HEX);
      Serial.print(" b-backlight: 0x");
      Serial.print(blueBacklight, HEX);
      Serial.print(" r-backlight: 0x");
      Serial.print(redBacklight, HEX);
      Serial.print("\r\n");
      
      Serial.print(" contrast: 0x");
      Serial.print(contrast, HEX);
      Serial.print("\r\n");

      
      Serial.print("\r\n");
    }
  }
}

void adjustDisplay() {
  ivadCmd(0x08, verticalSize); // vertical size
  ivadCmd(0x09, verticalPos);  // veritcal position
  ivadCmd(0x0D, horizontalSize); // horizontal size
  ivadCmd(0x07, horizontalPos);  // horizontal position

  //ivadCmd(0x01, greenBacklight);
  //ivadCmd(0x02, blueBacklight);
  //ivadCmd(0x03, redBacklight);

  //ivadCmd(0x00, contrast);
  
}

void ivadCmd(int cmd, int value) {
  writeToIvad(70, cmd, value);
}

void initIvadBoard() {

  for (int j = 0 ; j < 1 ; j++) {


    writeToIvad(70, 0 , 0);

    for (int i = 0 ; i <= 100 ; i += 10) {
      writeToIvad(83, i);
      readFromIvad(83, 10);

    }//end for
   
    writeToIvad(70, 0x01 , 0xAE);
    writeToIvad(70, 0x02 , 0xAA);
    writeToIvad(70, 0x03 , 0xB6);
    writeToIvad(70, 0x04 , 0xBF);
    writeToIvad(70, 0x05 , 0xBC);
    writeToIvad(70, 0x06 , 0x3B);
    writeToIvad(70, 0x07 , 0xCE);
    writeToIvad(70, 0x08 , 0xB9);
    writeToIvad(70, 0x09 , 0xB3);
    writeToIvad(70, 0x0A , 0x96);
    writeToIvad(70, 0x0B , 0xD3);
    writeToIvad(70, 0x0C , 0xDB);
    writeToIvad(70, 0x0D , 0x1A);
    writeToIvad(70, 0x0E , 0xC5);
    writeToIvad(70, 0x0F , 0xC2);
    writeToIvad(70, 0x10 , 0x8A);
    writeToIvad(70, 0x11 , 0x0B);
    writeToIvad(70, 0x12 , 0x46);
    writeToIvad(70, 0x14 , 0x37);
    writeToIvad(70, 0x15 , 0x43);
    writeToIvad(76, 0x00 , 0xD4);
    writeToIvad(76, 0x01 , 0xCE);
    writeToIvad(76, 0x02 , 0xCE);
    writeToIvad(76, 0x03 , 0x9D);
    writeToIvad(70, 0x00 , 0xFF);

  }
}
