#include "ElEMaterial.h"
#include "ElE.h"

ElEMaterial::ElEMaterial() : vertexShader(nullptr),
						fragmentShader(nullptr),
						programid(-1), textureid(-1)
{
    shaderAttribFunction = nullptr;    //ctor
}

ElEMaterial::~ElEMaterial()
{
    //dtor
    if(glIsProgram(programid))
        glDeleteProgram(programid);
    if(glIsTexture(textureid))
        glDeleteTextures(1,&textureid);
}

ElEMaterial::ElEMaterial(const ElEMaterial& other)
{
    //copy ctor
}

ElEMaterial& ElEMaterial::operator=(const _IN_ ElEMaterial& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

ElEvoid ElEMaterial::initVertexShader(const _IN_ ElEchar * filename)
{
	if (vertexShader) return;
	vertexShader = new ElEShader(ElE::getGraphicsRenderer());
	vertexShader->LoadVertexShader(filename);
}

ElEvoid ElEMaterial::initFragmentShader(const _IN_ ElEchar * filename)
{
	if (fragmentShader) return;
	fragmentShader = new ElEShader(ElE::getGraphicsRenderer());
	fragmentShader->LoadFragmentShader(filename);
}

ElEvoid ElEMaterial::changeVertexShader(const _IN_ ElEchar * filename)
{
/** TODO (komo97#1#): Llenar esta funcion
 */
}

ElEvoid ElEMaterial::changeFragmentShader(const _IN_ ElEchar * filename)
{
/** TODO (komo97#1#): Llenar esta funcion
 */
}

ElEvoid ElEMaterial::setup(const ElEuint& slot)
{
#ifdef RASPBERRY_COMPILE
    GLint linked;
    if(!vertexShader)
        initVertexShader("vShader.glsl");
    if(!fragmentShader)
        initFragmentShader("fShader.glsl");
    programid = glCreateProgram();
    glAttachShader(programid, vertexShader->getID());
    glAttachShader(programid, fragmentShader->getID());
    if(!shaderAttribFunction)
    {
        shaderAttribFunction(programid, slot);
    }
    glLinkProgram(programid);
    glGetProgramiv(programid, GL_LINK_STATUS, &linked);
    if(!linked)
    {
            GLint infoLen = 0;
            glGetProgramiv(programid, GL_INFO_LOG_LENGTH, &infoLen);

            if(infoLen > 1)
            {
                    char* infoLog = (char*)malloc(sizeof(char) * infoLen);
                    glGetProgramInfoLog(programid, infoLen, NULL, infoLog);
                    printf("Error linking program:\n%s\n", infoLog);
                    free(infoLog);
            }
            glDeleteProgram(programid);
            return;
    }
    else printf("The program %d compiled succesfully\n");
#endif
/** TODO (komo97#1#): Añadir funcionalidad de texturas */

}

ElEvoid ElEMaterial::setTexture(_IN_ ElEvoid* const& data,
                const ElEint& target,
                const ElEint& mipmapLevel,
                const ElEint& internalFormat,
                const ElEsize_t& width,
                const ElEsize_t& height,
                const ElEint& texelDataType)
{
/** TODO (komo97#1#): Llenar esta funcion
 */

}
