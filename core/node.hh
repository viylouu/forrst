#ifndef FUR_NODE_HH
#define FUR_NODE_HH

#include <core/macros.h>
#include <vector>
#include <stdio.h>
#include <core/mat4.h>

class FURnode;

typedef enum {
    FUR_TYPEOF_STRING,
    FUR_TYPEOF_REF,
    FUR_TYPEOF_VECTOR,
    FUR_TYPEOF_INT,
    FUR_TYPEOF_FLOAT,
    FUR_TYPEOF_VEC2,
    FUR_TYPEOF_VEC3,
    FUR_TYPEOF_VEC4
} FURtype;

typedef struct {
    void* var;
    const char* name;
    FURtype type;
} FURvarInfo;

class FURcomponent {
public:
    const char* title;
    std::vector<FURvarInfo> publics;

    FURcomponent() { title = "untitled"; }

    virtual void init()            {}
    FURnode* parent;
    virtual void update(f32 delta) {}
    virtual void render()          {}
    virtual ~FURcomponent()        {}
};

class FURnode {
public:
    char* name;

    FURnode* parent;
    std::vector<FURnode*> children;
    std::vector<FURcomponent*> components;

    v3 pos, scale, rot;
    mat4 transf;

    FURnode() : parent(NULL) { name = "untitled"; }
    virtual ~FURnode() {
        for (s32 i = 0; i < (s32)children.size(); ++i)
            delete children[i];
        for (s32 i = 0; i < (s32)components.size(); ++i)
            delete components[i];

    }

    void addChild(FURnode* child) { 
        child->parent = this;
        children.push_back(child); 
    }

    void addComponent(FURcomponent* component) {
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
        fur_mat4_scale(&transf, scale.x,scale.y,scale.z);
        mat4 a;
        fur_mat4_rotateX(&a, rot.x);
        fur_mat4_multiply(&transf, transf, a);
        fur_mat4_rotateY(&a, rot.y);
        fur_mat4_multiply(&transf, transf, a);
        fur_mat4_rotateZ(&a, rot.z);
        fur_mat4_multiply(&transf, transf, a);
        fur_mat4_translate(&a, pos.x,pos.y,pos.z);
        fur_mat4_multiply(&transf, transf, a);

        for (s32 i = 0; i < (s32)components.size(); ++i)
            components[i]->render();
        for (s32 i = 0; i < (s32)children.size(); ++i)
            children[i]->recrender();
    }
};

#endif
