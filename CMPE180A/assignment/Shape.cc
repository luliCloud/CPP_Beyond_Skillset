#include <iostream>
#include <cmath> // for M_PI
#include <stdexcept>
#include <algorithm>
#include "Shape.h"
using namespace std;

Circle::Circle(const XYPoint& cp, const double& r) {
    center = cp;
    radius = r;
}

double Circle::area() const {
    return M_PI * radius * radius;
}

double distance(const XYPoint& a, const XYPoint& b) {
    double x_dist = a.getX() - b.getX();
    double y_dist = a.getY() - b.getY();
    return sqrt(x_dist * x_dist + y_dist * y_dist); // c = sqrt(a^2 + b^2). maybe diagnal
}

Triangle::Triangle(const XYPoint& p1, const XYPoint& p2, const XYPoint& p3) {
    // determine whether it is avalid triangle
    point1 = p1;
    point2 = p2;
    point3 = p3;

    // calcualte 3 edges
    e1 = distance(point1, point2);
    e2 = distance(point1, point3);
    e3 = distance(point2, point3);
    if ((e1 + e2 <= e3) || (e1 + e3) <= e2 || (e2 + e3 <= e1)) {
        throw::invalid_argument("Triangle inequality violated.\n");
    }
}

double Triangle::area() const {
    // half perimeter
    double hp = (e1 + e2 + e3) / 2;
    return sqrt(hp * (hp - e1) * (hp - e2) * (hp - e3));
}


Rectangle::Rectangle(const XYPoint& p1, const XYPoint& p2, const XYPoint& p3, const XYPoint& p4) {
    point1 = p1;
    point2 = p2;
    point3 = p3;
    point4 = p4;

    // calcualte all distance betwee any pair of two points
    vector<double> distances = {
        distance(p1, p2), distance(p1, p3), distance(p1, p4),
        distance(p2, p3), distance(p2, p4), distance(p3, p4)
    };

    sort(distances.begin(), distances.end());

    // valid distance
    if (distances[0] != distances[1] || distances[2] != distances[3] || distances[4] != distances[5]) {
        throw invalid_argument("Points do not form a rectangle");
    }

    width = distances[0];
    height = distances[2];
}

double Rectangle::area() const {
    return width * height;
}

void ShapeSorter(vector<Shape*>& shapes) {
    sort(shapes.begin(), shapes.end(), [](Shape* a, Shape* b) {
        return a->area() < b->area();
    });
}