#ifndef Guid_h__
#define Guid_h__

#include <array>
#include <cstdint>

struct Guid {
	union {
		std::array<uint8_t, 16> data;
		std::array<uint32_t, 4> datai;
	};

	Guid() :datai{ 0,0,0,0 } {

	}
	Guid(uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3) : datai{ i0,i1,i2,i3 } {

	}
	Guid(const std::array<uint32_t, 4>& data_i) : datai(data_i) {

	}
	Guid(const std::array<uint8_t, 16>& data) : data(data) {

	}
	Guid(const Guid& guid) : data(guid.data) {

	}
	Guid& operator =(const Guid& right) {
		data = right.data;
		return *this;
	}
	bool operator ==(const Guid& right) const {
		return std::equal(data.begin(), data.end(), right.data.begin());
	}
	bool operator !=(const Guid& right) const {
		return !std::equal(data.begin(), data.end(), right.data.begin());
	}
	bool IsZero() const {
		return (datai[0] == 0) && (datai[1] == 0) && (datai[2] == 0) && (datai[3] == 0);
	}
};

#endif // Guid_h__
