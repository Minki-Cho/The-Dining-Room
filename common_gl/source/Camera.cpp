/*
 * MINJAE YU
 * CS200
 * Fall 2022
 */
#include "Camera.h"
#include <cmath>

Camera::Camera(vec2 camera_position, vec2 camera_up) noexcept
{
    // Position <- camera_position
    Position = camera_position;
    // IsFirstPerson <- false
    IsFirstPerson = false;
    // up <- camera_up
    up = camera_up;
    // right <- Rot -90(up)
    right = vec2{ up.y,-up.x };
    // orientation <- angle representation of up vector
    orientation = atan2(up.y, up.x);
}

void Camera::SetUp(vec2 camera_up) noexcept
{
    // up <- camera_up
    up = camera_up;
    // right <- Rot -90(up)
    right = vec2{ up.y,-up.x };
    // orientation <- angle representation of up vector
    orientation = atan2(up.y, up.x);
}

void Camera::SetOrientation(float angle_radians) noexcept
{
    // orientation <- angle_radians
    orientation = angle_radians;
    // up <- vector from angle orientation
    up = vec2{ cos(angle_radians),sin(angle_radians) };
    // right <- Rot - 90(up)
    right = vec2{ up.y,-up.x };
}

void Camera::MoveUp(float distance) noexcept
{
    // Position <- Position + up * distance
    Position = Position + up * distance;
}

void Camera::MoveRight(float distance) noexcept
{
    // Position <- Position + right * distance
    Position = Position + right * distance;
}

void Camera::Rotate(float angle_radians) noexcept
{
    // call SetOrientation( orientation + angle_radians )
    SetOrientation(orientation + angle_radians);
}

mat3<float> Camera::BuildCameraToWorld() const noexcept
{
    if (IsFirstPerson)
    {
        // build and return camera to world matrix using our up, right and position vectors
        return mat3<float>{ {right.x,right.y,0},{up.x,up.y,0},{Position.x,Position.y,1} };
    }
    else
    {
        // build and return camera to world matrix using only our position vector
        return mat3<float>{ {1,0,0},{0,1,0},{Position.x,Position.y,1} };
    }
}

mat3<float> Camera::BuildWorldToCamera() const noexcept
{
    if (IsFirstPerson)
    {
        // build and return world to camera matrix using our up, right and position vectors
        float x = (-right.x * Position.x) + (-right.y * Position.y);
        float y = (-up.x * Position.x) + (-up.y * Position.y);
        return mat3<float>{ {right.x,up.x,0},{right.y,up.y,0},{x,y,1} };
    }
    else
    {
        // build and return world to camera matrix using only our position vector
        return mat3<float>{ {1,0,0},{0,1,0},{-Position.x,-Position.y,1} };
    }
}