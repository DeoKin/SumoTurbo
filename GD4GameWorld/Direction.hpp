#pragma once
#ifndef AIRCRAFT_DIRECTION_HPP
#define AIRCRAFT_DIRECTION_HPP


struct Direction
{
	Direction(float movementAngle, float distance, float rotation)
		: angle(movementAngle)
		, distance(distance)
		, rotation(rotation)
	{
	}

	float angle; // gives the direction to move
	float distance;
	float rotation;
};

#endif // AIRCRAFT_DIRECTION_HPP