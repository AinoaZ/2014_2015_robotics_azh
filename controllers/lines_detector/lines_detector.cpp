/**
 * @file    lines_detector.cpp
 * @brief   Controller example for detecting yellow lines
 * @author  Ainoa Zugasti Hernandez <100292754@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

/**
 * @brief Main program.
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
