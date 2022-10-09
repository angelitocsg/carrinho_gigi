
#include <Arduino.h>
#include <AFMotor.h>

#define TURN_LEFT 'l'
#define TURN_RIGHT 'r'
#define GO_FORWARD 'f'
#define GO_BACKWARD 'b'
#define START 'o'
#define STOP 's'
#define LIGHT 'g'

#define VELOCITY 150

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup_bluetooth();
void liga_motores();
void desliga_motores();
void anda_para_frente();
void anda_para_tras();
void pisca_led();
void virar_para_esquerda();
void virar_para_direita();

bool statusFarol = true;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, OUTPUT);
  setup_bluetooth();
  pisca_led();
  digitalWrite(A0, HIGH);
}

void loop()
{
  while (Serial.available())
  {
    // desliga_motores();
    char c = (char)Serial.read();

    switch (c)
    {
    case START:
      liga_motores();
      break;
    case STOP:
      desliga_motores();
      break;
    case GO_FORWARD:
      anda_para_frente();
      break;
    case GO_BACKWARD:
      anda_para_tras();
      break;
    case TURN_LEFT:
      virar_para_esquerda();
      break;
    case TURN_RIGHT:
      virar_para_direita();
      break;
    case LIGHT:
      digitalWrite(A0, statusFarol ? HIGH : LOW);
      statusFarol = !statusFarol;
      break;
    default:
      desliga_motores();
      break;
    }
  }
}

void setup_bluetooth()
{
  Serial.begin(9600);
  // Serial.println("Configurando...");
  // Serial.write("AT+");
  // delay(1000);
  // Serial.write("AT+NAMEGIGICAR");
  // delay(1000);
  // Serial.write("AT+PIN1234");
  // delay(1000);
}

void pisca_led()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

void liga_motores()
{
  // pisca_led();
  motor3.setSpeed(50);
  motor4.setSpeed(50);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  // delay(200);
}

void desliga_motores()
{
  // pisca_led();
  liga_motores();
  delay(2000);
}

void anda_para_frente()
{
  motor3.setSpeed(VELOCITY);
  motor4.setSpeed(VELOCITY);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void anda_para_tras()
{
  motor3.setSpeed(VELOCITY);
  motor4.setSpeed(VELOCITY);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void virar_para_esquerda()
{
  motor3.setSpeed(VELOCITY);
  motor4.setSpeed(VELOCITY - 50);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void virar_para_direita()
{
  motor3.setSpeed(VELOCITY - 50);
  motor4.setSpeed(VELOCITY);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}