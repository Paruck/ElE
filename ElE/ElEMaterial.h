#pragma once
#include "ElEDefines.h"
#include "ElEShader.h"

#ifdef RASPBERRY_COMPILE
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#endif

class ElEMaterial
{
    public:
        /** Default constructor */
        ElEMaterial();
        /** Default destructor */
        ~ElEMaterial();
        /** Copy constructor
         *  \param other Object to copy from
         */
        ElEMaterial(const ElEMaterial& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        ElEMaterial& operator=(const _IN_ ElEMaterial& other);
        ElEvoid ElEcall initVertexShader(const _IN_ ElEchar* filename);
        ElEvoid ElEcall initFragmentShader(const _IN_ ElEchar* filename);
        ElEvoid ElEcall changeVertexShader(const _IN_ ElEchar* filename);
        ElEvoid ElEcall changeFragmentShader(const _IN_ ElEchar* filename);
        inline ElEuint ElEcall getProgramID(){ return programid; }
        inline ElEuint ElEcall getTextureiD(){ return textureid; }
        ElEvoid ElEcall setup();
        ElEvoid ElEcall setTexture(_IN_ ElEvoid* const& data,
                const ElEint& target,
                const ElEint& mipmapLevel,
                const ElEint& internalFormat,
                const ElEsize_t& width,
                const ElEsize_t& height,
                const ElEint& texelDataType);
    private:
        ElEShader	*vertexShader,
                    *fragmentShader;
        ElEuint     programid,
                    textureid;
};
