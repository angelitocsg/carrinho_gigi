#ifdef FLAG_CAR

#include <Arduino.h>
#include <MyLights.h>
#include <MyMotors.h>
#include <MyReceiver.h>

MyMotors motors;
MyLights lights;
// MyReceiver receiver;
void do_action(char c);
byte message[VW_MAX_MESSAGE_LEN];
byte msgLength = VW_MAX_MESSAGE_LEN;

void setup_rf_rx()
{
  Serial.print("setup_rf_rx");
  vw_set_rx_pin(RX_PIN);
  vw_setup(1000);
  vw_rx_start();
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando...");
  pinMode(A5, OUTPUT);

  setup_rf_rx();
}

void loop()
{
  uint8_t message[VW_MAX_MESSAGE_LEN];
  uint8_t msgLength = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(message, &msgLength))
  {
    Serial.println(message[0]);
    Serial.println(msgLength);
    if (msgLength == 1)
    {
      do_action(message[0]);
      setup_rf_rx();
    }
  }

  while (Serial.available())
  {
    char c = (char)Serial.read();
    do_action(c);
    setup_rf_rx();
  }
}

void do_action(char c)
{
  Serial.println("Action: ");
  Serial.println(c);
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

#endif