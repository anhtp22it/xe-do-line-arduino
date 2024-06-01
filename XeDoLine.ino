#define MOTOR_L_1 7
#define MOTOR_L_2 6
#define MOTOR_R_1 5
#define MOTOR_R_2 4

const uint8_t SENSORS_PIN[] = { A0, A1, A2, A3, A4 };

const uint8_t maxspeed = 180;
const uint8_t minspeed = 10;

const int HeSoLech = 13;
int GiaTriLech = 0;

void setup() { 
  pinMode(MOTOR_L_1, OUTPUT);
  pinMode(MOTOR_L_2, OUTPUT);
  pinMode(MOTOR_R_1, OUTPUT);
  pinMode(MOTOR_R_2, OUTPUT);

  digitalWrite(MOTOR_L_1, LOW);
  digitalWrite(MOTOR_L_2, LOW);
  digitalWrite(MOTOR_R_1, LOW);
  digitalWrite(MOTOR_R_2, LOW);

  for (auto sensorPin : SENSORS_PIN) {
    pinMode(sensorPin, INPUT);
  }
  Serial.begin(115200);
  delay(100);
}

bool stoped = 0;
void loop() {

  while (isRunning) {
    read_sensors();
    motor_control();
    delay(10);
  }
  digitalWrite(MOTOR_L_1, LOW);
  digitalWrite(MOTOR_L_2, LOW);
  digitalWrite(MOTOR_R_1, LOW);
  digitalWrite(MOTOR_R_2, LOW);
  while (1){
    
  }

}

void read_sensors() {
  String sensorArray = "";
  for (auto sensorPin : SENSORS_PIN) {
    sensorArray += (char)(digitalRead(sensorPin) + 48);
  }

  if (sensorArray == "00001") error = 5;
  else if (sensorArray == "00111") error = 4;
  else if (sensorArray == "00011") error = 3;
  else if (sensorArray == "00010") error = 2;
  else if (sensorArray == "00110") error = 1;
  else if (sensorArray == "00100") error = 0;
  else if (sensorArray == "01110") error = 0;
  else if (sensorArray == "01100") error = -1;
  else if (sensorArray == "01000") error = -2;
  else if (sensorArray == "11000") error = -3;
  else if (sensorArray == "11100") error = -4;
  else if (sensorArray == "10000") error = -5;
  else if (sensorArray == "00000"){ 
    if (error > 0) error = 6;
    else error = -6;
  }
   else if (sensorArray == "11111") { 
    isRunning = 0;
  }
}


void set_motor(int speedA, int speedB) {
  speedA = -speedA;

  if (speedA > 0){
    speedA = constrain(speedA, minspeed, maxspeed);
    digitalWrite(MOTOR_R_2, LOW);
    analogWrite(MOTOR_R_1, speedA);
  } else{
    speedA = constrain(speedA, -maxspeed, -minspeed);
    digitalWrite(MOTOR_R_2, HIGH);
    analogWrite(MOTOR_R_1,255 + speedA);
  }

  if (speedB > 0){
    speedB = constrain(speedB, minspeed, maxspeed);
    digitalWrite(MOTOR_L_1, LOW);
    analogWrite(MOTOR_L_2, speedB);
  } else{
    speedB = constrain(speedB, -maxspeed, -minspeed);
    digitalWrite(MOTOR_L_1, HIGH);
    analogWrite(MOTOR_L_2, 255 + speedB);
  }
}

void motor_control() {
  GiaTriLech = HeSoLech * error;
  
  if (error < 0) 
    set_motor(maxspeed , maxspeed + GiaTriLech);
  else 
    set_motor(maxspeed - GiaTriLech, maxspeed );
}


