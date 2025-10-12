#ifndef FUR_NODE_HH
#define FUR_NODE_HH

#include <core/macros.h>
#include <vector>
#include <stdio.h>
#include <core/mat4.h>
#include <core/state.hh>

namespace fur {
    class Node;

    enum class Type : u8 {
        STRING,
        REF,
        VECTOR,
        INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4
    };

    struct VarInfo {
        void* var;
        const char* name;
        Type type;
    };

    class Component {
    public:
        char* title;
        std::vector<VarInfo> publics;
        fur::State* st;

        Component(State* state) { title = "untitled"; st = state; }

        Node* parent;
        virtual void update(f32 delta) {}
        virtual void render()          {}
        virtual ~Component()           {}
    };

    class Node {
    public:
        char* name;

        Node* parent;
        std::vector<Node*> children;
        std::vector<Component*> components;

        v3 pos, scale, rot;
        mat4 transf;

        Node() : parent(NULL) { name = "untitled"; pos = v3{0,0,0}; scale = v3{1,1,1}; rot = v3{0,0,0}; }
        virtual ~Node() {
            for (s32 i = 0; i < (s32)children.size(); ++i)
                delete children[i];
            for (s32 i = 0; i < (s32)components.size(); ++i)
                delete components[i];

        }

        void addChild(Node* child) { 
            child->parent = this;
            children.push_back(child); 
        }

        void addComponent(Component* component) {
            component->parent = this;
            components.push_back(component);
        }

        void recupdate(f32 delta) {
            for (s32 i = 0; i < (s32)components.size(); ++i)
                components[i]->update(delta);
            for (s32 i = 0; i < (s32)children.size(); ++i)
                children[i]->recupdate(delta);
        }

        void recrender() {
            mat4_scale(&transf, scale.x,scale.y,scale.z);
            mat4 a;
            mat4_rotateX(&a, rot.x);
            mat4_multiply(&transf, transf, a);
            mat4_rotateY(&a, rot.y);
            mat4_multiply(&transf, transf, a);
            mat4_rotateZ(&a, rot.z);
            mat4_multiply(&transf, transf, a);
            mat4_translate(&a, pos.x,pos.y,pos.z);
            mat4_multiply(&transf, transf, a);

            for (s32 i = 0; i < (s32)components.size(); ++i)
                components[i]->render();
            for (s32 i = 0; i < (s32)children.size(); ++i)
                children[i]->recrender();
        }
    };
}

#endif
