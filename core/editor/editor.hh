#ifndef FST_EDITOR_HH
#define FST_EDITOR_HH

#include <core/node.hh>

void* fst_editor_init();
void fst_editor_end(void* mstate);
void fst_editor(void* mstate, void* gstate, void* rstate, FSTnode* scene);

#endif
