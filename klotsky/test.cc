#include <iostream>
#include <ctime>

using namespace std;

int main() {
  float a = 0.0;
  for (int i = 0; i < 1000000000; ++i) {
    a +=  1/((float) i + 1.0);
  }

  std:: cout << a << endl;
  std::cout << "Time taken = " << clock()/CLOCKS_PER_SEC << endl;
}
