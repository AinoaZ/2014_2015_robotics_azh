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

    _left_speed = 0;
    _right_speed = 0;

    _mode = FORWARD;


     // este bucle permite simplificarla declaracion de todas las distancias de los sensores y su habilitacion
    for(i=0; i<16; i++)
    {

        string matriz;
        ostringstream conversion;
        conversion<<i;
        matriz= conversion.str();
        _distance_sensor[i] = getDistanceSensor("ds"+matriz);
        _distance_sensor[i]->enable(_time_step);

    }

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);
}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    for (int x=0; x<NUM_DISTANCE_SENSOR; x++) {
        _distance_sensor[x]->disable();
    }
    _my_compass->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;


    double sensor0=0.0,sensor1=0.0,sensor2=0.0, sensor3=0.0,sensor4=0.0, sensor5=0.0,
            sensor6=0.0,sensor7=0.0 ,sensor8=0.0,sensor9=0.0,sensor10=0.0,sensor11=0.0,
            sensor12=0.0,sensor13=0.0,sensor14=0.0, sensor15=0.0;

    while (step(_time_step) != -1)
    {
        // Read the sensors
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        // Print count value to console

        // Set the motor speeds
        cout << "left speed: " << _left_speed << endl;
        cout << "right speed: " << _right_speed<< endl;

        for(j=0; j<16; j++)
        {
            string matriz2;
            double sensor[NUM_DISTANCE_SENSOR];
            ostringstream conversion2;
            conversion2<<j;
            matriz2= conversion2.str();
            sensor[j]=  _distance_sensor[j]->getValue();
            cout << "Distance sensor " << j <<": "<< sensor[j]<< endl;

            }

         // Wall following
        // Condicion para que el robot siga la brujula
        if ((sensor0==0) && (sensor1==0) &&(sensor2==0) &&(sensor3==0) &&(sensor4==0) &&(sensor5==0) &&(sensor6==0) &&(sensor7==0) &&(sensor8==0) &&(sensor9==0) &&(sensor10==0) &&(sensor11==0) && (sensor12==0) &&(sensor13==0) &&(sensor14==0) && (sensor15==0))
        {
            cout << "Siguiendo a la brujula" << endl;

            if (compass_angle < (DESIRED_ANGLE - 2 )) {
                // Turn right
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED - 15;
            }
            else {
                if (compass_angle > (DESIRED_ANGLE + 2  )) {
                    // Turn left
                    _left_speed = MAX_SPEED - 15;
                    _right_speed = MAX_SPEED;
                }
                else {
                    // Move straight forward
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED;
                }
            }
        }

        else                                        // Condicion para que el robot siga paredes.
        {
            if ((sensor1 > DISTANCE_LIMIT) || (sensor14> DISTANCE_LIMIT)|| (sensor13> DISTANCE_LIMIT)|| (sensor2> DISTANCE_LIMIT)  )
            {
                if((sensor14>sensor1) || (sensor13>sensor2))
                {
                    _mode = WALL_FOLLOWER_RIGHT;   // Sigue la pared de la derecha
                    cout<< "Modo derecha"<<endl;
                }
                else
                {
                    _mode = WALL_FOLLOWER_LEFT;   // Sigue la pared de la izquierda
                    cout<< "Modo izquierda"<<endl;
                }
            }

            else
            {
                if(sensor3 != 0)
                {
                    if(sensor3 > DISTANCE_LIMIT)
                    {
                        _mode = TURN_LEFT;
                    }
                    else
                    {
                        _mode = TURN_RIGHT;
                    }
                }
                else
                { if (sensor2 !=0)
                    {
                        if(sensor2 > DISTANCE_LIMIT)
                        {
                            _mode = TURN_LEFT;
                        }
                        else
                        {
                            _mode = TURN_RIGHT;
                        }
                    }

                    else
                    {

                        if (sensor12 != 0)
                        {
                            if (sensor12 > DISTANCE_LIMIT)
                            {
                                _mode= TURN_RIGHT;
                            }
                            else
                            {
                                _mode= TURN_LEFT;
                            }
                        }
                        else
                        {
                            if (sensor10 != 0)
                            {
                                if (sensor10 > DISTANCE_LIMIT)
                                {
                                    _mode= TURN_RIGHT;
                                }
                                else
                                {
                                    _mode= TURN_LEFT;
                                }

                            }

                        }

                    }
                }
            }
        }



        // Send actuators commands according to the mode
        switch (_mode)
        {
        case STOP:
            _left_speed = 0;
            _right_speed = 0;
            break;
        case FORWARD:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
            break;
        case TURN_LEFT:
            _left_speed = MAX_SPEED / 1.25;
            _right_speed = MAX_SPEED;
            break;
        case TURN_RIGHT:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED / 1.25;
            break;
        case WALL_FOLLOWER_RIGHT:                   //Nuevo caso del swirch que permite seguir la pared de la derecha
            _left_speed = -MAX_SPEED/ 3.0;
            _right_speed = MAX_SPEED/ 20;
            break;
        case WALL_FOLLOWER_LEFT:                    // Nuevo caso del switch que permite seguir la pared de la izquierda.
            _left_speed = MAX_SPEED/ 20;
            _right_speed = -MAX_SPEED/ 3.0;
            break;
        default:
            break;
        }

        // movimiento
        setSpeed(_left_speed, _right_speed);
    }
}



//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////

