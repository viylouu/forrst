#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>

int main(void) {
    FUR_platfState* platf = fur_platf_constr();
    FUR_renderState* render = fur_render_constr(.api = FUR_RENDER_API_GL);

    while (!fur_platf_shouldWindowClose(platf)) {
        fur_platf_poll(platf);

        fur_render_clear(render, .2,.4,.3);

        fur_render_flush(render);

        fur_platf_present(platf);
    }   

    fur_render_destr(render);
    fur_platf_destr(platf);
}
