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
    string postid;
    public:
    comment(){commentid=" ",userptr=nullptr,text=" ",postptr=nullptr;}
    comment(string commentidn,user* usern,string textn,post* postn)
    {
        commentid=commentidn;
        userptr=usern;
        text=textn;
        postptr=postn;
    }

    // //getters
    string getpostid() {return postid;}
    // //setters
    void setpostid(string pid) {pid = postid;}



    friend ostream& operator<<(ostream &out,comment &c)
    {
        out<<"\tcommentid: ";
        out<<c.commentid<<endl;
        out<<"\ttext: ";
        out<<c.text<<endl;
        return out;
    }
    friend istream &operator>>(istream &in,comment &c)
    {
        
        string uid,pid;
        in>>pid;
        c.postid = pid;
        in>>c.commentid;
        in>>uid;
        string x = " ";
        while(x!=".")
        {
            in>>x;
            c.text=c.text+" "+x;
        }
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