#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;
VL53L1X sensor2;

void setup()
{

  pinMode(16, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(16, LOW);
  digitalWrite(14, LOW);

  delay(500);
  Wire.begin(4,5);


  Serial.begin (115200);

  pinMode(16, INPUT);
  delay(150);
  Serial.println("00");
  sensor.init(true);

  Serial.println("01");
  delay(100);
  sensor.setAddress(0x28);
  Serial.println("02");

  pinMode(14, INPUT);
  delay(150);
  sensor2.init(true);
  Serial.println("03");
  delay(100);
  sensor2.setAddress(0x31);
  Serial.println("04");

  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
  sensor2.setDistanceMode(VL53L1X::Long);
  sensor2.setMeasurementTimingBudget(50000);
  sensor2.startContinuous(50);
  sensor.setTimeout(100);
  sensor2.setTimeout(100);
  delay(150);
  Serial.println("addresses set");

  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;


  for (byte i = 1; i < 120; i++)
  {

    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
    } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");


}

void loop()
{

  Serial.print("Sensor1: ");
  Serial.print(sensor.read());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  //Serial.println();
  Serial.print("        Sensor2: ");
   Serial.print(sensor2.read());
  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
  

}
