// Codigo DanBot funcionando modo basico e usando servo 
// Codigo pronto! completo e funcionando!!!!!
// O aplicativo no smartphone é arduino car/tank

#include <SoftwareSerial.h>
#include <Servo.h>

// Define os pinos para o módulo Bluetooth HC-05
SoftwareSerial bluetooth(2, 3);

// Define os pinos para o driver de ponte H MX1508
int motor1Dir1 = 8;
int motor1Dir2 = 11;
int motor1Speed = 7;
int motor2Dir1 = 4;
int motor2Dir2 = 5;
int motor2Speed = 6;

// Define o pino para o servo motor
Servo myservo;
int servoPin = 10;

//// Leds da Sirene
int ledPin1 = 9; // define o pino do primeiro LED
int ledState1 = LOW; // variável para armazenar o estado do primeiro LED
int ledPin2 = 12; // define o pino do segundo LED
int ledState2 = LOW; // variável para armazenar o estado do segundo LED
long interval1 = 800; // intervalo de tempo para piscar o primeiro LED
long interval2 = 400; // intervalo de tempo para piscar o segundo LED
boolean ledsOn = false; 

////

void setup() {
  // Inicializa a comunicação serial para o módulo Bluetooth
  bluetooth.begin(9600);
  // Configura os pinos do driver de ponte H como saída
  pinMode(motor1Dir1, OUTPUT);
  pinMode(motor1Dir2, OUTPUT);
  pinMode(motor1Speed, OUTPUT);
  pinMode(motor2Dir1, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);
  pinMode(motor2Speed, OUTPUT);
  // Inicializa o servo motor
  myservo.attach(servoPin);
  myservo.write(1);

  pinMode(ledPin1, OUTPUT); // configura o pino do primeiro LED como saída
  pinMode(ledPin2, OUTPUT);
 
}

void loop() {
  // Verifica se há dados disponíveis no módulo Bluetooth
  while (bluetooth.available() > 0) {
    // Lê o dado recebido
    char comando = (char)bluetooth.read();
    // Executa o comando de acordo com o valor recebido
    if (comando == '9') {
      // Gira o servo para 0 graus
      myservo.write(4);
    } else if (comando == '8') {
      // Gira o servo para 90 graus
      myservo.write(8);
    } else if (comando == '7') {
      // Gira o servo para 180 graus
      myservo.write(12);
    } else if (comando == '6') {
      // Gira o servo para 90 graus
      myservo.write(18);
    } else if (comando == '5') {
      // Gira o servo para 180 graus
      myservo.write(25);
    }  else if (comando == '4') {
      // Gira o servo para 90 graus
      myservo.write(35);
    } else if (comando == '3') {
      // Gira o servo para 180 graus
      myservo.write(39);
    } else if (comando == '2') {
      // Gira o servo para 90 graus
      myservo.write(42);
    } else if (comando == '1') {
      // Gira o servo para 180 graus
      myservo.write(47);
    
    }
  
    
    else if (comando == 'F') {
      // Move o motor 1 para frente
      digitalWrite(motor1Dir1, HIGH);
      digitalWrite(motor1Dir2, LOW);
      analogWrite(motor1Speed, 255);
      digitalWrite(motor2Dir1, HIGH);
      digitalWrite(motor2Dir2, LOW);
      analogWrite(motor2Speed, 255);
      
    } else if (comando == 'B') {
      // Move o motor 1 para trás
      digitalWrite(motor1Dir1, LOW);
      digitalWrite(motor1Dir2, HIGH);
      analogWrite(motor1Speed, 255);
      digitalWrite(motor2Dir1, LOW);
      digitalWrite(motor2Dir2, HIGH);
      analogWrite(motor2Speed, 255);
      
    } else if (comando == 'S') {
      // Para o motor 1
      digitalWrite(motor1Dir1, LOW);
      digitalWrite(motor1Dir2, LOW);
      analogWrite(motor1Speed, 0);
      digitalWrite(motor2Dir1, LOW);
      digitalWrite(motor2Dir2, LOW);
      analogWrite(motor2Speed, 0);
      
    } else if (comando == 'L') {
      // Move o motor 2 para frente
      digitalWrite(motor1Dir1, HIGH);
      digitalWrite(motor1Dir2, LOW);
      analogWrite(motor1Speed, 255);
      digitalWrite(motor2Dir1, LOW);
      digitalWrite(motor2Dir2, HIGH);
      analogWrite(motor2Speed, 255);
    } else if (comando == 'R') {
      // Move o motor 2 para trás
      digitalWrite(motor1Dir1, LOW);
      digitalWrite(motor1Dir2, HIGH);
      analogWrite(motor1Speed, 255);
      digitalWrite(motor2Dir1, HIGH);
      digitalWrite(motor2Dir2, LOW);
      analogWrite(motor2Speed, 255);
    }

 
    // verifica se o sinal indica que os LEDs devem ser ligados
    if (comando == 'W') {
      ledsOn = true; // marca os LEDs como ligados
      ledState1 = HIGH; // liga o primeiro LED
      ledState2 = LOW; // desliga o segundo LED
    }
    // verifica se o sinal indica que os LEDs devem ser desligados
    else if (comando == 'w') {
      ledsOn = false; // marca os LEDs como desligados
      ledState1 = LOW; // desliga o primeiro LED
      ledState2 = LOW; // desliga o segundo LED
    }
  }

  // faz os LEDs piscarem se estiverem ligados
  if (ledsOn == true) {
    unsigned long currentMillis = millis();
    static unsigned long previousMillis1 = currentMillis;
    static unsigned long previousMillis2 = currentMillis;
    if (currentMillis - previousMillis1 >= interval1) {
      previousMillis1 = currentMillis; // atualiza o tempo anterior do primeiro LED
      if (ledState1 == HIGH) {
        ledState1 = LOW;
        ledState2 = HIGH; // liga o segundo LED quando o primeiro é desligado
      } else {
        ledState1 = HIGH;
        ledState2 = LOW; // liga o primeiro LED quando o segundo é desligado
      }
    }
    if (currentMillis - previousMillis2 >= interval2) {
      previousMillis2 = currentMillis; // atualiza o tempo anterior do segundo LED
      if (ledState2 == HIGH) {
        ledState2 = LOW;
        ledState1 = HIGH; // liga o primeiro LED quando o segundo é desligado
      } else {
        ledState2 = HIGH;
        ledState1 = LOW; // liga o segundo LED quando o primeiro é desligado
      }
    }
  }
  
  digitalWrite(ledPin1, ledState1); // atualiza o estado do primeiro LED
  digitalWrite(ledPin2, ledState2); // atualiza o estado do segundo LED
}

     
