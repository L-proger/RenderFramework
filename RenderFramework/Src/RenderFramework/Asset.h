#ifndef Asset_h__
#define Asset_h__

#include <Windows.h>
#include <cstdint>
#include <array>
#include <algorithm>
#include "Guid.h"

class AssetFileLink {
public:
	using LocalFileID = std::uint32_t;
	static constexpr LocalFileID InvalidID = -1;

	Guid fileGuid;
	LocalFileID localId;

	AssetFileLink():localId(InvalidID){}

	AssetFileLink(const AssetFileLink& link) :fileGuid(link.fileGuid), localId(link.localId) {}

	AssetFileLink(Guid _fileGuid, LocalFileID _localId) :fileGuid(_fileGuid), localId(_localId) {}

	AssetFileLink& operator=(const AssetFileLink& link) {
		fileGuid = link.fileGuid;
		localId = link.localId;
		return *this;
	}

	bool operator==(const AssetFileLink& link) const {
		return (fileGuid == link.fileGuid) && (localId == link.localId);
	}

	bool operator!=(const AssetFileLink& link) const {
		return (fileGuid != link.fileGuid) || (localId != link.localId);
	}

	bool IsValid() const{
		return (localId != InvalidID) && !fileGuid.IsZero();
	}
};



#endif // Asset_h__
