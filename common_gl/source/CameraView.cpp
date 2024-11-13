/*
 * MINJAE YU
 * CS200
 * Fall 2022
 */
#include "CameraView.h"

void CameraView::SetFramebufferSize(vec2 the_framebuffer_size) noexcept
{
    framebuffer_size = the_framebuffer_size;
}

void CameraView::SetFramebufferSize(int new_pixel_width, int new_pixel_height) noexcept
{
    SetFramebufferSize(vec2{ float(new_pixel_width), float(new_pixel_height) });
}

void CameraView::SetZoom(float new_zoom) noexcept
{
    // if new zoom is not 0
        // save as zoom
    if (new_zoom != 0)
    {
        zoom = new_zoom;
    }
}

mat3<float> CameraView::BuildCameraToNDC() const noexcept
{
    //         (v.w/2,v.h/2)              (1,1)
    //      +--------o             +--------o
    //      |        |             |        |
    //      | cam    |     --->    | ndc    |
    //      o--------+             o--------+
    // (-v.w/2,-v.h/2)          (-1,-1)
    //

    // get view size with zoom
    float width = CalcViewSizeWithZoom().width;
    float height = CalcViewSizeWithZoom().height;
    // build and return camera to NDC matrix
    const mat3<float> cam_to_ndc{ {2 / width,0,0},{0,2 / height,0},{0,0,1} };
    return cam_to_ndc;
}

mat3<float> CameraView::BuildWindowDeviceToCamera() const noexcept
{
    //    (0,0)             (-v.w/2,v.h/2)
    //      o--------+             o--------+
    //      |        |             |        |
    //      | win    |     --->    | cam    |
    //      +--------o             +--------o
    //           (f.w,f.h)            (v.w/2,-v.h/2)
    //

    // get view size with zoom
    float width = CalcViewSizeWithZoom().width;
    float height = CalcViewSizeWithZoom().height;
    // build and return window to camera matrix
    const mat3<float> win_to_cam{ {width / framebuffer_size.width,0,0},{0,-height / framebuffer_size.height,0},{-width / 2,height / 2,1} };
    return win_to_cam;
}