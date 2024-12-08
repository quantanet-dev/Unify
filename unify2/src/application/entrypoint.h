#pragma once

#include "application.h"
#include "pch/un2pch.h"

extern unify2::Application* unify2::CreateInstance();

int main(int argc, char** argv) {
	auto app = unify2::CreateInstance();
	app->run();
	delete app;
}
