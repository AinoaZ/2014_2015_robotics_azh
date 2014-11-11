

/**
 * @file    MyRobot.h
 * @brief   A simple example for view distances with our robot.
 *
 * @author  Ainoa Zugasti Hernandez <100292754@alumnos.uc3m.es>
 * @date    2014-11
 */

#include <iostream>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED       50
#define DESIRED_ANGLE   45
#define DISTANCIA_VALIDA 16


class MyRobot : public DifferentialWheels {
private:
    int _time_step;
    double _left_speed, _right_speed;
    // Nuevas variables para los encoders
    double _left_encoder, _right_encoder;
    // Distancia que recorre el robot

    double _my_distance;
    // Funciones sobre el movimiento del robot.
    void stop_robot();
    void go_robot ();




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
        @param
           @return
         */
    void run();

    /**
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          @param *in_vector
           @return deg
         */
    double convert_bearing_to_degrees(const double* in_vector);
};
