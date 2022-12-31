#include "strmsrv.h"
#include <iostream>
#include <fstream>
using namespace std;

// To do - Complete this function
StreamService::StreamService()

{
    // Update as needed
    cUser_ = NULL;

}

// To do - Complete this function
StreamService::~StreamService()
{
for(unsigned int i =0; i < content_.size(); i++){
  delete content_[i];
}
for(unsigned int i =0; i<users_.size(); i++){
  delete users_[i];
}

}

// Complete - Do not alter
void StreamService::readAndParseData(std::istream& is, Parser& p)
{
    p.parse(is, content_, users_);
    cout << "Read " << content_.size() << " content items." << endl;
    cout << "Read " << users_.size() << " users." << endl;
}

// To do - Complete this function
void StreamService::userLogin(const std::string& uname)
{
  if(cUser_ != NULL){
    throw std::runtime_error("The user is already logged in");
  }
  else if(users_.size()!=0){
    bool valid = false;
    for(unsigned int i =0; i< users_.size(); i++){
      if(users_[i]->uname == uname){
        valid = true;
        
      }
    }
    if(valid == false){
      throw std::invalid_argument("Not a valid username");
    }
  int index = getUserIndexByName(uname);
  cUser_ = users_[index];
}
}

// To do - Complete this function
void StreamService::userLogout()
{
  if(cUser_ != NULL){
    cUser_ = NULL;
  }
}

// To do - Complete this function
std::vector<CID_T> StreamService::searchContent(const std::string& partial) const
{
    std::vector<CID_T> results;
    for(size_t i = 0; i < content_.size(); i++){
        // TO DO - modify this to also push back when the string 'partial'
        //  is contained in the name of the current content. Lookup the string
        //  class documentation to find an appropriate function that can be used
        //  to do this simply.
        if(partial == "*" /* update me */ || content_[i]->name().find(partial) != string::npos){
            results.push_back(content_[i]->id());
        }
        // else{
        //   string str = content_[i]->name();
        //   unsigned int find = str.find(partial);
        //   if(find != string::npos){
        //     results.push_back(content_[i]->id());
        //   }
        // }        
    }
    return results;
}

// Complete - Do not alter
std::vector<CID_T> StreamService::getUserHistory() const
{
    throwIfNoCurrentUser();
    return cUser_->history;
}

// To do - Complete this function
void StreamService::watch(CID_T contentID)
{
  throwIfNoCurrentUser();
  if(!isValidContentID(contentID)){
    throw::range_error("Invalid content ID");
  }
  int index = getUserIndexByName(cUser_->uname);
  int ratinglimit = users_[index]->ratingLimit;
  for(unsigned int i =0; i< content_.size(); i++){
    if(content_[i]->id() == contentID){
      int rating = content_[i]->rating();
      if(rating > ratinglimit){
        throw::RatingLimitError("Rating limit error");
      }
      content_[i]->addViewer(cUser_->uname);
    }
  }
  cUser_->addToHistory(contentID);
  

}

// To do - Complete this function
void StreamService::reviewShow(CID_T contentID, int numStars)
{
  throwIfNoCurrentUser();
  if(!isValidContentID(contentID) || numStars >5 || numStars < 0){
    throw::ReviewRangeError("Range error");
  }
  for(unsigned int i =0; i< content_.size(); i++){
    if(content_[i]->id() == contentID){
      content_[i]->review(numStars);
    }
  }


}

// To do - Complete this function
CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const
{
    // Change this when you are ready, but for now it is a 
    // dummy implementation
    cout << "Started" << endl;
    if(!isValidContentID(contentID)){
      throw range_error("Invalid contentID");
    }
    throwIfNoCurrentUser();
    cout << "Made past error 2" << endl;
    std::vector<string> viewdUsers;
    std::vector<int> views;
    for(unsigned int i =0; i < content_.size(); i++){
      views.push_back(0);
    }

    // cout<< content_[0]->getViewers().size() << endl;
    for(unsigned int i =0; i<content_.size(); i++){
      // cout << "Ran first loop once " << endl;
        for(unsigned int j =0; j< content_[i]->getViewers().size();j++){
          // cout << "Ran first loop " << j <<  endl;
          if(content_[i]->id() == contentID){
            if(content_[i]->getViewers()[j] != cUser_->uname){
              viewdUsers.push_back(content_[i]->getViewers()[j]);
            }
          }
        }
      
    }
    cout << "Viewd user loop ran" << endl;
    cout << "Viwd user size " << viewdUsers.size() << endl;
    //Loop through the content have a views counter have an external max value and max content valid
    Content* max = NULL;
    int maxviews = 0;
    //Loop through users if the users name is in the viewd users take that users watch history
    //find the content id and then add that to the total vec
    for(unsigned int i =0; i< content_.size();i++){
      if(contentID == content_[i]->id()){
        if(content_[i]->getViewers().empty()){
          return -1;
        }
      }
    }
    
    for(unsigned int i=0; i<users_.size();i++){
      User* iuser = users_[i];
      for(unsigned int x =0; x < viewdUsers.size(); x++){
        if(iuser->uname == viewdUsers[x]){
          //get user history
          for(unsigned int j =0; j<iuser->history.size(); j++){
            int cid = iuser->history[j];
            if(cid != contentID && !cUser_->haveWatched(cid)){
              views[cid]++;
            }
            
          }
        }
      }
    }
  cout << "Ran this " << endl;
  int maxindex;
    for(unsigned int i =0; i<views.size();i++){
      cout << views[i] << " " << endl;
        if(views[i] > maxviews){
        maxindex = i;
        maxviews = views[i];
      }
    }
    if(maxviews ==0){
      return -1;
    }

    max = content_[maxindex];
      
    

    return max->id();


}

// To do - Complete this function
void StreamService::displayContentInfo(CID_T contentID) const
{
    // Do not alter this
    if(! isValidContentID(contentID)){
        throw std::invalid_argument("Watch: invalid contentID");
    }

    // Call the display abitlity of the appropriate content object
    content_[contentID]->display(std::cout);


}

// Complete - Do not alter
bool StreamService::isValidContentID(CID_T contentID) const
{
    return (contentID >= 0) && (contentID < (int) content_.size());
}

// Complete - Do not alter
void StreamService::throwIfNoCurrentUser() const
{
    if(cUser_ == NULL){
        throw UserNotLoggedInError("No user is logged in");
    }
}

// Complete - Do not alter
int StreamService::getUserIndexByName(const std::string& uname) const
{
    for(size_t i = 0; i < users_.size(); i++){
        if(uname == users_[i]->uname) {
            return (int)i;
        }
    }
    return -1;
}
