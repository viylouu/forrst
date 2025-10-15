#define FUR_EDITOR
#include <furry.hh>

class Game : public fur::Program {
public:
    Game(fur::State* state) : Program(state) {}

    void render() {
	    st->render->clear(v4{.2,.4,.3,1});
    }
};

int main() {
    fur::windowDoShit<Game>("helo", v2{800,600});
}
