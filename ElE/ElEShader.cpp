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
	GLint compiled;

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
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
            GLint infoLen = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1)
            {
                    char* infoLog = (char*)malloc(sizeof(char) * infoLen);
                    glGetShaderInfoLog(id, infoLen, NULL, infoLog);
                    printf("Error compiling shader:\n%s\n", infoLog);
                    free(infoLog);
            }
            glDeleteShader(id);
            return;
    }
    else printf("Shader compiled normally\n");

#endif
}

void ElEShader::LoadVertexShader(const ElEchar * filename)
{
	shaderType = vertexShader;
#ifdef RASPBERRY_COMPILE
	GLint compiled;

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
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
            GLint infoLen = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1)
            {
                    char* infoLog = (char*)malloc(sizeof(char) * infoLen);
                    glGetShaderInfoLog(id, infoLen, NULL, infoLog);
                    printf("Error compiling shader:\n%s\n", infoLog);
                    free(infoLog);
            }
            glDeleteShader(id);
            return;
    }
    else printf("Shader compiled normally\n");

#endif
}

