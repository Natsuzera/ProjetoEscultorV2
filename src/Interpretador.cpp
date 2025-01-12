#include "Interpretador.h"
#include "PutVoxel.h"
#include "CutVoxel.h"
#include "PutBox.h"
#include "CutBox.h"
#include "PutSphere.h"
#include "CutSphere.h"
#include "PutEllipsoid.h"
#include "CutEllipsoid.h"
#include <fstream>
#include <iostream>
#include <sstream>

Interpretador::Interpretador() {
    dimx = dimy = dimz = 0;
}

std::vector<FiguraGeometrica*> Interpretador::parse(std::string filename) {
    std::vector<FiguraGeometrica*> figs;
    std::ifstream fin;
    std::stringstream ss;
    std::string s, token;
    fin.open(filename.c_str());
    if (!fin.is_open()) {
        std::cout << "Arquivo nao encontrado" << std::endl;
        exit(0);
    }
    while (fin.good()) {
        std::getline(fin, s);
        if (fin.good()) {
            ss.clear();
            ss.str(s);
            ss >> token;
            if (ss.good()) {
                if (token.compare("dim") == 0) {
                    ss >> dimx >> dimy >> dimz;
                } else if (token.compare("putvoxel") == 0) {
                    int x, y, z;
                    ss >> x >> y >> z >> r >> g >> b >> a;
                    figs.push_back(new PutVoxel(x, y, z, r, g, b, a));
                } else if (token.compare("cutvoxel") == 0) {
                    int x, y, z;
                    ss >> x >> y >> z;
                    figs.push_back(new CutVoxel(x, y, z));
                } else if (token.compare("putbox") == 0) {
                    int x0, x1, y0, y1, z0, z1;
                    ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
                    figs.push_back(new PutBox(x0, x1, y0, y1, z0, z1, r, g, b, a));
                } else if (token.compare("cutbox") == 0) {
                    int x0, x1, y0, y1, z0, z1;
                    ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
                    figs.push_back(new CutBox(x0, x1, y0, y1, z0, z1));
                } else if (token.compare("putsphere") == 0) {
                    int xcenter, ycenter, zcenter, radius;
                    ss >> xcenter >> ycenter >> zcenter >> radius >> r >> g >> b >> a;
                    figs.push_back(new PutSphere(xcenter, ycenter, zcenter, radius, r, g, b, a));
                } else if (token.compare("cutsphere") == 0) {
                    int xcenter, ycenter, zcenter, radius;
                    ss >> xcenter >> ycenter >> zcenter >> radius;
                    figs.push_back(new CutSphere(xcenter, ycenter, zcenter, radius));
                } else if (token.compare("putellipsoid") == 0) {
                    int xcenter, ycenter, zcenter, rx, ry, rz;
                    ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz >> r >> g >> b >> a;
                    figs.push_back(new PutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz, r, g, b, a));
                } else if (token.compare("cutellipsoid") == 0) {
                    int xcenter, ycenter, zcenter, rx, ry, rz;
                    ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz;
                    figs.push_back(new CutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz));
                }
            }
        }
    }
    return (figs);
}

int Interpretador::getDimx() {
    return dimx;
}

int Interpretador::getDimy() {
    return dimy;
}

int Interpretador::getDimz() {
    return dimz;
}