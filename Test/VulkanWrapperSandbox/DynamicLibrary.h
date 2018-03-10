#pragma once

#include <string>
#include "StdFilesystem.h"
#include <Windows.h>
#include <type_traits>

class DynamicLibrary {
public:
	DynamicLibrary(const StdFileSystem::path& path);
	static void addSearchPath(const StdFileSystem::path& path);

	template<typename FunctionPtr, typename = std::enable_if_t<std::is_function_v<std::remove_pointer_t<FunctionPtr>>>>
	FunctionPtr getFunction(const std::string& name) {
		return reinterpret_cast<FunctionPtr>(getFunction(name));
	}

	void* getFunction(const std::string& name);
private:
	HMODULE _library = NULL;
};