#pragma once

#include <fstream>
#include <Windows.h>
#include <vector>
#include <iostream>

class TempFile {
public:
	TempFile() {
		std::vector<char> path;
		path.resize(MAX_PATH);
		GetTempPathA(path.size(), path.data());

		std::vector<char> name;
		name.resize(MAX_PATH);
		GetTempFileNameA(path.data(), "vk", 0, name.data());
		_path = name.data();
	}

	std::fstream& open(std::ios_base::openmode mode = std::ios_base::out | std::ios_base::in | std::ios_base::binary) {
		_stream.open(_path, mode);
		return _stream;
	}

	void close() {
		_stream.close();
	}

	std::vector<char> readAll() {
		_stream.seekg(0, std::ios::end);
		auto pos = _stream.tellg();
		_stream.seekg(0, std::ios::beg);

		std::vector<char> result(pos);

		if (pos > 0) {
			_stream.read(&result[0], pos);
		}
		
		return result;
	}

	template<typename T>
	TempFile& operator <<(const T& value) {
		_stream << value;
		return *this;
	}

	template<typename T>
	TempFile& operator >>(T& value) {
		_stream >> value;
		return *this;
	}

	~TempFile() {
		if (_stream.is_open()) {
			_stream.close();
		}
		DeleteFileA(_path.data());
	}
	const std::string& path() const {
		return _path;
	}

	std::fstream& stream() {
		return _stream;
	}
private:
	std::fstream _stream;
	std::string _path;
};