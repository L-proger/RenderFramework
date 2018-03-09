#include "Archive.h"



Archive& Archive::operator << (AssetFileLink& value) {
	serialize(&value, sizeof(value)); return *this;
}