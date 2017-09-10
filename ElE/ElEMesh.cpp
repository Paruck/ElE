#include "ElEMesh.h"
#include "ElE.h"
#include <assert.h>

ElEMesh::ElEMesh() : isTriangleStrip(ElEtrue),
						vertexShader(nullptr),
						fragmentShader(nullptr)
{
}

ElEMesh::ElEMesh(_IN_ ElEfloat * const & verts,
	const _IN_ ElEsize_t & vertSize,
	_IN_ ElEfloat * const & indexarr,
	const _IN_ ElEsize_t & indexSize) : ElEMesh()
{
	assert(verts);

	for (ElEsize_t i = 0; i < vertSize; ++i)
	{
		vertex.push_back(verts[i]);
	}
	if (indexarr != nullptr)
	{
		for (ElEsize_t i = 0; i < indexSize; ++i)
		{
			vertex.push_back(indexarr[i]);
		}
		isTriangleStrip = ElEfalse;
	}
}

ElEMesh::ElEMesh(const _IN_ ElEVertex & verts,
	_IN_ ElEIndexes * const & indexarr) : ElEMesh()
{
	vertex = verts;
	if (indexarr != nullptr)
	{
		indexes = *indexarr;
		isTriangleStrip = ElEfalse;
	}
}

ElEMesh::~ElEMesh()
{
}

ElEvoid ElEMesh::draw()
{
#ifdef RASPBERRY_COMPILE

#endif
}

ElEvoid ElEMesh::initVertexShader(const _IN_ ElEchar * filename)
{
	if (vertexShader) return;
	vertexShader = new ElEShader(ElE::getGraphicsRenderer());
	vertexShader->LoadVertexShader(filename);
}

ElEvoid ElEMesh::initFragmentShader(const _IN_ ElEchar * filename)
{
	if (fragmentShader) return;
	fragmentShader = new ElEShader(ElE::getGraphicsRenderer());
	fragmentShader->LoadFragmentShader(filename);
}

ElEvoid ElEMesh::changeVertexShader(const _IN_ ElEchar * filename)
{
	return ElEvoid();
}

ElEvoid ElEMesh::changeFragmentShader(const _IN_ ElEchar * filename)
{
	return ElEvoid();
}
