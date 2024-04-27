#ifndef page_h
#define page_h
#include <iostream>
#include "user.h"
#include "post.h"

using namespace std;

class page
{
    private:
        string id;
        user *owner;
        string title;
        post** posts;
        int likes;
        int numposts;
    public:

        page(string idn="0x",string titlen=" ")
        {
            id=idn;
            title=titlen;
            numposts=0;
            likes=0;
        }
        string getpageid(){return id;}
        user* getowner(){return owner;}
        string gettitle(){return title;}
        post** getposts(){return posts;} 
        int getlikes(){return likes;}
        int getnumposts(){return numposts;}
        void settittle(string x){title=x;}
        post * getpost(int i)
        {
            return posts[i];
        }
        void uploadpost(post* newpost)
        {
         cout<<numposts;
            post **newpostlist=new post*[numposts+1];
            if(numposts!=0)
            {
                for (int i = 0; i < numposts; i++)
                {
                    //cout<<"end";
                    newpostlist[i]=posts[i];
                }
                delete[] posts;
                }
                newpostlist[numposts]=newpost;            
                posts=newpostlist;
            
            numposts=numposts+1;
            
        }
        friend istream& operator>>(istream &input,page *ptrp)
        {
            page p;
            input>>p.id;
            input>>p.likes;
            input>>p.title;
            ptrp=&p;
            return input;
        }
        void addpagelike()
        {
            likes++;
        }
        void setpageid(string idn)
        {
            id=idn;
        }
        void setlikes(int x)
        {
            likes=x;
        }


};
#endif