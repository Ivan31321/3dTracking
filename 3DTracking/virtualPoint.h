#ifndef VIRTUALPOINT_H
#define VIRTUALPOINT_H
class virtualPoint{
public:
    virtual double getT() const = 0;
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual double getZ() const = 0;
    virtual double getR() const = 0;
    virtual double getPhi() const = 0;
    virtual double getTeta() const = 0;
    virtual double getSpeed(const virtualPoint* previousPoint) = 0;
};

#endif // VIRTUALPOINT_H
