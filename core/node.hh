#ifndef FST_NODE_HH
#define FST_NODE_HH

#include <core/macros.h>
#include <vector>
#include <stdio.h>

class FSTcomponent {
public:
    virtual void update()   {}
    virtual void render()   {}
    virtual ~FSTcomponent() {}
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
        components.push_back(component);
    }

    virtual void update() {}
    virtual void render() {}

    void recupdate() {
        update();
        for (s32 i = 0; i < (s32)components.size(); ++i)
            components[i]->update();
        for (s32 i = 0; i < (s32)children.size(); ++i)
            children[i]->recupdate();
    }

    void recrender() {
        render();
        for (s32 i = 0; i < (s32)components.size(); ++i)
            components[i]->render();
        for (s32 i = 0; i < (s32)children.size(); ++i)
            children[i]->recrender();
    }
};



#endif
