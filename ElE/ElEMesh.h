#pragma once
#include "ElEDefines.h"
#include "ElEVector.h"
#include "ElEMaterial.h"

#ifdef RASPBERRY_COMPILE
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#endif

class ElEMesh
{
public:
	ElEMesh();
	ElEMesh(_IN_ ElEfloat* const& verts,
		const _IN_ ElEsize_t & vertSize,
		_IN_ ElEfloat* const& indexarr = nullptr,
		const _IN_ ElEsize_t & indexSize = 0);
	ElEMesh(const _IN_ ElEVertex& verts, _IN_ ElEIndexes* const& indexarr = nullptr);
	~ElEMesh();
	ElEvoid ElEcall draw();
	inline ElEVertex ElEcall getVertex() const { return vertex; }
	inline ElEIndexes ElEcall getIndexes() const { return indexes; }
	inline ElEvoid ElEcall	setVertex(const _IN_ ElEVertex& verts)
	{ modifiedVertex = ElEtrue; vertex = verts; }
	inline ElEvoid ElEcall setIndexes(_IN_ ElEIndexes* const& indexarr)
	{ modifiedIndexes = ElEtrue; indexes = *indexarr; }
	inline ElEvoid ElEcall useTriangleStrip(const _IN_ ElEbool& val)
	{ isTriangleStrip = val; }
	inline ElEbool ElEcall usingTriangleStrip() { return isTriangleStrip; }
	inline ElEMaterial& getMaterial(){ return material; }
	ElEvoid ElEcall initVertexShader(const _IN_ ElEchar* filename);
	ElEvoid ElEcall initFragmentShader(const _IN_ ElEchar* filename);
	ElEvoid ElEcall changeVertexShader(const _IN_ ElEchar* filename);
	ElEvoid ElEcall changeFragmentShader(const _IN_ ElEchar* filename);
	ElEvoid ElEcall setup();
private:
	ElEVertex	vertex;
	ElEIndexes	indexes;
	ElEbool		isTriangleStrip,
                modifiedVertex,
                modifiedIndexes;
	ElEMaterial material;
	ElEuint     meshName,
                indexName;

};

