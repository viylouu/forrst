#ifndef FUR_TIME_H
#define FUR_TIME_H

#include <core/macros.h>
#include <platf/state.h>

typedef struct {
    FUR_targetPlatf plat;
    f64 time;
    f64 delta;
    f64 scale;
} FUR_timer;

FUR_timer* fur_makeTimer(FUR_targetPlatf plat, f64 off);
void fur_updateTimers(FUR_timer** timers, u32 amt);

#endif
