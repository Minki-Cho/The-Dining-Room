// Name : MINJAE YU
// Course : CS200
// Term : Fall 2022
#include "GLVertexArray.h"
#include "glCheck.h"

GLVertexArray::GLVertexArray(GLPrimitive::Type the_primitive_pattern) : primitive_pattern(the_primitive_pattern)
{
	glCheck(glCreateVertexArrays(1, &vertex_array_handle));
}

GLVertexArray::~GLVertexArray()
{
	glCheck(glDeleteVertexArrays(1, &vertex_array_handle));
}

GLVertexArray::GLVertexArray(GLVertexArray&& temp) noexcept
{
	if (this != &temp)
	{
		vertex_array_handle = temp.vertex_array_handle;
		std::swap(vertex_buffers, temp.vertex_buffers);
		index_buffer = std::move(temp.index_buffer);
		num_indices = temp.num_indices;
		indices_type = temp.indices_type;
		primitive_pattern = temp.primitive_pattern;
		num_vertices = temp.num_vertices;

		temp.vertex_array_handle = 0;
	}
}

GLVertexArray& GLVertexArray::operator=(GLVertexArray&& temp) noexcept
{
	if (this != &temp)
	{
		vertex_array_handle = temp.vertex_array_handle;
		std::swap(vertex_buffers, temp.vertex_buffers);
		std::swap(index_buffer, temp.index_buffer);
		num_indices = temp.num_indices;
		indices_type = temp.indices_type;
		primitive_pattern = temp.primitive_pattern;
		num_vertices = temp.num_vertices;

		temp.vertex_array_handle = 0;
	}
	return (*this);
}

void GLVertexArray::Use(bool bind) const
{
	if (bind == true)
	{
		glCheck(glBindVertexArray(vertex_array_handle));
	}
	else if (bind == false)
	{
		glCheck(glBindVertexArray(0));
	}
}

void GLVertexArray::AddVertexBuffer(GLVertexBuffer&& vertex_buffer, std::initializer_list<GLAttributeLayout> buffer_layout)
{
	GLHandle vb_handle = vertex_buffer.GetHandle();
	for (const GLAttributeLayout& attribute : buffer_layout)
	{
		glCheck(glEnableVertexArrayAttrib(vertex_array_handle, attribute.vertex_layout_location));
		//bind a buffer to a vertex buffer bind point
		glCheck(glVertexArrayVertexBuffer(vertex_array_handle, attribute.vertex_layout_location, vb_handle, attribute.offset, attribute.stride));
		glCheck(glVertexArrayAttribFormat(vertex_array_handle, attribute.vertex_layout_location, attribute.component_dimension, attribute.component_type, attribute.normalized, attribute.relative_offset));
		glCheck(glVertexArrayAttribBinding(vertex_array_handle, attribute.vertex_layout_location, attribute.vertex_layout_location));
	}
	vertex_buffers.push_back(std::move(vertex_buffer));
}

void GLVertexArray::SetIndexBuffer(GLIndexBuffer&& the_indices)
{
	num_indices = the_indices.GetCount();
	indices_type = the_indices.GetElementType();
	index_buffer = std::move(the_indices);
	glCheck(glVertexArrayElementBuffer(vertex_array_handle, index_buffer.GetHandle()));
}

void GLDrawIndexed(const GLVertexArray& vertex_array) noexcept
{
	glCheck(glDrawElements(vertex_array.GetPrimitivePattern(), vertex_array.GetIndicesCount(), vertex_array.GetIndicesType(), 0));
}

void GLDrawVertices(const GLVertexArray& vertex_array) noexcept
{
	glCheck(glDrawArrays(vertex_array.GetPrimitivePattern(), 0, vertex_array.GetVertexCount()));
}