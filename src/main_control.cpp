#ifdef FLAG_CONTROL

#include <Arduino.h>
#include <VirtualWire.h>

String message;
void send(char *message);

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  vw_set_tx_pin(12);
  vw_setup(1000); // Bits per sec
}

void loop()
{
  char data[1];

  data[0] = 'g';
  send(data);
  delay(100);
}

void send(char *message)
{
  Serial.println("Enviando...");
  Serial.println(message);
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Aguarda o envio de dados
}

#endif