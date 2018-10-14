#pragma once

#include <vector>
#include <string>
#include "TempFile.h"
#include <stdexcept>

enum class ShaderCompilerStage {
	vert,
	tesc,
	tese, 
	geom, 
	frag, 
	comp
};

inline const char* toString(ShaderCompilerStage stage) {
	switch (stage) {
	case ShaderCompilerStage::vert:
		return "vert";
	case ShaderCompilerStage::tesc:
		return "tesc";
	case ShaderCompilerStage::tese:
		return "tese";
	case ShaderCompilerStage::geom:
		return "geom";
	case ShaderCompilerStage::frag:
		return "frag";
	case ShaderCompilerStage::comp:
		return "comp";
	}
}

struct ShaderCompilerResult {
	bool success;
	std::string errors;
	std::vector<char> binary;
};

class ShaderCompiler {
public:
	static ShaderCompilerResult compile(const std::string& code, ShaderCompilerStage stage) {
		ShaderCompilerResult result;
		auto inputFile = TempFile();
		inputFile.open();
		inputFile << code;
		inputFile.close();

		auto outputVertexFile = TempFile();

		auto errorFile = TempFile();

		std::string cmd = R"(C:\VulkanSDK\1.1.82.1\Bin32\glslangValidator.exe -V )";
		cmd += inputFile.path() + " -o " + outputVertexFile.path() + " -S " + toString(stage) + " >" + errorFile.path();

		int errorCode = std::system(cmd.c_str());
		errorFile.open(std::ios_base::in | std::ios_base::binary);
		auto errorData = errorFile.readAll();
		std::string error(errorData.data(), errorData.size());
		result.errors = error;

		result.success = errorCode == 0;

		outputVertexFile.open(std::ios_base::in | std::ios_base::binary);
		result.binary = outputVertexFile.readAll();
		return result;
	}
};