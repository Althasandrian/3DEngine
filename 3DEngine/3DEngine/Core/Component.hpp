#pragma once

class Component
{
public:
	Component();
	virtual ~Component();
	
private:

};

Component::Component()
{
}

Component::~Component()
{
}


class testiComp : public Component
{
public:
	testiComp();
	~testiComp();
std::string asd;
private:
	
};

testiComp::testiComp()
{
	asd = "testi";
}

testiComp::~testiComp()
{
}

class toinentesti : public Component
{
public:
	toinentesti();
	~toinentesti();
std::string debug;
private:
	
};

toinentesti::toinentesti()
{
	debug = "kakkaa";
}

toinentesti::~toinentesti()
{
}