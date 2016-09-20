#include "mymath.h"

#include <math.h>

int iteratedLog(double value){
    if(value > 1){
        return 1 + iteratedLog(log2(value));
    }else{
        return 0;
    }
}
