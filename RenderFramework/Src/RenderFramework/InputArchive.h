#ifndef InputArchive_h__
#define InputArchive_h__


#include "Archive.h"
#include "Object.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <fstream>

class InputArchive : public Archive {
public:
	InputArchive(std::shared_ptr<std::istream> stream)
		:_stream(stream) {
	}

	virtual bool is_loading() const override {
		return true;
	}

	virtual void serialize(void* data, size_t size) override {
	
		_stream->read(reinterpret_cast<char*>(data), size);
		if(!_stream)
		{
			
		}
	}

	size_type get_offset() const override
	{
		return _stream->tellg();
	}

	void set_offset(size_type offset) override {
		_stream->seekg(offset, std::ios::beg);
	}

	~InputArchive() {}

	std::shared_ptr<std::istream> GetStream(){
		return _stream;
	}
private:
	std::shared_ptr<std::istream> _stream;
};

#endif // InputArchive_h__
