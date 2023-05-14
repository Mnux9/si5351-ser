#include "si5351.h"

Si5351 si5351;


int long out = 2500000000;
String fset = "25000000";

//Serial stuff
static String buffer;

void setup() {
  Serial.begin(9600);

  //si5351 connection info
  bool i2c_found;
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  
  if(!i2c_found) {
    Serial.println("Device not found on I2C bus!");
  }

  //set the correction factor
  si5351.set_correction(132800, SI5351_PLL_INPUT_XO);
  
  //set the initial frequency output
  si5351.set_freq(2500000000ULL, SI5351_CLK0);

  //serial ui
  Serial.println(":3333333333333333333333");
  Serial.println("---------INIT----------");
  Serial.println("INITIALIZED SI5351 WITH:");
  Serial.println("Correcetion factor: 132800");
  Serial.print("OUT frequency: ");
  Serial.println(fset);
  Serial.println("-----------------------");
  Serial.println("");
  Serial.println("Enter a frequency in Hz:");
  Serial.println("");
}

void loop() {

   while (Serial.available() > 0) {
        char rx = Serial.read();
        buffer += rx;
        if (rx != '\n') { // THIS IS IMPORTANT!!! -M
            continue;
        }
        buffer.trim();
        
        if (buffer.startsWith("F")) {
            fset = buffer.substring(1,20);
            Serial.print("Output frequency set to: ");
            Serial.println(fset);
            out = strtoul(fset.c_str(), NULL, 10);
            si5351.set_freq(out * 100ULL, SI5351_CLK0);
        }
        
      buffer = "";

      Serial.println(out);


    }

   
}
