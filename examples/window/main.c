#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <core/macros.h>
#include <stdlib.h>
#include <render/gl/loader.h>

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

    while (!fur_platf_shouldWindowClose(platf)) {
        fur_platf_poll(platf);

        glClearColor(.2,.4,.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        fur_platf_present(platf);
    }   

    fur_render_destr(render);
    fur_platf_destr(platf);
}
