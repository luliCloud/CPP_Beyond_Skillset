#include "XYPoint.h"
#include <iostream>
using namespace std;

XYPoint::XYPoint() {
    x = 0.0;
    y = 0.0;
}

XYPoint::XYPoint(const double& x_value, const double& y_value) {
    x = x_value;
    y = y_value;
}

void XYPoint::setX(const double& x_value) {
    x = x_value;
}

void XYPoint::setY(const double& y_value) {
    y = y_value;
}

double XYPoint::getX() const {
    return x;
}

double XYPoint::getY() const {
    return y;
}
