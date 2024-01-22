#include "configreader.h"
#include <boost/json/src.hpp>

void ConfigReader::parseGenomeConfig()
{
	std::string path = ((std::string)PATH_RESOURCES) + "/genome.json";
    readInputs(path);
    readOuputs(path);

}

void ConfigReader::readInputs(const std::string& path)
{
    std::ifstream is(path, std::ifstream::binary);
    if (is)
    {
        boost::json::value jv = boost::json::parse(is);
        boost::json::array arr = jv.at(confInputs).as_array();
        for (boost::json::value e : arr)
        {
            boost::json::object o = e.as_object();
            Input in;
            in.name = o.at(confName).as_string().c_str();
            in.mean = o.at(confMean).as_double();
            in.standardDeviation = o.at(confStd).as_double();
            inputs.push_back(in);
        }
    }
}

void ConfigReader::readOuputs(const std::string& path)
{
    std::ifstream is(path, std::ifstream::binary);
    if (is)
	{
		boost::json::value jv = boost::json::parse(is);
		boost::json::array arr = jv.at(confOutputs).as_array();
		for (boost::json::value e : arr)
		{
			boost::json::object o = e.as_object();
			Output out;
			out.name = o.at(confName).as_string().c_str();
			out.squash = o.at(confSquash).as_string().c_str();
			outputs.push_back(out);
		}
    }
}