#include "core/Mesh.h"

#include "core/Fbx.h"
#include "core/File.h"
#include "core/Assert.h"

Mesh::Mesh(const char* path)
{
	m_path = path;
	m_vertexCount = 0;
	m_indexCount = 0;
	m_vertices = nullptr;
	m_uvs = nullptr;
	m_normals = nullptr;
	m_indices = nullptr;
}

Mesh::~Mesh()
{
}

void Mesh::onLoad()
{
	File fbxFile(m_path.c_str());
	fbxFile.load();

	if (fbxFile.getError() != Resource::RESOURCE_NOERROR)
	{
		setError(Resource::RESOURCE_LOADERROR, fbxFile.getErrorDescription());
		fbxFile.release();
		return;
	}

	fbx::Node* fbx = new fbx::Node;
	fbx::Read(fbxFile.getContent(), fbx);


	fbx::Node* Objects = fbx->getNodeAt("Objects");

	fbx::Node* objectNode = Objects->subStart;
	bool firstMesh = true;
	while (objectNode)
	{
		if ((strcmp(objectNode->name, "Model") == 0) && (strcmp(objectNode->getValueAt(1)->getString(), "Mesh") == 0))
		{
			if (firstMesh)
			{
				firstMesh = false;

				// NAME
				m_name = objectNode->getValueAt(0)->getString();

				// VERTICES
				{
					fbx::Node* vertices = objectNode->getNodeAt("Vertices");
					size_t memberCount = vertices->valueCount;
					m_vertexCount = memberCount / 3;
					m_vertices = new float[memberCount];
					fbx::Value* member = vertices->valueStart;
					for (auto i = 0u; i < memberCount; ++i)
					{
						m_vertices[i] = member->getNumber();
						member = member->next;
					}
				}

				// INDICES
				{
					fbx::Node* indices = objectNode->getNodeAt("PolygonVertexIndex");
					m_indexCount = indices->valueCount;
					m_indices = new uint32[m_indexCount];
					fbx::Value* index = indices->valueStart;
					for (auto i = 0u; i < m_indexCount; ++i)
					{
						m_indices[i] = static_cast<uint32>(index->getNumber());
						index = index->next;
					}
				}
				
				// NORMALS
				{
					fbx::Node* normals = objectNode->getNodeAt("LayerElementNormal", "Normals");
					size_t memberCount = m_vertexCount * 3;
					m_normals = new float[memberCount];
					fbx::Value* member = normals->valueStart;
					for (auto i = 0u; i < memberCount; ++i)
					{
						m_normals[i] = member->getNumber();
						member = member->next;
					}
				}
				

				// UVS
				{
					fbx::Node* uvs = objectNode->getNodeAt("LayerElementUV", "UV");
					size_t memberCount = m_vertexCount * 2;
					m_uvs = new float[memberCount];
					fbx::Value* member = uvs->valueStart;
					for (auto i = 0u; i < memberCount; ++i)
					{
						m_uvs[i] = member->getNumber();
						member = member->next;
					}
				}
			}
			else
			{
				ASSERT(false);
				setError(RESOURCE_LOADERROR, "Don't know how to handle multiple meshes yet.");
				delete fbx;
				fbxFile.release();
				return;
			}
		}

		objectNode = objectNode->next;
	}


	delete fbx;
	fbxFile.release();
}

void Mesh::onRelease()
{
	delete m_vertices;
	delete m_indices;
	delete m_normals;
	delete m_uvs;

	m_vertices = nullptr;
	m_indices = nullptr;
	m_normals = nullptr;
	m_uvs = nullptr;

	m_vertexCount = 0;
	m_indexCount = 0;
}