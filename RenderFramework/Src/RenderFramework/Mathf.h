#pragma once

class Mathf {
public:
	static float Pi() {
		return  3.1415926535897932384626f;
	}
	static float RadToDeg() {
		return 180.0f / Pi();
	}
	static float DegToRad() {
		return Pi() / 180.0f;
	}
};