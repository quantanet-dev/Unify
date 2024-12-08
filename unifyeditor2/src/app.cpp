#include "unify2.h"

class editor : public unify2::Application {
public:
	editor() {};
	~editor() {};
};

unify2::Application* unify2::CreateInstance() {
	return new editor();
}

