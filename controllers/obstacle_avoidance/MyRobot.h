/**
 * @file    MyRobot.h
 * @brief   A simple example for maintaining a straight line with the compass.
 *
 * @author Ainoa Zugasti Hernandez <100292754@alumnos.uc3m.es>
 * @date    2014-07
 */

#include <iostream>
#include <cmath>
#include <sstream>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED       40
#define DESIRED_ANGLE   45
#define NUM_DISTANCE_SENSOR 16
#define DISTANCE_LIMIT  100

class MyRobot : public DifferentialWheels {
private:
    int _time_step;
    int i,j;


    DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
    Compass * _my_compass;
    double _left_speed, _right_speed;

    enum Mode {
        STOP,
        FORWARD,
        TURN_LEFT,
        TURN_RIGHT,
        WALL_FOLLOWER_RIGHT,
        WALL_FOLLOWER_LEFT
    };

    Mode _mode;

public:
    /**
     * @brief Empty constructor of the class.
       @param
       @return

     */
    MyRobot();

    /**
         * @brief Destructor of the class.
           @param
           @return
         */
    ~MyRobot();

    /**
         * @brief User defined function for initializing and running the template class.
         * @param
           @return
         */
    void run();

    /**
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          * @param *in_vector
          * @return deg
          */
    double convert_bearing_to_degrees(const double* in_vector);
};
