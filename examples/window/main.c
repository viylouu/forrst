#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>
#include <core/macros.h>

int main(void) {
    FUR_platfState* platf = fur_platf_constr();
    FUR_renderState* render = fur_render_constr();

    fur_platf_setRender(platf, render);

    while (!fur_platf_shouldWindowClose(platf)) {
        fur_platf_poll(platf);

        fur_render_clear(render, .2,.4,.3);
        fur_render_rect(render, .pos = (v2){64,64}, .size = (v2){64,64}, .col = (v4){1,0,0,1});

        // todo: implement texture rendering
        // - add the thing i thought of where the default is null and it figures out shit from there
        // - make sample {0,0,1,1} when texture null

        fur_render_flush(render);

        fur_platf_present(platf);
    }   

    fur_render_destr(render);
    fur_platf_destr(platf);
}
