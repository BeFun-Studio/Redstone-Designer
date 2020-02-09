#pragma once
#include <string>
#include <Windows.h>
#include "def.hpp"
using namespace std;
enum CommandBlockType
{
	COMMON_COMMAND_BLOCK=0,
	CHAIN_COMMAND_BLOCK,
	REPEAT_COMMAND_BLOCK
};

class CommandBlock
{
private:
	wstring storaged_command;
	CommandBlockType type;
	bool conditional;
	Direction direction;
	bool keep_active;
	wstring custom_name;
	Location location;
public:
	CommandBlock()
	{
		this->storaged_command = L"";
		this->type = COMMON_COMMAND_BLOCK;
		this->conditional = false;
		this->direction = UP;
		this->keep_active = false;
		this->custom_name = L"";
	}
	CommandBlock(LPCWSTR initial_command,CommandBlockType command_block_type,bool _conditional,bool _keep_active,LPCWSTR _custom_name,Location _location)
	{
		this->storaged_command = initial_command;
		this->type = command_block_type;
		this->conditional = _conditional;
		this->keep_active = _keep_active;
		this->custom_name = _custom_name;
		this->location = _location;
	}
	CommandBlock(LPCWSTR initial_command, CommandBlockType command_block_type, bool _conditional, bool _keep_active, LPCWSTR _custom_name, int location_x, int location_y)
	{
		this->storaged_command = initial_command;
		this->type = command_block_type;
		this->conditional = _conditional;
		this->keep_active = _keep_active;
		this->custom_name = _custom_name;
		this->location.x = location_x;
		this->location.y = location_y;
	}
	LPCWSTR GetCommand()
	{
		return this->storaged_command.c_str();
	}
	CommandBlockType GetCommandBlockType()
	{
		return this->type;
	}
	bool IsConditional()
	{
		return this->conditional;
	}
	bool IsKeepActive()
	{
		return this->keep_active;
	}
	LPCWSTR GetCustomName()
	{
		return this->custom_name.c_str();
	}
	Location GetLocation()
	{
		return this->location;
	}
	void SetCommand(LPCWSTR command)
	{
		this->storaged_command = command;
	}
	void SetCommandBlockType(CommandBlockType cmd_block_type)
	{
		this->type = cmd_block_type;
	}
	void SetConditional(bool is_conditional)
	{
		this->conditional = is_conditional;
	}
	void SetKeepActive(bool is_keep_active)
	{
		this->keep_active = is_keep_active;
	}
	void SetCustomName(LPCWSTR _custom_name)
	{
		this->custom_name = _custom_name;
	}
	void SetLocation(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(int location_x, int location_y)
	{
		this->location.x = location_x;
		this->location.y = location_y;
	}
	void SetDirection(Direction _direction)
	{
		this->direction = _direction;
	}
	Direction GetDirection()
	{
		return this->direction;
	}
};
class RedstoneWire
{
private:
	Location location;
public:
	RedstoneWire()
	{
		this->location = { 0,0 };
	}
	RedstoneWire(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(int location_x, int location_y)
	{
		this->location.x = location_x;
		this->location.y = location_y;
	}
	Location GetLocation()
	{
		return this->location;
	}
};
class RedstoneBlock
{
private:
	Location location;
public:
	RedstoneBlock()
	{
		this->location = { 0,0 };
	}
	RedstoneBlock(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(int location_x, int location_y)
	{
		this->location.x = location_x;
		this->location.y = location_y;
	}
	Location GetLocation()
	{
		return this->location;
	}
};
class RedstoneTorch
{
private:
	Location location;
	Direction direction;
public:
	RedstoneTorch()
	{
		this->location = { 0,0 };
		this->direction = UP;
	}
	RedstoneTorch(Location _location,Direction _direction)
	{
		this->location = _location;
		this->direction = _direction;
	}
	void SetLocation(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(int location_x, int location_y)
	{
		this->location.x = location_x;
		this->location.y = location_y;
	}
	bool SetDirection(Direction _direction)
	{
		if (_direction == DOWN)
			return false;
		this->direction = _direction;
		return true;
	}
	Location GetLocation()
	{
		return this->location;
	}
	Direction GetDirection()
	{
		return this->direction;
	}
};
class TrapDoor
{
private:
	Location location;
	Direction direction;
public:
	TrapDoor()
	{
		this->location = { 0,0 };
		this->direction = NORTH;
	}
	TrapDoor(Location _location, Direction _direction)
	{
		this->location = _location;
		if (direction == UP || direction == DOWN)
		{
			throw InvalidDirection();
			this->direction = NORTH;
		}
		this->direction = _direction;
	}
	TrapDoor(int location_x, int location_y, Direction _direction)
	{
		this->location.x = location_x;
		this->location.y = location_y;
		if (direction == UP || direction == DOWN)
		{
			throw InvalidDirection();
			this->direction = NORTH;
		}
		this->direction = _direction;
	}
	void SetLocation(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(int location_x, int location_y)
	{
		this->location.x = location_x;
		this->location.y = location_y;
	}
	bool SetDirection(Direction _direction)
	{
		if (_direction == UP || _direction == DOWN)
			return false;
		this->direction = _direction;
	}
	Location GetLocation()
	{
		return this->location;
	}
	Direction GetDirection()
	{
		return this->direction;
	}
};