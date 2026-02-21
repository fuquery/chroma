// RUN: %verify

#include "simple.hpp"

int main(){
    // CHECK: not a red function
    b();

    b(unchecked);
}
