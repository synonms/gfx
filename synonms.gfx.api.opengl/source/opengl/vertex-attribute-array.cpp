#include "vertex-attribute-array.h"

#include <GL\glew.h>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

void VertexAttributeArray::Configure(unsigned int index, int noOfComponentsPerAttribute, DataType dataType, int noOfBytesPerVertex, bool isNormalised, unsigned int offset)
{
    glVertexAttribPointer(index, noOfComponentsPerAttribute, static_cast<unsigned int>(dataType), isNormalised, noOfBytesPerVertex, (const void*)offset);
}

void VertexAttributeArray::Enable(unsigned int index)
{
    glEnableVertexAttribArray(index);
}
