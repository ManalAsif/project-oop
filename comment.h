#ifndef comment_h
#define comment_h
#include <iostream>
#include "user.h"
#include "post.h"
using namespace std;
class user;
class post;

class comment
{
    private: 
    string commentid;
    user* userptr;
    string text;
    post* postptr;
    public:
    comment(){commentid=" ",userptr=nullptr,text=" ",postptr=nullptr;}
    comment(string commentidn,user* usern,string textn,post* postn)
    {
        commentid=commentidn;
        userptr=usern;
        text=textn;
        postptr=postn;
    }
    friend ostream& operator<<(ostream &out,comment &c)
    {
        out<<"\tcommentid: ";
        out<<c.commentid<<endl;
        //out<<c.userptr;
        out<<"\ttext: ";
        out<<c.text<<endl;
        //out<<c.postptr;
        return out;
    }
    friend istream &operator>>(istream &in,comment &c)
    {
        
        string uid,pid;
        in>>pid;

        //cout<<pid<<endl;
        in>>c.commentid;
        //cout<<endl<<c.commentid<<endl;
        //c.postptr->setpostid(pid);
        in>>uid;
        cout<<"comment by: "<<uid<<endl;
        //c.userptr->setuserid(uid);
        string x=" ";
        while(x!=".")
        {
            in>>x;
            c.text=c.text+" "+x;
        }
        //cout<<c.text<<endl;
        return in;
    }
    string getcommentid()
    {
        return commentid;
    }
    
    string gettext()
    {
        return text;
    }
    const post* getpost()
    {
        return postptr;
    }

};
#endif