#include <Arduino.h>
#include <AFMotor.h>

#define NORMAL_VELOCITY 150
#define TURBO_VELOCITY 255

#define TURN_LEFT 'l'
#define TURN_RIGHT 'r'
#define GO_FORWARD 'f'
#define GO_BACKWARD 'b'
#define START 'o'
#define STOP 's'
#define LIGHT 'g'
#define TURBO 't'

class MyMotors
{
private:
    AF_DCMotor *motor3;
    AF_DCMotor *motor4;
    int current_velocity = NORMAL_VELOCITY;
    bool turbo_mode = false;
    bool forward_direction = true;

    void vai()
    {
        if (forward_direction)
            anda_para_frente();
        else
            anda_para_tras();
    }

    int turn_velocity()
    {
        return current_velocity / 2;
    }

public:
    MyMotors()
    {
        motor3 = new AF_DCMotor(3);
        motor4 = new AF_DCMotor(4);
    }

    bool esta_indo_para_frente()
    {
        return forward_direction;
    }

    void liga_motores()
    {
        motor3->setSpeed(50);
        motor4->setSpeed(50);
        motor3->run(RELEASE);
        motor4->run(RELEASE);
    }

    void desliga_motores()
    {
        liga_motores();
        delay(2000);
    }

    void anda_para_frente()
    {
        forward_direction = true;
        motor3->setSpeed(current_velocity);
        motor4->setSpeed(current_velocity);
        motor3->run(FORWARD);
        motor4->run(FORWARD);
    }

    void anda_para_tras()
    {
        forward_direction = false;
        motor3->setSpeed(current_velocity);
        motor4->setSpeed(current_velocity);
        motor3->run(BACKWARD);
        motor4->run(BACKWARD);
    }

    void virar_para_esquerda()
    {
        motor3->setSpeed(current_velocity);
        motor4->setSpeed(current_velocity - turn_velocity());
        motor3->run(forward_direction ? FORWARD : BACKWARD);
        motor4->run(forward_direction ? FORWARD : BACKWARD);
    }

    void virar_para_direita()
    {
        motor3->setSpeed(current_velocity - turn_velocity());
        motor4->setSpeed(current_velocity);
        motor3->run(forward_direction ? FORWARD : BACKWARD);
        motor4->run(forward_direction ? FORWARD : BACKWARD);
    }

    void turbina_motores()
    {
        turbo_mode = !turbo_mode;

        if (!turbo_mode)
        {
            current_velocity = NORMAL_VELOCITY;
            vai();
            return;
        }

        current_velocity = TURBO_VELOCITY;
        vai();
    }
};