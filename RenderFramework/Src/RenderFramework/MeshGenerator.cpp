#include "MeshGenerator.h"
#include <vector>

void MeshGenerator::Cube(MeshPtr mesh, bool splitFaces){
	if (mesh == nullptr) {
		return;
	}

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	float3 corners[8];
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			int id = i * 4 + j;
			corners[id].x() = ((j == 0) || (j == 3)) ? -0.5f : 0.5f;
			corners[id].y() = -((float)(j >> 1) - 0.5f);
			corners[id].z() =(float)i - 0.5f;
		}
	}

	int vid[] = { 0,1,2,3, 5,4,7,6, 1,5,6,2, 4,0,3,7, 4,5,1,0, 3,2,6,7 };
	for (int i = 0; i < 24; ++i) {
		Vertex v;
		v.position.x() = corners[vid[i]].x();
		v.position.y() = corners[vid[i]].y();
		v.position.z() = corners[vid[i]].z();
		vertices.push_back(v);
	}

	float3 normals[6] = { float3(0.0f,0.0f,-1.0f), float3(0.0f,0.0f,1.0f), float3(1.0f,0.0f,0.0f), float3(-1.0f,0.0f,0.0f), float3(0.0f,1.0f,0.0f), float3(0.0f,-1.0f,0.0f) };
	int indicesBase[] = { 0,1,3,1,2,3 };
	float2 uvBase[] = { float2(0.0f,0.0f), float2(1.0f,0.0f), float2(1.0f,1.0f), float2(0.0f,1.0f) };

	mesh->SetSubmeshCount(splitFaces ? 6 : 1);

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; ++j) {
			vertices[i * 4 + j].normal = normals[i];
			vertices[i * 4 + j].uv0 = uvBase[j];
		}

		for (int j = 0; j < 6; ++j) {
			indices.push_back(indicesBase[j] + i * 4);
		}

		if (splitFaces) {
			mesh->SetIndices(indices, MeshTopology::TriangleList, i);
			indices.resize(0);
		}
	}

	mesh->SetVertices(vertices);
	
	if (!splitFaces) {
		mesh->SetIndices(indices, MeshTopology::TriangleList, 0);
	}
}

void MeshGenerator::Plane(MeshPtr mesh) {
	if (mesh == nullptr) {
		return;
	}

	float3 normal(0.0f, 1.0f, 0.0f);
	float extend = 0.5f;

	std::vector<Vertex> vertices = {
		Vertex(float4(-extend, 0.0f,  extend, 1.0f), normal, float2(0.0f,0.0f)),
		Vertex(float4(extend, 0.0f,  extend, 1.0f), normal, float2(1.0f,0.0f)),
		Vertex(float4(extend, 0.0f, -extend, 1.0f), normal, float2(1.0f,1.0f)),
		Vertex(float4(-extend, 0.0f, -extend, 1.0f), normal, float2(0.0f,1.0f)),
	};

	std::vector<uint32_t> indices = { 0,1,3,1,2,3 };

	mesh->SetSubmeshCount(1);
	mesh->SetVertices(vertices);
	mesh->SetIndices(indices, MeshTopology::TriangleList, 0);
}