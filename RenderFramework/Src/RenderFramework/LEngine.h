#ifndef Application_h__
#define Application_h__

#include "Scene.h"
#include "ForwardDeclarations.h"
#include <string>
#include "Renderer.h"
#include "RenderOutput.h"

class LEngine {
public:
	static std::shared_ptr<LEngine> Instance();
	friend class Scene;
	ScenePtr GetActiveScene();
	void LoadScene(const std::string& path);
	void Init(const std::wstring& assetsPath);
	RendererPtr& GetRenderer() {
		return _renderer;
	}
	void AddOutput(RenderOutputPtr output) {
		_outputs.push_back(output);
	}
	std::vector<RenderOutputPtr> GetOutputs() {
		return _outputs;
	}
private:
	LEngine() 
	{
		_renderer = std::make_shared<Renderer>();
	}
	RendererPtr _renderer;
	ScenePtr _activeScene;
	static std::shared_ptr<LEngine> _instance;
	std::vector<RenderOutputPtr> _outputs;
};

#endif // Application_h__
