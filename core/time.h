#ifndef FUR_TIME_H
#define FUR_TIME_H

#include <core/macros.h>
#include <platf/state.h>

/* ====== DATATYPES ====== */

typedef struct {
    FUR_targetPlatf plat;
    f64 time;
    f64 delta;
    f64 scale;
} FUR_timer;

/* ====== DATATYPES ====== */

typedef struct {
    FUR_targetPlatf plat;
    f64 off;
} OP_fur_makeTimer;

/* ====== FUNCS ====== */

FUR_timer* IMPL_fur_makeTimer(OP_fur_makeTimer op);
void fur_updateTimers(FUR_timer** timers, u32 amt);
void fur_destroyTimer(FUR_timer* timer);

/* ====== MACROS ====== */

#define fur_makeTimer(...) \
    IMPL_fur_makeTimer((OP_fur_makeTimer){ .plat = FUR_PLATF_GLFW, .off = 0, __VA_ARGS__ })

#endif
