#pragma once
#include "ElEScene.h"
#include "ElEDefines.h"
#include "ElEShader.h"
#include "include\SDL\SDL.h"
#include "ElE.h"
#include "ElEVector2f.h"
#include <vector>
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
	ElEShader								*vertexS,
											*fragmentS;
	ElEuint									programID,
											*buffers,
											textureID,
											frameBufferID;
	ElEuchar								*pixData,
											r = 255,
											g = 255,
											b = 0,
											a = 255;
	ElEuint									cX = 0,
											cY = 0;
	const ElEfloat							PI = 3.1415f;
	const ElEfloat							degtorad = PI / 180.f;
	static const ElEfloat					tris[];
	ElESurface								*surface;
	std::vector<std::vector<ElEVector2f>>	sierpinskiTriangle;

	void __cdecl refreshText();
	void __cdecl drawEverything();
	void __cdecl miniUpdate();
	void __cdecl putPixel(const ElEuint& x, const ElEuint& y, const ElEuchar& r, const ElEuchar& g, const ElEuchar& b, const ElEuchar& a);
	void __cdecl putPixel(const ElEuint& x, const ElEuint& y);
	void __cdecl putLine(const ElEuint& x, const ElEuint& y, const ElEuint& x1, const ElEuint& y1);
	void __cdecl putCircle(const ElEuint& x, const ElEuint& y, const ElEuint& r);
	void __cdecl putLine(const ElEuint& x1, const ElEuint& y1);
	void __cdecl putCircle(const ElEuint& r);
	void __cdecl putPixelsCircumference(const ElEuint& x, const ElEuint& y);
	void __cdecl putGeometricalFigure(const ElEuint& r, const ElEuint& vertNum);
	std::vector<std::vector<ElEVector2f>> __cdecl putSierpinskiTriangle(const ElEuint& r, const ElEuint& level);
	ElEVector2f __cdecl getMidPoint(const ElEVector2f & v1, const ElEVector2f & v2);
	inline void __cdecl setR(const ElEuchar& _r) { r = _r; }
	inline void __cdecl setG(const ElEuchar& _g) { g = _g; }
	inline void __cdecl setB(const ElEuchar& _b) { b = _b; }
	inline void __cdecl setA(const ElEuchar& _a) { a = _a; }
	inline void __cdecl setCenterX(const ElEuint& x) { cX = x; }
	inline void __cdecl setCenterY(const ElEuint& y) { cY = y; }
	inline void __cdecl clearScreen();
};

