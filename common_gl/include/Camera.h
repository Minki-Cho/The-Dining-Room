/*
 * Rudy Castan
 * CS200
 * Fall 2022
 */
#pragma once

#include "mat3.h"
#include "vec2.h"


class [[nodiscard]] Camera
{
public:
    vec2 Position{}; // Where are we in the world?
    bool IsFirstPerson{false}; // Should we orientate the world view or not?

public:
    Camera() noexcept = default;
    Camera(vec2 camera_position, vec2 camera_up) noexcept;


    [[nodiscard]] vec2 GetUp() const noexcept
    {
        return up;
    }

    [[nodiscard]] vec2 GetRight() const noexcept
    {
        return right;
    }

    [[nodiscard]] float GetOrientation() const noexcept
    {
        return orientation;
    }

    void SetUp(vec2 camera_up = {0, 1}) noexcept;
    void SetOrientation(float angle_radians) noexcept;

    void MoveUp(float distance) noexcept; // Translate along the View/Up vector. A negative distance will move it backwards
    void MoveRight(float distance) noexcept; // Translate along the Side/Right vector. Creates a strafing effect.
    void Rotate(float angle_radians) noexcept; // Rotate the orientation of the camera

    mat3<float> BuildCameraToWorld() const noexcept; // Generates transform to go from Camera Space to World Space. Useful for picking

    mat3<float> BuildWorldToCamera() const noexcept; // Generates transform to go from World Space to Camera Space. Useful for rendering

private:
    vec2  up{0, 1}; // View direction representation as a vector
    vec2  right{1, 0}; // Side direction. Always perpendicular to the view direction
    float orientation{0}; // Orientation represented as an angle rather than a vector
};
