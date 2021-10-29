#include <string>

std::string replace_slash(std::string path)
{
	std::string formatted_path;
	int start = 0;
	int end = path.find("\\");
	int len = 0; 
	while (end != -1) {
		len = end - start;
		formatted_path.append(path.substr(start, len));
		start = end + 1;
		end = path.find("\\", start);
		formatted_path.append("/");
	}
	len = end - start;
	formatted_path.append(path.substr(start, len));
	return formatted_path;
}