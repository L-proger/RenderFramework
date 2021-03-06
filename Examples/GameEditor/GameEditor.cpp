#include <Windows.h>
#include <tchar.h>
#include <RenderFramework/LEngine.h>
#include <DirectUI/Ui.h>
#include <DirectUI/Controls/UiHwndCoreWindow.h>
#include <DirectUI/Controls/UiSwapChainWindow.h>
#include <RenderFramework/RenderTargetOutput.h>
#include <RenderFramework/SwapChainOutput.h>
#include <RenderFramework/Mesh.h>
#include <RenderFramework/GameObject.h>
#include <RenderFramework/SceneRenderer.h>
#include <RenderFramework/AssetManager.h>
#include <RenderFramework/ObjMeshLoader.h>
#include "FreeCameraController.h"
#include <lframework/Input/Input.h>
#include <chrono>
#include "BoundsView.h"
#include <objbase.h>
#include <RenderFramework/AssetDatabase.h>
#include <RenderFramework/AssetMetadata.h>
#include <RenderFramework/OutputArchive.h>
#include <RenderFramework/InputArchive.h>
#include <RenderFramework/Asset.h>
#include <RenderFramework/AssetFile.h>
#include <sstream>


#pragma comment(lib, "RenderFramework.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "DirectUI.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "DXGUID.LIB")



GameObjectPtr CreateCube() {
	auto cubeObject = GameObject::create();
	cubeObject->AddComponent<MeshRenderer>()->SetMesh(Mesh::Create([](MeshPtr mesh) {MeshGenerator::Cube(mesh, true); }));
	return cubeObject;
}

struct TestObject : public Object {
	uint8_t uint8_t_;
	uint16_t uint16_t_;
	uint32_t uint32_t_;
	uint64_t uint64_t_;
	std::string string_;
	std::wstring wstring_;

	std::shared_ptr<TestObject> next;

	virtual void serialize(Archive& archive) override {
		archive << uint8_t_ << uint16_t_ << uint32_t_;
		archive << uint64_t_ << string_ << wstring_;
		auto ptr = std::static_pointer_cast<Object>(next);
		archive << ptr;
	}
};

void SaveScene(const std::wstring& path) {
	AssetDatabase::get().open_asset_file(path);

	AssetFile asset(Guid(1, 2, 3, 4), path);

	//find all game objects
	auto scene_objects = Object::FindObjectsOfType<GameObject>();

	//add all game objects and components to scene asset
	for (auto obj : scene_objects) {
		asset.AddObject(obj);
		auto components = obj->GetComponents<Component>();
		for (auto component : components) {
			asset.AddObject(component);
		}
	}

	asset.Save();
}

void CreateTestScene() {
	auto cameraGo = GameObject::create();
	cameraGo->SetName(L"Main camera");
	cameraGo->AddComponent<Camera>()->fov = 45.0f;
	cameraGo->transform->SetLocalPosition(float3(0.0f, 4.0f, -4.0f));
	cameraGo->AddComponent<FreeCameraController>();
}

void LoadScene(const std::wstring& path) {
	auto archive = AssetDatabase::get().open_asset_file(path);
}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	AllocConsole();
	FILE* stm = nullptr;
	freopen_s(&stm, "CONOUT$", "w", stdout);

	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);

	auto ints = Input::Instance();
	AssetDatabase::get().set_root_path(L"./../Assets/");

	auto editorWindow = UiSwapChainWindow::Create(L"LEngineEditorWindow");
	auto engine = LEngine::Instance();
	engine->Init(L"./../Assets/");
	engine->LoadScene("");

	std::wstring scene = L"TestScene.asset";

	CreateTestScene();
	//SaveScene(scene);

	//LoadScene(scene);

	auto outputs = engine->GetRenderer()->EnumOutputs();
	auto modes = engine->GetRenderer()->GetDisplayModes(DXGI_FORMAT_B8G8R8A8_UNORM, outputs[0]);

	editorWindow->size = UiSize(640, 480);


	auto output = std::make_shared<SwapChainOutput>(engine->GetRenderer(), editorWindow->GetWindow()->GetHwnd(), 640, 480, false);
	engine->AddOutput(output);

	auto sceneRenderer = std::make_shared<SceneRenderer>();

	ObjMeshLoader loader;
	auto ob = loader.Load(L"./../Assets/Boxes.obj");
	//ob[0]->AddComponent<BoundsView>();

	auto mat = Material::Create(Shader::Create(L"shaders/shader.fx"), "");
	auto tex = AssetManager::Instance()->LoadTexture(L"textures/1_store.dds");
	mat->GetParametersBlock().SetTexture("diffuse", tex);


	for (auto o : ob)
	{
		o->GetComponent<MeshRenderer>()->SetMaterial(mat, 0);
	}

	/*AssetMetadata meta(L"D:\\lengine\\Assets\\Boxes.obj");
	meta.Save();

	auto& factory = ObjectsFactory::instance();

	*/
	auto cameras = Object::FindObjectsOfType<Camera>();

	auto cameraGo = cameras[0]->gameObject;

	cameraGo->transform->SetLocalPosition(float3(0.0f, 0.0f, -4.0f));

	typedef std::chrono::high_resolution_clock clock;

	auto last_time = clock::now();
	float delta_time = 0.0f;

	float totalTime = 0;
	while (true) {
		auto now_time = clock::now();
		delta_time = (float)((double)std::chrono::duration_cast<std::chrono::microseconds>(now_time - last_time).count() / 1000000.0);
		last_time = now_time;
		totalTime += delta_time;
		if (totalTime >= 30.0f)
		{
			//sceneRenderer->createPSO = false;
		}
		std::chrono::high_resolution_clock::now();
		LEngine::Instance()->GetActiveScene()->tick(delta_time);
		sceneRenderer->RenderScene(engine->GetRenderer(), engine->GetActiveScene(), cameraGo->GetComponent<Camera>(), output);
		editorWindow->Update(1);
		Input::Instance()->strobe();
		//output->Present();
	}

	return 0;
}
