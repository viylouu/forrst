#ifndef FUR_PLATFORM_AGNOSTIC_H
#define FUR_PLATFORM_AGNOSTIC_H

#include <core/macros.h>
#include <platf/state.h>
#include <render/state.h>

/* ====== DATATYPES ====== */
typedef struct {
    char* title;
    v2 dims;
    FUR_targetPlatf platf;
} OP_fur_platf_constr;

/* ====== FUNCS ====== */

FUR_platfState* IMPL_fur_platf_constr(OP_fur_platf_constr ops);
void fur_platf_destr(FUR_platfState* state);

b8 fur_platf_shouldWindowClose(FUR_platfState* state);

void fur_platf_poll(FUR_platfState* state);

void fur_platf_present(FUR_platfState* state);

void fur_platf_setRender(FUR_platfState* state, FUR_renderState* render);

/* ====== MACROS ====== */
#define fur_platf_constr(...) \
    IMPL_fur_platf_constr((OP_fur_platf_constr){ .title = "untitled", .dims = (v2){800,600}, .platf = FUR_PLATF_GLFW, __VA_ARGS__ })


#endif
