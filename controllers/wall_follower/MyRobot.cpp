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



    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds3");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds12");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds13");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds14");
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds15");
    _distance_sensor[7]->enable(_time_step);


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

   double sensor0=0.0,sensor1=0.0,sensor2=0.0, sensor3=0.0,sensor12=0.0, sensor13=0.0,sensor14=0.0,sensor15=0.0;




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
        setSpeed(_left_speed, _right_speed);





       // Read the sensors
       sensor0 =  _distance_sensor[0]->getValue();
       sensor1 =  _distance_sensor[1]->getValue();
       sensor2 =  _distance_sensor[2]->getValue();
       sensor3 =  _distance_sensor[3]->getValue();
       sensor12 =  _distance_sensor[4]->getValue();
       sensor13 =  _distance_sensor[5]->getValue();
       sensor14=  _distance_sensor[6]->getValue();
       sensor15=  _distance_sensor[7]->getValue();
       cout << "Distance sensor 0: " <<  sensor0<< endl;
       cout << "Distance sensor 1 : " <<  sensor1 << endl;
       cout << "Distance sensor 2: " << sensor2  << endl;
       cout << "Distance sensor 3: " <<  sensor3<< endl;
       cout << "Distance sensor 12 : " <<  sensor12 << endl;
       cout << "Distance sensor 13: " << sensor13  << endl;
       cout << "Distance sensor 14: " <<  sensor14<< endl;
       cout << "Distance sensor 15 : " <<  sensor15 << endl;


       // Control logic of the robot
       if (_mode == FORWARD) {
           // Move forward

           // When sufficiently close to a wall in front of robot,
           // switch mode to wall following
           if ((sensor1 > DISTANCE_LIMIT) || (sensor13 > DISTANCE_LIMIT)) {
               _mode = WALL_FOLLOWER;

               cout << "Mode " << WALL_FOLLOWER << ": Wall following mode activated" << endl;
           }
       }
       else {
           // Wall following

           if ((sensor1 > DISTANCE_LIMIT) || (sensor13 > DISTANCE_LIMIT)) {
               _mode = WALL_FOLLOWER;
               cout << "Voy a seguir la pared" << endl;
           }
           else {
               if (sensor12 > DISTANCE_LIMIT) {
                   _mode = TURN_LEFT;
                   cout << "Giro a la izquierda." << endl;
               }
               else {
                   if (sensor14 < DISTANCE_LIMIT + 50) {
                       _mode = TURN_RIGHT;
                       cout << "Giro a la derecha." << endl;
                   }
                   else {
                       _mode = FORWARD;
                       cout << "Moving forward." << endl;
                   }
               }
           }
       }
       // Send actuators commands according to the mode
       switch (_mode){
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
           case WALL_FOLLOWER:
               _left_speed = -MAX_SPEED/ 3.0;
               _right_speed = MAX_SPEED/ 20;
               break;
           default:
               break;
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
