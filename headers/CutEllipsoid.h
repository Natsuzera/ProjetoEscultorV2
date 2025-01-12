#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H
#include "FiguraGeometrica.h"

class CutEllipsoid : public FiguraGeometrica{
    
    int xcenter, ycenter, zcenter, rx, ry, rz;

public:
    CutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    ~CutEllipsoid(){};

    void draw(Sculptor &t);
};

#endif // CUTELLIPSOID_H