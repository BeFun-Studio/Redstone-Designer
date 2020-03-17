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
};
struct Step
{
	Position current_pos;
	unsigned int step;
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