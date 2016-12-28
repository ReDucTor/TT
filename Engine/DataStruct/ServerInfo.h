#pragma once
#include <string>
struct ServerInfo {
	ServerInfo(std::string db, std::string name) 
		:
		database(db),
		name(name)
	{}
	std::string database;
	std::string name;
};