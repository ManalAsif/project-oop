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
    ~socialnetworkapp(){
        for (int i = 0; i < numpages; i++)
        {
            delete likedpages[i];
        }
        for (int i = 0; i < numusers; i++)
        {
            delete users[i];
        }
        delete currentuser;
        
        
    }
    socialnetworkapp(user* ncurrenntuser=nullptr)
    {
        currentuser=ncurrenntuser;
    }
    void setcurrentuser(user *u)
    {
        *currentuser=*u;
        cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   "<<u->getfirstname()<<" "<<u->getlastname()<<" succesfully set as current user     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl<<endl;
    }
    void options()
 {
    for (int i = 0; i < currentuser->getnumfriends(); i++)
    {
                
                user *f=currentuser->getfriend(i);
                cout<<"\t\tfriend: "<<f->getid()<<endl;
                for (int j = 0; j < f->getnumposts(); j++)
                {
                    post *p=f->getpost(j);
                    cout<<"id: "<<p->getpostid()<<endl;
                }
              
    }
    for (int i = 0; i < currentuser->getnumpages(); i++)
    {
                page *p1=currentuser->getpage(i);
                cout<<"\t\tpage "<<p1->getpageid()<<endl;
                for (int j = 0; j < p1->getnumposts(); j++)
                {
                    post *p=p1->getpost(j);
                    cout<<"id: "<<p->getpostid()<<endl;
                }
                
    }
            
 }
    void run()
    {

        int choice=0;
        string currentUserName = currentuser->getfirstname();
        char border = '-';
	    Color(5);
        cout<<endl;
        for (int i = 0; i < 65; i++)
        {
            cout << border; 
        }
        while(choice!=10)
        {
        Color(5);
        cout<<endl;
        cout << "Welcome, " << currentUserName << "!" << endl;
        cout << "1. View Home" << endl;
        cout << "2. View Timeline" << endl;
        cout << "3. View Friend List" << endl;
        cout << "4. View Page" << endl;
        cout << "5. View Liked by list for a Post" << endl;
        cout << "6. Comment on a Post" << endl;
        cout << "7. Share a Memory" << endl;
        cout << "8. View a post"<<endl;
        cout<<"9. like a post"<<endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;  
        Color(3);
        if(choice==1){ viewhome();}  
        else if(choice==2){ viewtimeline();}
        else if(choice==3){viewfriendlist();}
        else if(choice==4)
        {
            string pageid;
            cout<<"enter page id from the list of liked pages below: "<<endl;
            for (int i = 0; i < currentuser->getnumpages(); i++)
            {
               cout<<"ID: "<<currentuser->getpage(i)->getpageid()<<endl;
            }
            cout<<"enter page id: "<<endl;
            cin>>pageid;
            viewpage(pageid);
        }
        else if(choice==5)
        {
            string postid;
            options();
            cout<<"enter post id: "<<endl;
            cin>>postid;
            viewlikedbylist(postid);
        }
        else if(choice==6)
        {
            options();
            
            string postid,text;
            cout<<"\t\tenter post id: ";
            cin>>postid;
            cout<<"\t\tenter comment: ";
            string x=" ";
            while(x!=".")
            {
                cin>>x;
                text=text+" "+x;
            }
            Color(4);
           
            addcommenttopost(postid,text);

        }
        else if(choice==7)
        {
            for (int i = 0; i < currentuser->getnumposts(); i++)
            {
                post *p=currentuser->getpost(i);
                cout<<"id: "<<p->getpostid()<<endl;
            }
            
            string text,postid;
            cout<<"enter postid: ";
            cin>>postid;
            cout<<"enter text: ";
            string x=" ";
            while(x!=".")
            {
                cin>>x;
                text=text+" "+x;
            }
            sharememory(postid,text);
            cout<<"\n\n\n MEMORY SHARED"<<endl;
            viewtimeline();
        }
        else if(choice==8)
        {
            string id;
            options();
            cout<<"enter id: ";
            cin>>id;
            viewpost(id);
        }
        else if(choice==9)
        {
            string id;
            options();
            cout<<"enter id: ";
            cin>>id;
            likepost(id);
        }
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
                Color(4);
                cout<<" \t\tTITLE: "<<currentpage->gettitle()<<endl;
                cout<<"\t\tLIKES: "<<currentpage->getlikes()<<endl;
                cout<<"\t\tID: "<<currentpage->getpageid()<<endl<<endl<<endl;
               for (int i = 0; i < currentpage->getnumposts(); i++)
               {
                post *post=currentpage->getpost(i);
                cout<<post;
                viewcomment(post->getpostid());
                viewlikedbylist(post->getpostid());
               }
            }

        }
        
    }
    void likepost(string id)
    {
        post*currentpost;
        if(checkfriendpost(id))
        {
            currentpost=checkfriendpost(id);
        }
        else if(checkpagepost(id))
        {
            currentpost=checkpagepost(id);
        }
        else
        {
            cout<<"invalid post id please (you can only view posts of your friends and pages you have liked ) "<<endl;
            return;
        }
        viewlikedbylist(id);
        cout<<endl<<"ID:"<<currentuser->getId()<<endl;
        cout<<"Name:  "<<currentuser->getfirstname()<<" "<<currentuser->getlastname()<<endl<<endl;
        if(currentpost->addpostlike(currentuser))
        {
            currentpost->adduserid(currentuser->getId());
            cout<<"post with id "<<id<<" liked succesfully"<<endl;
        }
        else
        {
            cout<<"limits of number of likes exceeded"<<endl;
        } 
        Color(8);
        
        
        return;
        
        

    }
    void viewpost(string id)
    {
        post*currentpost;
        if(checkfriendpost(id))
        {
            currentpost=checkfriendpost(id);           
        }
        else if(checkpagepost(id))
        {
            currentpost=checkpagepost(id);
        }
        else
        {
            cout<<"invalid post id please (you can only view posts of your friends and pages you have liked ) "<<endl;
            return;
        }
            
        cout<<currentpost;
        viewcomment(id);
      
        
    }
    void sharememory(string postid,string text)
{
    date currentdate(27,4,2024);
    for (int i = 0; i < currentuser->getnumposts(); i++)
        {
            post *npost=new post;
            npost=currentuser->getpost(i);
            date postdate= (*npost).getshareddate();
            if((currentdate.differenceInSeconds(postdate)%31536000)==0 && npost->getpostid()==postid)
            {   
                
                int diff=currentdate.getYear()-postdate.getYear();
                npost->setmemorydate(diff);
                npost->setmemorytext(text);
            }
        }
}
    void addcommenttopost(string postid, string commenttext)
    {  
        post* currentpost;
        if(checkfriendpost(postid))
        {
            currentpost = checkfriendpost(postid);
        }
        else if(checkpagepost(postid))
        {
            currentpost = checkpagepost(postid);
        }
        else
        {
            cout<<"invalid post id please (you can only view posts of your friends and pages you have liked ) "<<endl;
            return;
        }
        viewcomment(postid);
        comment newcomment("c14", currentuser, commenttext, currentpost);
        if (currentpost->addcomment(newcomment))
        {                    
           cout<<newcomment;
           cout<<currentpost;
           cout << "Comment added successfully to the post with ID " << postid << endl;
           return;
        }
        else
        {
            cout << "Failed to add comment. Maximum comment limit reached for this post." << endl;
        }
    }
    post* checkfriendpost(string postid)
{
    for (int i = 0; i < currentuser->getnumfriends(); i++)
    {
        user* frienduser = currentuser->getfriend(i);
        for (int j = 0; j < frienduser->getnumposts(); j++)
        {
            post* currentpost = frienduser->getpost(j);
            if (currentpost->getpostid() == postid)
            {
                return currentpost;
            }
            
        }
    }
    // cout<<"invalid post id please (you can only view posts of your friends) "<<endl;
    // return false;
}
    post* checkpagepost(string postid)
{
     for (int i = 0; i < currentuser->getnumpages(); i++)
        {
           page *currentpage=(*currentuser).getpage(i);
           for(int j=0;j<(*currentpage).getnumposts();j++)
           {
                post *currentpost=(*currentpage).getpost(j);
                if (currentpost->getpostid() == postid)
            {
                return currentpost;
            }
           }
        }
        
}
    void viewcomment(string id)
    {
        post*currentpost;
        if(checkfriendpost(id))
        {
            currentpost=checkfriendpost(id);           
        }
        else if(checkpagepost(id))
        {
            currentpost=checkpagepost(id);
        }
        else
        {
            for (int i = 0; i < currentuser->getnumposts(); i++)
        {
            post *currpost=currentuser->getpost(i);
            if (currpost->getpostid() == id)
            {
                currentpost=currpost;
            }
            
        }            
        }
        Color(4);
        cout<<"<<<<<<<<<<<<<<<<<<<<< COMMENTS >>>>>>>>>>>>>>>>>>>>>"<<endl;
        int numcomments;
        string filename = "comment.txt";
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }
                
        file >> numcomments;
        file.ignore(); 
        cout << "Comments for post " << id << ":" << endl;
        for (int k = 0; k < numcomments; k++)
        {
            comment c;
            file >> c;
            if (c.getpostid() == id)
            {
                cout << c;
                currentpost->addcomment(c);
            }
        }
            
        
    }
    void viewhome()
    {
        cout<<"<<<<<<<<<<<<<<<<<<<<<<<< HOME >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        date currentdate(27,4,2024);
    for(int i=0;i<(*currentuser).getnumfriends();i++)
    {

        user *frienduser=(*currentuser).getfriend(i);
        Color(3);
        cout<<"--------------------------------------------------------------------"<<endl<<endl;
        cout<<i+1<<")  FRIEND:    "<<frienduser->getfirstname()<<"  "<<frienduser->getlastname()<<endl<<endl;
        for(int j=0;j<(*frienduser).getnumposts();j++)
        {
            post *post=(*frienduser).getpost(j);
            date postdate= (*post).getshareddate();           
            if(currentdate.differenceInSeconds(postdate)>=0 && (currentdate.differenceInSeconds(postdate))<=86400)
            {
                cout<<"--------------------------------------------------------------------"<<endl<<endl;
                Color(5);
                cout<<post;
                viewcomment(post->getpostid());          
            }
        }
    }
    cout<<currentuser->getnumpages();
        for (int i = 0; i < currentuser->getnumpages(); i++)
        {
           page *currentpage=(*currentuser).getpage(i);
           cout<<(*currentpage).getnumposts()<<endl;
           Color(3);
           cout<<"--------------------------------------------------------------------"<<endl<<endl;
           cout<<i+1<<")   PAGE:     "<<currentpage->getpageid()<<endl<<endl;
           for(int j=0;j<(*currentpage).getnumposts();j++)
           {
                post *post=(*currentpage).getpost(j);
                date postdate= (*post).getshareddate();
                if(currentdate.differenceInSeconds(postdate)>=0 && (currentdate.differenceInSeconds(postdate))<=86400)
                {
                    cout<<"--------------------------------------------------------------------"<<endl<<endl;
                    Color(5);
                    cout<<post;
                    viewcomment(post->getpostid());
                  
                }
            }
        
        
    
    }
    }
    void setpost()
    {
       
        string filename="posts.txt";
        ifstream file(filename);
        string cuserid=currentuser->getId();
        int num;
        file>>num;
        for (int i = 0; i < num*5; i++)
        {
           string line;
            getline(file,line);
            size_t pos = line.find(' ');
            string userid = line.substr(0, pos);
            if(userid==cuserid)
            {
                post *p=new post;
                file>>p;
                currentuser->addpost(p);
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
                }
           
            }
        }
        file.seekg(0, std::ios::beg);
        
        for (int i = 0; i < currentuser->getnumpages(); i++)
        {
           
            string x;
            file.clear();
            file.seekg(0, std::ios::beg);
            file>>x;

            
            page *f=currentuser->getpage(i);
            string id=f->getpageid();
           
            
            for (int j = 0; j < num*5; j++)
            {
                
                string line1;

                getline(file,line1);
                
                size_t pos = line1.find(' ');
                string userid = line1.substr(0, pos);
                if(id==userid)
                {
                    
                    post *p=new post;
                    file>>p;
                    f->uploadpost(p);
                    
                }
            }
           
        }
        file.close();

    }
    void viewlikedbylist(string id)
    {  Color(8);

       post *p;
       if(checkfriendpost(id))
       {
            p=checkfriendpost(id);
       }
       else if(checkpagepost(id))
       {
            p=checkpagepost(id);
       }
       else
        {
            for (int i = 0; i < currentuser->getnumposts(); i++)
        {
            post *currpost=currentuser->getpost(i);
            if (currpost->getpostid() == id)
            {
                p=currpost;
            }
        }
        }
        cout<<"<<<<<<<<<<<<<<<<<<<<<<<liked by>>>>>>>>>>>>>>>>>>>>>"<<endl;
        string *list=p->getuserid();
        string filename1="user.txt";
        ifstream file(filename1); 
        
                int num;
                num=p->gettemplikes();
                for (int n = 0; n <num; n++)
                {
                    file.clear();
                    file.seekg(0, std::ios::beg);

                    string line;
                    int count;
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
                    cout<<endl<<"ID:"<<p->getlikedby(n)->getId()<<endl;
                    cout<<"Name:  "<<p->getlikedby(n)->getfirstname()<<" "<<p->getlikedby(n)->getlastname()<<endl;                                                       
                }
    }
    void setfriendnames(string s)
    {
        //cout<<"friend func"<<endl;
        string filename=s;
        ifstream file(filename); 
        for (int i = 0; i < currentuser->getnumfriends(); i++)
        {
            file.clear();
            file.seekg(0, std::ios::beg);
        
            user *f=currentuser->getfriend(i);
            string id=f->getId();
            // cout<<"friend"<<i<<endl;
            // cout<<f->getId()<<endl;
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
                    //cout<<f->getfirstname()<<endl;
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
                //cout<<id;
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
                //cout<<id<<endl<<"title:"<<title<<endl;


            }
        
        }
    void viewtimeline()
    {
        cout<<"numpost: "<<currentuser->getnumposts();
        for (int i = 0; i < currentuser->getnumposts(); i++)
        {
            Color(3);
            cout<<endl<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< POST # "<<i+1<<" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl<<endl;;
           
            post *npost=new post;
            npost=currentuser->getpost(i);
            Color(5);
            cout<<npost;
            viewcomment(npost->getpostid());
         
            
        }
        
    }
};
int main()
{
    
    string userid;
    cout<<"\t\tENTER USER ID:";
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
    user *uptr=&u;
    socialnetworkapp s1(uptr);
    s1.setcurrentuser(uptr);
    s1.setpost();
    s1.setpages();
    s1.setfriendnames("user.txt");
    s1.run();
}
