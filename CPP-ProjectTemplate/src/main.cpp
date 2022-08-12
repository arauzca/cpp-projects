#include <iostream>
#include <project_template.hpp>

using namespace std;

int main()
{
  ProjectTemplate p("Hello World!");
  cout << p.getString() << endl;
  return 0;
}
