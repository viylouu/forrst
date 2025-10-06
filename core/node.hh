#ifndef FST_NODE_HH
#define FST_NODE_HH

#include <core/macros.h>
#include <vector>
#include <stdio.h>
#include <core/mat4.h>

class FSTnode;

typedef enum {
    FST_TYPEOF_STRING,
    FST_TYPEOF_REF,
    FST_TYPEOF_VECTOR,
    FST_TYPEOF_INT,
    FST_TYPEOF_FLOAT,
    FST_TYPEOF_VEC2,
    FST_TYPEOF_VEC3,
    FST_TYPEOF_VEC4
} FSTtype;

typedef struct {
    void* var;
    const char* name;
    FSTtype type;
} FSTvarInfo;

class FSTcomponent {
public:
    const char* title;
    std::vector<FSTvarInfo> publics;

    FSTcomponent() { title = "untitled"; }

    virtual void init()            {}
    FSTnode* parent;
    virtual void update(f32 delta) {}
    virtual void render()          {}
    virtual ~FSTcomponent()        {}
};

class FSTnode {
public:
    char* name;

    FSTnode* parent;
    std::vector<FSTnode*> children;
    std::vector<FSTcomponent*> components;

    v3 pos, scale, rot;
    mat4 transf;

    FSTnode() : parent(NULL) { name = "untitled"; }
    virtual ~FSTnode() {
        for (s32 i = 0; i < (s32)children.size(); ++i)
            delete children[i];
        for (s32 i = 0; i < (s32)components.size(); ++i)
            delete components[i];

    }

    void addChild(FSTnode* child) { 
        child->parent = this;
        children.push_back(child); 
    }

    void addComponent(FSTcomponent* component) {
        component->parent = this;
        components.push_back(component);
        component->init();
    }

    void recupdate(f32 delta) {
        for (s32 i = 0; i < (s32)components.size(); ++i)
            components[i]->update(delta);
        for (s32 i = 0; i < (s32)children.size(); ++i)
            children[i]->recupdate(delta);
    }

    void recrender() {
        fst_mat4_scale(&transf, scale.x,scale.y,scale.z);
        mat4 a;
        fst_mat4_rotateX(&a, rot.x);
        fst_mat4_multiply(&transf, transf, a);
        fst_mat4_rotateY(&a, rot.y);
        fst_mat4_multiply(&transf, transf, a);
        fst_mat4_rotateZ(&a, rot.z);
        fst_mat4_multiply(&transf, transf, a);
        fst_mat4_translate(&a, pos.x,pos.y,pos.z);
        fst_mat4_multiply(&transf, transf, a);

        for (s32 i = 0; i < (s32)components.size(); ++i)
            components[i]->render();
        for (s32 i = 0; i < (s32)children.size(); ++i)
            children[i]->recrender();
    }
};

#endif
