// RUN: %compile

#include "simple.hpp"

int main(){
  b(unchecked);
  b(std::meta::access_context::unchecked());
}
