#include <iostream>
#include <vector>
#include "Sculptor.h"
#include "Interpretador.h"
#include "FiguraGeometrica.h"

int main() {
    Sculptor *s;
    Interpretador parser;
    std::vector<FiguraGeometrica*> figs;
    figs = parser.parse("input/teste.txt");
    s = new Sculptor(parser.getDimx(), parser.getDimy(), parser.getDimz());
    for (size_t i = 0; i < figs.size(); i++) {
        figs[i]->draw(*s);
    }
    s->writeOFF((char*)"output/escultor3d.off");
    for (size_t i = 0; i < figs.size(); i++) {
        delete figs[i];
    }
    delete s;
    return 0;
}