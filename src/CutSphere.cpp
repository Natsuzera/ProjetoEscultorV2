#include "CutSphere.h"

CutSphere::CutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    this->xcenter = xcenter; this->ycenter = ycenter; this->zcenter = zcenter;
    this->radius = radius;
}

void CutSphere::draw(Sculptor &t) {
    t.cutSphere(xcenter,ycenter,zcenter,radius);
}

