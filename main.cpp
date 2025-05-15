#include <iostream>
#include <libraw/libraw.h> // sudo apt install libraw-dev

using namespace std;

int main() {
  LibRaw rawProcesor;
  std::cout << "LibRaw version: " << LibRaw::version() << std::endl;
  return 0;
}