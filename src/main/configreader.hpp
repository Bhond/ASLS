#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "common.hpp"
#include "misc.hpp"

class ConfigReader
{
	struct Mutation
	{
	public:
		std::string name;
		double mean;
		double standardDeviation;
	};

	struct Input
	{
	public:
		std::string name;
		double mean;
		double standardDeviation;
	};

	struct Output
	{
	public:
		std::string name;
		std::string squash;
	};

public:
	std::vector<Mutation> mutations;
	std::vector<Input> inputs;
	std::vector<Output> outputs;

public:
	ConfigReader() = default;

public:
	void parseGenomeConfig();
	void readMutations(const std::string& path);
	void readInputs(const std::string& path);
	void readOuputs(const std::string& path);

};