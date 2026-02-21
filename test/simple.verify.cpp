// RUN: %verify

#include "simple.hpp"

int main(){
    // STATIC_ASSERT: not a red function
    b();
    
    b(unchecked);
}
