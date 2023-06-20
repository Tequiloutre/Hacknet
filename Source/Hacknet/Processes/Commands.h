#pragma once

#include "Processes/Process.h"

class Folder;

class cat : public Process
{
public:
	
	cat(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class cd : public Process
{
public:
	
	cd(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class connect : public Process
{
public:

	connect(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class disconnect : public Process
{
public:

	disconnect(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class ip : public Process
{
public:

	ip(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class ls : public Process
{
public:

	ls(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class mkdir : public Process
{
public:

	mkdir(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class probe : public Process
{
public:

	probe(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class rm : public Process
{
public:

	rm(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class rmdir : public Process
{
public:

	rmdir(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class say : public Process
{
public:

	say(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class shutdown : public Process
{
public:

	shutdown(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class touch : public Process
{
public:

	touch(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};
