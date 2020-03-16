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
class InvalidDirection
{
};
class FileNotFound
{
};
class FileStructureDamaged
{
};