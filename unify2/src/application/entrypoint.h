#pragma once

#include "application.h"
#include "pch/un2pch.h"

extern unify2::application* unify2::createInstance();

int main(int argc, char** argv) {
	auto app = unify2::createInstance();
	app->run();
	delete app;
}
