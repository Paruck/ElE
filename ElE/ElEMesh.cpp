#include "ElEMesh.h"
#include "ElE.h"
#include <assert.h>

ElEMesh::ElEMesh() : isTriangleStrip(ElEtrue)
{
}

ElEMesh::ElEMesh(_IN_ ElEfloat * const & verts,
	const _IN_ ElEsize_t & vertSize,
	_IN_ ElEfloat * const & indexarr,
	const _IN_ ElEsize_t & indexSize) : ElEMesh()
{
	assert(verts);

	for (ElEsize_t i = 0; i < vertSize; ++i)
	{
		vertex.push_back(verts[i]);
	}
	if (indexarr != nullptr)
	{
		for (ElEsize_t i = 0; i < indexSize; ++i)
		{
			vertex.push_back(indexarr[i]);
		}
		isTriangleStrip = ElEfalse;
	}
}

ElEMesh::ElEMesh(const _IN_ ElEVertex & verts,
	_IN_ ElEIndexes * const & indexarr) : ElEMesh()
{
	vertex = verts;
	if (indexarr != nullptr)
	{
		indexes = *indexarr;
		isTriangleStrip = ElEfalse;
	}
}

ElEMesh::~ElEMesh()
{
}

ElEvoid ElEMesh::draw()
{
#ifdef RASPBERRY_COMPILE
    glUseProgram(material.getProgramID());
    if(modifiedVertex)
    {
        //glBufferData(meshName, sizeof(ElEfloat)*vertex.size(),
            //&vertex.front(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(meshName,4,
            GL_FLOAT,GL_FALSE, 0, &vertex.front());
        modifiedVertex = ElEfalse;
    }
    if(modifiedIndexes)
    {
        //glBufferData(indexName, sizeof(ElEubyte)*indexes.size(),
            //&indexes.front(), GL_STATIC_DRAW);
        modifiedIndexes = ElEfalse;
    }
    //glBindBuffer(GL_ARRAY_BUFFER, meshName);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(ElEfloat)*vertex.size(),
        //&vertex.front(), GL_DYNAMIC_DRAW);
    //glVertexAttribPointer(0,vertex.size(),GL_FLOAT,GL_FALSE,0,&vertex.front());
    glEnableVertexAttribArray(meshName);

    if(indexes.size() > 0)
    {
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexName);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElEubyte)*indexes.size(),
           // &indexes.front(), GL_STATIC_DRAW);
        glDrawElements(isTriangleStrip ? GL_TRIANGLE_STRIP : GL_TRIANGLES,
            vertex.size()/4,GL_UNSIGNED_BYTE, indexes.data());
    }
    else
        glDrawArrays(isTriangleStrip ? GL_TRIANGLE_STRIP : GL_TRIANGLES,
            0,vertex.size()/4);
    glDisableVertexAttribArray(meshName);
#endif
}

ElEvoid ElEMesh::initVertexShader(const _IN_ ElEchar * filename)
{
	material.initVertexShader(filename);
}

ElEvoid ElEMesh::initFragmentShader(const _IN_ ElEchar * filename)
{
    material.initFragmentShader(filename);
}

ElEvoid ElEMesh::changeVertexShader(const _IN_ ElEchar * filename)
{
	material.changeVertexShader(filename);
}

ElEvoid ElEMesh::changeFragmentShader(const _IN_ ElEchar * filename)
{
	material.changeFragmentShader(filename);
}

ElEvoid ElEMesh::setup()
{
    meshName = ElE::getIDManager().getUnusedID();
    material.setup(meshName);
    /*glGenBuffers(1,&meshName);
    glBindBuffer(GL_ARRAY_BUFFER, meshName);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ElEfloat)*vertex.size(),
        &vertex.front(), GL_DYNAMIC_DRAW);
    if(!indexes.size())
    {
        glGenBuffers(1, &indexName);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexName);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElEubyte)*indexes.size(),
            &indexes.front(), GL_STATIC_DRAW);
    }*/
    glVertexAttribPointer(meshName,4,
        GL_FLOAT,GL_FALSE, 0, &vertex.front());
    modifiedIndexes = modifiedVertex = ElEfalse;
}
