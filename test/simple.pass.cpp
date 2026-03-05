// RUN: %compile

#include "simple.hpp"

int main(){
  b(std::meta::access_context::unchecked());
}
