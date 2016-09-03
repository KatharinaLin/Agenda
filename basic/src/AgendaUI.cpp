#include <iostream>
#include "AgendaUI.hpp"
#include <sstream>
#include <iomanip>
using namespace std;

AgendaUI::AgendaUI() {
    startAgenda();
}
void AgendaUI::OperationLoop(void) {
    while (true) {
        cout << endl;
        cout << "-----------------------------Agenda------------------------------"<<endl;
        cout << "-----------Warmly Welcome you to use the Agenda System-----------"<<endl;
        cout << "Action : " <<endl;
        cout << "l   -log in Agenda by user name and password" <<endl;
        cout << "r   -register a Agenda account" <<endl;
        cout << "q   -quit Agenda"<<endl;
        cout << "-----------------------------------------------------------------"<<endl;
        cout << endl;
        cout << "Agenda : ~$ ";
        string command;
        cin >> command;
        if (command == "l") {
            userLogIn();
        } else if (command == "r") {
            userRegister();
        } else if (command == "q") {
            quitAgenda();
            break;
        }
    }
}
    /**
     * constructor
     */
void AgendaUI::startAgenda(void) {
    m_agendaService.startAgenda();
}
    /**
     * catch user's operation
     * @return the operation
     */
std::string AgendaUI::getOperation() {
    cout << "-----------------------------Agenda------------------------------"<<endl;
    cout << "--------------------------OperationList--------------------------"<<endl;
    cout << "Action :"<<endl;
    cout << "o   - log out Agenda"<<endl;
    cout << "dc  - delete Agenda account"<<endl;
    cout << "lu  - list all Agenda user"<<endl;
    cout << "cm  - create a meeting"<<endl;
    cout << "la  - list all meetings"<<endl;
    cout << "las - list all sponsor meetings"<<endl;
    cout << "lap - list all participate meetings"<<endl;
    cout << "qm  - query meeting by title"<<endl;
    cout << "qt  - query meeting by time interval"<<endl;
    cout << "dm  - delete meeting by title"<<endl;
    cout << "da  - delete all meetings"<<endl;
    cout << "cs  - change password"<<endl;
    cout << "ce  - change email"<<endl;
    cout << "cp  - change phone"<<endl;
    cout << "------------------------------------------------------------------"<<endl;
    cout <<endl;
    cout << "Agenda@"<<m_userName<<" : # ";
    string order;
    cin >> order;
    return order; 
}

    /**
     * execute the operation
     * @return if the operationloop continue
     */
bool AgendaUI::executeOperation(std::string t_operation) {
    cout << endl;
    if (t_operation == "o") {
        userLogOut();
        return false;
    } else if (t_operation == "dc") {
        deleteUser();
        return false;
    } else if (t_operation == "lu") {
        listAllUsers();
        return true;
    } else if (t_operation == "cm") {
        createMeeting();
        return true;
    } else if (t_operation == "la") {
        listAllMeetings();
        return true;
    } else if (t_operation == "las") {
        listAllSponsorMeetings();
        return true;
    } else if (t_operation == "lap") {
        listAllParticipateMeetings();
        return true;
    } else if (t_operation == "qm") {
        queryMeetingByTitle();;
        return true;
    } else if(t_operation == "qt") {
        queryMeetingByTimeInterval();
        return true;
    } else if (t_operation == "dm") {
        deleteMeetingByTitle();
        return true;
    } else if (t_operation == "da") {
        deleteAllMeetings();
        return true;
    } else if (t_operation == "cs") {
        changePassword();
        return true;
    } else if (t_operation == "ce") {
        changeEmail();
    } else if (t_operation == "cp") {
        changePhone();
    } else {
        return true;
    }
}
void AgendaUI::changePassword() {
    cout << endl;
    cout << "[changePassword]   [newPassword] :"<<endl;
    cout << "[changePassword]   ";
    string one;
    cin >> one;
    m_agendaService.changePassword(m_userName, m_userPassword, one);
    cout << "[changePassword]   succeed!" <<endl;
}
void AgendaUI::changeEmail() {
    cout << endl;
    cout << "[changeEmail]   [newEmail] :"<<endl;
    cout << "[changeEmail]   ";
    string one;
    cin >> one;
    m_agendaService.changeEmail(m_userName, m_userPassword, one);
    cout << "[changeEmail]   succeed!" <<endl;
}
void AgendaUI::changePhone() {
    cout << endl;
    cout << "[changePhone]   [newPhone] :"<<endl;
    cout << "[changePhone]   ";
    string one;
    cin >> one;
    m_agendaService.changePhone(m_userName, m_userPassword, one);
    cout << "[changePhone]   succeed!" <<endl;
}
    /**
     * user Login
     */
void AgendaUI::userLogIn(void) {
    cout << endl;
    cout << "[log in]   [user name]   [password]"<<endl;
    cout << "[log in]   ";
    string Name, Password;
    cin >> Name >> Password;
    if(m_agendaService.userLogIn(Name, Password)) {
        m_userName = Name;
        m_userPassword = Password;
        cout << "[log in]   succeed!"<<endl;
        while (executeOperation(getOperation()));
    } else {
        cout << "[error]   log in fail!" <<endl;
    }
}

    /**
     * user regist
     */
void AgendaUI::userRegister(void) {
    cout << endl;
    cout << "[register]   [user name] [password] [email] [phone]"<<endl;
    cout << "[register]   ";
    string Name, Password, Phone, Email;
    cin >> Name >> Password >> Phone >> Email;
    if (m_agendaService.userRegister(Name, Password, Phone, Email)) {
        m_userName = Name;
        m_userPassword = Password;
        cout << "[register]   succeed!"<<endl;
    } else {
        cout << "[error]      register fail!"<<endl;
    }
}

    /**
     * quit the Agenda
     */
void AgendaUI::quitAgenda(void) {
    m_agendaService.quitAgenda();
}

    /**
     * user logout
     */
void AgendaUI::userLogOut(void) {
    m_userPassword.clear();
    m_userName.clear();
}

    /**
     * delete a user from storage
     */
void AgendaUI::deleteUser(void) {
    m_agendaService.deleteUser(m_userName, m_userPassword);
    m_userName.clear();
    m_userPassword.clear();
    cout << "[delete Agenda account]  succeed!"<<endl;
}

    /**
     * list all users from storage
     */
void AgendaUI::listAllUsers(void) {
    auto AllUser = m_agendaService.listAllUsers();
    cout << endl;
    cout << "[list all users]" <<endl;
    cout << std::left<<std::setw(25)<<"[name]"<<std::left<<std::setw(25)<<"[email]"<<"[phone]" <<endl;
    for (auto it = AllUser.begin(); it != AllUser.end(); it++) {
        cout << std::left<<std::setw(25)<<(*it).getName() << std::left<<std::setw(25)<<(*it).getEmail() <<(*it).getPhone()<<endl;
    }
    cout <<endl;
}

    /**
     * user create a meeting with someone else
     */
void AgendaUI::createMeeting(void) {
    cout << endl;
    cout << "[create meeting]   [the number of participators]"<<endl;
    cout << "[create meeting]   ";
    string amount;
    cin >> amount;
    for (auto i = 0; i < amount.length(); i++) {
        if (amount[i] < '0' || amount[i] > '9') {
            cout << "Sorry, you enter wrong data, and please enter again." <<endl;
            return;
        }
    }
    stringstream ss;
    int n = 0;
    ss << amount;
    ss >> n;
    cout << endl;
    std::vector<string> pator;
    for (auto i = 0; i < n; i++) {
        cout << "[create meeting]   [please enter the participator " << (i+1) << " ]" <<endl;
        cout << "[create meeting]   ";
        string pp;
        cin >> pp;
        pator.push_back(pp);
        cout << endl;
    };
    cout << "[create mmeting]   [title]  [start time(yyyy-mm-dd/hh:mm)]  [end time(yyyy-mm-dd/hh:mm)]"<< endl;
    cout << "[create meeting]   ";
    string Title, StartTime, EndTime;
    cin >> Title >> StartTime >> EndTime;
    cout << endl;
    try {
        m_agendaService.createMeeting(m_userName, Title, StartTime, EndTime, pator);
        cout << "[create meeting]   succeed!"<<endl;
    } catch (ICTitle e) {
        cout << "[create meeting]   error!"<<endl;
        std::cout << "title has already exist." <<endl;
    } catch (ICValidTime e) {
        cout << "[create meeting]   error!"<<endl;
        std::cout << "Time you enter is Invalid." <<endl;
    } catch (ICStartTimeEndtime e) {
        cout << "[create meeting]   error!"<<endl;
        std::cout << "start time is later than end time." <<endl;
    } catch (ICValidParticipators e) {
        cout << "[create meeting]   error!"<<endl;
        std::cout << "Participators you enter is Invalid." <<endl;
    } catch (ICSponsorParticipators e) {
        cout << "[create meeting]   error!"<<endl;
        std::cout << "Sponsor can't be a Participator." <<endl;
    } catch (InProTimeUser e){
        cout << "[create meeting]   error!"<<endl;
        std::cout << "The time is confilcted with user." <<endl;
    } catch (InProTimeParticipator e) {
        cout << "[create meeting]   error!"<<endl;
        std::cout << "The time is confilcted with Participators"<<endl;
    }
}

    /**
     * list all meetings from storage
     */
void AgendaUI::listAllMeetings(void) {
    cout << endl;
    cout << "[list all meetings]"<<endl;
    cout << endl;
    auto KKList = m_agendaService.listAllMeetings(m_userName);
    printMeetings(KKList);
}

    /**
     * list all meetings that this user sponsored
     */
void AgendaUI::listAllSponsorMeetings(void) {
    cout << endl;
    cout << "[list all  sponsor meetings]"<<endl;
    cout << endl;
    auto KKList = m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(KKList);
}

    /**
     * list all meetings that this user take part in
     */
void AgendaUI::listAllParticipateMeetings(void) {
    cout << endl;
    cout << "[list all  participator meetings]"<<endl;
    cout << endl;
    auto KKList = m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(KKList);
}

    /**
     * search meetings by title from storage
     */
void AgendaUI::queryMeetingByTimeInterval(void) {
    cout << endl;
    cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)]  [end time(yyyy-mm-dd/hh:mm)] :"<<endl;
    cout << "[query meeting] ";
    string Start, End;
    cin >> Start >> End;
    cout << endl;
    auto KKList = m_agendaService.meetingQuery(m_userName, Start, End);
    printMeetings(KKList);
}

    /**
     * search meetings by timeinterval from storage
     */
void AgendaUI::queryMeetingByTitle(void) {
    cout << endl;
    cout << "[query meeting] [title] :"<<endl;
    cout << "[query meeting] ";
    string Title;
    cin >> Title;
    cout << endl;
    auto KKList = m_agendaService.meetingQuery(m_userName, Title);
    printMeetings(KKList);
}

    /**
     * delete meetings by title from storage
     */
void AgendaUI::deleteMeetingByTitle(void) {
    cout << endl;
    cout << "[delete meeting] [title] :"<<endl;
    cout << "[delete meeting] ";
    string Title;
    cin >> Title;
    cout << endl;
    cout << endl;
    if (m_agendaService.deleteMeeting(m_userName, Title)) {
        cout << "[delete meeting by title] :  succeed!"<<endl;
    } else {
        cout << "[error] delete meeting fail!" <<endl;
    }
}

    /**
     * delete all meetings that this user sponsored
     */
void AgendaUI::deleteAllMeetings(void) {
    cout << endl;
    m_agendaService.deleteAllMeetings(m_userName);

    cout << "[delete all meetings] succeed!"<<endl;
}
    
    /**
     * show the meetings in the screen
     */
void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    cout << std::left<<std::setw(40)<<"title"<<std::left<<std::setw(30)<<"sponsor"<<std::left<<std::setw(25)<<"start time"<<std::left<<std::setw(25)<<"end time"<<"participators"<<endl;
    for (auto it = t_meetings.begin(); it != t_meetings.end(); it++) {
        cout << std::left<<std::setw(40)<<(*it).getTitle();
        cout << std::left<<std::setw(30)<<(*it).getSponsor();
        string memeda = ((*it).getStartDate()).dateToString((*it).getStartDate());
        cout << std::left<<std::setw(25)<<memeda;
        string heheda = ((*it).getEndDate()).dateToString((*it).getEndDate());
        cout << std::left<<std::setw(25)<<heheda;
        auto List = ((*it).getParticipator());
        cout << List[0];
        for (auto i = 1; i < List.size(); i++) {
            cout << ", " << List[i];
        }
        cout << endl;
    }
}
