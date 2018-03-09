#ifndef MeshGenerator_h__
#define MeshGenerator_h__

#include "Mesh.h"
#include "ForwardDeclarations.h"

class MeshGenerator
{
public:
	static void Cube(MeshPtr mesh, bool splitFaces);

	static void Plane(MeshPtr mesh);
};
#endif // MeshGenerator_h__

