#include "time.h"

#include <core/platf/glfw/time.h>

#include <core/macros.h>
#include <stdlib.h>
#include <stdio.h>

FUR_timer* fur_makeTimer(FUR_targetPlatf plat, f64 off) {
    FUR_timer* timer = NEW(FUR_timer);

    timer->plat = plat;
    timer->time = off;
    timer->scale = 1;
    timer->delta = 1;

    return timer;
}

void fur_updateTimers(FUR_timer** timers, u32 amt) {
    fur_glfw_updateTime();

    for (u32 i = 0; i < amt; ++i) {
        switch(timers[i]->plat) {
            case FUR_PLATF_GLFW:
                fur_glfw_updateTimer(timers[i]); break;
            warn_def_for("fur_updateTimer");
        }
    }
}
