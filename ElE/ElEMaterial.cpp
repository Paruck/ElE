#include "ElEMaterial.h"
#include "ElE.h"

ElEMaterial::ElEMaterial() : vertexShader(nullptr),
						fragmentShader(nullptr),
						programid(-1), textureid(-1)
{
    //ctor
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

ElEvoid ElEMaterial::setup()
{
#ifdef RASPBERRY_COMPILE

    if(!vertexShader)
        initVertexShader("vShader.glsl");
    if(!fragmentShader)
        initFragmentShader("fShader.glsl");
    programid = glCreateProgram();
    glAttachShader(programid, vertexShader->getID());
    glAttachShader(programid, fragmentShader->getID());
    glLinkProgram(programid);
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
