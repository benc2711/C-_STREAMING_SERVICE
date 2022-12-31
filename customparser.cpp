// Complete me
#include "customparser.h"
#include <iostream>
#include <sstream>

using namespace std;

const char* error_msg_1 = "Cannot read integer n";
const char* error_msg_2 = "Error in content parsing";
const char* error_msg_3 = "Error in user parsing";

// To Do - Complete this function
void CustomFormatParser::parse(std::istream& is, std::vector<Content*>& content, std::vector<User*>& users)
{
    // Erase any old contents
    content.clear();
    users.clear();

    // TO DO - Add your code below.
    int n;
    is >> n;
    if(is.fail()){
      throw ParserError(error_msg_1);
    }
    for(int i =0; i< n; i++){
      
            int id;
            int type;
            int nr;
            int ts;
            int rating;
            string name;
            is >> id >> type;
            if(is.fail()){
              throw ParserError(error_msg_2);
            }
            cout << "ID: " << id << "Type: " << type << endl;
            string uncutname;
            
            is >> name;
            if(is.fail()){
              throw ParserError(error_msg_2);
            }
            // name += " ";
            // cout << "Nametest" << nametest << endl;
            getline(is, uncutname);
            // cout << "Uncut name" << uncutname << endl;
            stringstream uncutnames(uncutname);
            string pname;
            while(uncutnames >> pname){
              name += " ";
              name +=pname;
              
            }
            cout << "Name: " << name << endl;
            

            
            is >> nr;
            if(is.fail()){
              throw ParserError(error_msg_2);
            }
            is >> ts;
            if(is.fail()){
              throw ParserError(error_msg_2);
            }
            is >> rating;
            if(is.fail()){
              throw ParserError(error_msg_2);
            }

            cout << "nr: " << nr << " ts: " << ts << " rating: " << rating << endl;
            int numEp = 0;
            if(type == 1){
              is>> numEp;
              if(is.fail()){
                throw ParserError(error_msg_2);
            }
            }
            Content* newc = NULL;
            if(type == 0){
                newc = new Movie(id, name, nr, ts, rating);
                content.push_back(newc);
                // cout << "Created movie" << endl;
            }
            else {
                newc = new Series(id, name, nr, ts, rating, numEp);
                content.push_back(newc);
                // cout << "Created Series" << endl;
            }
            // string user1;
            // is >> user1;
            // cout << "First user: " << user1 << endl;
            // newc->addViewer(user1);
            string linef;
            getline(is, linef);
            string line;
            getline(is, line);
            if(!line.empty()){
              // cout << "LINE: " << line << endl;
              stringstream ss(line);
              string word;
              
              while(ss >> word){
                cout << "User: " << word << endl;
                newc->addViewer(word);
              }
            }
      
         
    }


    // User Entry 
    // string uname;
    // int limit;
    // is >> uname;
    // cout << "First user: " << uname << endl;
    // if(is.fail()){
    //   throw ParserError(error_msg_3);
    // }
    // is >> limit;
    // if(is.fail()){
    //   throw ParserError(error_msg_3);
    // }

    // cout << "First user Limit: " << limit << endl;
    // vector<int> vec;
    // int firstWatchedContent;
    // is >> firstWatchedContent;
    // cout << "First Watched Content ID: " << firstWatchedContent << endl;
    // vec.push_back(firstWatchedContent);

    // string uNline;
    // getline(is, uNline);
    // cout << "LINE: " << uNline << endl;
    // stringstream ss(uNline);
    // int number;
    // while(ss >> number){
    //      vec.push_back(number);
    //   }
    // User* u = new User(uname, limit);
    // for(unsigned int i =0; i<vec.size();i++){
    //   u->addToHistory(vec[i]);
    // }
    // users.push_back(u);

  // cout << "USERS next " << endl;
    string uname;
    while(is >> uname){
      // cout << "LINER: " << liner << endl;
      // stringstream ss(liner);
      // cout << "WORKER" << endl;
      int limit;
      cout << "Username: " << uname << endl;
      is >> limit;
      // if(is.fail()){
      //   throw ParserError(error_msg_3);
      // }
      cout << "LIMIT: " << limit << endl;
      vector<int> vec;
      // int firstWatchedContent;
      // is >> firstWatchedContent;
      // cout << "First Watched Content ID: " << firstWatchedContent << endl;
      // vec.push_back(firstWatchedContent);

      string uNline;
      getline(is, uNline);
      getline(is, uNline);
    cout << "LINE: " << uNline << endl;
      stringstream ssr(uNline);
      int number;
      while(ssr >> number){
         vec.push_back(number);
         cout << "NUmber: " << number << endl;
      }
      User* un = new User(uname, limit);
      for(unsigned int i =0; i<vec.size();i++){
        un->addToHistory(vec[i]);
      }
      users.push_back(un);

      
    }
    // users.pop_back();



  


}

