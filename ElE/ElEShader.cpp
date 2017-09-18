#include "ElEShader.h"


ElEShader::ElEShader(const ElEGraphicsComponents & renderT) :src(nullptr)
{
}

ElEShader::~ElEShader()
{
	if (src) delete[] src;
	if(glIsShader(id))
        glDeleteShader(id);
}

void ElEShader::LoadFragmentShader(const ElEchar * filename)
{
	shaderType = fragmentShader;
#ifdef RASPBERRY_COMPILE

	FILE* f = fopen(filename, "rb");
	assert(f);
	fseek(f, 0, SEEK_END);
	ElEint sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	src = new GLchar[sz + 1];
	fread(src, 1, sz, f);
	src[sz] = 0;
	fclose(f);
	id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(id, 1, (const GLchar**)&src, 0);
	glCompileShader(id);
#endif
}

void ElEShader::LoadVertexShader(const ElEchar * filename)
{
	shaderType = vertexShader;
#ifdef RASPBERRY_COMPILE
	FILE* f = fopen(filename, "rb");
	assert(f);
	fseek(f, 0, SEEK_END);
	int sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	src = new GLchar[sz + 1];
	fread(src, 1, sz, f);
	src[sz] = 0;
	fclose(f);
	id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(id, 1, (const GLchar**)&src, 0);
	glCompileShader(id);
#endif
}

