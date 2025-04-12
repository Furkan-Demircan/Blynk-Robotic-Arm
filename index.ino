#define BLYNK_TEMPLATE_ID "Template ID"
#define BLYNK_TEMPLATE_NAME "Your Template Name"
#define BLYNK_AUTH_TOKEN "Your Auth Token"   // E-posta ile gelen token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Wi-Fi Bilgileri
char ssid[] = "FurkanPc";       // Wi-Fi ağ adınız                                                 
char pass[] = "Eren1234";   // Wi-Fi şifreniz

BlynkTimer timer;
Servo myServo;

// Step Motor Pin Tanımlamaları
#define IN1_PIN D12
#define IN2_PIN D13
#define IN3_PIN D14
#define IN4_PIN D15
#define SERVO_PIN D0

#define IN1_PIN_2 D4
#define IN2_PIN_2 D5
#define IN3_PIN_2 D6
#define IN4_PIN_2 D7

// Elektromıknatıs Pin Tanımlaması
#define ELECTROMAGNET_PIN D1  // Elektromıknatıs bağlı pin

// Step Sıralamaları
const int steps[8][4] = {
  {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
  {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}
};

// Motor Parametreleri
int currentStep = 0, currentStep2 = 0;
float currentAngle = 0.0, currentAngle2 = 0.0;
float stepAngle = 0.0879;
int stepDelay = 4000;

void setup() {
  Serial.begin(115200);

  // Blynk ve Wi-Fi Bağlantısı
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Step Motor Pin Modları
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  pinMode(IN1_PIN_2, OUTPUT);
  pinMode(IN2_PIN_2, OUTPUT);
  pinMode(IN3_PIN_2, OUTPUT);
  pinMode(IN4_PIN_2, OUTPUT);

  // Elektromıknatıs Pin Modu
  pinMode(ELECTROMAGNET_PIN, OUTPUT);
  digitalWrite(ELECTROMAGNET_PIN, LOW); // Başlangıçta kapalı

  // Servo Motor Başlat
  myServo.attach(SERVO_PIN);
  myServo.write(0);

  Serial.println("Blynk ile Step Motor, Servo ve Elektromıknatıs Kontrolü Başladı!");
}

void loop() {
  Blynk.run();
  timer.run();
}

// Step Motor 1 Kontrol
BLYNK_WRITE(V1) {  // Blynk uygulamasında V1 için düğme
  float targetAngle = param.asFloat();
  moveStepMotor(targetAngle, currentAngle, currentStep, true);
}

// Step Motor 2 Kontrol
BLYNK_WRITE(V2) {  // Blynk uygulamasında V2 için düğme
  float targetAngle = param.asFloat();
  moveStepMotor(targetAngle, currentAngle2, currentStep2, false);
}

// Servo Motor Kontrol
BLYNK_WRITE(V3) {  // Blynk uygulamasında V3 için slider
  int angle = param.asInt();
  myServo.write(constrain(angle, 0, 180));
  Serial.print("Servo açısı: ");
  Serial.println(angle);
}

// Elektromıknatıs Kontrol
BLYNK_WRITE(V4) {  // Blynk uygulamasında V4 için düğme
  int state = param.asInt();
  if (state == 1) {
    digitalWrite(ELECTROMAGNET_PIN, HIGH); // Elektromıknatısı aktif et
    Serial.println("Elektromıknatıs Açık");
  } else {
    digitalWrite(ELECTROMAGNET_PIN, LOW); // Elektromıknatısı kapat
    Serial.println("Elektromıknatıs Kapalı");
  }
}

void moveStepMotor(float targetAngle, float &currentAngle, int &currentStep, bool motor1) {
  float angleDifference = targetAngle - currentAngle;
  int stepsToMove = abs(angleDifference / stepAngle);
  bool clockwise = angleDifference > 0;

  for (int i = 0; i < stepsToMove; i++) {
    if (clockwise) {
      currentStep = (currentStep + 1) % 8;
    } else {
      currentStep = (currentStep - 1 + 8) % 8;
    }

    if (motor1) {
      setStep1(currentStep);
    } else {
      setStep2(currentStep);
    }

    delayMicroseconds(stepDelay);
  }

  currentAngle = targetAngle;
  Serial.print(motor1 ? "Motor 1 açısı: " : "Motor 2 açısı: ");
  Serial.println(currentAngle);
}

void setStep1(int step) {
  digitalWrite(IN1_PIN, steps[step][0]);
  digitalWrite(IN2_PIN, steps[step][1]);
  digitalWrite(IN3_PIN, steps[step][2]);
  digitalWrite(IN4_PIN, steps[step][3]);
}

void setStep2(int step) {
  digitalWrite(IN1_PIN_2, steps[step][0]);
  digitalWrite(IN2_PIN_2, steps[step][1]);
  digitalWrite(IN3_PIN_2, steps[step][2]);
  digitalWrite(IN4_PIN_2, steps[step][3]);
}
