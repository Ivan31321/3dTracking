#ifndef MYPOINT_H
#define MYPOINT_H
#include<cmath>
class MyPoint{
    public:
        double t;
        double x;
        double y;
        double z;
        double r;
        double phi;
        double teta;
        MyPoint(double t,double x, double y,double z,bool isRectangular){
            this->t = t;
            if (isRectangular){
                this->x = x;
                this->y = y;
                this->z = z;
                this->r = sqrt(x*x + y*y + z*z);
                this->phi = atan(y/x);
                this->teta = acos(z/r);
            }
            else{
                this->r = x;
                this->phi = y;
                this->teta = z;
                this->x = r* sin(teta)*cos(phi);
                this->y = r*sin(teta)*sin(phi);
                this->z = r*cos(teta);
            }
        }
};

#endif // MYPOINT_H
