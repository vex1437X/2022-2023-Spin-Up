#include "main.h"
#include "colourWheel.hpp"
using namespace pros;

c::optical_rgb_s_t rgb_value;

c::optical_rgb_s_t getRGB(){
    rgb_value = optical_sensor.get_rgb();
    return rgb_value;
}