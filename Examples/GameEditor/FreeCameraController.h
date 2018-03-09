#ifndef FreeCameraController_h__
#define FreeCameraController_h__

#include <RenderFramework/Component.h>
#include "lframework/Input/Input.h"
#include <iostream>
#include <RenderFramework/Transform.h>
#include <RenderFramework/ObjectsFactory.h>

LOBJECT(FreeCameraController, Component)
public:
	float mouse_speed;
	float move_speed = 3.0f;
	static constexpr float pi = 3.14159265358979f;

	FreeCameraController() : mouse_speed(0.01f){
		_angle_x = _angle_y = 0.0f;
	}

	virtual void tick(float deltaTime) override {
		auto mice = Input::Instance()->mice();
		auto mouse = mice[0];
		_angle_x += mouse_speed * mouse->GetDx();
		_angle_y += mouse_speed * mouse->GetDy();

		_angle_y = clamp(_angle_y, -pi / 2.0f, pi / 2.0f);

		auto rv = Quaternion_f::angleAxis(_angle_y, float3(1.0f, 0.0f, 0.0f));
		auto rh = Quaternion_f::angleAxis(_angle_x, float3(0.0f, 1.0f, 0.0f));

	/*	if (mouse->GetDx() != 0) {
			std::cout << "Mouse DX: " << mouse->GetDx() << std::endl;
		}
		if (mouse->GetDy() != 0) {
			std::cout << "Mouse DY: " << mouse->GetDy() << std::endl;
		}*/

		gameObject->transform->SetLocalRotation(lm::mul(rh, rv));



		auto keyboards = Input::Instance()->keyboards();
		auto keyboard = keyboards[0];

		if(keyboard->GetKeyState(0x57)){
			gameObject->transform->SetLocalPosition(gameObject->transform->GetLocalPosition() + gameObject->transform->forward() * (deltaTime * move_speed));
		}

		if (keyboard->GetKeyState(0x53)) {
			gameObject->transform->SetLocalPosition(gameObject->transform->GetLocalPosition() - gameObject->transform->forward() * (deltaTime * move_speed));
		}

		if (keyboard->GetKeyState(0x41)) {
			gameObject->transform->SetLocalPosition(gameObject->transform->GetLocalPosition() - gameObject->transform->right() * (deltaTime * move_speed));
		}

		if (keyboard->GetKeyState(0x44)) {
			gameObject->transform->SetLocalPosition(gameObject->transform->GetLocalPosition() + gameObject->transform->right() * (deltaTime * move_speed));
		}

		
	}
private:
	float _angle_x;
	float _angle_y;
};
#endif // FreeCameraController_h__
