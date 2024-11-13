#pragma once

enum class CharacterAnim
{
	None_F,	// idle_front
	None_B, // idle_back
	None_L, // idle_left
	None_R, // idle_right
	Front,  // moving_front
	Back,  // moving_back
	Left,  // moving_left
	Right,  // moving_right
	H_None_F,	// idle_front (handle)
	H_None_B, // idle_back (handle)
	H_None_L, // idle_left (handle)
	H_None_R, // idle_right (handle)
	H_Front,  // moving_front (handle)
	H_Back,  // moving_back (handle)
	H_Left,  // moving_left (handle)
	H_Right  // moving_right (handle)
};