#ifndef post_h
#define post_h
#include <iostream>
#include <ctime>
#include "user.h"
#include "page.h"
#include "comment.h"

using namespace std;
class activity{
    private:
    string type;
    string value;
    public:
    activity(string typen=" ",string valuen=" ")
    {
        type=typen;
        value=valuen;
    }
    string gettype()
    {
        return type;
    }
    friend ostream&operator<<(ostream &out,activity a)
    {
        cout<<endl;
        cout<<"type:"<<a.type<<endl<<endl;
        cout<<"value:"<<a.value<<endl<<endl;
    }
};
class date
{
    private:
    int day;
    int month;
    int year;
    public:
    date(int dayn=0,int monthn=0,int yearn=0)
    {
        day=dayn;
        month=monthn;
        year=yearn;
    }
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }


    static date getcurrentdate() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        return date(localTime->tm_mday, localTime->tm_mon + 1,localTime->tm_year + 1900 );
    }
    int differenceInSeconds(const date& other) const {
        // Calculate total seconds for each date
        long long totalSeconds1 = year * 31536000LL + month * 2592000LL + day * 86400LL;
        long long totalSeconds2 = other.getYear() * 31536000LL + other.getMonth() * 2592000LL + other.getDay() * 86400LL;

        // Return absolute difference in seconds
        return (totalSeconds1 - totalSeconds2);
    }
    
    friend ostream& operator<<(ostream &out,const date&date)
    {
        out<<date.day<<"-"<<date.month<<"-"<<date.year;
        return out;
    }

    friend istream& operator>>(istream &in,date &date)
    {
        in>>date.day>>date.month>>date.year;
        return in;
    }
};
// class date
// {
//     private:
//     int day;
//     int month;
//     int year;
//     public:
//     date(int dayn=0,int monthn=0,int yearn=0)
//     {
//         day=dayn;
//         month=monthn;
//         year=yearn;
//     }
// };

const int maxcomments=10;
    const int maxlikes=10;
    const int maxtextlenth=100;


class post
{
    private:
    
        string postid;
        string text;
        int likes;
        user** likedby;
        string *userid;
        int numcomments;
        comment** comments;
        date shareddate;
        activity activityn;
    public:
        post(const string &postidn=" ",const string& textn=" ",date daten=0)
        {
            postid=postidn;
            text=textn;
            shareddate=daten;
        }
        string getpostid(){return postid;}
        int getnumcomments(){return numcomments;}
        string gettext(){return text;}
        int getlikes(){return likes;}
        user** getlikedby(){return likedby;}
        date getshareddate(){return shareddate;}
        activity getactivity(){return activityn;}
        bool addpostlike(user*by)
        {
            if(likes++<10)
            {
                user **newlikelist=new user*[likes+1];
                if(likes!=0)
                {
                for (int i = 0; i < likes; i++)
                {
                    //cout<<"end";
                    newlikelist[i]=likedby[i];
                }
                delete[] likedby;
                }
                newlikelist[likes]=by;            
                likedby=newlikelist;
            
            likes=likes+1;
            }
            else
            {
                return false;
                
            }
        }
        bool addcomment(comment *commentnew)
        {
            if(numcomments<10)
            {
                comment **newcommentlist=new comment*[numcomments+1];
                for (int i = 0; i < numcomments; i++)
                {
                    newcommentlist[i]=comments[i];
                }
                newcommentlist[numcomments]=commentnew;
                delete[] comments;
                comments =newcommentlist;
                numcomments++;
                return true;
            }
            else
            {
                return false;
            }
        }
        user *getlikedby(int i)
        {
            return likedby[i];
        }
       friend istream& operator>>(istream &input,post *p)
       {
        input>>p->postid;
        string x=" ";
        while(x!=".")
        {
            input>>x;
            p->text=p->text+" "+x;
        }
        input>>p->likes;
        //cout<<p->likes;
        // p->likedby=new user*[p->likes];
        p->userid=new string[p->likes];
        for (int i = 0; i < p->likes; i++)
        {
            
            input >> p->userid[i];
        //    (p->likedby[i])->setuserid(userId);
        //     p->addpostlike(p->likedby[i]);
        //     string userId;
        // input >> userId;
        // p->likedby[i] = new user(userId);
            // string x;
            // input>>x;
            // cout<<x;
            // user *nu=new user();
            // nu->setuserid(x);
            // likedby[i]=nu;
        }
        string type,value;
        input>>type>>value;
        activity a1(type,value);
        p->activityn=a1;

        input>>p->shareddate;
        
       }
    void addlikedby(user *u)
    {
        
        
    }
    string* getuserid()
    {
        return userid;
    }
       friend ostream&operator<<(ostream &out,post *npost)
       {
            cout<<"POST ID: "<<npost->getpostid()<<endl<<endl;
            cout<<"DESCRIPTION: "<<npost->gettext()<<endl<<endl;
            cout<<"likes:"<<npost->getlikes()<<endl<<endl;
            cout<<"SHARED DATE:";
            cout<<npost->getshareddate()<<endl<<endl;
            cout<<"activity";
            cout<<npost->getactivity();
            
       }
};
#endif