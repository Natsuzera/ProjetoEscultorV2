#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H
#include <vector>
#include <string>
#include "FiguraGeometrica.h"

class Interpretador {
    int dimx, dimy, dimz;
    float r, g, b, a;

public:
    Interpretador();
    ~Interpretador(){};
    std::vector<FiguraGeometrica*> parse(std::string filename);
    int getDimx();
    int getDimy();
    int getDimz();
};

#endif // INTERPRETADOR_H