#include "unify2.h"

class editor : public unify2::application {
public:
	editor() {};
	~editor() {};
};

unify2::application* unify2::createInstance() {
	return new editor();
}

