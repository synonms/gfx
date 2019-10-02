#include "vertex-attribute-array.h"

#include <glproxy\error.h>
#include <GL\glew.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void VertexAttributeArray::Configure(unsigned int index, int noOfComponentsPerAttribute, DataType dataType, int noOfBytesPerVertex, bool isNormalised, unsigned int offset, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glVertexAttribPointer(index, noOfComponentsPerAttribute, static_cast<unsigned int>(dataType), isNormalised, noOfBytesPerVertex, (const void*)offset);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Index (" + std::to_string(index) + ") is greater than or equal to GL_MAX_VERTEX_ATTRIBS (" + std::to_string(GL_MAX_VERTEX_ATTRIBS) + ") OR noOfComponentsPerAttribute is not 1, 2, 3, 4 or (for glVertexAttribPointer), GL_BGRA OR noOfBytesPerVertex is negative." },
        {GL_INVALID_OPERATION, "noOfComponentsPerAttribute is GL_BGRA and DataType is not GL_UNSIGNED_BYTE, GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV *OR* DataType is GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV and noOfComponentsPerAttribute is not 4 or GL_BGRA *OR* noOfComponentsPerAttribute is GL_BGRA and isNormalised is GL_FALSE *OR* if zero is bound to the GL_ARRAY_BUFFER buffer object binding point and the pointer argument is not NULL *OR* there is no Vertex Array Object bound." },
        {GL_INVALID_ENUM , "DataType is invalid." },
        });
}

void VertexAttributeArray::Enable(unsigned int index, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glEnableVertexAttribArray(index);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Index is greater than or equal to GL_MAX_VERTEX_ATTRIBS." },
        {GL_INVALID_OPERATION, "There is no current vertex array object." }
        });
}
