// Name : MINJAE YU
// Course : CS200
// Term : Fall 2022
#include "GLIndexBuffer.h"
#include "glCheck.h"

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned int> indices) : element_type(GLIndexElement::UInt), count(static_cast<GLsizei>(indices.size()))
{
	create_indices_buffer(indices);
}

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned short> indices) : element_type(GLIndexElement::UShort), count(static_cast<GLsizei>(indices.size()))
{
	create_indices_buffer(indices);
}

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned char> indices) : element_type(GLIndexElement::UByte), count(static_cast<GLsizei>(indices.size()))
{
	create_indices_buffer(indices);
}

GLIndexBuffer::~GLIndexBuffer()
{
	glCheck(glDeleteBuffers(1, &indices_handle));
}

GLIndexBuffer::GLIndexBuffer(GLIndexBuffer&& temp) noexcept
{
	if (this != &temp)
	{
		element_type = temp.element_type;
		count = temp.count;
		indices_handle = temp.indices_handle;
	}
}

GLIndexBuffer& GLIndexBuffer::operator=(GLIndexBuffer&& temp) noexcept
{
	if (this != &temp)
	{
		element_type = temp.element_type;
		count = temp.count;
		indices_handle = temp.indices_handle;
	}
	return (*this);
}

void GLIndexBuffer::Use(bool bind) const
{
	if (bind == true)
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_handle));
	}
	else if (bind == false)
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}

template<typename T>
void GLIndexBuffer::create_indices_buffer(std::span<const T> indices)
{
	glCheck(glCreateBuffers(1, &indices_handle));
	glCheck(glNamedBufferStorage(indices_handle, indices.size_bytes(), indices.data(), GL_DYNAMIC_STORAGE_BIT));
}