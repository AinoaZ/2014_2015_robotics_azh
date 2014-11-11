/**
 * @file    MyRobot.cpp
 * @brief   A simple example for following walls.
 *
 * @author  Ainoa Zugasti Hernandez <100292754@alumnos.uc3m.es>
 * @date   11.14
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = MAX_SPEED;
    _right_speed = MAX_SPEED;
    _right_encoder= 0;      //inicia el encoder derecho a cero
    _left_encoder = 0;      // inicia el encoder izquierdo a cero
    _my_distance = 0;       // la distancia inicial que detecta el robot es cero
    enableEncoders(_time_step); // habilitacion de los encoders


}

// destructor de la clase MyRobot

MyRobot::~MyRobot()
{
    // deshabilitacion de los encoders
    disableEncoders();
}




void MyRobot::run()
{



    while (step(_time_step) != -1)

    {

        // imprime por pantalla parametros necesarios.

        cout << "La distancia del encoder de la derecha es: " << _right_encoder << endl;
        cout << "La distancia del encoder de la izquierda es: " << _left_encoder << endl;
        cout << "VELOCIDAD DERECHA: " << _right_speed << endl;
        cout << "VELOCIDAD IZQUIERDA: " << _left_speed << endl;
        cout << " Mi distancia actual es: " << _my_distance << endl;

        // devuelve el valor del encoder derecho
        _right_encoder = getRightEncoder();

        // devuelve el valor del encoder izquierda

        _left_encoder = getLeftEncoder();

        //  valor para la distancia del robot

        _my_distance = (_left_encoder/5)*0.0825;

        // condicion para el seguimiento recto del robot

        if(_left_encoder > _right_encoder)
        {   _left_speed = MAX_SPEED/2;
            _right_speed = MAX_SPEED;
        }
        else
        {
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED/2;
        }


        // condicion entre distancias

        if(_my_distance < DISTANCIA_VALIDA)
        {
            // llamada a la funcion go_robot
            go_robot();


        }

        else
        {
            // llamada a la funcion stop_robot
            stop_robot ();
        }
    }


}


//////////////////////////////////////////////

// Funcion go_robot, permite continuar el movimiento del robot

void MyRobot::go_robot()
{




    if( _my_distance > 4.2)
    {
        // llamada a la funcion right_robot

        right_robot();
    }




    setSpeed(_left_speed, _right_speed);

    if(_my_distance > 8.8)
    {
        cout<<" Voy a girar a la izquierda"<<endl;
        left_robot();
    }



}




//////////////////////////////////////////////

// Funcion stop_robot que permite la parada del robot.

void MyRobot::stop_robot()
{

    _left_speed=0;
    _right_speed = 0;
    setSpeed(_left_speed, _right_speed);
}


///////////////////////////////////////////////

// Funcion right_robot, permite que el robot gire a la derecha

void MyRobot::right_robot()
{




    _right_encoder = getRightEncoder();
    _left_encoder = getLeftEncoder();
    _my_distance = (_left_encoder/5)*0.0825;

    _left_speed = MAX_SPEED/ 3.0;
    _right_speed = 0;

    if(_my_distance > 4.76)
    {
        cout<<" Voy a girar a la derecha"<<endl;

        if(_left_encoder > _right_encoder)
        {   _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
        }
        else
        {
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
        }


    }





    setSpeed(_left_speed, _right_speed);











}

//////////////////////////////////////////////////


// Funcion right_robot, permite que el robot gire a la izquierda



void MyRobot::left_robot()
{
    _right_encoder = getRightEncoder();
    _left_encoder = getLeftEncoder();
    _my_distance = (_right_encoder/5)*0.0825;

    _left_speed = 0;
    _right_speed = MAX_SPEED/3.0;

    if(_my_distance > 8.76)
    { cout<<" modo recto activado"<<endl;

        if(_left_encoder > _right_encoder)
        {   _left_speed = MAX_SPEED/2;
            _right_speed = MAX_SPEED;
        }
        else
        {
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED/2;
        }


    }

    setSpeed(_left_speed, _right_speed);

}



