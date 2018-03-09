#ifndef OutputArchive_h__
#define OutputArchive_h__

#include "Archive.h"
#include "Object.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <fstream>

class OutputArchive : public Archive {
public:
	OutputArchive(std::shared_ptr<std::ostream> stream)
		:_stream(stream) {
	//	_stream = std::ofstream(path, std::ios::binary);
	}

	virtual bool is_loading() const override {
		return false;
	}

	size_type get_offset() const override {
		return _stream->tellp();
	}

	void set_offset(size_type offset) override {
		_stream->seekp(offset, std::ios::beg);
	}

	virtual void serialize(void* data, size_t size) override {
		_stream->write(reinterpret_cast<char*>(data), size);
	}

	virtual void flush() override {
		if(_stream->good()){
			_stream->flush();
		}
	}

	~OutputArchive() {
		flush();
	}
	std::shared_ptr<std::ostream> GetStream()
	{
		return _stream;
	}
private:
	std::shared_ptr<std::ostream> _stream;
	std::vector<std::shared_ptr<Object>> _processed_objects;
};


#endif // OutputArchive_h__
