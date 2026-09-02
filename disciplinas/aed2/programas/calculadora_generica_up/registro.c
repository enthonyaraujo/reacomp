#include "calculator.h"
#include "registro.h"


Calculator* make_calculator(OPERATION_TYPE ot){
    switch (ot)
    {
    case INT:
        return calculator_create(sizeof(int), 2, (const Operation[]){add_int, multiply_int});

    case DOUBLE:
        return calculator_create(sizeof(double), 2, (const Operation[]){add_double, multiply_double});

    default:
        return NULL;
    }
}
