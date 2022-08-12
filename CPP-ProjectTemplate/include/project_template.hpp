#pragma once
#include <string>

using namespace std;

class ProjectTemplate {
protected:
  string in;
public:
  ProjectTemplate(string in): in(in) {}
  ~ProjectTemplate() {}
  
  inline string getString() { return this->in;}
};
