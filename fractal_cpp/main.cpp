#include "fractalgen.h"
int main(int argc, char** args){
  mesh_info<double> result = generateMesh("grammars/test.grammar", 1);
  return 0;
}
