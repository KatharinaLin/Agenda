#include <iostream>
#include "AgendaService.hpp"
    /**
     * constructor
     */
AgendaService::AgendaService() {
    startAgenda();
}

    /**
     * destructor
     */
AgendaService::~AgendaService() {
    quitAgenda();
}

    /**
     * check if the username match password
     * @param userName the username want to login
     * @param password the password user enter
     * @return if success, true will be returned
     */
bool AgendaService::userLogIn(const std::string userName, const std::string password) {
    std::list<User> test;
    test = (*m_storage).queryUser(
          [userName](const User &Guy) -> bool {
            if (userName == Guy.getName()) return true;
            return false;
          }
        );
    if (test.size() == 0) return false;
    if ((test.front()).getPassword() == password) {
        return true;
    }
    return false;
}

    /**
     * regist a user
     * @param userName new user's username
     * @param password new user's password
     * @param email new user's email
     * @param phone new user's phone
     * @return if success, true will be returned
     */
bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
    std::list<User> test;
    test = (*m_storage).queryUser(
          [userName](const User &Guy) -> bool {
            if (userName == Guy.getName()) return true;
            return false;
          }
        );
    if (test.size() != 0) return false;
    for (auto i = 0; i < userName.length(); i++) {
        if (userName[i] == '\"' || userName[i] == ',') return false;
    }
    for (auto i = 0; i < password.length(); i++) {
        if (password[i] == '\"' || password[i] == ',') return false;
    }
    User Oth(userName, password, email, phone);
    (*m_storage).createUser(Oth);
    return true;
}

    /**
     * delete a user
     * @param userName user's username
     * @param password user's password
     * @return if success, true will be returned
     */




bool AgendaService::deleteUser(const std::string userName, const std::string password) {
    auto example = (*m_storage).deleteUser(
            [userName, password] (const User& Guy) -> bool {
                if (userName == Guy.getName() && password == Guy.getPassword()) {
                    return true;
                }
                return false;
            }
        );
    if (example == 0) return false;
    auto gg = (*m_storage).deleteMeeting(
            [userName] (const Meeting& HeHe) -> bool {
                if (HeHe.getSponsor() == userName || HeHe.isParticipator(userName)) {
                    return true;
                }
                return false;
            }
        );
    return true;
}

    /**
     * list all users from storage
     * @return a user list result
     */
std::list<User> AgendaService::listAllUsers(void) const {
    auto test = (*m_storage).queryUser(
            [] (const User& HeHe) -> bool {
                return true;
            }
        );
    return test;
}

    /**
     * create a meeting
     * @param userName the sponsor's userName
     * @param title the meeting's title
     * @param participator the meeting's participator
     * @param startData the meeting's start date
     * @param endData the meeting's end date
     * @return if success, true will be returned
     */
bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) throw(Incorrect){


    auto tested = (*m_storage).queryMeeting(
            [title] (const Meeting& Hallo) -> bool {
                if (title == Hallo.getTitle()) return true;
                return false;
            }
        );
    if (tested.size() != 0) {
        ICTitle a;
        throw a;
    }
    
    

    Date startone(startDate);
    Date endone(endDate);
    if (!(startone.isValid(startone))) {
        ICValidTime b;
        throw b;
    } else if (!(endone.isValid(endone))) {
        ICValidTime c;
        throw c;
    } else {
        if (startone >= endone) {
            ICStartTimeEndtime d;
            throw d;
        } else {

if (participator.size() < 0) {
                ICValidParticipators f;
                    throw f; 
            }
            //Whether Pariticipators are Valid
            for (auto i = 0; i < participator.size();i++) {
                if (userName == participator[i]) {
                    ICSponsorParticipators e;

                    throw e;
                }
            }
            
            for (auto i = 0; i < participator.size(); i++) {
                auto Want = participator[i];
                auto testing = (*m_storage).queryUser(
                        [Want] (const User& Going) -> bool {
                            if (Want == Going.getName()) {

                                return true;
                            }
                            return false;
                        }
                    );
                
                if (testing.size() != 1) {
                    ICValidParticipators f;
                    throw f;
                }
            }
            //Whether Pariticipators are Valid




            //Time Checking
            auto SponCheck = listAllMeetings(userName);
            for (auto iter = SponCheck.begin(); iter != SponCheck.end(); iter++) {
                        if ((!(iter->getStartDate() >= endone)) && (!(iter->getEndDate() <= startone))) {
                            InProTimeUser g;
                            throw g;
                            
                        }
            }
//2012-02-26/15:00
            for (auto it = participator.begin(); it != participator.end(); it++) {
                auto PartiCheck = listAllMeetings(*it);
                for (auto iter = PartiCheck.begin(); iter != PartiCheck.end(); iter++) {
                        if ((!(iter->getStartDate() >= endone)) && (!(iter->getEndDate() <= startone))) {
                            
                            InProTimeParticipator h;
                            throw h;
                        }
                }
            }
            Meeting ggda(userName, participator, startone, endone, title);
            m_storage->createMeeting(ggda);
            return true;
        }
    }
}

    /**
     * search meetings by username and title (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param title the meeting's title
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
    auto GgGg = (*m_storage).queryMeeting(
            [userName, title] (const Meeting& Sad) -> bool {
                if (userName == Sad.getSponsor() || Sad.isParticipator(userName)) {
                    if (title == Sad.getTitle()) {
                        return true;
                    }
                }
                return false;
            }
        );
    return GgGg;
}
    /**
     * search a meeting by username, time interval (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param startDate time interval's start date
     * @param endDate time interval's end date
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
    auto Judge = (*m_storage).queryUser(
            [userName] (const User& GoDie) -> bool {
                if (userName == GoDie.getName()) return true;
                return false;
            }
        );
    std::list<Meeting> emptyone;
    if (Judge.size() == 0) {
        return emptyone;
    }

    Date startone(startDate);
    Date endone(endDate);
    if (!(startone.isValid(startone) && endone.isValid(endone))) {
        return emptyone;
    }
    if (startone > endone) return emptyone;
    
    auto OtherList = (*m_storage).queryMeeting(
        [userName, startone, endone] (const Meeting& Ai) -> bool {
            if (userName == Ai.getSponsor() || Ai.isParticipator(userName)) {
                if (!((Ai.getStartDate()>endone)||(Ai.getEndDate()<startone))) {
                    return true;
                }
            }
            return false;
        }
        );
    return OtherList;
}

    /**
     * list all meetings the user take part in
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
    auto ListOne = (*m_storage).queryMeeting(          

            [userName] (const Meeting& Find) -> bool {
                if (userName == Find.getSponsor() || Find.isParticipator(userName)) return true;
                return false;
            }
        );
    return ListOne;
}

    /**
     * list all meetings the user sponsor
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
    auto Spon = (*m_storage).queryMeeting(
            [userName] (const Meeting& Find) -> bool {
                if (userName == Find.getSponsor()) return true;
                return false;
            }
        );
    return Spon;
}

    /**
     * list all meetings the user take part in and sponsor by other
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
    auto Pati = (*m_storage).queryMeeting(
            [userName] (const Meeting& Fin) -> bool {
                if (Fin.isParticipator(userName)) return true;
                return false;
            }
        );
    return Pati;
}

    /**
     * delete a meeting by title and its sponsor
     * @param userName sponsor's username
     * @param title meeting's title
     * @return if success, true will be returned
     */
bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
    int amount = (*m_storage).deleteMeeting(
            [userName, title] (const Meeting& MeetingAll) -> bool {
                if (userName == MeetingAll.getSponsor() && title == MeetingAll.getTitle()) {
                    return true;
                }
                return false;
            }
        );
    if (amount == 0) return false;
    return true;
}

    /**
     * delete all meetings by sponsor
     * @param userName sponsor's username
     * @return if success, true will be returned
     */
bool AgendaService::deleteAllMeetings(const std::string userName) {
    int amount = (*m_storage).deleteMeeting(
            [userName] (const Meeting& MeetingAll) -> bool {
                if (userName == MeetingAll.getSponsor()) {
                    return true;
                }
                return false;
            }
        );
    if (amount == 0) return false;
    return true;
}

    /**
     * start Agenda service and connect to storage
     */
void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
}

    /**
     * quit Agenda service
     */
void AgendaService::quitAgenda(void) {
   m_storage->sync();
}

bool AgendaService::changePassword(const std::string userName, const std::string password, std::string newPass) {
    auto fil = (*m_storage).updateUser(
            [userName, password] (const User& one) -> bool {
                if (userName == one.getName() && password == one.getPassword()) {
                    return true;
                }
                return false;
            },
            [=] (User& one) {
                one.setPassword(newPass);
            }
        );
}
bool AgendaService::changeEmail(const std::string userName, const std::string password, std::string NewEmail) {
    auto fil = (*m_storage).updateUser([userName, password] (const User& one) -> bool {
                if (userName == one.getName() && password == one.getPassword()) {
                    return true;
                }
                return false;
            },
            [=] (User& one) {
                one.setEmail(NewEmail);
            }
            );
}
bool AgendaService::changePhone(const std::string userName, const std::string password, std::string NewPhone) {
    auto fil = (*m_storage).updateUser([userName, password] (const User& one) -> bool {
                if (userName == one.getName() && password == one.getPassword()) {
                    return true;
                }
                return false;
            },
            [=] (User& one) {
                one.setPhone(NewPhone);
            }
            );
}