#ifndef __SHAPE_H__
#define __SHAPE_H__
#include "XYPoint.h"
#include <vector>

class Shape {
public:
    virtual ~Shape() = default; // using compiler default op. 
    virtual double area() const = 0; // implement in children class
};

class Circle : public Shape {
public:
    Circle(const XYPoint& cp, const double& r);
    double area() const override;
private:
    XYPoint center;
    double radius;
};

class Triangle : public Shape {
public:
    Triangle(const XYPoint& p1, const XYPoint& p2, const XYPoint& p3);
    double area() const override;
    friend double distance(const XYPoint& a, const XYPoint& b); // calcualte distance between two points
private:
    XYPoint point1, point2, point3;
    double e1, e2, e3; // 3 edges
};

class Rectangle : public Shape {
public:
    Rectangle(const XYPoint& p1, const XYPoint& p2, const XYPoint& p3, const XYPoint& p4);
    double area() const override;
    friend double distance(const XYPoint& a, const XYPoint& b);
private:
    XYPoint point1, point2, point3, point4;
    double height, width; // 4 edges
};

// sort function
void ShapeSorter(std::vector<Shape*> &shapes);

#endif