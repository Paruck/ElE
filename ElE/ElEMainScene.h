#pragma once
#include "ElEScene.h"
#include "ElEDefines.h"
#include "ElEShader.h"
#ifdef WIN32_COMPILE
#include "include\SDL\SDL.h"
#endif
#include "ElE.h"
#include "ElEVector2f.h"
#include "ElEMesh.h"
#include <vector>
class ElEMainScene : public ElEScene
{
public:
	ElEMainScene();
	~ElEMainScene();
	ElEvoid ElEcall Start() final;
	ElEvoid ElEcall Update() final;
	ElEvoid ElEcall Draw() final;
	ElEvoid ElEcall SceneEnd() final;
private:
    ElEMesh mesha;

	ElEvoid ElEcall refreshText();
	ElEvoid ElEcall drawEverything();
	ElEvoid ElEcall miniUpdate();
	ElEvoid ElEcall putPixel(const ElEuint& x, const ElEuint& y, const ElEuchar& r, const ElEuchar& g, const ElEuchar& b, const ElEuchar& a);
	ElEvoid ElEcall putPixel(const ElEuint& x, const ElEuint& y);
	ElEvoid ElEcall putLine(const ElEuint& x, const ElEuint& y, const ElEuint& x1, const ElEuint& y1);
	ElEvoid ElEcall putCircle(const ElEuint& x, const ElEuint& y, const ElEuint& r);
	ElEvoid ElEcall putLine(const ElEuint& x1, const ElEuint& y1);
	ElEvoid ElEcall putCircle(const ElEuint& r);
	ElEvoid ElEcall putPixelsCircumference(const ElEuint& x, const ElEuint& y);
	ElEvoid ElEcall putGeometricalFigure(const ElEuint& r, const ElEuint& vertNum);
	std::vector<std::vector<ElEVector2f>> ElEcall putSierpinskiTriangle(const ElEuint& r, const ElEuint& level);
	ElEVector2f ElEcall getMidPoint(const ElEVector2f & v1, const ElEVector2f & v2);
	inline ElEvoid ElEcall clearScreen();
};

