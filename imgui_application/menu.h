#include <string>
#include <vector>

namespace menu
{
	extern bool active;
	extern std::vector<std::string> saved_rgb;
	extern bool debug_console;

	void render();
}