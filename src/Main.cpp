#include <memory>
#include "Application/SdlTemplate.hpp"



int main(int argc, char** argv)
{
	std::unique_ptr<App::Application> game = std::make_unique<App::Application>();
	game->run();
}