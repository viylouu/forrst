#ifndef FUR_EDITOR_HH
#define FUR_EDITOR_HH

#include <core/node.hh>

namespace fur {
    namespace editor {
        void* init();
        void  end(void* mstate);
        void  main(void* mstate, void* gstate, void* rstate, Node* scene);
    }
}

#endif
