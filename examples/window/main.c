#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <core/macros.h>
#include <stdlib.h>

int main(void) {
    FUR_platfState* platf = NEW(FUR_platfState);
    platf->plat = FUR_PLATF_GLFW;

    platf->title = "window test";
    platf->width = 800;
    platf->height = 600;

    fur_platf_constr(platf);

    FUR_renderState* render = NEW(FUR_renderState);
    render->api = FUR_RENDER_API_GL;
    fur_render_constr(render);

    

    fur_render_destr(render);
    fur_platf_destr(platf);
}
