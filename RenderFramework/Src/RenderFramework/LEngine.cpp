#include "LEngine.h"
#include "AssetManager.h"

std::shared_ptr<LEngine> LEngine::_instance = nullptr;

std::shared_ptr<LEngine> LEngine::Instance() {
	if (_instance == nullptr) {
		_instance = std::shared_ptr<LEngine>(new LEngine());
	}
	return _instance;
}

ScenePtr LEngine::GetActiveScene() {
	return _activeScene;
}

void LEngine::Init(const std::wstring& assetsPath) {
	AssetManager::Instance()->SetAssetsFolder(assetsPath);
	_renderer->Init();
}

void LEngine::LoadScene(const std::string& path) {
	_activeScene = nullptr;
	_activeScene = std::make_shared<Scene>();
	_activeScene->SetName("New scene");
}