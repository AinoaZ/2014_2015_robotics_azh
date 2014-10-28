/**
 * @file    MyRobot.cpp
 * @brief   A simple example for maintaining a straight line with the compass.
 *
 * @author  Raul Perula-Martinez <raul.perula@uc3m.es>
 * @date    2014-07
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // Get frontal sensor

    _distance_sensor[0] = getDistanceSensor("ds1");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds2");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds3");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds15");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds14");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds13");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds0");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds12");
    _distance_sensor[5]->enable(_time_step);


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
    int contador;
    contador = 0;
    double ir1_val = 0.0, ir13_val = 0.0, ir14_val = 0.0;




    while (step(_time_step) != -1)
    {
        // Read the sensors
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        // Print count value to console




       if( contador < 390)

        {
          contador ++;
          cout << "Count: " << contador << endl;





        // Simple bang-bang control
        if ((compass_angle < (DESIRED_ANGLE - 2 ) && (contador < 390)))
        {
            // Turn right
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED - 15;
        }
        else {
             if ((compass_angle > (DESIRED_ANGLE - 2 ) && (contador < 390))) {
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

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
       else
       { cout << "Count: " << contador << endl;
         _left_speed =  0;
         _right_speed = 0;
         // Set the motor speeds
         setSpeed(_left_speed, _right_speed);

         }




       // Read the sensors
       ir1_val =  _distance_sensor[0]->getValue();
       ir13_val =  _distance_sensor[1]->getValue();
       ir14_val =  _distance_sensor[2]->getValue();

       if ((_left_speed == 0) && ( _right_speed == 0))
       {
       cout << "Distance sensor 1: " <<  ir1_val<< endl;
       cout << "Distance sensor 2: " <<  ir13_val << endl;
       cout << "Distance sensor 3: " << ir14_val  << endl;
       }
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
