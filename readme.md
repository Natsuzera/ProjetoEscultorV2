# Projeto Escultor 3D - Parte 2: Estruturas Avançadas

Este projeto é a continuação da ferramenta Escultor 3D, desenvolvida em **C++**, que permite a criação de esculturas digitais representadas por matrizes tridimensionais. Nesta segunda parte, implementamos **estruturas geométricas avançadas** para manipulação e desenho de formas em um espaço 3D. O resultado final é exportado no formato **OFF**, compatível com visualizadores como **MeshLab** ou **Geomview**.

---

## 🛠️ Funcionalidades
- **Classes Abstratas e Concretas:**
  - **FiguraGeometrica**: Classe base abstrata para representar figuras geométricas.
  - **PutVoxel e CutVoxel**: Adicionar e remover voxels individuais.
  - **PutBox e CutBox**: Adicionar e remover caixas delimitadas.
  - **PutSphere e CutSphere**: Adicionar e remover esferas.
  - **PutEllipsoid e CutEllipsoid**: Adicionar e remover elipsoides.

- **Interpretação de Arquivos de Entrada:**
  - Leitura de comandos como `putvoxel`, `putsphere`, entre outros, a partir de um arquivo de texto.

- **Exportação no Formato OFF:**
  - Salva o modelo criado no formato OFF, incluindo cores e transparência para visualização em ferramentas especializadas.

---

## 📋 Como Usar
### 1. Crie um Arquivo de Entrada
Insira os comandos no arquivo `input/teste.txt` com o formato:
```plaintext
dim 30 30 30
putvoxel 5 5 5 1.0 0.0 0.0 1.0
putsphere 15 15 15 5 0.0 1.0 0.0 0.8


### 2. Compile o Projeto
Certifique-se de que possui um compilador C++ (como `g++`). Compile o projeto com o seguinte comando:
```bash
g++ -o escultor main.cpp Sculptor.cpp Interpreter.cpp FiguraGeometrica.cpp -std=c++11

