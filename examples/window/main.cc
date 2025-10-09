#define FUR_EDITOR
#include <furry.hh>

#include <cstdlib>

class Game : public FURgame {
public:
	const fur::State* st;

    Game(const fur::State* state) { st = state; }

    void render() {
	    st->render->clear(rstate, NULL, .2,.4,.3,1);       
    }
};

FUR_MAIN(Game);
