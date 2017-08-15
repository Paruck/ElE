#include "ElEMainScene.h"
#include "ElE.h"

const ElEfloat ElEMainScene::tris[]{
	-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f
};

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

	pixData = new ElEuchar[ElE::getWidth() * ElE::getHeight() * 4];
	for (int i = ElE::getWidth() * ElEuint::getHeight() * 4; i--;)
		pixData[i] = 255;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ElE::getWidth(), ElEuint::getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pixData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &framebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#else
	pixData = new ElEuchar[ElE::getWidth() * ElE::getHeight() * 4];
	for (int i = ElE::getWidth() * ElE::getHeight() * 4; i--;)
		pixData[i] = 0;
	surface = new ElESurface(ElE::getGraphicsRenderer());
	surface->surface.sdlSurface = SDL_CreateRGBSurface(0, ElE::getWidth(), ElE::getHeight(), 32, 0, 0, 0, 0);
	//surface->surface.sdlSurface = SDL_CreateRGBSurfaceWithFormat(0, ElE::getWidth(), ElE::getHeight(), 32,
		//SDL_PIXELFORMAT_RGBA32);

#endif
	
}

void ElEMainScene::Update()
{
	miniUpdate();
	refreshText();
	drawEverything();
#ifdef RASPBERRY_COMPILE

	eglSwapBuffers(ELE::getRender()->render.eglRender, ELE::getSurface()->surface.eglSurface);
#else
	SDL_Texture* renderTexture = SDL_CreateTextureFromSurface(ElE::getRender()->render.sdlRender,
		surface->surface.sdlSurface);
	SDL_RenderCopy(ElE::getRender()->render.sdlRender, renderTexture,
		nullptr, nullptr);
	SDL_DestroyTexture(renderTexture);
#endif
	clearScreen();
	
}

void ElEMainScene::Draw()
{

}

void ElEMainScene::SceneEnd()
{

}

void ElEMainScene::refreshText()
{
#ifdef RASPBERRY_COMPILE
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ElE::getWidth(), ElEuint::getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, pixData);
	glBindTexture(GL_TEXTURE_2D, 0);
#else
	surface->surface.sdlSurface->pixels = pixData;
#endif
}

void ElEMainScene::drawEverything()
{
#ifdef RASPBERRY_COMPILE
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glViewport(0, 0, ElE::getWidth(), ElE::getWidth());

	glUseProgram(programID);

	glUniform2f(glGetUniformLocation(programID, "offset"), 0, 0);
	glUniform2f(glGetUniformLocation(programID "scale"), 1, 1);
	glUniform1i(glGetUniformLocation(programID, "tex"), 0);

	glBindBuffer(GL_ARRAY_BUFFER, tris);
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLuint loc = glGetAttribLocation(programID, "vertex");
	glVertexAttribPointer(loc, 4, GL_FLOAT, 0, 16, 0);
	glEnableVertexAttribArray(loc);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable(GL_BLEND);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFinish();
	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, ElE::getWidth(), ElE::getHeight());
#endif
}

void ElEMainScene::miniUpdate()
{
#pragma region LineCircle
	setR(rand() % 255);
	setG(rand() % 255);
	setB(rand() % 255);
	setA(0);
	setCenterX(rand() % ElE::getWidth());
	setCenterY(rand() % ElE::getHeight());
	for (int i = 360; i--;)
		putLine((100 * cos(degtorad*i)) + cX, (100 * sin(degtorad*i)) + cY);
#pragma endregion EndLineCircle
#pragma region Circle
	setCenterX(4012 << 1);
	setCenterY(4012 << 1);
	putCircle(50);
#pragma endregion EndCircle

}

void ElEMainScene::putPixel(const ElEuint & x, const ElEuint & y, const ElEuchar & r, const ElEuchar & g, const ElEuchar & b, const ElEuchar & a)
{
	int offset = (x + (y * ElE::getWidth())) * 4;
	if (offset < 0 || offset > ElE::getWidth() * ElE::getHeight() *4)
		return;

	pixData[offset] = r;
	pixData[offset + 1] = g;
	pixData[offset + 2] = b;
	pixData[offset + 3] = a;
}

void ElEMainScene::putPixel(const ElEuint & x, const ElEuint & y)
{
	int offset = (x + (y * ElE::getWidth())) * 4;
	if (offset < 0 || offset > ElE::getWidth() * ElE::getHeight() * 4)
		return;

	pixData[offset] = r;
	pixData[offset + 1] = g;
	pixData[offset + 2] = b;
	pixData[offset + 3] = a;
}

void ElEMainScene::putLine(const ElEuint & x, const ElEuint & y, const ElEuint & x1, const ElEuint & y1)
{
	//dise�ar este pedo en putiza
	ElEint	dx = x1 - x,
			dy = y1 - y,
			d,
			signx = dx > 0 ? 1 : -1,
			signy = dy > 0 ? 1 : -1,
			yt = y,
			xt = x;
	dx = abs(dx);
	dy = abs(dy);

	if (dy > dx) // y > x 
	{
		ElEint	E = 2 * dx,
				NE = 2 * (dx - dy),
				d = 2 * dx - dy;
		while (yt != y1)
		{
			if (xt > ElE::getWidth() || xt < 0) { printf("wtf"); return; }
			if (yt > ElE::getHeight() || yt < 0) { printf("wtf"); return; }
			putPixel(xt, yt);
			if (d > 0)
			{
				d += NE;
				xt += signx;
			}
			else
				d += E;
			yt += signy;
		}
	}
	else //x > y 
	{
		ElEint	E = 2 * dy,
				NE = 2 * (dy - dx),
				d = 2 * dy - dx;
		while (xt != x1)
		{
			if (xt > ElE::getWidth() || xt < 0) { printf("wtf"); return; }
			if (yt > ElE::getHeight() || yt < 0) { printf("wtf"); return; }
			putPixel(xt, yt);
			if (d > 0)
			{
				yt += signy;
				d += NE;
			}
			else
				d += E;
			xt += signx;
		}
	}
}

void ElEMainScene::putCircle(const ElEuint & x, const ElEuint & y, const ElEuint & r)
{
	//este tambien
	ElEint	x1 = r - 1,
		y1 = 0,
		dx = 1,
		dy = 1,
		d = dx - (r << 1);
	while (x1 >= y1)
	{
		putPixelsCircumference(x1, y1);
		if (d <= 0)
		{
			++y1;
			d += (dy += 2);
		}
		else
		{
			--x1;
			d += ((0-r) << 1) + (dx += 2);
		}
		//d <= 0 ? ++y1, d += dy, dy += 2 : --x1, dx += 2, d += ((0 - r) << 1) + dx;
	}
}

void ElEMainScene::putLine(const ElEuint & x1, const ElEuint & y1)
{
	putLine(cX, cY, x1, y1);
	
}

void ElEMainScene::putCircle(const ElEuint & r)
{
	putCircle(cX, cY, r);
	//esto es lo mismo que el pinche circulo solo hay que usar los centros
}

void ElEMainScene::putPixelsCircumference(const ElEuint & x, const ElEuint & y)
{
	putPixel(cX + x, cY + y);
	putPixel(cX + y, cY + x);
	putPixel(cX - y, cY + x);
	putPixel(cX - x, cY + y);
	putPixel(cX - x, cY - y);
	putPixel(cX - y, cY - x);
	putPixel(cX + y, cY - x);
	putPixel(cX + x, cY - y);
}

void ElEMainScene::putGeometricalFigure(const ElEuint & r, const ElEuint & vertNum)
{
	ElEVector<ElEVector2f>	vertex;
	ElEfloat				divOffset = 360 / vertNum,
							currDiv = 0;
	for (ElEuint i = vertNum; i--; currDiv += divOffset)
		vertex.add(ElEVector2f(	cX + (r * cos(degtorad * currDiv)),
								cY + (r * sin(degtorad * currDiv))));
	for (ElEuint i = vertNum; i--;)
	{
		putLine(vertex.at(i)->x, vertex.at(i)->y,
			vertex.at((i + 1) % vertNum)->x, vertex.at((i + 1) % vertNum)->x);
	}
}

void ElEMainScene::putSerspinskiTriangle(const ElEuint & r, const ElEuint & level)
{
	ElEVector<ElEVector<ElEVector2f>>	vertex;
	ElEfloat				divOffset = 360 / 3,
							currDiv = 0;
	ElEuint					currTriangleArray = 0,
							sizeBeforeDivisions;
	vertex.add(ElEVector<ElEVector2f>());
	for (ElEuint i = 3; i--; currDiv += divOffset)
		vertex.at(0)->add(ElEVector2f(cX + (r * cos(degtorad * currDiv)),
			cY + (r * sin(degtorad * currDiv))));
	for (ElEuint i = level; i--;)
	{
		sizeBeforeDivisions = vertex.count();
		for (ElEuint j = currTriangleArray; j < sizeBeforeDivisions; ++j)
		{
			vertex.add(ElEVector<ElEVector2f>());
			for (ElEuint k = 3; k--;)
			{
				vertex.at(vertex.count()-1)->add(ElEVector2f((vertex.at(j)->at((k + 1) % vertex.at(j)->count())->x - vertex.at(j)->at(k)->x) / 2,
					(vertex.at(j)->at((k + 1) % vertex.count())->y - vertex.at(j)->at(k)->y) / 2));
			}
			++currTriangleArray;
		}
	}
}

inline void ElEMainScene::clearScreen()
{
	for (int i = ElE::getWidth() * ElE::getHeight() * 4; i--;)
		pixData[i] = 0;
}
