#include <Arduino.h>
#include <MyLights.h>
#include <MyMotors.h>

MyMotors motors;
MyLights lights;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A5, OUTPUT);
}

void loop()
{
  while (Serial.available())
  {
    char c = (char)Serial.read();

    switch (c)
    {
    case START:
      lights.acende_farol();
      motors.liga_motores();
      break;
    case STOP:
      lights.apaga_farol();
      motors.desliga_motores();
      break;
    case GO_FORWARD:
      lights.acende_farol();
      motors.anda_para_frente();
      break;
    case GO_BACKWARD:
      lights.apaga_farol();
      motors.anda_para_tras();
      break;
    case TURN_LEFT:
      if (motors.esta_indo_para_frente())
        motors.virar_para_esquerda();
      else
        motors.virar_para_direita();
      break;
    case TURN_RIGHT:
      if (motors.esta_indo_para_frente())
        motors.virar_para_direita();
      else
        motors.virar_para_esquerda();
      break;
    case LIGHT:
      if (lights.obter_status_farol())
        lights.apaga_farol();
      else
        lights.acende_farol();
      break;
    case TURBO:
      motors.turbina_motores();
      break;
    default:
      motors.desliga_motores();
      break;
    }
  }
}

void change_bt_settings()
{
  Serial.println("Setting...");
  Serial.write("AT+");
  delay(1000);
  Serial.write("AT+NAMEGIGICAR");
  delay(1000);
  Serial.write("AT+PIN1234");
  delay(1000);
}
