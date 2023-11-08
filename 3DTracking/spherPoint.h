#ifndef SPHERPOINT_H
#define SPHERPOINT_H
#include<virtualPoint.h>
#include<cmath>
class spherPoint : public virtualPoint {
private:
    double t;
    double r;
    double phi;
    double teta;
public:
    spherPoint(double t,double r,double phi,double teta){
        this->t = t;
        this->r = r;
        this->phi = phi;
        this->teta = teta;
    }
    double getT() const {
        return t;
    }
    double getX() const {
        return r* cos(teta)*cos(phi);
    }
    double getY() const {
        return r*cos(teta)*sin(phi);
    }
    double getZ() const{
        return r*sin(teta);
    }
    double getR() const{
        return r;
    }
    double getPhi() const{
        return phi;
    }
    double getTeta() const{
        return teta;
    }
    double getSpeed(const virtualPoint* previousPoint){
        double dt = this->getT() - previousPoint->getT();
        double dx = this->getX() - previousPoint->getX();
        double dy = this->getY() - previousPoint->getY();
        double dz = this->getZ() - previousPoint->getZ();
        return sqrt(dx * dx + dy * dy + dz * dz) / dt;
    }
};

#endif // SPHERPOINT_H
