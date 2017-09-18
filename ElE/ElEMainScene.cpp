#include "ElEMainScene.h"
#include "ElE.h"
#include "ElEMatrix3x3.h"
#include "ElEInput.h"

ElEMainScene::ElEMainScene()
{

}


ElEMainScene::~ElEMainScene()
{

}

ElEvoid ElEMainScene::Start()
{
    ElEVertex verts1;
    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); // 1
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); // 2
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); // 3

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); // 4
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); // 5
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); // 6
//////////////////////////////////////////1

    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);

    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
////////////////////////////////////////////////////////////2

    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);

    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    //////////////////////////////////////////////////////////////3

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    ////////////////////////////////////////4

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    /////////////////////////////////5

    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);

    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    /////////////////////////////////6
    mesha.setVertex(verts1);

    ElEIndexes index1;
    /*for(ElEint i = 0; i < verts1.size(); ++i)
        index1.push_back(i);
    mesha.setIndexes(&index1);*/
    mesha.useTriangleStrip(ElEfalse);
    mesha.setup();

}

ElEvoid ElEMainScene::Update()
{
    if(ElEInput::getInstance()->keyPressed(kb_esc))
        exit(0);

}

ElEvoid ElEMainScene::Draw()
{
    glViewport(0, 0, ElE::getWidth(), ElE::getHeight());
    glClear(GL_COLOR_BUFFER_BIT);
    mesha.draw();
    eglSwapBuffers(ElE::getRender()->render.eglRender,ElE::getSurface()->surface.eglSurface);
    glFlush();
}

ElEvoid ElEMainScene::SceneEnd()
{

}

ElEvoid ElEMainScene::refreshText()
{

}

ElEvoid ElEMainScene::drawEverything()
{

}

ElEvoid ElEMainScene::miniUpdate()
{

}

ElEvoid ElEMainScene::putPixel(const ElEuint & x, const ElEuint & y, const ElEuchar & r, const ElEuchar & g, const ElEuchar & b, const ElEuchar & a)
{

}

ElEvoid ElEMainScene::putPixel(const ElEuint & x, const ElEuint & y)
{

}

ElEvoid ElEMainScene::putLine(const ElEuint & x, const ElEuint & y, const ElEuint & x1, const ElEuint & y1)
{

}

ElEvoid ElEMainScene::putCircle(const ElEuint & x, const ElEuint & y, const ElEuint & r)
{

}

ElEvoid ElEMainScene::putLine(const ElEuint & x1, const ElEuint & y1)
{


}

ElEvoid ElEMainScene::putCircle(const ElEuint & r)
{

}

ElEvoid ElEMainScene::putPixelsCircumference(const ElEuint & x, const ElEuint & y)
{

}

ElEvoid ElEMainScene::putGeometricalFigure(const ElEuint & r, const ElEuint & vertNum)
{

}

std::vector<std::vector<ElEVector2f>>
ElEMainScene::putSierpinskiTriangle(const ElEuint & r, const ElEuint & level)
{
    return std::vector<std::vector<ElEVector2f>>();
}

ElEVector2f ElEMainScene::getMidPoint(const ElEVector2f & v1, const ElEVector2f & v2)
{
    return ElEVector2f();
}

inline ElEvoid ElEMainScene::clearScreen()
{
}
