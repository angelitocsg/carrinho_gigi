#include <Arduino.h>
#include <VirtualWire.h>

#define RX_PIN 13

class MyReceiver
{
private:
public:
    MyReceiver()
    {
        vw_set_rx_pin(RX_PIN);
        vw_setup(2000);
        vw_rx_start();
    }
};