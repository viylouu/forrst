#ifndef FST_NODE_HH
#define FST_NODE_HH

#include <core/macros.h>
#include <vector>
#include <stdio.h>

class FSTnode;

typedef enum {
    FST_TYPEOF_STRING,
    FST_TYPEOF_REF,
    FST_TYPEOF_VECTOR,
    FST_TYPEOF_INT,
    FST_TYPEOF_FLOAT
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

    virtual void init() { title = "untitled"; }

    FSTnode* parent;
    virtual void update(f32 delta) {}
    virtual void render()          {}
    virtual ~FSTcomponent()        {}
};

class FSTnode {
public:
    FSTnode* parent;
    std::vector<FSTnode*> children;
    std::vector<FSTcomponent*> components;

    FSTnode() : parent(NULL) {}
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
    }

    void recupdate(f32 delta) {
        for (s32 i = 0; i < (s32)components.size(); ++i)
            components[i]->update(delta);
        for (s32 i = 0; i < (s32)children.size(); ++i)
            children[i]->recupdate(delta);
    }

    void recrender() {
        for (s32 i = 0; i < (s32)components.size(); ++i)
            components[i]->render();
        for (s32 i = 0; i < (s32)children.size(); ++i)
            children[i]->recrender();
    }
};

#endif
