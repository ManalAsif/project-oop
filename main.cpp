#include "user.h"
#include "page.h"
#include "post.h"
#include<iostream>
#include <chrono>
#include <ctime>
#include<windows.h>
#include<fstream>
#include<cstring>
#include <sstream>
#include <fstream>
using namespace std;
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	//Set Sets the attributes of characters written to the console screen. In this context, it's used to change the text color and background color.
}
class socialnetworkapp:public date
{
    
    private:
        user *currentuser;
        user **users;
        int numusers;
        page** likedpages;
        int numpages;
    public:
    socialnetworkapp(user* ncurrenntuser=nullptr)
    {
        currentuser=ncurrenntuser;
        cout<<"socialnetwork app const()"<<endl;
    }
    user* findUserById(const string& userId) {
        cout<<"in";
        for (int i = 0; i < numusers; ++i) {
             cout<<"in";
            cout<<users[i]->getId();
            if (users[i]->getid() == userId) {
                return users[i];
            }
        }
        cout << "User with ID " << userId << " not found." << endl;
        return nullptr;
    }
    page* findPageById(const string& pageId) {
        for (int i = 0; i < numpages; ++i) {
            if (likedpages[i]->getpageid() == pageId) {
                return likedpages[i];
            }
        }
        cout << "Page with ID " << pageId << " not found." << endl;
        return nullptr;
    }
    void readUserDataFromFile(const string& filename) 
    {

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

    int count = 0;
    string line;
    while (getline(file, line)) {
        count++;

    }
    
    file.seekg(0, ios::beg);
    numusers=count;
    user **ux=new user*[numusers];
    for (int i = 0; i < count; i++)
    {
        user u1;
        file>>u1;
        ux[i]=&u1;
        
    }
    

    
    }
    // Method to read user data from a file and initialize User objects
    // void readUserDataFromFile(const string& filename) {

    //     ifstream file(filename);
    //     if (!file.is_open()) {
    //         cerr << "Error: Unable to open file " << filename << endl;
    //         return;
    //     }

    // int count = 0;
    // string line;
    // while (getline(file, line)) {
    //     count++;
    // }

    // //file.close();

    //  file.seekg(0, ios::beg);
    //     //file >> numusers;
    //     users = new user*[count];
    //     cout<<count;
    //     numusers=count;
    //     numpages = 0; // Initialize numpages
    //     cout << "out" << endl;
    //     int i = 0;
    //     for(int i=0;i<count;i++) {
    //         cout << "out" << endl;
    //         stringstream ss(line);
    //         string userId, firstName, lastName;
    //         string friendId, likedPage;

    //         ss >> userId >> firstName >> lastName;

    //         int numFriends = 0;
    //         user** friendlist = nullptr;

    //         while (ss >> friendId && friendId != "-1") {
    //             cout<<friendId;
    //             cout << "in" << endl;
    //             user* friendToAdd = findUserById(friendId);
    //             if (friendToAdd != nullptr) {
    //                 user** resizedTemp = new user*[numusers + 1];
    //             for (int j = 0; j < numFriends; j++) {
    //                 resizedTemp[j] = friendlist[j];
    //             }
    //             delete[] friendlist;
    //             friendlist = resizedTemp;
    //             }
    //         }

    //         int numPages = 0;
    //         page** tempLikedPages = new page*[10]; // Temporary array for liked pages

    //         while (ss >> likedPage && likedPage != "-1") {
    //             tempLikedPages[numPages] = new page(likedPage, "Page Name");
               
    //             numpages++;

    //             // Resize the tempLikedPages array
    //             page** resizedTemp = new page*[numPages + 1];
    //             for (int j = 0; j < numPages; j++) {
    //                 resizedTemp[j] = tempLikedPages[j];
    //             }
    //             delete[] tempLikedPages;
    //             tempLikedPages = resizedTemp;
    //         }

    //         // Copy tempLikedPages to likedpages for the current user
    //         likedpages = new page*[numPages];
    //         for (int j = 0; j < numPages; j++) {
    //             likedpages[j] = tempLikedPages[j];
    //         }
    //         delete[] tempLikedPages;
    //         post **posts=new post*(NULL);
    //         int numposts=0;
    //         users[i] = new user(userId,firstName,lastName,friendlist,likedpages,posts,numFriends, numPages,numposts);
    //         i++;
    //     }
    //     file.close();
    // }
    
    void setcurrentuser(user *u)
    {
        *currentuser=*u;
        cout<<"set";
        
    }
    void run()
    {

        int choice;
        string currentUserName = currentuser->getfirstname();
        char border = '-';
	    Color(5);

        for (int i = 0; i < 65; i++)
        {
            cout << border; //first row border
        }

        cout<<endl;
        cout << "Welcome, " << currentUserName << "!" << endl;
        cout << "1. View Home" << endl;
        cout << "2. View Timeline" << endl;
        cout << "3. View Friend List" << endl;
        cout << "4. View Page" << endl;
        cout << "5. Like a Post" << endl;
        cout << "6. Comment on a Post" << endl;
        cout << "7. Share a Memory" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;  
        if(choice==1)
        {
            viewhome();
        }  
    }
    void viewfriendlist()
    {
        for (int i = 0; i < currentuser->getnumfriends(); i++)
        {
            user*frienduser=currentuser->getfriend(i);
            cout<<"friend"<<i<<": ";
            cout<<frienduser->getId()<<"  ";
            cout<<frienduser->getfirstname()<<" ";
            cout<<frienduser->getlastname();
            cout<<endl;
            cout<<endl;
        }
        cout<<endl;
    }
    void viewpage(string id)
    {
        for (int i = 0; i < currentuser->getnumpages(); i++)
        {
            page* currentpage=currentuser->getpage(i);
            if(currentpage->getpageid()==id)
            {
                cout<<"title: "<<currentpage->gettitle()<<endl;
                cout<<"likes: "<<currentpage->getlikes()<<endl;
                cout<<"id: "<<currentpage->getpageid()<<endl;
               for (int i = 0; i < currentpage->getnumposts(); i++)
               {
                post *post=currentpage->getpost(i);
                cout<<post;
               }
            }

        }
        
    }
    // void likepost(string id)
    // {
    //     for (int i = 0; i < currentuser->getnumfriends(); i++)
    //     {
    //         user*frienduser=currentuser->getfriend(i);
    //         for (int j = 0; j < frienduser->getnumposts(); i++)
    //         {
    //            post*currentpost=frienduser->getpost(j);
    //            if(currentpost->getpostid()==id)
    //            {
    //             if(currentpost->addpostlike())
    //             {
    //             cout<<"post with id "<<id<<" liked succesfully"<<endl;
    //             }
    //             else
    //             {
    //                 cout<<"limits of number of likes exceeded"<<endl;

    //             }
    //            }
    //         }
            
    //     }
        

    // }
    void addcommenttopost(string postid,string commenttext)
    {
        for (int i = 0; i < currentuser->getnumfriends(); i++)
        {
            user*frienduser=currentuser->getfriend(i);
            for (int j = 0; j < frienduser->getnumposts(); i++)
            {
                post*currentpost=frienduser->getpost(j);
                if(currentpost->getpostid()==postid)
                {
                    comment* newcomment=new comment(postid,currentuser,commenttext,currentpost);
                    if(currentpost->addcomment(newcomment))
                    {
                        cout<<"Comment added successfully to the post with ID " << postid << endl;
                    }
                    else 
                    {
                        cout << "Failed to add comment. Maximum comment limit reached for this post." << endl;
                    }
                }
            }
            
        }
        

        
    }
    void viewhome()
    {
        cout<<"home";
        date currentdate = date::getcurrentdate();
        cout<<currentdate;
        cout<<currentuser->getid();
        cout<<(*currentuser).getnumfriends();
    for(int i=0;i<(*currentuser).getnumfriends();i++)
    {
      cout<<"in";
        user *frienduser=(*currentuser).getfriend(i);
        cout<<(*frienduser).getnumposts()<<endl;
        for(int j=0;j<(*frienduser).getnumposts();j++)
        {
            post *post=(*frienduser).getpost(j);
            date postdate= (*post).getshareddate();
            //cout<<"current date"<<currentdate<<"post date"<<postdate<<endl;
            //cout<<"(diff)"<<currentdate.differenceInSeconds(postdate)<<endl;
           
            if(currentdate.differenceInSeconds(postdate)>=0 && (currentdate.differenceInSeconds(postdate))<=86400)
            {
                cout<<"FRIEND:    "<<frienduser->getfirstname()<<"  "<<frienduser->getlastname()<<endl<<endl;
                cout<<post;
            //    cout<<"do you want to like this post"<<endl;
            //    bool ans;
            //    cin>>ans;
            //    if(ans==1)
            //    {
            //     likepost(post->getpostid());
            //    }
               
            }
        }
    }
        for (int i = 0; i < currentuser->getnumpages(); i++)
        {
           page *currentpage=(*currentuser).getpage(i);
           cout<<(*currentpage).getnumposts()<<endl;
            //cout<<"current date"<<currentdate<<"post date"<<postdate<<endl;
            //cout<<"(diff)"<<currentdate.differenceInSeconds(postdate)<<endl;
           for(int j=0;j<(*currentpage).getnumposts();j++)
           {
            post *post=(*currentpage).getpost(j);
            date postdate= (*post).getshareddate();
            if(currentdate.differenceInSeconds(postdate)>=0 && (currentdate.differenceInSeconds(postdate))<=86400)
            {
                cout<<"page: "<<currentpage->getpageid()<<endl<<endl;
               cout<<post;
            }
            }
        
        
    
    }
    }
    void setpost()
    {
        cout<<"in";
        string filename="post.txt";
        ifstream file(filename);
        string cuserid=currentuser->getId();
        int num;
        file>>num;
        for (int i = 0; i < num*3; i++)
        {
           string line;
            getline(file,line);
            size_t pos = line.find(' ');
            string userid = line.substr(0, pos);
            
            //streampos currentPosition = file.tellg();
            if(userid==cuserid)
            {
                cout<<"JJJ";
                post *p=new post;
                //file.seekg(currentPosition - streampos());
                file>>p;
                cout<<" founddddddddddddddid:currentuser"<<p->getpostid()<<endl;
                cout<<p->gettext()<<endl;
                string *list=p->getuserid();
                string filename="user.txt";
                ifstream file(filename); 
                cout<<p->getlikes()<<endl;
                user **userlist=new user*[p->getlikes()];
                
                for (int i = 0; i < p->getlikes(); i++)
                {
                    cout<<list[i]<<endl;
                    file.clear();
                    file.seekg(0, std::ios::beg);
                    int count;
                    for (char c:list[i])
                    {
                        if(isdigit(c))
                        {  
                            count=c-'0';   
                        }
                    }
                    cout<<count;
                    for (int n = 0; n < count-1; n++)
                    {
                    
                        string x=" ";
                        getline(file,x);
                    }
                    user u2;
                    
                    file>>u2;
                    cout<<i<<u2.getid()<<endl<<"refregrr";
                    user *uptr=&u2;
                    p->addpostlike(uptr);
                }
                viewlikedbylist(p);
                
            }
        }
      file.seekg(0, std::ios::beg);
        
        for (int i = 0; i < currentuser->getnumfriends(); i++)
        {
            string x;
            file.clear();
            file.seekg(0, std::ios::beg);
            file>>x;
            
            user *f=currentuser->getfriend(i);
            string id=f->getId();
            cout<<"friend"<<i<<endl;
            cout<<f->getId()<<endl;
            
            for (int j = 0; j < num*3; j++)
            {
                
                string line1;

                getline(file,line1);
                
                size_t pos = line1.find(' ');
                string userid = line1.substr(0, pos);
                if(id==userid)
                {
                    post *p=new post;
                    file>>p;
                    f->addpost(p);
                    cout<<" founddddddddddddddid:"<<p->getpostid()<<endl;
                    cout<<p->gettext()<<endl;
                    string *list=p->getuserid();
                string filename="user.txt";
                ifstream file(filename); 
                user **userlist=new user*[p->getlikes()];
                
                for (int n = 0; n < p->getlikes(); n++)
                {
                    file.clear();
                    file.seekg(0, std::ios::beg);
                    int count;
                    cout<<"ddddddddddddddd"<<list[n]<<endl;
                    for (char c:list[n])
                    {
                        if(isdigit(c))
                        {  
                            count=c-'0';   
                        }
                    }

                    for (int z= 0; z < count-1; z++)
                    {
                    
                        string x=" ";
                        getline(file,x);
                    }
                    user u2;
                    file>>u2;
                    user *uptr=&u2;
                    p->addpostlike(uptr);
                    
                }
                
                }
            }
           
        }
        file.seekg(0, std::ios::beg);
        
        for (int i = 0; i < currentuser->getnumpages(); i++)
        {
            cout<<"pages..................."<<endl;
            string x;
            file.clear();
            file.seekg(0, std::ios::beg);
            file>>x;

            
            page *f=currentuser->getpage(i);
            string id=f->getpageid();
           
            
            for (int j = 0; j < num*3; j++)
            {
                
                string line1;

                getline(file,line1);
                
                size_t pos = line1.find(' ');
                string userid = line1.substr(0, pos);
                if(id==userid)
                {
                    cout<<"in";
                    post *p=new post;
                    file>>p;
                    f->uploadpost(p);
                    cout<<" founddddddddddddddid:"<<p->getpostid()<<endl;
                    cout<<p->gettext()<<endl;
                }
            }
           
        }

    }
    void viewlikedbylist(post*p)
    {  cout<<"list of users>>>>>>>>>>>>>>>"<<endl;
        user **u=p->getlikedby();    
        for (int i = 0; i < p->getlikes(); i++)
        {
            cout<<u[i]->getid()<<endl;
            cout<<u[i]->getfirstname()<<" "<<u[i]->getlastname()<<endl;
        }
        
    }
    void setfriendnames(string s)
    {
        cout<<"friend func"<<endl;
        string filename=s;
        ifstream file(filename); 
        for (int i = 0; i < currentuser->getnumfriends(); i++)
        {
            file.clear();
            file.seekg(0, std::ios::beg);
        
            user *f=currentuser->getfriend(i);
            string id=f->getId();
            cout<<"friend"<<i<<endl;
            cout<<f->getId()<<endl;
            string line1;
            int count=0;
                for (char c:id)
                {
                    if(isdigit(c))
                    {  
                        count=c-'0';   
                    }
                }

                for (int i = 0; i < count-1; i++)
                {
                
                    string x=" ";
                    getline(file,x);
                }
                    string y, fname,lname;
                    file>>y;
                    file>>fname;
                    file>>lname;
                   
                    f->setfirstname(fname);
                    f->setlastname(lname);
                    cout<<f->getfirstname()<<endl;
            }

   
        }
    void setpages()
    
        {
            string filename="page.txt";
            ifstream file(filename); 

            for (int i = 0; i < currentuser->getnumpages(); i++)
            {
                page *f=currentuser->getpage(i);
                string id=f->getpageid();
                cout<<id;
               //cout<<"page"<<i<<endl;
               //cout<<f->getpageid()<<endl;
               string line1;
               int count=0;
                for (char c:id)
                {
                    if(isdigit(c))
                    {  
                        count=c-'0';   
                    }
                }

                for (int i = 0; i < count-1; i++)
                {
                
                    string x=" ";
                    getline(file,x);
                }
                string pageid,title;
                int likes;
                file>>pageid;
                file>>likes;
                getline(file,title);
                f->setpageid(pageid);
                f->settittle(title);
                f->setlikes(likes);
                cout<<id<<endl<<"title:"<<title<<endl;


            }
        
        }
    void viewtimeline()
    {
        for (int i = 0; i < currentuser->getnumposts(); i++)
        {

            post *npost=new post;
            npost=currentuser->getpost(i);
            cout<<npost;
        }
        
    }
};

    

int main()
{
    
    string userid;
    cin>>userid;
    user u;
    string filename="user.txt";
    ifstream file(filename); 
    int count; 
    for (char c:userid)
    {
        if(isdigit(c))
        {  
            count=c-'0';   
        }
    }

    for (int i = 0; i < count-1; i++)
    {
    
        string x=" ";
        getline(file,x);
    }
    file>>u;
    cout<<u.getnumfriends();
    user *uptr=&u;
    socialnetworkapp s1(uptr);
    s1.setcurrentuser(uptr);
    //s1.readUserDataFromFile("user.txt");
    //s1.findUserById("u6");
    s1.setpost();
    s1.setpages();
    s1.setfriendnames("user.txt");
    s1.viewhome();
    cout<<"friend list............................"<<endl;
     s1.viewfriendlist();
    //s1.likepost("post1");
    s1.viewtimeline();
    //s1.viewpage("p1");
}
