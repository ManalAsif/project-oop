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
class post
{
    private:
    
        string postid;
        string text;
        int likes;
        int templikes;
        user* likedby[10];
        string userid[10];
        int numcomments;
        comment comments[10];
        date shareddate;
        activity activityn;
        string memorytext;
        int diffdate;
    public:
        post(const string &postidn=" ",const string& textn=" ",date daten=0)
        {
            postid=postidn;
            text=textn;
            shareddate=daten;
            memorytext=" ";
            diffdate=0;
            for (int i = 0; i < 10; i++)
            {
                userid[i]=" ";
            }
        }
        ~post(){ for (int i = 0; i < 10; i++)
        {
            delete likedby[i];
        }
        } 
        void setmemorydate(int date){diffdate=date;}
        int getmemorydate(){return diffdate;}
        string getmemorytext(){return memorytext;}
        void setmemorytext(string text){memorytext=text;}
        string getpostid(){return postid;}
        void setpostid(string id){postid=id;}
        int getnumcomments(){return numcomments;}
        string gettext(){return text;}
        int getlikes(){return likes;}
        user** getlikedby(){return likedby;}
        date getshareddate(){return shareddate;}
        activity getactivity(){return activityn;}
        int gettemplikes(){return templikes;}
        string* getuserid(){return userid;}
        comment getcomment(int i){return comments[i];}
        user* getlikedby(int n){return likedby[n];}
        bool adduserid(string x)
        {
            userid[likes]=x;
        }
        bool addpostlike(user*by)
        {
            if(likes<10)
            {
                
                likedby[likes]=by;
                likes++;               
                return true;
            }
            else
            {
                return false;
                
            }
           
        }
        bool addcomment(comment commentnew)
        {
            if(numcomments<10)
            {
                comments[numcomments]=commentnew;
                numcomments++;                
                return true;
            }
            else
            {
                return false;
            }
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
            p->templikes=p->likes;
            for (int i = 0; i < p->likes; i++)
            {
                input >> p->userid[i];
            }
            string type,value;
            input>>type>>value;
            activity a1(type,value);
            p->activityn=a1;

            input>>p->shareddate;
            p->likes=0;
            
       }
       friend ostream&operator<<(ostream &out,post *npost)
       {
            cout<<"POST ID: "<<npost->getpostid()<<endl<<endl;
            cout<<"DESCRIPTION: "<<npost->gettext()<<endl<<endl;
            cout<<"SHARED DATE:";
            cout<<npost->getshareddate()<<endl<<endl;
            cout<<"activity";
            cout<<npost->getactivity()<<endl;
            cout<<"likes: "<<npost->gettemplikes()<<endl;
            if(npost->getmemorydate()!=0 &&npost->getmemorytext()!=" ")
            {
                cout<<"memory date: "<<npost->getmemorydate()<<endl<<endl;
                cout<<"memory text: "<<npost->getmemorytext()<<endl<<endl;
            }
            return out;
            
       }
};
#endif