#pragma once

#include "Mesh.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <lmath/lmath.h>
#include <stack>
#include <sstream>
#include <array>
#include <tuple>
#include <map>
#include <cstdio>
#include <filesystem>

#include "MeshRenderer.h"
using namespace lm;


struct ObjVertex {
	int32_t vid;
	int32_t tid;
	int32_t nid;
};

struct ObjFace {
	int32_t sid;
	int32_t mid;
	std::array<ObjVertex, 3> vertices;
};

class ObjGroup {
public:
	ObjGroup(std::string objName) 
		:name(objName), smoothGroupsEnabled(true), activeSmoothGroup(0)
	{

	}
	void AddFace(int32_t matId, const ObjVertex& v0, const ObjVertex& v1, const ObjVertex& v2) {
		ObjFace f;
		f.vertices[0] = v0;
		f.vertices[1] = v1;
		f.vertices[2] = v2;
		f.mid = matId;
		f.sid = activeSmoothGroup;
		faces.push_back(f);

		if (std::find(materials.begin(), materials.end(), matId) == materials.end()) {
			materials.push_back(matId);
		}
	}
	std::vector<uint32_t> materials;
	std::string name;
	std::vector<ObjFace> faces;
	int32_t activeSmoothGroup;
	bool smoothGroupsEnabled;
};

class ObjMeshLoader {
public:
	friend class ObjGroup;
	ObjMeshLoader() : _activeMatId(-1){

	}

	std::string read_file(std::wstring path)
	{
		FILE* file = nullptr;
		auto err = _wfopen_s(&file, path.c_str(), L"rb");

		fseek(file, 0, SEEK_END);
		auto file_size = ftell(file);

		std::string str;
		str.resize(file_size);
		fseek(file, 0, SEEK_SET);

		auto done = fread_s(&str[0], file_size, 1, file_size, file);
		fclose(file);
		return str;
	}
	std::vector<GameObjectPtr> Load(const std::wstring& path) {
		std::vector<GameObjectPtr> result;

		/*if (!file1.good()) {
			return result;
		}*/

		auto str = read_file(path);

		
		std::stringstream buffer(str);
		std::vector<char> line_buffer;
		line_buffer.resize(8192);


		std::string previous_line;
		std::string line;
		//while (buffer.getline(&line_buffer[0], line_buffer.size())) {
		while (std::getline(buffer, line)) {
			
			//std::string line(&line_buffer[0]);
			if (line.size() < 3) {
				continue;
			}
			switch(line[0]){
			case 'v':
				switch (line[1]) {
				case ' ': {
					float3 v;
					sscanf_s(&line[2], "%f%f%f", &v.x(), &v.y(), &v.z());
					_vertices.push_back(v);
					break;
				}
				case 'n': {
					float3 n;
					sscanf_s(&line[2], "%f%f%f", &n.x(), &n.y(), &n.z());
					_normals.push_back(n);
					break;
				}
				case 't':
					float3 t;
					sscanf_s(&line[2], "%f%f%f", &t.x(), &t.y(), &t.z());
					_texcoords.push_back(t);
					break;
				}
				break;
			case 'f': {
				bool is_open = false;
				size_t start = 2;
				int slash_pos_0 = 0;
				int slash_pos_1 = 0;

				if(line[line.size() - 1] == '\r')
				{
					line[line.size() - 1] = ' ';
				}else
				{
					line += " ";
				}
				
				std::vector<ObjVertex> fVertices;
				for (size_t i = 2; i < line.size(); ++i) {
					if (line[i] == ' ') {
						if (is_open) { //finalize chunk
							is_open = false;
							ObjVertex v;
							if (slash_pos_0 == -1) {
								auto pos2 = (int)buffer.tellg();
								sscanf_s(&line[start], "%d", &v.vid);
								v.tid = v.nid = -1;
							} else if (slash_pos_1 == -1) {
								sscanf_s(&line[start], "%d/%d", &v.vid, &v.tid);
								v.nid = -1;
							} else {
								if (slash_pos_1 - slash_pos_0 == 1) {
									sscanf_s(&line[start], "%d//%d", &v.vid, &v.nid);
									v.tid = -1;
								} else {
									sscanf_s(&line[start], "%d/%d/%d", &v.vid, &v.tid, &v.nid);
								}
							}
							fVertices.push_back(v);
						}
					} else {
						if (!is_open) {
							start = i;
							slash_pos_0 = -1;
							slash_pos_1 = -1;
							is_open = true;
						} else {
							if (line[i] == '/') {
								if (slash_pos_0 == -1) {
									slash_pos_0 = i;
								} else {
									slash_pos_1 = i;
								}
							}
						}
					}

					
				}

				//emit triangles (split if quads)
				if (fVertices.size() == 3) {
					_groups[_groups.size() - 1].AddFace(_activeMatId, fVertices[0], fVertices[1], fVertices[2]);
				} else if (fVertices.size() == 4) {
					_groups[_groups.size() - 1].AddFace(_activeMatId, fVertices[0], fVertices[1], fVertices[2]);
					_groups[_groups.size() - 1].AddFace(_activeMatId, fVertices[0], fVertices[2], fVertices[3]);
				}
				break;
			} 
			case 'g': {
				auto name = line.substr(2);
				_groups.push_back(ObjGroup(name));
				break;
			}
			case 's':
				if (line.find("off") != std::string::npos) {
					_groups[_groups.size() - 1].smoothGroupsEnabled = false;
				} else {
					sscanf_s(&line[2], "%d", &_groups[_groups.size() - 1].activeSmoothGroup);
				}
				break;
			case 'm': {
				std::stringstream ss(line);
				std::string key, value;
				ss >> key;
				ss >> value;
				_mtlLibName = value;
				std::cout << "Found material library: " << value << std::endl;
				break;
			}
			case 'u': {
				std::stringstream ss(line);
				std::string key, value;
				ss >> key;
				ss >> value;
				SetActiveMaterial(value);
				break;
			}
			}

			previous_line = line;
		}


		auto mtllib_path = obj_to_mtl_path(path);

		_mats = load_mtllib(mtllib_path);

		for (auto& group : _groups) {
			result.push_back(UnpackGroup(group));
		}
		return result;
	}
private:
	std::vector<MaterialPtr> _mats;
	std::wstring obj_to_mtl_path(const std::wstring& obj_path){
		std::experimental::filesystem::path src(obj_path);
		auto dst = src.parent_path();
		return dst.append(_mtlLibName).wstring();
	}

	std::vector<MaterialPtr> load_mtllib(const std::wstring& path){
		std::vector<MaterialPtr> result;

		auto text = std::ifstream(path);

		std::string line;
		auto default_shader = Shader::Create(L"shaders/default.fx");

		MaterialPtr active_material;
		while(std::getline(text, line))
		{
			if(line[0] == '#' || line.empty()){
				continue;
			}

			std::string word;
			std::stringstream ls(line);
			ls >> word;

			if (word == "newmtl") {
				std::string mat_name;
				ls >> mat_name;
				if(active_material != nullptr)
				{
					result.push_back(active_material);
				}
				active_material = Material::Create(default_shader, mat_name);
				
			} else {
				if (active_material == nullptr) {
					continue;
				} else {
					if(word == "Kd")
					{
						std::vector<float> color;
						float tmp = 0.0f;
						while(ls >> tmp)
						{
							color.push_back(tmp);
						}

						if(color.size() == 3)
						{
							active_material->GetParametersBlock().SetValue(Material::DiffuseColorName(), float4(color[0], color[1], color[2], 1.0f));
						}
					}
				}
			}
		}

		if (active_material != nullptr) {
			result.push_back(active_material);
		}

		return result;

	}

	typedef std::tuple<ObjVertex, Vertex> VertexPair;
	GameObjectPtr UnpackGroup(const ObjGroup& group) {
		std::vector<std::vector<ObjFace*>> facesTable;
		facesTable.resize(_vertices.size());
		std::vector<Vertex> vertices;
		std::map<size_t, std::vector<uint32_t>> submeshes;

		//EmitGeometry(group, vertices, submeshes);
		EmitGeometrySimple(group, vertices, submeshes);

		auto mesh = Mesh::Create();
		mesh->SetSubmeshCount(group.materials.size());
		mesh->SetVertices(vertices);



		int id = 0;
		for(auto& p : submeshes)
		{
			mesh->SetIndices(p.second, MeshTopology::TriangleList, id);
			id++;
		}

		auto obj = GameObject::create();
		obj->AddComponent<MeshRenderer>()->SetMesh(mesh);



		for (size_t i = 0; i < group.materials.size(); ++i){
			auto mat_id = group.materials[i];

			obj->GetComponent<MeshRenderer>()->SetMaterial(_mats[mat_id], i);
		}

		mesh->RecalculateBounds();
		return obj;
	}

	/*MeshPtr BuildMesh(ObjGroup& group) {
		std::vector<Vertex> vertices;
		std::vector<int32_t> indices;
		EmitGeometry(group, vertices, indices);

		auto mesh = Mesh::Create();
		mesh->SetSubmeshCount(group.materials.size());
		return mesh;
	}*/

	void EmitGeometry(const ObjGroup& group, std::vector<Vertex>& vertices, std::map<size_t, std::vector<uint32_t>>& submeshes) {
		auto vComp = [](ObjVertex v1, ObjVertex v2) {
			return (v1.vid == v2.vid) && (v1.tid == v2.tid) && (v1.nid && v2.nid);
		};

		std::vector<ObjVertex> tmpVertices;

		for (auto& f : group.faces) {
			for (auto& v : f.vertices) {
				int id = -1;
				for (size_t i = 0; i < tmpVertices.size(); ++i) {
					if (vComp(tmpVertices[i], v)) {
						id = i;
						break;
					}
				}

				if (id == -1) {
					id = tmpVertices.size();
					tmpVertices.push_back(v);
					Vertex vertex;
					vertex.position = float4(_vertices[v.vid - 1], 1.0f);
					vertex.normal = _normals[v.nid - 1];
					vertex.uv0 = _texcoords[v.tid - 1].xy();
					vertices.push_back(vertex);
				}

				submeshes[f.mid].push_back(id);
			}
		}
	}

	void EmitGeometrySimple(const ObjGroup& group, std::vector<Vertex>& vertices, std::map<size_t, std::vector<uint32_t>>& submeshes) {
		int id = 0;
		for (auto& f : group.faces) {
			for (auto& v : f.vertices) {
				Vertex vertex;
				vertex.position = float4(_vertices[v.vid - 1], 1.0f);
				vertex.normal = _normals[v.nid - 1];
				vertex.uv0 = _texcoords[v.tid - 1].xy();
				vertices.push_back(vertex);
				submeshes[f.mid].push_back(id);
				++id;
			}
		}
	}

	void SetActiveMaterial(const std::string& name) {
		for (size_t i = 0; i < _materials.size(); ++i) {
			if (_materials[i] == name) {
				_activeMatId = i;
				return;
			}
		}
		_activeMatId = _materials.size();
		_materials.push_back(name);
	}
	int _activeMatId;
	std::string _mtlLibName;
	std::vector<float3> _vertices;
	std::vector<float3> _normals;
	std::vector<float3> _texcoords;
	std::vector<std::string> _materials;
	std::vector<ObjGroup> _groups;
};