#ifndef _XYPOINT_H_
#define _XYPOINT_H_

class XYPoint {
public:
    XYPoint();
    XYPoint(const double& x_value, const double& y_value);

    void setX(const double& x_value);
    void setY(const double& y_value);
    double getX() const;
    double getY() const;
private:
    double x, y;
};

#endif