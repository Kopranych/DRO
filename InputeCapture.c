#include "InputCapture.h"


void init_input_capture32(void)
{
    RPINR7bits.IC1R0 = 0;//set IC1 to pin RP0
}
