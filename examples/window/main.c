#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>
#include <core/macros.h>
#include <core/input.h>
#include <core/time.h>
#include <core/renderTarget.h>

int main(void) {
    FUR_platfState* platf = fur_platf_constr();
    FUR_renderState* render = fur_render_constr();

    fur_platf_setRender(platf, render);

    FUR_timer* time = fur_makeTimer();

    f32 x = 64;

    FUR_renderTarget* targ = fur_renderTarget_constr(256, 256,);

    while (!fur_platf_shouldWindowClose(platf)) {
        fur_platf_poll(platf);
        fur_input_poll(platf);

        fur_updateTimers(&time, 1);

        fur_render_clear(render, .target = targ, .col = (v3){.2,.4,.3});
        fur_render_rect(render, .target = targ, .pos = (v2){x,64}, .size = (v2){64,64}, .col = (v4){1,0,0,1});

        if (fur_input_isKeyHeld(FUR_KEY_D))
            x += 64 * time->delta;
        if (fur_input_isKeyHeld(FUR_KEY_A))
            x -= 64 * time->delta;

        if (fur_input_isKeyHeld(FUR_KEY_T))
            fur_render_tex(render, .target = targ, .size = (v2){64,64}, .col = (v4){1,1,1,1});

        // spacing

        fur_render_clear(render, .col = (v3){1,1,1});

        fur_render_renderTarget(render, .in_target = targ, .out_target = NULL, .pos = (v2){0,0}, .size = (v2){render->width,render->height}, .col = (v4){1,1,1,1}, .sample = (v4){0,0,targ->texture->width,targ->texture->height});

        fur_render_flush(render);

        fur_platf_present(platf);
    }   

    fur_renderTarget_destr(targ);

    fur_render_destr(render);
    fur_platf_destr(platf);
}
