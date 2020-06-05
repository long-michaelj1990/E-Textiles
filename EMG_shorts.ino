# include <Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050

// BT Data Logger
 // BlueTooth Configuration
 /* Include the software serial port library */
 #include <SoftwareSerial.h>
 /* to communicate with the Bluetooth module's TXD pin */
 #define BT_SERIAL_TX 10
 /* to communicate with the Bluetooth module's RXD pin */
 #define BT_SERIAL_RX 11
 /* Initialise the software serial port */
 SoftwareSerial BluetoothSerial(BT_SERIAL_TX, BT_SERIAL_RX);



long accelX, accelY, accelZ; // stores raw data
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gryoZ; //stores raw data
float rotX, rotY, rotZ;

int LED=12;

// the setup routine runs once when you press reset:
void setup() {
  Wire.begin();
  setupMPU();
  
  // initialize serial communication at 9600 bits per second:
 // Serial.begin(9600);
  BluetoothSerial.begin(9600); // Initialise BlueTooth
}
// the loop routine runs over and over again forever:
void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  delay (30);

  
    // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
    // print out the value you read:
  float voltage = sensorValue*(5.0/1023.0);
//Serial.print("Gryo (deg)");
//Serial.print(",");
//Serial.print(rotX);
//Serial.print(",");
//Serial.print(rotY);
//Serial.print(",");
//Serial.println(rotZ);
//Serial.print(",");
//Serial.print("Accel (g)");
//Serial.print(",");
//Serial.print(gForceX);
//Serial.print(",");
//Serial.println(gForceY);
//Serial.print(",");
// Serial.println(gForceZ); 

//Serial.print(sensorValue);
//Serial.print(",");
//Serial.print(rotY);
//Serial.print(";");
//Serial.print(gForceY);
//Serial.print("*");
//Serial.print(gForceZ);
//Serial.print("~");
//Serial.println(rotX);
//Serial.print("#");

BluetoothSerial.print(sensorValue);
BluetoothSerial.print(",");
BluetoothSerial.print(rotY);
BluetoothSerial.print(";");
BluetoothSerial.print(gForceY);
BluetoothSerial.print("*");
BluetoothSerial.print(gForceZ);
BluetoothSerial.print("~");
BluetoothSerial.println(rotX);
//BluetoothSerial.print("#");


  delay(1);        // delay in between reads for stability
if (sensorValue> 100){
digitalWrite (LED,HIGH);
}else{
  digitalWrite(LED,LOW);
}
}

void setupMPU (){

Wire.beginTransmission (MPU); //I2c adress of the MPU
Wire.write (0x6B); //gets MCU out of sleep mode (power_management) 
Wire.write (0b00000000);
Wire.endTransmission();
Wire.beginTransmission(MPU);
Wire.write (0x1B); //access reg 1B - gyro config
Wire.write(0x00000000); //set gyro to +/- 250 degrees
Wire.endTransmission();
Wire.beginTransmission(MPU); 
Wire.write (0x1C);
Wire.write (0b00011000); //Accel +/-16g
Wire.endTransmission();
}

void  recordAccelRegisters(){
  Wire.beginTransmission (MPU);
  Wire.write (0x3B);
  Wire.endTransmission();
  Wire.requestFrom (MPU,6);
while (Wire.available ()> 6);
accelX=Wire.read()<<8|Wire.read();//store 1st 2 bytes 
accelY=Wire.read()<<8|Wire.read();// store next 2 bytes
accelZ=Wire.read()<<8|Wire.read();// store next 2 bytes
  processAccelData();
}

void  processAccelData(){
gForceX=accelX/=2048.0; //amount if to have accel at +/- 16 g
gForceY=accelY/2048.0; //amount if to have accel at +/- 16 g
gForceZ=accelZ/2048.0; //amount if to have accel at +/- 16 g
}

void   recordGyroRegisters(){
  Wire.beginTransmission (MPU);
  Wire.write (0x43);
  Wire.endTransmission();
  Wire.requestFrom (MPU,6);
while (Wire.available ()> 6);
gyroX=Wire.read()<<8|Wire.read();//store 1st 2 bytes 
gyroY=Wire.read()<<8|Wire.read();// store next 2 bytes
gryoZ=Wire.read()<<8|Wire.read();// store next 2 bytes
  processGyroData();
}

void  processGyroData(){
rotX=gyroX/131.0;
rotY=gyroY/131.0;
rotZ=gryoZ/131.0;
}


