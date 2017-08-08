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

	pixData = new ElEuchar[ElE::getWidth() * ElEuint::getHeight() * 4];
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
#endif
	
}

void ElEMainScene::Update()
{
#ifdef RASPBERRY_COMPILE

	miniUpdate();
	refreshText();
	drawEverything();
	eglSwapBuffers(ELE::getRender()->render.eglRender, ELE::getSurface()->surface.eglSurface);
#endif
	
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
	//aqui va todo el codigo chido pa no confundirse
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
	//diseñar este pedo en putiza
	ElEint	dX = x1 > x ? x1 - x : x - x1, // -x, -y && x, y
			dY = y1 > y ? y1 - y : y - y1; // -x, -y && x, y
	if (dY > dX) // y > x 
	{
		if (dX < 0) 
		{
			if ((0 - dX) > dY)
			{
				ElEint	E = 2 * dY,
						NE = 2 * (dY - dX),
						d = 2 * dY - dX,
						xt = x + 1,
						yt = y;
				putPixel(x, y);
				while (xt <= y1)
				{
					if (d > 0)
					{
						--yt;
						d += NE;
					}
					else
						d += E;
					putPixel(xt, yt);
					++xt;
				}
				return;
			}
			ElEint	E = 2 * dX,
					NE = 2 * (dX - dY),
					d = 2 * dX - dY,
					xt = y + 1,
					yt = x;
			putPixel(x, y);
			while (xt <= y1)
			{
				if (d > 0)
				{
					--yt;
					d += NE;
				}
				else
					d += E;
				putPixel(xt, yt);
				++xt;
			}
		}
		else
		{
			ElEint	E = 2 * dX,
					NE = 2 * (dX - dY),
					d = 2 * dX - dY,
					xt = y + 1,
					yt = x;
			putPixel(x, y);
			while (xt <= y1)
			{
				if (d > 0)
				{
					++yt;
					d += NE;
				}
				else
					d += E;
				putPixel(xt, yt);
				++xt;
			}
		}
	} 
	else //x > y
	{
		if (dY < 0)
		{
			ElEint	E = 2 * dY,
					NE = 2 * (dY - dX),
					d = 2 * dY - dX,
					xt = x + 1,
					yt = y;
			putPixel(x, y);
			while (xt <= x1)
			{
				if (d > 0)
				{
					--yt;
					d += NE;
				}
				else
					d += E;
				putPixel(xt, yt);
				++xt;
			}
		}
		else
		{
			ElEint	E = 2 * dY,
					NE = 2 * (dY - dX),
					d = 2 * dY - dX,
					xt = x + 1,
					yt = y;
			putPixel(x, y);
			while (xt <= x1)
			{
				if (d > 0)
				{
					++yt;
					d += NE;
				}
				else
					d += E;
				putPixel(xt, yt);
				++xt;
			}
		}
	}
}

void ElEMainScene::putCircle(const ElEuint & x, const ElEuint & y, const ElEuint & r)
{
	//este tambien
}

void ElEMainScene::putLine(const ElEuint & x1, const ElEuint & y1)
{
	//este es lo mismo que la puta linea solo hay que usar los centros
}

void ElEMainScene::putCircle(const ElEuint & r)
{
	//esto es lo mismo que el pinche circulo solo hay que usar los centros
}
