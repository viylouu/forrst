#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>
#include <core/macros.h>
#include <core/input.h>

int main(void) {
    FUR_platfState* platf = fur_platf_constr();
    FUR_renderState* render = fur_render_constr();

    fur_platf_setRender(platf, render);

    while (!fur_platf_shouldWindowClose(platf)) {
        fur_platf_poll(platf);
        fur_input_poll(platf);

        fur_render_clear(render, .2,.4,.3);
        fur_render_rect(render, .pos = (v2){64,64}, .size = (v2){64,64}, .col = (v4){1,0,0,1});

        fur_render_tex(render, .size = (v2){64,64}, .col = (v4){1,1,1,1});

        fur_render_flush(render);

        fur_platf_present(platf);
    }   

    fur_render_destr(render);
    fur_platf_destr(platf);
}
