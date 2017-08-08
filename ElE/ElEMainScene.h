#pragma once
#include "ElEScene.h"
#include "ElEDefines.h"
#include "ElEShader.h"
class ElEMainScene : public ElEScene
{
public:
	ElEMainScene();
	~ElEMainScene();
	void __cdecl Start() final;
	void __cdecl Update() final;
	void __cdecl Draw() final;
	void __cdecl SceneEnd() final;
private:
	ElEShader	*vertexS,
				*fragmentS;
	ElEuint		programID,
				*buffers,
				textureID,
				frameBufferID;
	ElEuchar	*pixData,
				r = 255,
				g = 255,
				b = 0,
				a = 255,
				cX = 0,
				cY = 0;
	static const ElEfloat tris[];
	void __cdecl refreshText();
	void __cdecl drawEverything();
	void __cdecl miniUpdate();
	void __cdecl putPixel(const ElEuint& x, const ElEuint& y, const ElEuchar& r, const ElEuchar& g, const ElEuchar& b, const ElEuchar& a);
	void __cdecl putPixel(const ElEuint& x, const ElEuint& y);
	void __cdecl putLine(const ElEuint& x, const ElEuint& y, const ElEuint& x1, const ElEuint& y1);
	void __cdecl putCircle(const ElEuint& x, const ElEuint& y, const ElEuint& r);
	void __cdecl putLine(const ElEuint& x1, const ElEuint& y1);
	void __cdecl putCircle(const ElEuint& r);
	inline void __cdecl setR(const ElEuchar& _r) { r = _r; }
	inline void __cdecl setG(const ElEuchar& _g) { g = _g; }
	inline void __cdecl setB(const ElEuchar& _b) { b = _b; }
	inline void __cdecl setA(const ElEuchar& _a) { a = _a; }
	inline void __cdecl setCenterX(const ElEuint& x) { cX = x; }
	inline void __cdecl setCenterY(const ElEuint& y) { cY = y; }
};

