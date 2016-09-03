#include <iostream>
#include <exception>

using namespace std;
class Incorrect {
public:
	Incorrect() {}
    virtual ~Incorrect(){}
};

class ICTitle : public Incorrect {
public:
	ICTitle() {
		name = "title";
	}
	~ICTitle() {}
private:
	string name;
};

class ICValidTime : public Incorrect {
public:
	ICValidTime() {
		name = "TimeInvalid ";
	}
	~ICValidTime(){}
private:
	string name;
	string time;
};

class ICStartTimeEndtime : public Incorrect {
public:
	ICStartTimeEndtime() {
		name = "StartTimeEndTime";
	}
	~ICStartTimeEndtime(){}
private:
	string name;
};

class ICValidParticipators : public Incorrect {
public:
	ICValidParticipators() {
		name = "ParticipatorsInvalid ";
	}
	~ICValidParticipators(){}
private:
	string name;
	string pa;
};

class ICSponsorParticipators : public Incorrect {
public:
	ICSponsorParticipators () {
		name = "SponsorIsParticipators";
	}
    ~ICSponsorParticipators (){}
private:
	string name;
};



class InProTimeUser : public Incorrect {
public:
	InProTimeUser () {
		name = "UserTimeConfilct";
	}
	~InProTimeUser (){}
private:
	string name;
};

class InProTimeParticipator : public Incorrect {
public:
	InProTimeParticipator () {
		name = "PariticipatorsTimeConfilct ";
	}
	~InProTimeParticipator (){}
private:
	string name;
};