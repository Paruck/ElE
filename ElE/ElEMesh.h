#pragma once
#include "ElEDefines.h"
#include "ElEVector.h"
#include "ElEShader.h"

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
	ElEvoid __cdecl draw();
	inline ElEVertex __cdecl getVertex() const { return vertex; }
	inline ElEIndexes __cdecl getIndexes() const { return indexes; }
	inline ElEvoid __cdecl	setVertex(const _IN_ ElEVertex& verts) { vertex = verts; }
	inline ElEvoid __cdecl setIndexes(_IN_ ElEIndexes* const& indexarr)
	{ indexes = *indexarr; }
	inline ElEvoid __cdecl useTriangleStrip(const _IN_ ElEbool& val)
	{ isTriangleStrip = val; }
	inline ElEbool __cdecl usingTriangleStrip() { return isTriangleStrip; }
	ElEvoid __cdecl initVertexShader(const _IN_ ElEchar* filename);
	ElEvoid __cdecl initFragmentShader(const _IN_ ElEchar* filename);
	ElEvoid __cdecl changeVertexShader(const _IN_ ElEchar* filename);
	ElEvoid __cdecl changeFragmentShader(const _IN_ ElEchar* filename);
private:
	ElEVertex	vertex;
	ElEIndexes	indexes;
	ElEbool		isTriangleStrip;
	ElEShader	*vertexShader,
				*fragmentShader;
};

