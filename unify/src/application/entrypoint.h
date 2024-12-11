#pragma once

#include "application.h"

extern unify::Application* unify::CreateInstance();

int main(int argc, char** argv) {
	auto app = unify::CreateInstance();
	app->run();
	delete app;
}
