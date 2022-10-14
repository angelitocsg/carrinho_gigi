#include <Arduino.h>
#include <Thread.h>

class MyLights
{
private:
    bool statusFarol = false;

public:
    bool obter_status_farol()
    {
        return statusFarol;
    }

    void acende_farol()
    {
        digitalWrite(A5, HIGH);
        statusFarol = true;
    }

    void apaga_farol()
    {
        digitalWrite(A5, LOW);
        statusFarol = false;
    }
};