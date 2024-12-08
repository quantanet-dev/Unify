#include "unify.h"

class editor : public unify::Application {
public:
	editor() {};
	~editor() {};
};

unify::Application* unify::CreateInstance() {
	return new editor();
}

