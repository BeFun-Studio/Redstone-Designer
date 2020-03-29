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
struct Position
{
	int x;
	int y;
	bool operator ==(Position target)
	{
		if (target.x == this->x && target.y == this->y)
			return true;
		return false;
	}
	bool operator ==(Position* target)
	{
		if (target->x == this->x && target->y == this->y)
			return true;
		return false;
	}
};
class InvalidDirection
{
};
class FileNotFound
{
};
class FileStructureDamaged
{
};