#define FUR_EDITOR
#include <furry.hh>

class Square : public fur::Component {
public:
    Square(fur::State* state) : Component(state) {}

    void render() {
        st->render->rect(NULL, v2{0,0}, v2{1,1}, v4{1,0,0,1});
    }
};

class Game : public fur::Program {
public:
    Game(fur::State* state) : Program(state) {
        fur::Node* node = new fur::Node();
        node->addComponent(new Square(st));
        node->scale = v3{64,64,1};
        scene->addChild(node);
    }

    void render() {
	    st->render->clear(v4{.2,.4,.3,1});
    }
};

int main() {
    fur::windowDoShit<Game>("helo", v2{800,600});
}
