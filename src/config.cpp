#include "config.h"
#include <fstream>
#include <sys/time.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

Config::Config()
{
  this->read();
}

Config::~Config()
{
  this->write();
}

void Config::read()
{
  this->read(DEFAULT_CONFIG_FILE);
}

void Config::read(std::string filename)
{
  boost::property_tree::ptree root;
  try
  {
    boost::property_tree::read_json(filename, root);
    this->id = root.get<std::string>("id");
    this->internalIpAddress = root.get<std::string>("internalipaddress");
    this->username = root.get<std::string>("username");
    this->password = root.get<std::string>("password");
    this->url = root.get<std::string>("url");
    this->timestamp = root.get<uint64_t>("timestamp");
  }
  catch(std::exception &e)
  {
    std::cout << "No Config file found.\n";
  }

}

void Config::write()
{
  // TODO: eventually this should probably check a variable
  // and possibly an environment variable, before using the 
  // default.  Also, there should be a hard coded skeleton config
  // in case the default does not exist.
  this->write(DEFAULT_CONFIG_FILE);
}

void Config::write(std::string filename)
{
  boost::property_tree::ptree root;
  root.put("id", this->id);
  root.put("internalipaddress", this->internalIpAddress);
  root.put("username", this->username);
  root.put("password", this->password);
  root.put("url", this->url);
  std::fstream fs(filename, std::fstream::out);
  if(fs.is_open())
  {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    this->timestamp = ts.tv_sec * 1000 + ts.tv_nsec / 1000;
    root.put("timestamp", this->timestamp);
    boost::property_tree::write_json(fs, root);
    fs.close();
  }
  else
  {
    std::cout << "Error opening file: " << filename << ".\n";
  }
}


std::string Config::getId() const
{
  return this->id;
}

void Config::setId(const std::string value)
{
  this->id = value;
}

std::string Config::getInternalIpAddress() const
{
  return this->internalIpAddress;
}

void Config::setInternalIpAddress(const std::string value)
{
  this->internalIpAddress = value;
}

std::string Config::getUsername() const
{
  return this->username;
};

void Config::setUsername(const std::string value)
{
  this->username = value;
};

std::string Config::getPassword() const
{
  return this->password;
};

void Config::setPassword(const std::string value)
{
  this->password = value;
};

std::string Config::getUrl() const
{
  return this->url;
};

void Config::setUrl(const std::string value)
{
  this->url = value;
};

uint64_t Config::getTimestamp() const
{
  return this->timestamp;
};
