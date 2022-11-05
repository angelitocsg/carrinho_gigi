#ifdef FLAG_CONTROL

#include <Arduino.h>
#include <VirtualWire.h>
#include <PSX.h>

#define rfPinTX 9

#define dataPin 10  // Brown wire
#define cmdPin 11   // Orange wire
#define attPin 12   // Yellow wire
#define clockPin 13 // Blue wire

#define TURN_LEFT "l"
#define TURN_RIGHT "r"
#define GO_FORWARD "f"
#define GO_BACKWARD "b"
#define START "o"
#define STOP "s"
#define LIGHT "g"
#define TURBO "t"

PSX psx;
PSX::PSXDATA PSXdata;
int PSXerror;

String message;
void send(const char *message);

void setup_psx()
{
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_DIGITAL);
}

void setup()
{
  vw_set_tx_pin(rfPinTX);
  vw_setup(1000);

  setup_psx();

  Serial.begin(9600);
}

void loop()
{
  PSXerror = psx.read(PSXdata);
  message = "";

  if (PSXerror == PSXERROR_SUCCESS)
  {
    if (PSXdata.buttons & PSXBTN_LEFT)
      message = TURN_LEFT;

    if (PSXdata.buttons & PSXBTN_DOWN)
      message = GO_BACKWARD;

    if (PSXdata.buttons & PSXBTN_RIGHT)
      message = TURN_RIGHT;

    if (PSXdata.buttons & PSXBTN_UP)
      message = GO_FORWARD;

    if (PSXdata.buttons & PSXBTN_START)
      message = START;

    if (PSXdata.buttons & PSXBTN_SELECT)
      message = STOP;

    if (PSXdata.buttons & PSXBTN_SQUARE)
      message = TURN_LEFT;

    if (PSXdata.buttons & PSXBTN_CROSS)
      message = GO_BACKWARD;

    if (PSXdata.buttons & PSXBTN_CIRCLE)
      message = TURN_RIGHT;

    if (PSXdata.buttons & PSXBTN_TRIANGLE)
      message = GO_FORWARD;

    if (PSXdata.buttons & PSXBTN_R1)
      message = TURN_RIGHT;

    if (PSXdata.buttons & PSXBTN_L1)
      message = TURN_LEFT;

    if (PSXdata.buttons & PSXBTN_R2)
      message = TURBO;

    if (PSXdata.buttons & PSXBTN_L2)
      message = LIGHT;

    if (message != "")
    {
      send(message.c_str());
      setup_psx();
    }
  }
}

void send(const char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  Serial.print("Sended: ");
  Serial.println(message);
}

#endif