#include "fractalgen.h"
int main(int argc, char** args){
  mesh_info<double> result = generateMesh("../examples/standard/sierpinski.txt", 3);
  return 0;
}
