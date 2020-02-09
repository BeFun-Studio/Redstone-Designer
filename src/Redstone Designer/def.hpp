#pragma once
enum Direction
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
	UP,
	DOWN
};
struct Location
{
	int x;
	int y;
};
class InvalidDirection
{
};