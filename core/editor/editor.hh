#ifndef FUR_EDITOR_HH
#define FUR_EDITOR_HH

#include <core/node.hh>

void* fur_editor_init();
void fur_editor_end(void* mstate);
void fur_editor(void* mstate, void* gstate, void* rstate, FURnode* scene);

#endif
