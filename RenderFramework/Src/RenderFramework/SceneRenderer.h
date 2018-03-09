#pragma once
#include "LEngine.h"
#include "Mesh.h"
#include "MeshGenerator.h"
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "FatalError.h"
#include "MeshRenderer.h"

#pragma comment(lib, "d3d11.lib")

class SceneRenderer {
public:
	SceneRenderer();
	void RenderScene(RendererPtr renderer, ScenePtr scene, CameraPtr camera, std::shared_ptr<RenderOutput> renderScreen);
private:
	ComPtr<ID3D12DescriptorHeap> samplers_heap;
};

