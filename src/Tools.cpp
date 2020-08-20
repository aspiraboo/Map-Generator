#include "Tools.h"

void toLowerCase(std::string& source)
{
	transform(source.begin(), source.end(), source.begin(), [](unsigned char c){ return std::tolower(c); });
}