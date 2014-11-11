/**
 * @file    MyRobot.cpp
 * @brief   A simple example for following walls.
 *
 * @author  Ainoa Zugasti Hernandez <100292754@alumnos.uc3m.es>
 * @date   28.10.14
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = MAX_SPEED;
    _right_speed = MAX_SPEED;
    _right_encoder= 0;
    _left_encoder = 0;
    _my_distance = 0;
    enableEncoders(_time_step);


}

MyRobot::~MyRobot()
{
    disableEncoders();
}




void MyRobot::run()
{



    while (step(_time_step) != -1)

    {

        // Impresion por pantalla de parametros necesarios

        cout << "La distancia del encoder de la derecha es: " << _right_encoder << endl;
        cout << "La distancia del encoder de la izquierda es: " << _left_encoder << endl;
        cout << "VELOCIDAD DERECHA: " << _right_speed << endl;

        cout << "VELOCIDAD IZQUIERDA: " << _left_speed << endl;
         cout << " Mi distancia actual es: " << _my_distance << endl;

         // Condicion que permite elegir si el robot debe moverse o frenar.

        if(_my_distance < DISTANCIA_VALIDA)
        {
            go_robot();
        }

        else
        {
            stop_robot ();
        }
    }


    }


//////////////////////////////////////////////
// La funcion go_robot permite al robot el avance.

void MyRobot::go_robot()
{
     // Devoluciones de los valores de los respectivos encoders
    _right_encoder = getRightEncoder();
    _left_encoder = getLeftEncoder();

    _my_distance = (_left_encoder/5)*0.0825;

    if(_left_encoder > _right_encoder)
    {   _left_speed = MAX_SPEED/2;
        _right_speed = MAX_SPEED;
    }
    else
    {
        _left_speed = MAX_SPEED;
        _right_speed = MAX_SPEED/2;
    }

    setSpeed(_left_speed, _right_speed);
}




//////////////////////////////////////////////

// La funcion stop_robot permite al robot frenar.

void MyRobot::stop_robot()
{

_left_speed=0;
_right_speed = 0;
setSpeed(_left_speed, _right_speed);
}
