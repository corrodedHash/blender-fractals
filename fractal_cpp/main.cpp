#include "fractalgen.h"
#include <string>
int main(int argc, char** args){
  //mesh_info<double> result = generateMesh("grammars/test.grammar", 1);
  mesh_info<double> result = generateMesh("../examples/standard/sierpinski.txt", std::stoi(std::string(args[1])));
  return 0;
}
