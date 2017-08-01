#include "ElEShader.h"

ElEShader::ElEShader(const ElEGraphicsComponents & renderT)
{
}

ElEShader::~ElEShader()
{
	if (src) delete[] src;
}

void ElEShader::LoadFragmentShader(const ElEchar * filename)
{
#ifdef RASPBERRY_COMPILE
	assert(!src);
	FILE* f = fopen(filename, "rb");
	assert(f);
	fseek(f, 0, SEEK_END);
	ElEint sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	Src = new GLchar[sz + 1];
	fread(src, 1, sz, f);
	src[sz] = 0;
	fclose(f);
	Id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Id, 1, (const GLchar**)&src, 0);
	glCompileShader(Id);
#endif
}

void ElEShader::LoadVertexShader(const ElEchar * filename)
{
#ifdef RASPBERRY_COMPILE
	assert(!Src);
	FILE* f = fopen(filename, "rb");
	assert(f);
	fseek(f, 0, SEEK_END);
	int sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	Src = new GLchar[sz + 1];
	fread(Src, 1, sz, f);
	Src[sz] = 0;
	fclose(f);
	Id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Id, 1, (const GLchar**)&Src, 0);
	glCompileShader(Id);
#endif
}

