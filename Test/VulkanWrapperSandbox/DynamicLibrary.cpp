#include "DynamicLibrary.h"


DynamicLibrary::DynamicLibrary(const StdFileSystem::path& path) {
	_library = LoadLibraryW(path.c_str());

	if (_library == NULL) {
		throw std::runtime_error("Failed to load library");
	}
}

void DynamicLibrary::addSearchPath(const StdFileSystem::path& path) {
	SetDllDirectoryW(path.c_str());
}

void* DynamicLibrary::getFunction(const std::string& name) {
	return GetProcAddress(_library, name.c_str());
}