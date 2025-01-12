#include "CutEllipsoid.h"

CutEllipsoid::CutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    this->xcenter = xcenter; this->ycenter = ycenter; this->zcenter = zcenter;
    this->rx = rx; this->ry = ry; this->rz = rz;
}

void CutEllipsoid::draw(Sculptor &t) {
    t.cutEllipsoid(xcenter,ycenter,zcenter,rx,ry,rz);
}
