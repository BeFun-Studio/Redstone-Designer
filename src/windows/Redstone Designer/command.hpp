#pragma once
#include "circuit.hpp"
#include <vector>

struct Command
{
	wstring* parts;
	unsigned int part_count;
};

Command PartitionCommand(LPCWSTR command)
{
	vector<wstring> parts;
	wstring current_part;
	for (int i = 0; i < wcslen(command); i++)
		if (command[i] == L' ')
			if (current_part.length() == 0)
				continue;
			else
				parts.push_back(current_part);
		else
			if (command[i + 1] == L'\0')
			{
				current_part += command[i];
				if (current_part.length() == 0)
				{
					Command ret_command;
					ret_command.parts = new wstring[parts.size()];
					ret_command.part_count = parts.size();
					for (int i = 0; i < parts.size(); i++)
						ret_command.parts[i] = parts[i];
					return ret_command;
				}
				else
					parts.push_back(current_part);
			}
			else
				parts.push_back(current_part);
	Command ret_command;
	ret_command.parts = new wstring[parts.size()];
	ret_command.part_count = parts.size();
	for (int i = 0; i < parts.size(); i++)
		ret_command.parts[i] = parts[i];
	return ret_command;
}

Command* CreateCommand(LPCWSTR command)
{
	Command* new_command = new Command;
	*new_command = PartitionCommand(command);
	return new_command;
}

bool GenerateCommandBlockCircuit(Command* commands, unsigned int command_count, unsigned int width, unsigned int height)
{
	int current_x = 0;
	int current_y = 0;
}