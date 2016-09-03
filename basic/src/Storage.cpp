#include <iostream>
#include "Storage.hpp"
#include <functional>
#include <list>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Path.hpp"
using std::string;
using std::endl;
std::shared_ptr<Storage> Storage::m_instance = NULL;
Storage::Storage() {
  readFromFile();
  m_dirty = false;
}
  /*
  *   read file content into memory
  *   @return if success, true will be returned
  */
bool Storage::readFromFile(void) {
  std::ifstream in(Path::userPath);
  if (!in) return false;
  string line;
  while (getline(in, line)) {
    if (line.length() == 0) break;
    if (in) {
      std::istringstream sin(line);
    std::vector<string> datas;
    string data;
    while (getline(sin, data, ',')) {
      datas.push_back(data);
    }
    std::vector<string> updatas;
    int i;
    for (i = 0; i < 4; i++) {
      updatas.push_back(datas[i].substr(1, datas[i].length()-2));
    }

    User newone(updatas[0], updatas[1], updatas[2], updatas[3]);
    m_userList.push_back(newone);
    }
  }
  in.close();
  std::ifstream min(Path::meetingPath);


  //meeting reading 
  if (!min) return false;
  while (getline(min, line)) {
    if (line.length() == 0) break;
    if (min) {
      std::istringstream msin(line);
    std::vector<string> num;
    string numb;
    while (getline(msin, numb, ',')) {
      num.push_back(numb);
    }

    std::vector<string> part;
    int i;
    std::vector<string> upmeetings;
    for (i = 0; i < num.size(); i++) {
      upmeetings.push_back(num[i].substr(1, num[i].length()-2));
    }
    std::vector<int> sign;
    string str = upmeetings[1];

    
    for (i = 0; i < upmeetings[1].length(); i++) {
      if (str[i] == '&') sign.push_back(i);
    }
    std::vector<string> participate;
    int j = sign.size();
    
    if (j == 0) {
      participate.push_back(str);
    } else if (j == 1) {
      participate.push_back(str.substr(0, sign[0]));
      participate.push_back(str.substr(sign[0]+1, str.length()-sign[0]-1));
    } else {
      for (i = 0; i < j; i++) {
      if (i == 0) participate.push_back(str.substr(0, sign[0]));
      else participate.push_back(str.substr(sign[i-1]+1, sign[i]-sign[i-1]-1));
    }
    participate.push_back(str.substr(sign[j-1]+1, str.length()-sign[j-1]-1));
  }
    Date A(upmeetings[2]);
    Date B(upmeetings[3]);
    Meeting newtwo(upmeetings[0], participate, A, B, upmeetings[4]);
    participate.clear();
    m_meetingList.push_back(newtwo);
    }
  }
  min.close();
  return true;
}

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
bool Storage::writeToFile(void) {
  if (m_dirty) {
    std::ofstream outfile;
    if (outfile.fail()) return false;
  outfile.open(Path::userPath);
  if (!outfile.is_open()) return false;
  for (auto iter = m_userList.begin(); iter != m_userList.end(); ++iter) {
    outfile << "\"" << (*iter).getName() << "\"" << "," << "\"" << (*iter).getPassword()
    << "\"" << ","<< "\"" << (*iter).getEmail() << "\"" << "," << "\"" 
    << (*iter).getPhone() << "\"" << endl;
  }
  outfile.close();
  std::ofstream output;
  output.open(Path::meetingPath);
  if (!output.is_open()) return false;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    output << "\"" << (*it).getSponsor() << "\"" << ",";
    std::vector<std::string> participat = (*it).getParticipator();
    int i = 1;
    output << "\"" << participat[0];
    for (i = 1; i < participat.size(); i++) {
      output << '&' << participat[i];
    }
    output << "\"" << ","<< "\"" ;
    output << ((*it).getStartDate()).dateToString((*it).getStartDate());
    output << "\"" << ","<< "\"" ;
    output << ((*it).getEndDate()).dateToString((*it).getEndDate());
    output << "\"" ","<< "\"" ;
    output << (*it).getTitle();
    output << "\"" << endl;
  }
  output.close();
  m_dirty = false;
  return true;
  }
  return true;
}


  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
std::shared_ptr<Storage> Storage::getInstance(void) {
  if (m_instance == NULL) {
    m_instance = (std::shared_ptr<Storage>)new Storage;
    return m_instance;
  } else {
    return m_instance;
  }
}

  /**
  *   destructor
  */
Storage::~Storage() {
  sync();
}

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
void Storage::createUser(const User & t_user) {
  m_dirty = true;
  m_userList.push_back(t_user);
}

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
  std::list<User>::iterator it;
  std::list<User> completelyNew;
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if ((filter)((*it))) completelyNew.push_back((*it));
  }
  return completelyNew;
}

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
  int counter = 0;
 
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if ((filter)((*it))) {
      (switcher)(*it);
      ++counter;
    }
  }
  m_dirty = true;
  return counter;
}

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
int Storage::deleteUser(std::function<bool(const User &)> filter) {
  int counter = 0;
  for (auto it = m_userList.begin(); it != m_userList.end();) {
    if ((filter)((*it))) {
      it = m_userList.erase(it);
      ++counter;
    } else {
      it++;
    }
  }
  
  m_dirty = true;
  return counter;
}

  /**
  * create a meeting
  * @param a meeting object
  */
void Storage::createMeeting(const Meeting & t_meeting) {
  m_meetingList.push_back(t_meeting);
  m_dirty = true;
}

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {

  std::list<Meeting> completelyNew;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if ((filter)((*it))) completelyNew.push_back((*it));
  }
  return completelyNew;
}

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
  int counter = 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if ((filter)((*it))) {
      (switcher)(*it);
      ++counter;
    }
  }
  m_dirty = true;
  return counter;
}

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
  int counter = 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end();) {
    if ((filter)((*it))) {
      it = m_meetingList.erase(it);
      ++counter;
    } else {
      it++;
    }
  }
  m_dirty = true;
  return counter;
}

  /**
  * sync with the file
  */
bool Storage::sync(void) {
  if (writeToFile()) return true;
  return false;
}