#ifndef comment_h
#define comment_h
#include <iostream>

using namespace std;
class user;
class post;

class comment
{
    private: 
    string commentid;
    const user* userptr;
    string text;
    const post* postptr;
    public:
    comment(string commentidn,const user* usern,string textn,post* postn)
    {
        commentid=commentidn;
        userptr=usern;
        text=textn;
        postptr=postn;
    }
    string getcommentid()
    {
        return commentid;
    }
    const user* getuser()
    {
        return userptr;
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