#ifndef RECTPOINT_H
#define RECTPOINT_H
#include<virtualPoint.h>
#include<cmath>
class rectPoint : public virtualPoint {
private:
    double t;
    double x;
    double y;
    double z;
public:
    rectPoint(double t,double x,double y,double z){
        this->t = t;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    double getT() const {
        return t;
    }
    double getX() const {
        return x;
    }
    double getY() const {
        return y;
    }
    double getZ() const{
        return z;
    }
    double getR() const{
        return sqrt(x*x + y*y + z*z);
    }
    double getPhi() const{
        return atan(y/x);
    }
    double getTeta() const{
        return asin(z/getR());
    }
    double getSpeed(const virtualPoint* previousPoint){
        double dt = this->getT() - previousPoint->getT();
        double dx = this->getX() - previousPoint->getX();
        double dy = this->getY() - previousPoint->getY();
        double dz = this->getZ() - previousPoint->getZ();
        return sqrt(dx * dx + dy * dy + dz * dz) / dt;
    }
};

#endif // RECTPOINT_H
