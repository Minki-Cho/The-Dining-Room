/*
 * Rudy Castan
 * CS200
 * Fall 2022
 */
#pragma once
#include "mat3.h"
#include "vec2.h"

class [[nodiscard]] CameraView
{
public:
    void SetFramebufferSize(vec2 the_framebuffer_size) noexcept; // Call one these overloads when the display area changes size
    void SetFramebufferSize(int new_framebuffer_width, int new_framebuffer_height) noexcept;
    vec2 GetViewSize() const;
    void SetZoom(float new_zoom) noexcept; // 1 for no Zoom, < 1 for Zoom out, > 1 for Zoom in   

    vec2 CalcViewSizeWithZoom() const noexcept
    {
        return framebuffer_size / zoom;
    }

    [[nodiscard]] float GetZoom() const noexcept
    {
        return zoom;
    }

    mat3<float> BuildCameraToNDC() const noexcept;

    mat3<float> BuildWindowDeviceToCamera() const noexcept;

private:
    vec2  framebuffer_size{};
    float zoom{1.0f};
};
