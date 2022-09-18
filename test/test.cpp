#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {

  istringstream iss("1a1b4a4b9");
  cin.rdbuf(
    iss.rdbuf());  // This line actually sets cin's input buffer
  // to the same one as used in iss (namely the
  // string data that was used to initialize it)
  string c;
  cin >> c;
}