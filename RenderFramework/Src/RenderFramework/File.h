#ifndef File_h__
#define File_h__

#include <fstream>
#include <stdint.h>
#include <vector>

uint32_t FileSize(const std::wstring& path) {
	std::ifstream file(path, std::ios_base::binary);
	if (!file.good()) {
		return 0;
	}
	std::streampos current_position = file.tellg();
	file.seekg(0, std::ios::end);
	std::streampos ending_position = file.tellg();
	file.seekg(current_position);
	file.close();
	return (uint32_t)(ending_position - current_position);
}

void FileReadAllText(const std::wstring& path, std::string& result) {
	auto size = FileSize(path);
	if (size == 0) {
		return;
	}

	std::ifstream file(path, std::ios::in);
	result.reserve(size);
	result.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();
}

void FileReadAllBytes(const std::wstring& path, std::vector<char>& result) {
	auto size = FileSize(path);
	if (size == 0) {
		return;
	}

	std::ifstream file(path, std::ios::in | std::ios::binary);
	result.reserve(size);
	result.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();
}


#endif // File_h__
