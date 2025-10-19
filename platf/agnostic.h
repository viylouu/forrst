#ifndef FUR_PLATFORM_AGNOSTIC_H
#define FUR_PLATFORM_AGNOSTIC_H

#include <core/macros.h>
#include <platf/state.h>

/* ====== DATATYPES ====== */
typedef struct {
    char* title;
    s32 width;
    s32 height;
    FUR_targetPlatf plat;
} OP_fur_platf_constr;

/* ====== FUNCS ====== */

FUR_platfState* IMPL_fur_platf_constr(OP_fur_platf_constr ops);
void fur_platf_destr(FUR_platfState* state);

b8 fur_platf_shouldWindowClose(FUR_platfState* state);

void fur_platf_poll(FUR_platfState* state);

void fur_platf_present(FUR_platfState* state);

/* ====== MACROS ====== */
#define fur_platf_constr(...) \
    IMPL_fur_platf_constr((OP_fur_platf_constr){ .title = "untitled", .width = 800, .height = 600, __VA_ARGS__ })


#endif
