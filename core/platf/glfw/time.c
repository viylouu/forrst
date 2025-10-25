#include "time.h"

#include <core/macros.h>
#include <GLFW/glfw3.h>

f64 curTime, lastTime, delta;

void fur_glfw_updateTime(void) {
    lastTime = curTime;
    curTime = glfwGetTime();
    delta = curTime - lastTime;
}

void fur_glfw_updateTimer(FUR_timer* timer) {
    timer->delta = delta * timer->scale;
    timer->time += timer->delta;
}
