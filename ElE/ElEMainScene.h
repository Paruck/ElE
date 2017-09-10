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
	ElEvoid __cdecl Start() final;
	ElEvoid __cdecl Update() final;
	ElEvoid __cdecl Draw() final;
	ElEvoid __cdecl SceneEnd() final;
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
	static const ElEfloat					tris[];
	ElESurface								*surface;
	std::vector<std::vector<ElEVector2f>>	sierpinskiTriangle;

	ElEvoid __cdecl refreshText();
	ElEvoid __cdecl drawEverything();
	ElEvoid __cdecl miniUpdate();
	ElEvoid __cdecl putPixel(const ElEuint& x, const ElEuint& y, const ElEuchar& r, const ElEuchar& g, const ElEuchar& b, const ElEuchar& a);
	ElEvoid __cdecl putPixel(const ElEuint& x, const ElEuint& y);
	ElEvoid __cdecl putLine(const ElEuint& x, const ElEuint& y, const ElEuint& x1, const ElEuint& y1);
	ElEvoid __cdecl putCircle(const ElEuint& x, const ElEuint& y, const ElEuint& r);
	ElEvoid __cdecl putLine(const ElEuint& x1, const ElEuint& y1);
	ElEvoid __cdecl putCircle(const ElEuint& r);
	ElEvoid __cdecl putPixelsCircumference(const ElEuint& x, const ElEuint& y);
	ElEvoid __cdecl putGeometricalFigure(const ElEuint& r, const ElEuint& vertNum);
	std::vector<std::vector<ElEVector2f>> __cdecl putSierpinskiTriangle(const ElEuint& r, const ElEuint& level);
	ElEVector2f __cdecl getMidPoint(const ElEVector2f & v1, const ElEVector2f & v2);
	inline ElEvoid __cdecl setR(const ElEuchar& _r) { r = _r; }
	inline ElEvoid __cdecl setG(const ElEuchar& _g) { g = _g; }
	inline ElEvoid __cdecl setB(const ElEuchar& _b) { b = _b; }
	inline ElEvoid __cdecl setA(const ElEuchar& _a) { a = _a; }
	inline ElEvoid __cdecl setCenterX(const ElEuint& x) { cX = x; }
	inline ElEvoid __cdecl setCenterY(const ElEuint& y) { cY = y; }
	inline ElEvoid __cdecl clearScreen();
};

