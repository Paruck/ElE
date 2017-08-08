#include "ElEMainScene.h"
#include "ElE.h"


ElEMainScene::ElEMainScene()
{
	vertexS = new ElEShader(OpenGLes20Rasp);
	fragmentS = new ElEShader(OpenGLes20Rasp);
}


ElEMainScene::~ElEMainScene()
{
}

void ElEMainScene::Start()
{
#ifdef RASPBERRY_COMPILE
	vertexS->LoadVertexShader("vShader.glsl");
	fragmentS->LoadFragmentShader("fShader.glsl");
	programID = glCreateProgram();
	glAttachShader(programID, vertexS.getID());
	glAttachShader(programID, fragmentS.getID());
	glLinkProgram();
	char log[1024];
	glGetProgramInfoLog(Id, sizeof log, NULL, log);
	printf("%d:program:\n%s\n", Id, log);

	static const ElEfloat tris[]
	{
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f
	}

	static const ElEfloat textureCoords[]
	{
		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f
	}
		
	glGenBuffers(1, &buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tris), tris, GL_STATIC_DRAW);
#endif

}

void ElEMainScene::Update()
{
#ifdef RASPBERRY_COMPILE










	eglSwapBuffers(ELE::render->render.eglRender, ELE::surface->surface.eglSurface);
#endif
	
}

void ElEMainScene::Draw()
{

}

void ElEMainScene::SceneEnd()
{

}
