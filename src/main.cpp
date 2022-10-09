
#include <Arduino.h>
#include <AFMotor.h>

#define TURN_LEFT 'l'
#define TURN_RIGHT 'r'
#define GO_FORWARD 'f'
#define GO_BACKWARD 'b'
#define START 'o'
#define STOP 's'
#define LIGHT 'g'
#define TURBO 't'

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
void turbina_motores();
void vai();

bool statusFarol = true;

int current_velocity = VELOCITY;
bool turbo_mode = false;
bool forward_direction = true;
int turn_delay = 2000;
int turn_velocity() { return current_velocity / 2; }

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
      if (forward_direction)
        virar_para_esquerda();
      else
        virar_para_direita();
      break;
    case TURN_RIGHT:
      if (forward_direction)
        virar_para_direita();
      else
        virar_para_esquerda();
      break;
    case LIGHT:
      digitalWrite(A0, statusFarol ? HIGH : LOW);
      statusFarol = !statusFarol;
      break;
    case TURBO:
      turbina_motores();
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
  forward_direction = true;
  motor3.setSpeed(current_velocity);
  motor4.setSpeed(current_velocity);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void anda_para_tras()
{
  forward_direction = false;
  motor3.setSpeed(current_velocity);
  motor4.setSpeed(current_velocity);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void virar_para_esquerda()
{
  motor3.setSpeed(current_velocity);
  motor4.setSpeed(current_velocity - turn_velocity());
  motor3.run(forward_direction ? FORWARD : BACKWARD);
  motor4.run(forward_direction ? FORWARD : BACKWARD);

  delay(turn_delay);
  vai();
}

void virar_para_direita()
{
  motor3.setSpeed(current_velocity - turn_velocity());
  motor4.setSpeed(current_velocity);
  motor3.run(forward_direction ? FORWARD : BACKWARD);
  motor4.run(forward_direction ? FORWARD : BACKWARD);

  delay(turn_delay);
  vai();
}

void turbina_motores()
{
  turbo_mode = !turbo_mode;

  if (!turbo_mode)
  {
    current_velocity = VELOCITY;
    vai();
    return;
  }

  current_velocity = 255;
  vai();
}

void vai()
{
  if (forward_direction)
    anda_para_frente();
  else
    anda_para_tras();
}