#ifndef user_h
#define user_h
#include "page.h"
#include <iostream>

using namespace std;
class page;
class post;

class user{
    private:
        string id;
        string firstname;
        string lastname;
        int numfriends;
        user** friendlist;
        int numpages;
        page** likedpages;
        int numposts;
        post** timeline;
    public:
        ~user()
        {
            for (int i = 0; i < numfriends; i++)
            {
                delete friendlist[i];
            }
            for (int i = 0; i < numpages; i++)
            {
                delete likedpages[i];
            }
            for (int i = 0; i < numposts; i++)
            {
                delete timeline[i];
            }
            
            
        }
        user(const string id1="000XXX",const string name1="unknown",const string name2="unknown",user** friendlistn=nullptr,page**likedpagesn=nullptr,post** timelinen=nullptr,int numfriendsn=0,int numpagesn=0,int numpostsn=0)
        {
            id=id1;
            firstname=name1;
            lastname=name2;
            numfriends=numfriendsn;
            numpages=numpagesn;
            numposts=numpostsn;
            friendlist=friendlistn;
            likedpages=likedpagesn;
            timeline=timelinen;

        }
    friend istream& operator>>(istream& input, user& u) {
    input >> u.id >> u.firstname >> u.lastname;
    
    string x;
    input>>u.numfriends;
    string x2;
    // Read friend list
    u.friendlist = new user*[u.numfriends];
    for (int i = 0; i < u.numfriends; ++i) {
        u.friendlist[i] = new user();
        input >> x2;
        (u.friendlist[i])->setfriendid(x2,u.friendlist[i]);
    }

    // Read liked pages
    input>>u.numpages;
    u.likedpages = new page*[u.numpages];
    for (int i = 0; i < u.numpages; ++i) {
        u.likedpages[i] = new page();
        string y2=" ";
        input >>y2;
        (u.likedpages[i])->setpageid(y2);
    }

    return input;
}
    friend ostream& operator<<(ostream& out,user &u)
{
    out<<u.id<<endl;
    return out;
}

        int getnumpages(){return numpages;}
        void setfirstname(string s){firstname=s;}
        void setlastname(string s){lastname=s;}
        const string getid(){return id;}
        const string getfirstname(){return firstname;}
        const string getlastname(){return lastname;}
        user**getfriendlist(){return friendlist;}
        page** getlikedpages(){return likedpages;}
        post** gettimeline(){return timeline;}
        int getnumfriends(){return numfriends;}
        int getnumposts(){return numposts;}
    void setuserid(string i)
        {
            id=i;
        }
    void addFriend(user* friendToAdd) {
        
        if (friendToAdd != nullptr && friendToAdd != this) {
            
            if (friendlist == nullptr) {
               
                friendlist = new user*[1];
                friendlist[0] = friendToAdd;
                numfriends = 1;
            } else {
                
                user** newfriendlist = new user*[numfriends + 1];
             
                for (int i = 0; i < numfriends; ++i) {
                    newfriendlist[i] = friendlist[i];
                }
            
                newfriendlist[numfriends] = friendToAdd;
                numfriends++;
          
                delete[] friendlist;

                friendlist = newfriendlist;
            }
        } else {
            cout << "Cannot add friend. Invalid friend or trying to add self." << endl;
        }
    }
    string getId() const {
        return id;
    }
    void setfriendid(string idn,user* u)
        {
            u->id=idn;
        }
    void likepage(page* newpage)
        {
            page **newpagelist=new page*[numpages+1];
            for (int i = 0; i < numfriends; i++)
            {
                newpagelist[i]=likedpages[i];
            }
            newpagelist[numfriends]=newpage;
            delete[] likedpages;
            likedpages=newpagelist;
            numpages++;
        }
    void addpost(post* newpost)
        {
            post **newpostlist=new post*[numposts+1];
            if(numposts!=0)
            {
                for (int i = 0; i < numposts; i++)
                {
                    newpostlist[i]=timeline[i];
                }
                delete[] timeline;
            }
            newpostlist[numposts]=newpost;

            timeline=newpostlist;
            numposts=numposts+1;
        }
    void displayuserdetails()
        {
            cout<<"USER-ID: "<<id<<endl;
            cout<<"NAME: "<<firstname<<" "<<lastname<< endl;
        }
    user* getfriend(int i)
        {
            return friendlist[i];
        }
    post * getpost(int i)
        {
            return timeline[i];
        }
    page* getpage(int i)
        {
            return likedpages[i];
        }
        
};
#endif