char data; // Biến để lưu dữ liệu nhận từ Bluetooth
int IR1 = A0; // Cảm biến IR bên trái
int IR2 = A1; // Cảm biến IR bên phải
/////////////////////////////////
bool obstacleDetected = false; // Biến trạng thái vật cản
//////////////////////////////
//#include "Arduino.h"
#include <FastLED.h>
#define LeftSignal 3 // Left Blinker Signal Connection
#define RightSignal 12 // Right Blinker Signal Connection
#define MidSignal 8 // Reverse Signal Connection

#define NUM_LEDS 8 // Total no of LEDs in the LED strip
CRGB midleds[NUM_LEDS];
CRGB rightleds[NUM_LEDS];
CRGB leftleds[NUM_LEDS]; // Mảng lưu dữ liệu LED
int BlinkerSpeed = 35; // Blinker Running LED Speed. Adjust this to match with your bike blinker speed.



//viral science
//Ultrasonic Distance alarm
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

// defines variables
long duration;
int distance;
int safetyDistance;
int light;

void setup() {
  Serial.begin(9600); // Khởi tạo giao tiếp Serial với tốc độ 9600 baud

  // Đặt các chân điều khiển động cơ làm đầu ra
  pinMode(7, OUTPUT); // Motor 1
  pinMode(6, OUTPUT); // Motor 1
  pinMode(5, OUTPUT); // Motor 2
  pinMode(4, OUTPUT); // Motor 2
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // Starts the serial communication
  // Đặt các chân cảm biến IR làm đầu vào
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  ///////////////////////// xi nhan
  FastLED.addLeds<WS2812B, LeftSignal, GRB>(leftleds, NUM_LEDS);
  FastLED.addLeds<WS2812B, RightSignal, GRB>(rightleds, NUM_LEDS);
  FastLED.addLeds<WS2812B, MidSignal, GRB>(midleds, NUM_LEDS);
  FastLED.clear();
  pinMode(MidSignal, OUTPUT);
  pinMode(LeftSignal, OUTPUT);
  pinMode(RightSignal, OUTPUT);
}

void loop() {
  /////////////////xi nhan
  if(light==1) {
    FastLED.clear();
    setDefaultLights();
  } else if(light==2){
    FastLED.clear();
    setReverseLights();
  }
  else if(light==3){
    FastLED.clear();
    setLeftBlinker();
  }
  else if(light==4){
    FastLED.clear();
    setRightBlinker();
  }
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 10 ){ 
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
  setReverseLights();
    moveBackward();          
    delay(200);              
    stopMotors();            
    delay(200);   
}
else if (safetyDistance <= 20 ){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
}

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
  // Đọc tín hiệu từ cảm biến IR
  int irLeft = digitalRead(IR1);  // Đọc cảm biến bên trái
  int irRight = digitalRead(IR2); // Đọc cảm biến bên phải

  // Kiểm tra trạng thái cảm biến IR
  if ((irLeft == HIGH || irRight == HIGH) && !obstacleDetected) { 
    // Nếu phát hiện vật cản và trước đó chưa xử lý
    obstacleDetected = true; // Đánh dấu rằng đã phát hiện vật cản
    setReverseLights();
    moveBackward();          // Xe chạy lùi
    delay(500);              // Lùi trong 0.5 giây
    stopMotors();            // Sau đó dừng lại
    delay(500);              // Dừng trong 0.5 giây
  } 
  else if (irLeft == LOW && irRight == LOW) { 
    // Nếu không còn vật cản
    obstacleDetected = false; // Reset trạng thái vật cản
  }

  // Xử lý lệnh Bluetooth
  if (Serial.available() > 0 && !obstacleDetected) {
    data = Serial.read(); // Đọc dữ liệu từ Bluetooth

    // Điều khiển xe dựa trên dữ liệu nhận được
    switch (data) {
      case 'F': // Đi thẳng
        moveForward();
        light=1;
        break;
      case 'B': // Lùi
        moveBackward();
        light=2;
        break;
      case 'L': // Rẽ trái
        turnLeft();
        light=3;
        break;
      case 'R': // Rẽ phải
        turnRight();
        light=4;
        break;
      case 'S': // Dừng
        stopMotors();
        light=2;
        break;
       
    }
  }
        
        
}

// Hàm điều khiển xe đi thẳng
void moveForward() {
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
}

// Hàm điều khiển xe lùi
void moveBackward() {
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
}

// Hàm điều khiển xe rẽ trái
void turnLeft() {
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
}

// Hàm điều khiển xe rẽ phải
void turnRight() {
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
}

// Hàm dừng xe
void stopMotors() {
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
}

////////////////////////////////////////////////////

// Hàm bật đèn phanh
void setBrakeLights() {
  for (int i = 0; i < NUM_LEDS; i++) {
    midleds[i] = CRGB::Red; 
    leftleds[i] = CRGB::Red;
    rightleds[i] = CRGB::Red;
    // Màu đỏ cho đèn phanh
  }
  FastLED.show();
}

// Hàm điều khiển xi nhan trái
void setLeftBlinker() {
  static unsigned long lastUpdate = 0; // Lưu thời gian lần cập nhật cuối
  static bool ledState = false;       // Trạng thái bật/tắt LED

  if (millis() - lastUpdate >= BlinkerSpeed) { 
    lastUpdate = millis();            // Cập nhật thời gian hiện tại
    ledState = !ledState;             // Đổi trạng thái LED

    // Thay đổi màu LED theo trạng thái
    for (int i = 0; i < NUM_LEDS; i++) {
      leftleds[i] = ledState ? CRGB::Orange : CRGB::Black; // Bật cam hoặc tắt đen
    }
    FastLED.show(); // Hiển thị thay đổi
  }
}


// Hàm điều khiển xi nhan phải
void setRightBlinker() {
  static unsigned long lastUpdate = 0; // Lưu thời gian lần cập nhật cuối
  static bool ledState = false;       // Trạng thái bật/tắt LED

  if (millis() - lastUpdate >= BlinkerSpeed) { 
    lastUpdate = millis();            // Cập nhật thời gian hiện tại
    ledState = !ledState;             // Đổi trạng thái LED

    // Thay đổi màu LED theo trạng thái
    for (int i = 0; i < NUM_LEDS; i++) {
      rightleds[i] = ledState ? CRGB::Orange : CRGB::Black; // Bật cam hoặc tắt đen
    }
    FastLED.show(); // Hiển thị thay đổi
  }
}



// Hàm bật đèn lùi
void setReverseLights() {
  for (int i = 0; i < NUM_LEDS; i++) {
   midleds[i] = CRGB::Red; 
    leftleds[i] = CRGB::Red;
    rightleds[i] = CRGB::Red;
  }
  FastLED.show();
}
void setDefaultLights() {
  for(int i = 0; i < NUM_LEDS; i++) {
    midleds[i] = CRGB::Navy; // Set màu xanh nước biển đậm cho mảng midleds
    leftleds[i] = CRGB::Navy; // Set màu xanh nước biển đậm cho mảng leftleds
    rightleds[i] = CRGB::Navy; // Set màu xanh nước biển đậm cho mảng rightleds
  }
  FastLED.show();
}



