/*
 * MINJAE YU
 * CS200
 * Fall 2022
 */
#include "GLTexture.h"
#include "glCheck.h"
#include <stb_image.h>

GLTexture::~GLTexture() noexcept
{
    delete_texture();
}

GLTexture::GLTexture(GLTexture&& other) noexcept
{
    if (this != &other)
    {
        texture_handle = other.texture_handle;
        width = other.width;
        height = other.height;
        filtering = other.filtering;
        std::swap(wrapping, other.wrapping);

        other.texture_handle = 0;
    }
}

GLTexture& GLTexture::operator=(GLTexture&& other) noexcept
{
    if (this != &other)
    {
        texture_handle = other.texture_handle;
        width = other.width;
        height = other.height;
        filtering = other.filtering;
        std::swap(wrapping, other.wrapping);

        other.texture_handle = 0;
    }
    return (*this);
}

bool GLTexture::LoadFromFileImage(const std::filesystem::path& image_filepath, bool flip_vertical) noexcept
{
    // invoke stbi_set_flip_vertically_on_load()
    stbi_set_flip_vertically_on_load(flip_vertical);
    // invoke stbi_load() to get the RGBA data, width, height
    int color;
    unsigned char* data = stbi_load(image_filepath.string().c_str(), &width, &height, &color, 4);
    // invoke LoadFromMemory()
    if (LoadFromMemory(width, height, reinterpret_cast<RGBA*>(data)) == false)
        return false;
    // invoke stbi_image_free()
    stbi_image_free(data);
    // return if successful
    return true;
}

bool GLTexture::LoadFromMemory(int image_width, int image_height, const RGBA* colors) noexcept
{
    // delete current texture
    delete_texture();
    // copy and save image width
    width = image_width;
    // copy and save image height
    height = image_height;

    // Create 1 texture
    glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &texture_handle));
    // Create immutable storage of widthxheight RGBA8 GPU memory with only one texture level
    constexpr GLsizei ONE_TEXTURE_LEVEL = 1;
    glCheck(glTextureStorage2D(texture_handle, ONE_TEXTURE_LEVEL, GL_RGBA8, width, height));
    // Send `colors` data to GPU memory
    constexpr GLint   FIRST_LEVEL = 0;
    constexpr GLsizei OFFSET_X = 0, OFFSET_Y = 0;
    glCheck(glTextureSubImage2D(texture_handle, FIRST_LEVEL, OFFSET_X, OFFSET_Y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, colors));

    // Set Filtering to nearest pixel
    SetFiltering(Filtering::NearestPixel);
    // Set Wrapping to the repeat pattern
    SetWrapping(Wrapping::Repeat);

    // return if successful
    return true;
}

void GLTexture::SetFiltering(Filtering how_to_filter) noexcept
{
    if (texture_handle == 0)
        return;

    filtering = how_to_filter;

    // invoke glTextureParameteri to set minification filter
    glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_MIN_FILTER, filtering));
    // invoke glTextureParameteri to set magnification filter
    glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_MAG_FILTER, filtering));

}

void GLTexture::SetWrapping(Wrapping how_to_wrap, Coordinate coord) noexcept
{
    if (texture_handle == 0)
        return;

    // invoke glTextureParameteri to set how to wrap with coords S, T or both
    switch (coord)
    {
    case Coordinate::S:
        glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, how_to_wrap));
        break;
    case Coordinate::T:
        glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_T, how_to_wrap));
        break;
    case Coordinate::Both:
        glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, how_to_wrap));
        glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_T, how_to_wrap));
        break;
    }
}

void GLTexture::UseForSlot(unsigned int texture_unit) const noexcept
{
    // invoke glBindTextureUnit to associate the texture unit with this texture
    glCheck(glBindTextureUnit(texture_unit, texture_handle));
}

void GLTexture::delete_texture() noexcept
{
    // invoke glDeleteTextures
    glCheck(glDeleteTextures(1, &texture_handle));
    texture_handle = 0; // so we don't accidentally double it
    width = 0;
    height = 0;
}