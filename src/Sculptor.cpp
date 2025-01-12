#include "Sculptor.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// Construtor: aloca a matriz 3D
Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // Alocação dinâmica da matriz 3D
    v = new Voxel**[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
            for (int k = 0; k < nz; k++) {
                v[i][j][k].isOn = false; // Inicialmente, todos os voxels estão inativos
            }
        }
    }
}

// Destrutor: libera a memória alocada
Sculptor::~Sculptor() {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}

// Define a cor atual
void Sculptor::setColor(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

// Ativa um voxel
void Sculptor::putVoxel(int x, int y, int z) {
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

// Desativa um voxel
void Sculptor::cutVoxel(int x, int y, int z) {
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].isOn = false;
        // Zerar as propriedades do voxel para garantir que ele não seja renderizado
        v[x][y][z].r = 0;
        v[x][y][z].g = 0;
        v[x][y][z].b = 0;
        v[x][y][z].a = 0;
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int i = x0; i <= x1 && i < nx; i++) {
        for (int j = y0; j <= y1 && j < ny; j++) {
            for (int k = z0; k <= z1 && k < nz; k++) {
                putVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int i = x0; i <= x1 && i < nx; i++) {
        for (int j = y0; j <= y1 && j < ny; j++) {
            for (int k = z0; k <= z1 && k < nz; k++) {
                cutVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                int dist = (i - xcenter) * (i - xcenter) +
                           (j - ycenter) * (j - ycenter) +
                           (k - zcenter) * (k - zcenter);
                if (dist <= radius * radius) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                int dist = (i - xcenter) * (i - xcenter) +
                           (j - ycenter) * (j - ycenter) +
                           (k - zcenter) * (k - zcenter);
                if (dist <= radius * radius) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                float dx = (float)(i - xcenter) / rx;
                float dy = (float)(j - ycenter) / ry;
                float dz = (float)(k - zcenter) / rz;
                if (dx * dx + dy * dy + dz * dz <= 1.0) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                float dx = (float)(i - xcenter) / rx;
                float dy = (float)(j - ycenter) / ry;
                float dz = (float)(k - zcenter) / rz;
                if (dx * dx + dy * dy + dz * dz <= 1.0) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}


void Sculptor::writeOFF(const char* filename) {
    // Abrir arquivo
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    // Contar voxels ativos
    int activeVoxels = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    activeVoxels++;
                }
            }
        }
    }

    // Escrever cabeçalho
    file << "OFF\n";
    file << 8*activeVoxels << " " << 6*activeVoxels << " 0\n";

    // Configurar saída de ponto flutuante
    file << std::fixed << std::setprecision(2);

    // Escrever vértices
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    // Escrever os 8 vértices de cada voxel
                    file << i-0.5 << " " << j+0.5 << " " << k-0.5 << "\n";
                    file << i-0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    file << i+0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    file << i+0.5 << " " << j+0.5 << " " << k-0.5 << "\n";
                    file << i-0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                    file << i-0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    file << i+0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    file << i+0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                }
            }
        }
    }

    // Escrever faces
    int vertex = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    // Usar os valores de cor originais no intervalo [0,1]
                    float r = v[i][j][k].r;
                    float g = v[i][j][k].g;
                    float b = v[i][j][k].b;
                    float a = v[i][j][k].a;

                    // Escrever as 6 faces com os valores de cor em ponto flutuante
                    file << "4 " << vertex+0 << " " << vertex+3 << " " << vertex+2 << " " << vertex+1 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    file << "4 " << vertex+4 << " " << vertex+5 << " " << vertex+6 << " " << vertex+7 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    file << "4 " << vertex+0 << " " << vertex+1 << " " << vertex+5 << " " << vertex+4 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    file << "4 " << vertex+0 << " " << vertex+4 << " " << vertex+7 << " " << vertex+3 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    file << "4 " << vertex+3 << " " << vertex+7 << " " << vertex+6 << " " << vertex+2 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    file << "4 " << vertex+1 << " " << vertex+2 << " " << vertex+6 << " " << vertex+5 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    vertex += 8;
                }
            }
        }
    }

    file.close();
}