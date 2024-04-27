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
            cout<<"user const()"<<firstname<<endl;

        }
    // friend istream& operator>>(istream& input, user *uptr)
    // {
    //     user u;
    //     input>>u.id;
    //     cout<<"id    "<<u.id<<endl;
    //     input>>u.firstname;
    //     cout<<"first name "<<u.firstname<<endl;
    //     input>>u.lastname;
    //     input>>u.lastname;
    //     cout<<"last name  "<<u.firstname;

        
    //     string x=" ";
    //     while (input >> x && x != "-1") 
    //     {
    //         u.numfriends++;
    //     }

    //     string y=" ";
    //     while (input >> y && y != "-1") 
    //     {
    //     u.numpages++;
    //     }

    //     input.clear();
    //     //input.seekg();
    //     //input >> u.id >> u.firstname >> u.lastname;
    //     input>>u.id;
    //     cout<<"id    "<<u.id<<endl;
    //     input>>u.firstname;
    //     cout<<"first name "<<u.firstname<<endl;
    //     input>>u.lastname;
    //     input>>u.lastname;
    //     cout<<"last name  "<<u.firstname;



    //     u.friendlist = new user*[u.numfriends];
    //     for (int i = 0; i < u.numfriends; ++i) 
    //     {
    //         u.friendlist[i] = new user();
    //         input >> (u.friendlist[i]->firstname);
    //         input>>(u.friendlist[i]->lastname);
    //     }

    //     u.likedpages = new page*[u.numpages];

    //     for (int i = 0; i < u.numpages; ++i) 
    //     {
    //         u.likedpages[i] = new page();
    //         input>> (u.likedpages[i]);
    //     }

    //    uptr=&u;
    //     return input;
       
    
    // }
    friend istream& operator>>(istream& input, user& u) {
    input >> u.id >> u.firstname >> u.lastname;
    // Count the number of friends
    string x;
    // while (input >> x && x != "-1") {
    //     u.numfriends++;
    // }
    
    // // Count the number of liked pages
    // string y;
    // while (input >> y && y != "-1") {
    //     u.numpages++;
    // }
    
    // Reset the input stream
    //input.clear();
    //input.seekg(0, ios::beg);

    // Skip the id, firstname, and lastname
    //input >> x >> x >> x;
    
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
        // Check if friendToAdd is not null and user is not trying to add themselves as friend
        if (friendToAdd != nullptr && friendToAdd != this) {
            // Check if friendlist is not null
            if (friendlist == nullptr) {
                // If friendlist is null, allocate memory for the first friend
                friendlist = new user*[1];
                friendlist[0] = friendToAdd;
                numfriends = 1;
            } else {
                // Allocate memory for a new friend list with one more friend
                user** newfriendlist = new user*[numfriends + 1];
                // Copy existing friends to the new friend list
                for (int i = 0; i < numfriends; ++i) {
                    newfriendlist[i] = friendlist[i];
                }
                // Add the new friend to the end of the list
                newfriendlist[numfriends] = friendToAdd;
                numfriends++;
                // Deallocate memory for the old friend list
                delete[] friendlist;
                // Update friendlist pointer to point to the new friend list
                friendlist = newfriendlist;
            }
        } else {
            cout << "Cannot add friend. Invalid friend or trying to add self." << endl;
        }
    }

    // Method to get user ID
    string getId() const {
        return id;
    }

        // void addFriendById(const string& friendId) {
        //         // Search for the user with the given ID
        //         user* friendUser = getUserById(friendId);

        //         // If the user is found, add them to the friendlist
        //         if (friendUser != nullptr) {
        //             // Add the friendUser to the friendlist
        //             friendlist[numfriends] = friendUser;
        //             // Increment the numfriends count
        //             numfriends++;
        //         } else {
        //             cout << "User with ID " << friendId << " not found." << endl;
        //         }
        //     }

            
        // void addfriend(user* newfriend)
        // {
        //     user **newfriendlist=new user*[numfriends+1];
        //     for (int i = 0; i < numfriends; i++)
        //     {
        //         newfriendlist[i]=friendlist[i];
        //     }
        //     newfriendlist[numfriends]=newfriend;
        //     delete[] friendlist;
        //     friendlist=newfriendlist;
        //     numfriends++;
        // }
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