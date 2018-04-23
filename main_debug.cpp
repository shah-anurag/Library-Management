#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<cstring>
#include<algorithm>
#include<limits.h>
#include<stdlib.h>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<sstream>

#define cin_check if(cin.fail()){cin.clear();cin.ignore(INT_MAX, '\n');}

using namespace std;

bool first = 1;

template<typename T>
string to_string(T val)
{
    stringstream str_;
    str_ << val;
    return str_.str();
}

template <typename T>
void delete_pointed_to(T* const ptr)
{
    delete ptr;
}

class Resource;
class Member;
class IssuedBy;
class Staff;
class Phd;
class NonPhd;
class Faculty;

class Library
{
    string name;
    long long PhoneNumber;
    vector<Resource*> resources;
    vector<Phd*> phd;
    vector<NonPhd*> nphd;
    vector<Faculty*> faculty;
    vector<Staff*> staff;
    vector<Member*> member;

public:
    Library(string name, long long PhoneNumber): name(name), PhoneNumber(PhoneNumber){}
    string getLibraryName()
    {
        return name;
    }
    long long getPhoneNum()
    {
        return PhoneNumber;
    }
    bool VerifyMemberId(string Id);
    bool VerifyResource(string Id);
    bool CheckLimit(string UserId, string ResId);
    void AddMember();
    void AddNewResource();
    void RemoveMember(string Id);
    void RemoveResource(string Id);
    set<Resource*> search_by_author(string author);
    set<Resource*> search_by_Title(string title);
    Resource* search_by_Id(string Id);
    set<Resource*> search_by_tag(const vector<string> &tags);   //CORRECTION
    void ViewAllMembers();
    void ViewAllResource();
   // bool RenewBook(string userId, string resId);
    Phd* get_user_phd(string UserId);
    NonPhd* get_user_nonphd(string UserId);
    Faculty* get_user_faculty(string UserId);
    Staff* get_user_staff(string UserId);
    NonPhd* Login_as_Non_Phd(string);
    Phd* Login_as_Phd(string);
    Staff* Login_as_Staff(string);
    Faculty* Login_as_Faculty(string);
    string getStudentPhddata();
    string getStudentNonPhddata();
    string getFacultydata();
    string getStaffdata();
    string getResourcedata();
};

class Resource
{
    protected:
        string author;
        string title;
        string Id;
        string date_of_purchase;
        int Edition;
        double rack_num;
        bool status;
        vector<IssuedBy*> history;
    public:
        Resource(string author,string title,string Id,string DateOfPurchase, int Edition, double RackNumber):
            author(author), title(title), Id(Id), date_of_purchase(DateOfPurchase), Edition(Edition), rack_num(RackNumber)
            {
                status = true;
            }
        virtual ~Resource()
        {
            for_each(history.begin(), history.end(), delete_pointed_to<IssuedBy>);
        }
        bool getStatus();
        string getAuthor();
        string getTitle();
        string getId();
        string getDateOfPurchase();
        double getRackNumber();
        void gethistory(Library&);
        int GetEdition();        //CORRECTION
        void change_status(bool status);
        void update_history(string UserId, string IssueDate, bool status, int days);
        string latest_history_user_id();
        virtual string getdata();
        virtual vector<string> getTopic() = 0;
        virtual void getdetails() = 0;
};

class IssuedBy
{
    string Id;
    string IssueDate;
    int IssueFor;           //MaxLimit.
public:
    IssuedBy(string Id, string IssueDate): Id(Id), IssueDate(IssueDate){}
    string getId();
    string getIssueDate();
    int getNumOfDays();
    void EditId();
    void EditIssueDate(string);       //CORRECTION
    void setDays(int);
    void getdetails(Library&);
    string getdata()
    {
        return Id+"\n"+IssueDate+"\n"+to_string(IssueFor)+"\n";
    }
};

string Resource::latest_history_user_id()
{
    int n = history.size();
    if(n > 0)
        return history[n-1]->getId();
    else
        return "";
}

bool Resource::getStatus()
{
    return status;
}

string Resource::getAuthor()
{
    return author;
}

string Resource::getTitle()
{
    return title;
}
string Resource::getId()
{
    return Id;
}
string Resource::getDateOfPurchase()
{
    return date_of_purchase;
}
double Resource::getRackNumber()
{
    return rack_num;
}
int Resource::GetEdition()
{
    return Edition;
}
void Resource::change_status(bool status)
{
    Resource::status = status;
    return;
}

void Resource::update_history(string UserId, string IssueDate, bool status, int days)
{
    vector<IssuedBy*>::iterator it = history.end()-1;
    while(it != history.begin()-1 && (*it)->getId() != UserId)
        it--;
    if(it == history.begin()-1)
    {
        IssuedBy* issuedby = new IssuedBy(UserId, IssueDate);
        history.push_back(issuedby);
        Resource::change_status(status);
        return;
    }
    (*it)->IssuedBy::EditIssueDate(IssueDate);
    (*it)->IssuedBy::setDays(days);
    Resource::change_status(status);
    return;
}

string IssuedBy::getId()
{
    return Id;
}
string IssuedBy::getIssueDate()
{
    return IssuedBy::IssueDate;
}
int IssuedBy::getNumOfDays()
{
    return IssuedBy::IssueFor;
}
void IssuedBy::EditId()
{
    string Id;
    cout << "Enter your id: " << '\n';
    cin_check;cin >> Id;
    IssuedBy::Id = Id;
    return;
}
void IssuedBy::EditIssueDate(string date)
{
    IssuedBy::IssueDate = date;
}
void IssuedBy::setDays(int days)
{
    IssuedBy::IssueFor = days;
    return;
}

class Book: public Resource
{
    string SubjectCode;
    string name;

public:
    Book(string author,string title,string Id,string DateOfPurchase,int Edition,double RackNumber,string SubjectName,string SubCode):
    Resource(author, title, Id, DateOfPurchase, Edition, RackNumber), SubjectCode(SubCode), name(SubjectName){}
    void Update();
    void AddSubject();
    void DeleteSubject(string subject){name="";SubjectCode="";}
    string getSubjectName(){return name;}
    string getSubjectCode(){return SubjectCode;}
    vector<string> getTopic();
    void getdetails();
    string getdata()
    {
        return (string)"Book"+"\n"+Resource::getdata()+"\n"+SubjectCode+"\n"+name+"\n"+"\\Book"+"\n";
    }
};

void Book::getdetails()
{
    cout << "Subject Code: " << SubjectCode << endl;
    cout << "Author: " << getAuthor() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Id: " << getId() << endl;
    cout << "Edition: " << GetEdition() << endl;
    cout << "date_of_purchase: " << getDateOfPurchase() << endl;
    cout << "Rack number: " << getRackNumber() << endl;
    return;
}

void Book::Update()
{
    char update;
    cout << "Author: " << getAuthor() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;
    cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string author;
        cout << "Enter the name of Author: ";
        cin_check;
        cin >> author;
        Resource::author = author;
    }
    cout << "Title: " << getTitle() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;
    cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string title;
        cout << "Enter the Title: ";
        cin_check;
        cin >> title;
        Resource::title = title;
    }
    cout << "Edition: " << GetEdition() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;
    cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else
    {
        int edition;
        cout << "Enter the Edition: ";
        cin_check;
        cin >> edition;
        Resource::Edition = edition;
    }
    cout << "Date of Purchase: " << getDateOfPurchase() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;
    cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string date;
        cout << "Enter the date of purchase(dd/mm/yyyy): ";
        cin_check;
        cin >> date;
        Resource::date_of_purchase = date;
    }
    cout << "Rack number: " << getRackNumber() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;
    cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        double rack;
        cout << "Enter the rack number: ";
        cin_check;
        cin >> rack;
        Resource::rack_num = rack;
    }
    cout << "Subject Code: " << SubjectCode << endl;
    cout << "Update? Enter y or n: ";
    cin_check;
    cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        int sub_code;
        cout << "Enter the subject code: ";
        cin_check;
        cin >> sub_code;
        Book::SubjectCode = sub_code;
    }
    cout << "Subject Name: " << Book::name;
    cout << "Update? Enter y or n: ";
    cin_check;
    cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string name;
        cout << "Enter the name of Book: ";
        cin_check;
        cin >> name;
        Book::name = name;
    }
    cout << "\nUpdated!" << endl;
    return;
}
void Book::AddSubject()                             //Implement
{

}
vector<string> Book::getTopic()
{
    vector<string> topic;
    topic.push_back(name);
    topic.push_back(SubjectCode);
    return topic;
}

class Journal: public Resource
{
    string PublicationDate;
    vector<string> topic;

public:
    Journal(string author,string title,string Id,string DateOfPurchase,int Edition,double RackNumber,string PublicationDate,vector<string> topic):
    Resource(author, title, Id, DateOfPurchase, Edition, RackNumber),PublicationDate(PublicationDate)
    {
        int idx = 0;
        string last = "y";
        while(topic[idx] != last)
            {
                Journal::topic.push_back(topic[idx]);
                idx++;
            }
    }
    void Update();
    void AddTopic(string topic);
    void DeleteTopic(string topic);
    string getPublicDate()
    {
        return PublicationDate;
    }
    vector<string> getTopic();
    void getdetails();
    string getdata()
    {
        string data = (string)"Journal" + "\n" + Resource::getdata() + "\n" + PublicationDate + "\n" + "topic" + "\n";
        vector<string>::iterator it = topic.begin();
        while(it != topic.end())
        {
            data.append(*it);
            data.append("\n");
            ++it;
        }
        data.append("\\topic");
        data.append("\n");
        data.append("\\Journal");
        return data;
    }
};


void Journal::getdetails()
{
    cout << "Author: " << getAuthor() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Id: " << getId() << endl;
    cout << "Topics: " << endl;
    for(unsigned i = 0U; i < topic.size(); i++) cout << i+1 << " " << topic[i] << endl;
    cout << "Edition: " << GetEdition() << endl;
    cout << "date_of_purchase: " << getDateOfPurchase() << endl;
    cout << "Rack number: " << getRackNumber() << endl;
    return;
}

void Journal::Update()
{
    char update;
    cout << "Author: " << getAuthor() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string author;
        cout << "Enter the name of Author: ";
        cin >> author;
        Resource::author = author;
    }
    cout << "Title: " << getTitle() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string title;
        cout << "Enter the Title: ";
        cin_check;cin >> title;
        Resource::title = title;
    }
    cout << "Edition: " << GetEdition() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else
    {
        int edition;
        cout << "Enter the Edition: ";
        cin_check;cin >> edition;
        Resource::Edition = edition;
    }
    cout << "Date of Purchase: " << getDateOfPurchase() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string date;
        cout << "Enter the date of purchase(dd/mm/yyyy): ";
        cin_check;cin >> date;
        Resource::date_of_purchase = date;
    }
    cout << "Rack number: " << getRackNumber() << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        double rack;
        cout << "Enter the rack number: ";
        cin_check;cin >> rack;
        Resource::rack_num = rack;
    }
    cout << "Publication date : " << PublicationDate << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string pub_date;
        cout << "Enter the publication date: ";
        cin_check;cin >> pub_date;
        Journal::PublicationDate = pub_date;
    }
    return;
}

vector<string> Journal::getTopic()
{
    return topic;
}
void Journal::AddTopic(string topic)
{
    Journal::getTopic();
    /*
    cout << "Enter Topics you want to add:" << endl;
    cout << "Enter y when you are done:)" << endl;
    while(1)
    {
        string topic;
        cout << "Enter topic: ";
        cin_check;cin >> topic;
        if(topic == 'y')
            break;
        Journal::topic.push_back(topic);
    }
    */
    vector<string>::iterator it = find(Journal::topic.begin(), Journal::topic.end(), topic);
    if(it == Journal::topic.end())
    {
        Journal::topic.push_back(topic);
    }
    else
    {
        cout << topic << " Already Exists" << endl;
    }
    return;
}

void Journal::DeleteTopic(string topic)
{
    Journal::getTopic();
    auto it = find(Journal::topic.begin(), Journal::topic.end(), topic);
    if(it == Journal::topic.end())
    {
        cout << "Topic does not exist" << endl;
    }
    else
    {
        Journal::topic.erase(it);
    }
    return;
}

class Member
{
protected:
    string name;
    string Id;
    string JoinDate;
    long long ph_num;
    string address;
    string password;
    string emailId;
public:
    Member(string name, string JoinDate, string Id, long long ph_num, string password, string address = "", string emailId = ""):
        name(name), Id(Id), JoinDate(JoinDate), ph_num(ph_num), address(address), password(password), emailId(emailId){}
    virtual ~Member(){}
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
    virtual int getJournalsIssued() = 0;
    void edit_password();
    string getpassword() {return password;}
    string getId()
    {
        return Id;
    }
    string getname(){return name;}
    string getdata()
    {
        return name+"\n"+Id+"\n"+to_string(ph_num)+"\n"+address+"\n"+password+"\n"+emailId;
    }
    //virtual int getBooksIssued() = 0;
    //virtual void change_history_status(string ResId, string Date) = 0;
};

class Staff: public Member
{
public:
    Staff(string name, string JoinDate, string Id, long long ph_num, string password, string address = "", string emailId = ""):
        Member(name, JoinDate, Id, ph_num, password, address, emailId){}
    void ViewProfile(string Id);    //CORRECTION
    bool IssueResource(string UserId, string ResourceId, Library &);
    void ReturnResource(string UserId, string ResId, Library &);
    void CollectFine(string studId, long long fine, Library &);
    void UpdateHistory(string UserId, string ResId, Library &);
    int getJournalsIssued(){
        return 0;
    }
    void view_my_profile();
    void edit_my_profile();
    string getdata()
    {
        return Member::getdata() + "\n"+"\\Staff" + "\n";
    }
    //void change_history_status(string ResId, string Date){}
};

class BookIssued
{
    string BookId;
    string BookName;
    string Author;
    bool Status;
    string IssueDate;
    string ReturnDate;
    long long Fine;
    long long FinePaid;
    bool renew;
    int max_days;
public:
    BookIssued(string BookId, string BookName, string Author, bool status, string IssueDate, int max_days):
    BookId(BookId), BookName(BookName), Author(Author), Status(status), IssueDate(IssueDate), max_days(max_days)
    {
        ReturnDate = "";
    }
    BookIssued(Resource* Res, int max_days)
    {
        BookIssued::max_days = max_days;
        BookName = Res->getTitle();
        Author = Res->getAuthor();
        FinePaid = 0;
        Fine = 0;
        Status = true;
        BookId = Res->getId();
        renew = false;
        while(1)
        {
            cin_check;
            cout << "Enter today's date(dd/mm/yyyy): ";
            cin >> IssueDate;
            if(IssueDate.size() == 10 && IssueDate[2] == '/' && IssueDate[5] == '/')
            {
                int d30[] = {4,6,9,11};
                int d31[] = {1,3,5,7,8,10,12};
                if(((IssueDate[0]-'0')*10 + (IssueDate[1]-'0') <= 30) && find(d30, d30+4, ((IssueDate[3]-'0')*10 + (IssueDate[4]-'0'))))
                {
                    break;
                }
                if(((IssueDate[0]-'0')*10 + (IssueDate[1]-'0') <= 31) && find(d31, d31+7, ((IssueDate[3]-'0')*10 + (IssueDate[4]-'0'))))
                {
                    break;
                }
                if(((IssueDate[0]-'0')*10 + (IssueDate[1]-'0') <= 28) && IssueDate[3] == '0' && IssueDate[4] == '2')
                {
                    break;
                }
            }
            cout << "Invalid input\nTry again" << endl;
        }
        ReturnDate = "";
    }
    string getdata()
    {
        string data;
        data.append("BookIssued");
        data.append("\n");
        data.append(BookId);
        data.append("\n");
        data.append(BookName);
        data.append("\n");
        data.append(Author);
        data.append("\n"+to_string(Status)+"\n"+IssueDate+"\n"+ReturnDate+"\n"+to_string(Fine)+"\n"+to_string(FinePaid)+"\n"+to_string(renew)+"\n"+to_string(max_days)+"\n"+"\\BookIssued");
        return data;
    }
    void getDetails();
    string getId(){return BookId;}
    void setReturnDate(string Date);             //CORRECTION
    long long CalculateFine();                                 //CORRECTION
    void AcceptFine(long long fine);
    bool isRenew();
    void ChangeRenew();
    bool getStatus(){return Status;}
    void setStatus(bool);
};

void BookIssued::setStatus(bool status)
{
    Status = status;
    return;
}
void BookIssued::getDetails()
{
    cout << "Id: " << setw(20) << BookId << endl;
    cout << "Title: " << setw(20) << BookName << endl;
    cout << "Author: " << setw(20) << Author << endl;
    cout << "Status: " << setw(20) << Status << endl;
    cout << "Issue date: " << setw(20) << IssueDate << endl;
    cout << "Return date: " << setw(20) << ReturnDate << endl;
    cout << "Fine: " << setw(20) << Fine << endl;
    cout << "Fine Paid: " << setw(20) << FinePaid << endl;
    renew? cout << "Renewed" << endl: cout << "Non Renewed" << endl;
    return;
}
void BookIssued::setReturnDate(string Date)
{
    //cout << "REACHED" << endl;
    ReturnDate = Date;
    Fine = CalculateFine();
}
long long BookIssued::CalculateFine()
{
    fir:;
    int year = 0, month = 0, days = 0;
    string y,m,d;
    bool undo = 0;
    if(ReturnDate.empty())
    {
        undo = 1;
        cout << "Enter today's date: ";
        cin_check;cin >> ReturnDate;
    }
    for(int i = 0; i < 2; i++) d.push_back(ReturnDate[i]);
    for(int i = 3; i < 5; i++) m.push_back(ReturnDate[i]);
    for(int i = 6; i < 10; i++) y.push_back(ReturnDate[i]);
    stringstream convert_days(d), convert_month(m), convert_year(y);
    convert_days >> days;
    convert_month >> month;
    convert_year >> year;
    //cout << "RETURN DATE" << endl;
    //cout << days << " " << month << " " << year << endl;
    int issue_year = 0, issue_month = 0, issue_day = 0;
    string y1,m1,d1;
    for(int i = 0; i < 2; i++) d1.push_back(IssueDate[i]);
    for(int i = 3; i < 5; i++) m1.push_back(IssueDate[i]);
    for(int i = 6; i < 10; i++) y1.push_back(IssueDate[i]);
    stringstream iconvert_days(d1), iconvert_month(m1), iconvert_year(y1);
    iconvert_days >> issue_day;
    iconvert_month >> issue_month;
    iconvert_year >> issue_year;
    //cout << "ISSUE DATE" << endl;
    //cout << issue_day << " " << issue_month  << " " << issue_year << endl;
    int days_kept = 1;
    int cur_day = issue_day, cur_mon = issue_month, cur_year = issue_year;
    int d30[] = {4,6,9,11};
    while(cur_day != days || cur_mon != month || cur_year != year)
    {
        days_kept++;
        cur_day++;
        if(cur_mon == 2 && cur_day == 29)
        {
            cur_mon = 3;
            cur_day = 1;
        }
        else if(cur_day == 30 && cur_mon == 2 && (cur_year%400==0 || (cur_year%4 == 0 && cur_year%100 != 0)))
        {
            cur_mon = 3;
            cur_day = 1;
        }
        else if(cur_mon == 12 && cur_day == 32)
        {
            cur_day = 1;
            cur_mon = 1;
            cur_year++;
        }
        else if(find(d30, d30+4, cur_mon) && cur_day == 31)
        {
            cur_day = 1;
            cur_mon++;
        }
        if(days_kept == 1300)
            break;
    }

    if(undo)
    {
        ReturnDate = "";
    }
    if(days_kept == 1300)
    {
        cout << "Return date not valid:" << endl;
        cout << "Input return date: ";
        cin >> ReturnDate;
        goto fir;
    }
    bool isrenew = isRenew();
    int cur_fine = max((days_kept-max_days*(isrenew+1))*5,0);
    Fine = cur_fine;
    return cur_fine-FinePaid;
}
void BookIssued::AcceptFine(long long fine)
{
    FinePaid += min(fine, Fine);
    if(FinePaid > Fine)
    {
        cout << "Extra amount worth Rs " << FinePaid-Fine << " paid. Please take it back!" << endl;
    }
    return;
}
bool BookIssued::isRenew() {return renew;}
void BookIssued::ChangeRenew(){renew = !renew;}


class User: public Member
{
private:
    vector<BookIssued*> history;
protected:
    string Department;
    int num_of_books_issued;
public:
    User(string name, string JoinDate, string Id, long long ph_num, string password, string Department, string address = "", string emailId = "")
    :Department(Department), num_of_books_issued(0), Member(name, JoinDate, Id, ph_num, password, address, emailId){}
    User(string name, string JoinDate, string Id, long long ph_num, string password, string Department, string address = "", string emailId = "", vector<BookIssued*> &v)
    :Department(Department), num_of_books_issued(0), Member(name, JoinDate, Id, ph_num, password, address, emailId)
    {
        for(int i = 0; i < v.size(); i++)
        {
            history.push_back(v[i]);
        }
    }

    virtual ~User()
    {
        for_each(history.begin(), history.end(), delete_pointed_to<BookIssued>);
    }
    void editDepartment(string dep);
    void payfine();
    void payfine(int);                                          //CORRECTION
    void inc_num_of_books(){num_of_books_issued++;}
    void dec_num_of_books(){num_of_books_issued--;}
    void setreturndate(string Resid, string date)
    {
        for(unsigned i = history.size()-1; i >= 0; i--)
        {
            if(history[i]->getId() == Resid)
            {
                history[i]->setReturnDate(date);
                break;
            }
        }
        return;
    }
    int getBooksIssued()
    {
        return num_of_books_issued;
    }
    void getHistory();      //CORRECTION
    void updateHistory(string Resid, Library &);
    void change_history_status(string ResId, string Date);
    void RenewResource(string ResId);
    string getdata()
    {
        string data = Member::getdata() + "\n" + "history\n";
        vector<BookIssued*>::iterator it = history.begin();
        while(it != history.end())
        {
            data.append((*it)->getdata());
            ++it;
        }
        data.append("\n");
        data.append("\\history\n");
        return data;
    }
    virtual int getJournalsIssued() = 0;
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
};

void User::getHistory()
{
    vector<BookIssued*>::iterator it = history.begin();
    if(it == history.end())
    {
        cout << "No books/journals issued :)" << endl;
    }
    while(it != history.end())
    {
        (*it)->getDetails();
        it++;
    }
}

void User::RenewResource(string ResId)
{
    if(getId()[0] == 'N')
    {
        cout << "You cannot renew :'(" << endl;
        return;
    }
    else
    {
        vector<BookIssued*>::iterator it = history.begin();
        while(it != history.end())
        {
            if((*it)->getId() == ResId)
            {
                if((*it)->getStatus())
                {
                    if(!(*it)->isRenew())
                    {
                        (*it)->ChangeRenew();
                        cout << "Renewed!" << endl;
                        return;
                    }
                    break;
                }
            }
            it++;
        }
    }
    cout << "Cannot Renew:(" << endl;
    return;
}

void User::payfine(int fine)
{
    vector<BookIssued*>::iterator it = history.begin();
    long long int sum = fine;
    while(it != history.end())
    {
        sum += (*it)->CalculateFine();
        it++;
        (*it)->getDetails();
        it++;
    }
    it--;
    while(sum && it != history.begin()-1)
    {
        (*it)->AcceptFine(min(sum, (*it)->CalculateFine()));
        sum -= min(sum, (*it)->CalculateFine());
        (*it)->getDetails();
        it--;
    }
    if(sum > 0)
    {
        cout << "Extra money Rs. " << sum << " paid. Please take it back :)" << endl;
    }
    return;
}

void User::payfine()
{
    vector<BookIssued*>::iterator it = history.begin();
			long long int sum = 0;
			while(it != history.end())
			{
				sum += (*it)->CalculateFine();
				(*it)->getDetails();
				//cout << " Fine = " << (*it)->CalculateFine(getId()) << "" << endl;
				it++;
			}
			cout << "Total fine = " << sum << endl;
			cout << "Enter amount paid" << endl;
			cin_check;cin >> sum;
			it--;
			while(sum && it != history.begin()-1)
			{
			    long long money = (*it)->CalculateFine();
				(*it)->AcceptFine(min(sum, money));
				sum -= min(sum, money);
				(*it)->getDetails();
				//cout << " Fine = " << money << " " << sum << "" << endl;
				it--;
			}
			if(sum > 0)
			{
				cout << "Extra money Rs. " << sum << " paid" << endl;
			}
			return;
}

void User::change_history_status(string ResId, string Date)
{
    vector<BookIssued*>::iterator it = history.end()-1;
    while(it != history.begin())
    {
        if((*it)->getId() == ResId)
        {
            (*it)->setStatus(!(*it)->getStatus());
           // cout << (*it)->getStatus() << endl;
            (*it)->CalculateFine();
            /*
            (*it)->Status = 0;      											//note
			(*it)->setReturnDate(Date);
			struct tm iss = {0, 0, 0, (*it)->IssueDate[0], (*it)->IssueDate[1] - 1, (*it)->IssueDate[0] - 1900};
			struct tm ret = {0, 0, 0, (*it)->ReturnDate[0], (*it)->ReturnDate[1] - 1, (*it)->ReturnDate[0] - 1900};
			time_t iss_t = mktime(&iss);
			time_t ret_t = mktime(&ret);
			double difference = difftime(ret_t, iss_t) / (60 * 60 * 24);
			(*it)->fine += (5*difference);
			*/
			return;
        }
        it--;
    }
    return;
}

class Student: public User
{
    static const int MaxBookLimit;
public:
    Student(string name, string JoinDate, string Id, long long ph_num, string password, string Department, string address = "", string emailId = ""):
     User(name, JoinDate, Id, ph_num, password, Department, address, emailId){}
    static int getBookLimit()
    {
        return MaxBookLimit;
    }
    string getdata()
    {
        return User::getdata();//+MaxBookLimit+"\n";
    }
    virtual bool isEligible(string BookId);
    virtual int getJournalsIssued() = 0;
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
};

const int Student::MaxBookLimit = 5;

bool Student::isEligible(string BookId)
{
    return getBookLimit()>getBooksIssued();
}

class Faculty: public User
{
    static int maxBookLimit;
    static int maxJournalLimit;
    static int maxdays;
    int NumOfJournalsIssued;
public:
    Faculty(string name, string JoinDate, string Id, long long ph_num, string password, string Department, string address = "", string emailId = ""):
        User(name, JoinDate, Id, ph_num, password, Department, address, emailId), NumOfJournalsIssued(0){}
    void SuggestResource();
    static int getBookLimit()
    {
        return maxBookLimit;
    }
    static int getJournalLimit()
    {
        return maxJournalLimit;
    }
    static int getmaxdays(){return maxdays;}
    int getJournalsIssued(){return NumOfJournalsIssued;}
    bool isEligible(string BookId);
    void inc_num_of_journals();
    void dec_num_of_journals();
    void view_my_profile();
    void edit_my_profile();
    string getdata()
    {
        return User::getdata()+"\n"+to_string(maxBookLimit)+"\n"+to_string(maxJournalLimit)+"\n"+to_string(maxdays)+"\n"+to_string(NumOfJournalsIssued)+"\n"+"\\Faculty";
    }
};
int Faculty::maxBookLimit = 10;
int Faculty::maxJournalLimit = 10;
int Faculty::maxdays = 14;

bool Faculty::isEligible(string BookId)
{
    if(BookId[0] == 'J')
        return maxJournalLimit>NumOfJournalsIssued;
    else if(BookId[0] == 'B')
        return maxBookLimit>num_of_books_issued;
    else
        return false;
}
void Faculty::inc_num_of_journals()
{
    NumOfJournalsIssued++;
}
void Faculty::dec_num_of_journals()
{
    NumOfJournalsIssued--;
}
void Faculty::view_my_profile()
{
    cout << "\n-------------------------------------" << endl;
    cout << "name: " << setw(30) << name << endl;
    cout << "Id: " << setw(30) << Id << endl;
    cout << "Phone number: " << setw(30) << ph_num << endl;
    cout << "Address: " << setw(30) << address << endl;
    cout << "Email Id: " << setw(30) << emailId << endl;
    cout << "Department: " << setw(30) << Department << endl;
    cout << "---------------------------------------" << endl;
}
void Faculty::edit_my_profile()
{
    char update;
    cout << "Name: " << name << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_name;
        cout << "Enter your name: ";
        cin_check;
        cin.ignore(INT_MAX, '\n');
        getline(cin, cur_name, '\n');
        name = cur_name;
    }
    cout << "Join Date: " << JoinDate << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string join;
        cout << "Enter the Join Date(dd/mm/yyyy): ";
        cin_check;cin >> join;
        JoinDate = join;
    }
    cout << "Phone number: " << ph_num << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else if(update == 'y')
    {
        long long curr_ph;
        cout << "Enter the phone number: ";
        cin_check;cin >> curr_ph;
        ph_num = curr_ph;
    }
    cout << "Address: " << address << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_address;
        cout << "Enter address: ";
        cin_check;getline(cin, cur_address);
        address = cur_address;
    }
    cout << "email id: " << emailId << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string email_id;
        cout << "Enter email id: ";
        cin_check;cin >> email_id;
        emailId = email_id;
    }
    cout << "Department : " << Department << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_dep;
        cout << "Enter the department: ";
        cin_check;cin >> cur_dep;
        Department = cur_dep;
    }
    return;
}

class NonPhd: public Student
{
    int year;
    static int maxdays;
public:
    NonPhd(string name, string JoinDate, string Id, long long ph_num, string password, string Department, int year, string address = "", string emailId = ""):
    Student(name, JoinDate, Id, ph_num, password, Department, address, emailId), year(year)
    {}
    int getYear();
    void editYear();
    void view_my_profile();
    void edit_my_profile();
    static int getmaxdays(){return maxdays;}
    int getJournalsIssued()
    {
        return 0;
    }
    string getdata()
    {
        return (string)"NonPhd"+"\n"+Student::getdata()+to_string(year)+"\n"+to_string(maxdays)+"\n"+"\\NonPhd"+"\n";
    }
};
int NonPhd::maxdays = 7;
int NonPhd::getYear()
{
    return year;
}
void NonPhd::editYear()
{
    cout << "Enter your year: ";
    cin_check;cin >> year;
    NonPhd::year = year;
    cout << "Successfully changed!" << endl;
}
void NonPhd::view_my_profile()
{
    cout << "\n-------------------------------------" << endl;
    cout << "name: " << setw(30) << name << endl;
    cout << "Id: " << setw(30) << Id << endl;
    cout << "Phone number: " << setw(30) << ph_num << endl;
    cout << "Address: " << setw(30) << address << endl;
    cout << "Email Id: " << setw(30) << emailId << endl;
    cout << "Department: " << setw(30) << Department << endl;
    cout << "Year: " << year << endl;                           //-_-
    cout << "---------------------------------------" << endl;
}
void NonPhd::edit_my_profile()
{
    char update;
    cout << "Name: " << name << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_name;
        cout << "Enter your name: ";
        cin_check;
        cin.ignore(INT_MAX, '\n');
        getline(cin, cur_name, '\n');
        name = cur_name;
    }
    cout << "Join Date: " << JoinDate << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string join;
        cout << "Enter the Join Date: ";
        cin_check;cin >> join;
        JoinDate = join;
    }
    cout << "Phone number: " << ph_num << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else if(update == 'y')
    {
        long long curr_ph;
        cout << "Enter the phone number: ";
        cin_check;cin >> curr_ph;
        ph_num = curr_ph;
    }
    cout << "Address: " << address << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_address;
        cout << "Enter address: ";
        cin_check;getline(cin, cur_address);
        address = cur_address;
    }
    cout << "email id: " << emailId << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string email_id;
        cout << "Enter email id: ";
        cin_check;cin >> email_id;
        emailId = email_id;
    }
    cout << "Department : " << Department << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_dep;
        cout << "Enter the department: ";
        cin_check;cin >> cur_dep;
        Department = cur_dep;
    }
    return;
}


class Phd:public Student
{
    static int maxJournalLimit;
    int num_of_journals_issued;
    static int maxdays;
public:
    Phd(string name, string JoinDate, string Id, long long ph_num, string password, string Department, string address = "", string emailId = ""):
    Student(name, JoinDate, Id, ph_num, password, Department, address, emailId), num_of_journals_issued(0)
    {}
    static int getMaxJournalLimit()
    {
        return maxJournalLimit;
    }
    int getJournalsIssued(){return num_of_journals_issued;}
    static int getJournalLimit() {return maxJournalLimit;}
    void inc_num_of_journals();
    void dec_num_of_journals();
    void view_my_profile();
    void edit_my_profile();
    string getdata()
    {
        return (string)"Phd"+"\n"+Student::getdata()+to_string(maxJournalLimit)+"\n"+to_string(num_of_books_issued)+"\n"+to_string(maxdays)+"\n"+"\\Phd";
    }
    static int getmaxdays(){return maxdays;}
};

int Phd::maxJournalLimit = 5;
int Phd::maxdays = 7;

void Phd::inc_num_of_journals()
{
    num_of_journals_issued++;
}
void Phd::dec_num_of_journals()
{
    num_of_journals_issued--;
}
void Phd::view_my_profile()
{
    cout << "\n-------------------------------------" << endl;
    cout << "name: " << setw(20) << name << endl;
    cout << "Id: " << setw(20) << Id << endl;
    cout << "Join date: " << setw(20) << JoinDate << endl;
    cout << "Phone number: " << setw(20) << ph_num << endl;
    cout << "Address: " << setw(20) << address << endl;
    cout << "Email Id: " << setw(20) << emailId << endl;
    cout << "Department: " << setw(20) << Department << endl;
    cout << "---------------------------------------" << endl;
}
void Phd::edit_my_profile()
{
    char update;
    cout << "Name: " << name << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_name;
        cout << "Enter your name: ";
        cin_check;
        cin.ignore(INT_MAX, '\n');
        getline(cin, cur_name, '\n');
        name = cur_name;
    }
    cout << "Join Date: " << JoinDate << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string join;
        cout << "Enter the Join Date(dd/mm/yyyy): ";
        cin_check;cin >> join;
        JoinDate = join;
    }
    cout << "Phone number: " << ph_num << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else if(update == 'y')
    {
        long long curr_ph;
        cout << "Enter the phone number: ";
        cin_check;cin >> curr_ph;
        ph_num = curr_ph;
    }
    cout << "Address: " << address << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_address;
        cout << "Enter address: ";
        cin_check;getline(cin, cur_address);
        address = cur_address;
    }
    cout << "email id: " << emailId << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string email_id;
        cout << "Enter email id: ";
        cin_check;cin >> email_id;
        emailId = email_id;
    }
    cout << "Department : " << Department << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_dep;
        cout << "Enter the department: ";
        cin_check;cin >> cur_dep;
        Department = cur_dep;
    }
    return;
}

bool Library::VerifyMemberId(string Id)
{
    vector<Member*>::iterator it = member.begin();
    while(it != member.end())
    {
        if((*it)->getId() == Id)
        return true;
        it++;
    }
    return false;
}
bool Library::VerifyResource(string Id)
{
    vector<Resource*>::iterator it = resources.begin();
    while(it != resources.end())
    {
        if((*it)->getId() == Id)
            return true;
        it++;
    }
    return false;
}
bool Library::CheckLimit(string UserId, string ResId)
{
    if(UserId[0] == 'N' && ResId[0] == 'B')
    {
        NonPhd* current = Library::get_user_nonphd(UserId);
        if(current)
            return Student::getBookLimit()>current->getBooksIssued();
        else
        {
            return false;
        }
    }
    else if(UserId[0] == 'P')
    {
        Phd* current = Library::get_user_phd(UserId);
        if(!current)
        {
            cout << "No such Phd student" << endl;
            return false;
        }
        //cout << "You want to check limit for\n1. Journal 2.Book\nPress 1 or 2" << endl;
        //int ch;
        //cin_check;cin >> ch;
        //cout << "ch = " << ch << " Student::getBookLimit() = " << Student::getBookLimit() << " current->getBooksIssued() = " << current->getBooksIssued() << endl;

        if(ResId[0] == 'J')
            return Phd::getMaxJournalLimit() > current->getJournalsIssued();
        else if(ResId[0] == 'B')
            return Student::getBookLimit()>current->getBooksIssued();
        else {
                cout << "Invalid Input" << endl;
                return false;
        }
    }
    else if(UserId[0] == 'F')
    {
        Faculty* current = Library::get_user_faculty(UserId);
        if(!current)
        {
            cout << "No such faculty" << endl;
            return false;
        }
        //cout << "You want to check limit for\n1. Journal\n2.Book\nPress 1 or 2";
        //char ch;
        //cin_check;cin >> ch;
        if(ResId[0] == 'J')
            return Faculty::getJournalLimit() > current->getJournalsIssued();
        else if(ResId[0] == 'B')
            return Faculty::getBookLimit() > current->getBooksIssued();
        else{
                cout << "Invalid Input" << endl;
                return false;
        }
    }
    else
    {
        cout << "Invalid Id" << endl;
    }
    return false;
}
void Library::AddMember()
{
    if(first)
    {
        string name, JoinDate, Id, address = "", password, emailId = "", department;
        long long ph_num;
        Staff* staff = new Staff(name = "Anurag", JoinDate = "02/04/2018", Id = "Sadmin", ph_num = 101LL, password = "admin", address = "Office of academics", emailId = "anurag.2@iitj.ac.in");
        Library::member.push_back(staff);
        Library::staff.push_back(staff);
        first = false;
        return;
    }
    cout << "1 Phd Student\n2 NonPhd Student\n3Faculty\n4.Staff\nSelect appropriately" << endl;
    int x;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cin >> x;
    switch(x)
    {
    case 1:
        {
            string name, JoinDate, Id, address = "", password, emailId = "", department;
            long long ph_num;
            cout << "Enter your name: ";
            cin_check;
            cin.ignore(INT_MAX, '\n');
            getline(cin, name, '\n');
            again:;
            cout << "Enter Id: ";
            cin_check;
            cin >> Id;
            while(Id[0] != 'P')
            {
                cout << "First alphabet should be 'P'\nTry again.";
                cin_check;cin >> Id;
            }
            if(VerifyMemberId(Id))
            {
                cout << "Id already exists" << endl;
                goto again;
            }
            cout << "Enter phone number: ";
            cin_check;
            cin >> ph_num;
            cout << "Enter address: ";
            cin_check;
            cin.ignore(INT_MAX, '\n');
            getline(cin,address);
            cout << "Enter password: ";
            cin_check;
            cin >> password;
            cout << "Enter email id: ";
            cin_check;
            cin >> emailId;
            cout << "Enter Department: ";
            cin_check;
            cin >> department;
            Phd* phd = new Phd(name, JoinDate, Id, ph_num, password, department, address, emailId);
            Library::member.push_back(phd);
            Library::phd.push_back(phd);
            break;
        }
    case 2:
        {
            string name, JoinDate, Id, address = "", password, emailId = "", department;
            long long ph_num;
            cout << "Enter your name: ";
            cin.ignore(INT_MAX, '\n');
            getline(cin, name, '\n');
            again1:;
            cout << "Enter Id: ";
            cin >> Id;
            while(Id[0] != 'N')
            {
                cout << "First alphabet should be 'N'\nTry again.";
                cin >> Id;
            }
            if(VerifyMemberId(Id))
            {
                cout << "Id already exists" << endl;
                goto again1;
            }
            cout << "Enter phone number: ";
            cin_check;cin >> ph_num;
            cout << "Enter address: ";
            cin_check;
            cin.ignore(INT_MAX, '\n');
            getline(cin, address, '\n');
            cout << "Enter password: ";
            cin_check;cin >> password;
            cout << "Enter email id: ";
            cin_check;cin >> emailId;
            cout << "Enter Department: ";
            cin_check;cin >> department;cin_check;
            NonPhd* nonphd = new NonPhd(name, JoinDate, Id, ph_num, password, department, 1, address, emailId);
            Library::member.push_back(nonphd);
            Library::nphd.push_back(nonphd);
            break;
        }
    case 3:
        {
            string name, JoinDate, Id, address = "", password, emailId = "", department;
            long long ph_num;
            cout << "Enter your name: ";
            cin.ignore(INT_MAX, '\n');
            getline(cin, name, '\n');
            again2:;
            cout << "Enter Id: ";
            cin >> Id;
            while(Id[0] != 'F')
            {
                cout << "First alphabet should be 'F'\nTry again.";
                cin >> Id;
            }
            if(VerifyMemberId(Id))
            {
                cout << "Id already exists" << endl;
                goto again2;
            }
            cout << "Enter phone number: ";cin_check;
            cin >> ph_num;
            cout << "Enter address: ";cin_check;
            cin.ignore(INT_MAX, '\n');
            getline(cin, address, '\n');
            cout << "Enter password: ";cin_check;
            cin >> password;
            cout << "Enter email id: ";cin_check;
            cin >> emailId;
            cout << "Enter Department: ";cin_check;
            cin >> department;cin_check;
            Faculty* faculty = new Faculty(name, JoinDate, Id, ph_num, password, department, address, emailId);
            Library::member.push_back(faculty);
            Library::faculty.push_back(faculty);
            break;
        }
    case 4:
        {
            string name, JoinDate, Id, address = "", password, emailId = "", department;
            long long ph_num;
            cout << "Enter your name: ";
            cin_check;
            cin.ignore(INT_MAX, '\n');
            getline(cin, name, '\n');
            again3:;
            cout << "Enter Id: ";
            cin_check;
            cin >> Id;
            while(Id[0] != 'S')
            {
                cout << "First alphabet should be 'S'\nTry again.";
                cin >> Id;
            }
            if(VerifyMemberId(Id))
            {
                cout << "Id already exists" << endl;
                goto again3;
            }
            cout << "Enter phone number: ";
            cin_check;
            cin >> ph_num;
            cout << "Enter address: ";
            cin_check;
            cin.ignore(INT_MAX, '\n');
            getline(cin, address, '\n');
            cout << "Enter password: ";
            cin_check;
            cin >> password;
            cout << "Enter email id: ";
            cin_check;
            cin >> emailId;
            cin_check;
            Staff* staff = new Staff(name, JoinDate, Id, ph_num, password, address, emailId);
            Library::member.push_back(staff);
            Library::staff.push_back(staff);
            break;
        }
    default:
        {
            cout << "Invalid Input" << endl;
            break;
        }
    }
    return;
}
void Library::AddNewResource()
{
    cout << "You want to add\n1.Book 2.Journal\nto the library?\n    \
    Press 1 or 2 and then press enter" << endl;
    char ch;
    cin >> ch;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "incorrect option" << endl;
        return;
    }
    if(ch == '1')
    {
        string author, title, Id, DateOfPurchase, SubjectName;
        int Edition;
        string SubCode;
        double RackNumber;
        cout << "Enter Author: ";
        cin_check;cin >> author;
        cout << "Enter title: ";
        cin_check;cin >> title;
        tp:;
        cout << "Enter Id: ";
        cin_check;cin >> Id;
        while(Id[0] != 'B')
        {
            cout << "Invalid ID: ID should start with 'B', Try again..." << endl;
            cin_check;cin >> Id;
        }
        if(Library::search_by_Id(Id))
        {
            cout << "This Id already exists" << endl;
            goto tp;
        }
        cout << "Enter Date of Purchase(dd/mm/yyyy): ";
        cin_check;cin >> DateOfPurchase;

        cout << "Enter Subject Name: ";
        cin_check;cin >> SubjectName;
        cout << "Enter Subject code: ";
        cin_check;cin >> SubCode;
        cout << "Enter Edition: ";
        cin_check;cin >> Edition;
        cout << "Enter Rack Number: ";
        cin_check;cin >> RackNumber;cin_check;
        resources.push_back(new Book(author, title, Id, DateOfPurchase, Edition, RackNumber, SubjectName, SubCode));
    }
    else if(ch == '2')
    {
        string author, title, Id, DateOfPurchase, PubDate;
        int Edition;
        double RackNumber;
        cout << "Enter Author: ";
        cin_check;cin >> author;
        cout << "Enter title: ";
        cin_check;cin >> title;
        up:
        cout << "Enter Id: ";
        cin_check;cin >> Id;
        while(Id[0] != 'J')
        {
            cout << "Invalid ID: ID should start with 'J', Try again..." << endl;
            cin_check;cin >> Id;
        }
        if(Library::search_by_Id(Id))
        {
            cout << "This Id already exists" << endl;
            goto up;
        }
        cout << "Enter Date of Purchase(dd/mm/yyyy): ";
        cin_check;cin >> DateOfPurchase;
        cout << "Enter Publication date(dd/mm/yyyy): ";
        cin_check;cin >> PubDate;
        cout << "Enter Edition: ";
        cin_check;cin >> Edition;
        cout << "Enter Rack Number: ";
        cin_check;cin >> RackNumber;
        vector<string> topic;
        cout << "Enter the topics related to this journal\nPress ENTER while adding new topic\nPress 'y' when done" << endl;
        string last = "y";
        while(1)
        {
            string topic_;
            cin_check;cin >> topic_;
            topic.push_back(topic_);
            if(topic_ == last)
                break;
        }
        resources.push_back(new Journal(author, title, Id, DateOfPurchase, Edition, RackNumber, PubDate, topic));
    }
    else
    {
        cout << "Incorrect option" << endl;
    }
    return;
}
void Library::RemoveMember(string Id)
{
    bool del = 0;
    vector<Member*>::iterator it = member.begin();
    while(it != member.end())
    {
        if((*it)->getId() == Id)
        {
            if(Id[0] == 'F')
            {
                vector<Faculty*>::iterator it_ = faculty.begin();
                while(it_ != faculty.end())
                {
                    if((*it_)->getId() == Id)
                    {
                        del = 1;
                        faculty.erase(it_);
                        break;
                    }
                    it_++;
                }
            }
            else if(Id[0] == 'N')
            {
                vector<NonPhd*>::iterator it_ = nphd.begin();
                while(it_ != nphd.end())
                {
                    if((*it_)->getId() == Id)
                    {
                        del = 1;
                        nphd.erase(it_);
                        break;
                    }
                    it_++;
                }
            }
            else if(Id[0] == 'P')
            {
                vector<Phd*>::iterator it_ = phd.begin();
                while(it_ != phd.end())
                {
                    if((*it_)->getId() == Id)
                    {
                        del = 1;
                        phd.erase(it_);
                        break;
                    }
                    it_++;
                }
            }
            else if(Id[0] == 'S')
            {
                vector<Staff*>::iterator it_ = staff.begin();
                while(it_ != staff.end())
                {
                    if((*it_)->getId() == Id)
                    {
                        del = 1;
                        staff.erase(it_);
                        break;
                    }
                    it_++;
                }
            }
            if(!del)
            {
                cout << "No such member exists!" << endl;
                return;
            }
            delete *it;
            member.erase(it);
            cout << "Successfully deleted!" << endl;
            return;
        }
        it++;
    }
    cout << "No such member exists" << endl;
    return;
}
void Library::RemoveResource(string Id)
{
    vector<Resource*>::iterator it = resources.begin();
    while(it != resources.end())
    {
        if((*it)->getId() == Id)
        {
            delete *it;
            resources.erase(it);
            cout << "Successfully deleted!" << endl;
            return;
        }
        it++;
    }
    cout << "No such Book/Journal exists" << endl;
    return;
}
set<Resource*> Library::search_by_author(string author)
{
    vector<Resource*>::iterator it = resources.begin();
    set<Resource*> match;
    while(it != resources.end())
    {
        if((*it)->getAuthor() == author)
        {
            match.insert(*it);
        }
        it++;
    }
    if(match.empty())
        cout << "No such Book/Journal exists" << endl;
    return match;
}
set<Resource*> Library::search_by_Title(string title)
{
    vector<Resource*>::iterator it = resources.begin();
    set<Resource*> match;
    while(it != resources.end())
    {
        if((*it)->getTitle() == title)
        {
            match.insert(*it);
        }
        it++;
    }
    if(match.empty())
        cout << "No such Book/Journal exists" << endl;
    return match;
}
Resource* Library::search_by_Id(string ResId)           //CORRECTION
{
    vector<Resource*>::iterator it = resources.begin();
    while(it != resources.end())
    {
        if((*it)->getId() == ResId)
        {
            return *it;
        }
        it++;
    }
    cout << "No such Book/Journal exists" << endl;
    return nullptr;
}
set<Resource*> Library::search_by_tag(const vector<string> &tags)
{
    vector<Resource*>::iterator it = resources.begin();
    set<Resource*> matches;
    while(it != resources.end())
    {
        for(unsigned idx = 0U; idx < tags.size(); idx++)
        {
            auto it = resources.begin();
            vector<string> c_tags = (*it)->getTopic();
            for(unsigned i = 0U; i < c_tags.size(); i++)
            {
                if(c_tags[i] == tags[idx])
                {
                    matches.insert(*it);
                    break;
                }
            }
        }
        it++;
    }
    return matches;
}
void Library::ViewAllMembers()
{
    auto it = member.begin();
    while(it != member.end())
    {
        (*it)->view_my_profile();
        cout << "------------------" << endl;
        it++;
    }
    return;
}
void Library::ViewAllResource()
{
    for(unsigned i = 0U; i < resources.size(); i++)
    {
        resources[i]->getdetails();
        cout << "-------------------------------" << endl;
    }
    if(resources.size() == 0)
    {
        cout << "No books/journals are there in the library" << endl;
        cout << "---------------------------------------------" << endl;
    }
    return;
}

Phd* Library::get_user_phd(string UserId)
{
    vector<Phd*>::iterator phd = Library::phd.begin();
    while(phd != Library::phd.end())
    {
        if((*phd)->getId() == UserId)
        {
            return *phd;
        }
        phd++;
    }
    return nullptr;
}
NonPhd* Library::get_user_nonphd(string UserId)
{
    vector<NonPhd*>::iterator nphd = Library::nphd.begin();
    while(nphd != Library::nphd.end())
    {
        if((*nphd)->getId() == UserId)
            {
                return *nphd;
            }
        nphd++;
    }
    return nullptr;
}
Faculty* Library::get_user_faculty(string UserId)
{
    vector<Faculty*>::iterator faculty = Library::faculty.begin();
    while(faculty != Library::faculty.end())
    {
        if((*faculty)->getId() == UserId)
            {
                return *faculty;
            }
        faculty++;
    }
    return nullptr;
}
Staff* Library::get_user_staff(string UserId)
{
    vector<Staff*>::iterator it = staff.begin();
    string password;
    while(it != staff.end())
    {
        if((*it)->getId() == UserId)
            {
                return *it;
            }
        it++;
    }
    return nullptr;
}

NonPhd* Library::Login_as_Non_Phd(string Id)
{
    vector<NonPhd*>::iterator it = nphd.begin();
    while(it != nphd.end())
    {
        if((*it)->getId() == Id)
            {
                string password;
                cout << "Enter Password: ";
                cin_check;
                cin >> password;
                while(password != (*it)->getpassword())
                {
                    cout << "Incorrect password. Try again..." << endl;
                    cin_check;cin >> password;
                }
                return *it;
            }
        it++;
    }
    return nullptr;
}
Phd* Library::Login_as_Phd(string Id)
{
    vector<Phd*>::iterator it = phd.begin();
    string password;
    while(it != phd.end())
    {
        if((*it)->getId() == Id)
            {
                cout << "Enter Password: ";
                cin_check;
                cin >> password;
                //cout << "pss " << (*it)->getpassword() << endl;
                while(password != (*it)->getpassword())
                {
                    cout << "Incorrect password. Try again..." << endl;
                    cin_check;cin >> password;
                }
                return *it;
            }
            it++;
    }
    return nullptr;
}
Staff* Library::Login_as_Staff(string Id)
{
    vector<Staff*>::iterator it = staff.begin();
    string password;
    while(it != staff.end())
    {
        if((*it)->getId() == Id)
            {
                cout << "Enter Password: ";
                cin_check;
                cin >> password;
                while(password != (*it)->getpassword())
                {
                    cout << "Incorrect password. Try again..." << endl;
                    cin_check;cin >> password;
                }
                return *it;
            }
        it++;
    }
    return nullptr;
}
Faculty* Library::Login_as_Faculty(string Id)
{
    vector<Faculty*>::iterator it = faculty.begin();
    string password;
    while(it != faculty.end())
    {
        if((*it)->getId() == Id)
            {
                cout << "Enter Password: ";
                cin_check;
                cin >> password;
                while(password != (*it)->getpassword())
                {
                    cout << "Incorrect password. Try again..." << endl;
                    cin_check;cin >> password;
                }
                return *it;
            }
        it++;
    }
    return nullptr;
}

bool Staff::IssueResource(string UserId, string ResourceId, Library &lib)
{
    if(lib.VerifyMemberId(UserId) && lib.VerifyResource(ResourceId))
    {
        if(lib.CheckLimit(UserId, ResourceId))
        {
            int days = 0;
            string Date = "02/04/18";
            if(UserId[0] == 'F')
                days = 14;
            else
                days = 7;
            Resource* resource = lib.search_by_Id(ResourceId);
            resource->getdetails();
            if(resource->getStatus() == false)
            {
                //cout << "HERE" << endl;
                cout << resource->getTitle() << " Not Available" << endl;
                return false;
            }
            if(resource){
                if(UserId[0] == 'N')
                {
                    NonPhd* nphd = lib.get_user_nonphd(UserId);
                    if(!nphd)
                    {
                        cout << "No such Non phd student exists." << endl;
                        return false;
                    }
                    resource->update_history(UserId, Date, false, days);
                    nphd->updateHistory(ResourceId, lib);
                    if(ResourceId[0] == 'B')
                        nphd->inc_num_of_books();
                }
                else if(UserId[0] == 'P')
                {
                    Phd* phd = lib.get_user_phd(UserId);
                    if(!phd)
                    {
                        cout << "No such phd student exists" << endl;
                    }
                    resource->update_history(UserId, Date, false, days);
                    phd->updateHistory(ResourceId, lib);
                    if(ResourceId[0] == 'B')
                        phd->inc_num_of_books();
                    else if(ResourceId[0] == 'J')
                        phd->inc_num_of_journals();
                }
                else if(UserId[0] == 'F')
                {
                    Faculty* facl = lib.get_user_faculty(UserId);
                    if(!facl)
                    {
                        cout << "No such faculty" << endl;
                        return false;
                    }
                    resource->update_history(UserId, Date, false, days);
                    facl->updateHistory(ResourceId, lib);
                    if(ResourceId[0] == 'B')
                        facl->inc_num_of_books();
                    else if(ResourceId[0] == 'J')
                        facl->inc_num_of_journals();
                }
                return true;
            }
        }
        else
        {
            cout << endl << "Cannot Issue Resource. You may have exceed your maximum limit to issue(Ignore if you are not registered to the system)" << endl;
        }
    }
    return false;
}
void Staff::ReturnResource(string UserId, string ResId, Library &lib)
{
    if(lib.VerifyMemberId(UserId) && lib.VerifyResource(ResId) && (UserId[0] == 'P' || UserId[0] == 'N' || UserId[0] == 'F'))
    {
        Resource* resource = lib.search_by_Id(ResId);
        if(resource->getStatus())
        {
            cout << "This resource is already in library!" << endl;
            return;
        }
        if(resource->latest_history_user_id() != UserId)
        {
            cout << "User bearing UserId " << UserId << " does not hold this item" << endl;
            return;
        }
        string date;
        cout << "Enter today's date(dd/mm/yyyy): ";
        cin >> date;

        if(UserId[0] == 'P')
        {
            Phd* phd = lib.get_user_phd(UserId);
            if(phd)
            {
                phd->setreturndate(ResId, date);
                resource->update_history(UserId, ResId, true, phd->getmaxdays());
                phd->change_history_status(ResId, date);
                if(ResId[0] == 'B')
                    phd->dec_num_of_books();
                else
                    phd->dec_num_of_journals();
            }
            else
                cout << "No such Phd student" << endl;
        }
        else if(UserId[0] == 'N')
        {
            NonPhd* nphd = lib.get_user_nonphd(UserId);
            if(nphd)
                {
                    nphd->setreturndate(ResId, date);
                    resource->update_history(UserId, ResId, true, nphd->getmaxdays());
                    nphd->change_history_status(ResId, date);
                    nphd->dec_num_of_books();
                }
            else
                cout << "No such Non Phd student" << endl;
        }
        else if(UserId[0] == 'F')
        {
            Faculty* faculty = lib.get_user_faculty(UserId);
            if(faculty)
                {
                    faculty->setreturndate(ResId, date);
                    resource->update_history(UserId, ResId, true, faculty->getmaxdays());
                    faculty->change_history_status(ResId, date);
                    if(ResId[0] == 'B')
                        faculty->dec_num_of_books();
                    else if(ResId[0] == 'J')
                        faculty->dec_num_of_journals();
                }
            else
                cout << "No such faculty" << endl;
        }
    }
    return;
}
void Staff::CollectFine(string Id, long long fine, Library &lib)
{
    User* user;
    if(lib.VerifyMemberId(Id))
    {
        if(Id[0] == 'P')
            {
                user = lib.get_user_phd(Id);
                user->payfine(fine);
            }
        else if(Id[0] == 'N')
            {
                user = lib.get_user_nonphd(Id);
                user->payfine(fine);
            }
        else if(Id[0] == 'F')
            {
                user = lib.get_user_faculty(Id);
                user->payfine(fine);
            }
    }
    else
    {
        cout << "Invalid Id" << endl;
    }
    return;
}
void Staff::UpdateHistory(string UserId, string ResId, Library& lib){}
void Staff::view_my_profile()
{
    cout << "\n-------------------------------------" << endl;
    cout << "name: " << setw(30) << name << endl;
    cout << "Id: " << setw(30) << Id << endl;
    cout << "Phone number: " << setw(30) << ph_num << endl;
    cout << "Address: " << setw(30) << address << endl;
    cout << "Email Id: " << setw(30) << emailId << endl;
    cout << "---------------------------------------" << endl;
}
void Staff::edit_my_profile()
{
    char update;
    cout << "Name: " << name << endl;
    cout << "Update? Enter y or n: " << endl;
    cin_check;
    //cin >> update;
    cin >> update;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_name;
        cout << "Enter your name: ";
        cin_check;
        cin.ignore(INT_MAX, '\n');
        getline(cin, cur_name, '\n');
        name = cur_name;
    }
    cout << "Join Date: " << JoinDate << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string join;
        cout << "Enter the Join Date(dd/mm/yyyy): ";
        cin_check;cin >> join;
        JoinDate = join;
    }
    cout << "Phone number: " << ph_num << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else if(update == 'y')
    {
        long long curr_ph;
        cout << "Enter the phone number: ";
        cin_check;cin >> curr_ph;
        ph_num = curr_ph;
    }
    cout << "Address: " << address << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string cur_address;
        cout << "Enter address: ";
        cin_check;getline(cin, cur_address);cin_check;
        address = cur_address;
    }
    cout << "email id: " << emailId << endl;
    cout << "Update? Enter y or n: ";
    cin_check;cin >> update;
    if(update != 'y' && update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else if(update == 'y')
    {
        string email_id;
        cout << "Enter email id: ";
        cin_check;cin >> email_id;
        emailId = email_id;
    }
    return;
}

void IssuedBy::getdetails(Library &lib)
{
    cout << endl << "----------------------------------" << endl;
    if(Id[0] == 'F')
    {
        Faculty* faculty = lib.get_user_faculty(Id);
        if(faculty)
            faculty->view_my_profile();
        if(IssueFor)
        cout << "Issued for " << IssueFor << " days" << endl;
    }
    else if(Id[0] == 'N')
    {
        NonPhd* nphd = lib.get_user_nonphd(Id);
        if(nphd)
            nphd->view_my_profile();
        if(IssueFor)
        cout << "Issued for " << IssueFor << " days" << endl;
    }
    else if(Id[0] == 'P')
    {
        Phd* phd = lib.get_user_phd(Id);
        if(phd)
            phd->view_my_profile();
        if(IssueFor)
        cout << "Issued for " << IssueFor << " days" << endl;
    }
    cout << "-------------------------------" << endl;
    return;
}

void Resource::gethistory(Library& lib)
{
    for(unsigned i = 0U; i < Resource::history.size(); i++)
    {
        history[i]->getdetails(lib);
    }
    return;
}

void User::updateHistory(string Resid, Library &lib)
{
    Resource* res = lib.search_by_Id(Resid);
    if(getId()[0] == 'F' && Resid[0] == 'B')
        history.push_back(new BookIssued(res, Faculty::getmaxdays()));
    else if(getId()[0]=='F' && Resid[0] == 'J')
        history.push_back(new BookIssued(res, Faculty::getmaxdays()));
    else if(getId()[0]=='P' && Resid[0] == 'B')
        history.push_back(new BookIssued(res, Phd::getmaxdays()));
    else if(getId()[0]=='P' && Resid[0] == 'J')
        history.push_back(new BookIssued(res, Phd::getmaxdays()));
    else if(getId()[0]=='N' && Resid[0] == 'B')
        history.push_back(new BookIssued(res, NonPhd::getmaxdays()));
    return;
}


string Library::getStudentNonPhddata()
{
    string data;
    vector<NonPhd*>::iterator it = nphd.begin();
    while(it != nphd.end())
    {
        data.append((*it)->getdata());
        it++;
    }
    return data;
}

string Library::getStudentPhddata()
{
    string data;
    vector<Phd*>::iterator it = phd.begin();
    while(it != phd.end())
    {
        data.append((*it)->getdata());
        it++;
    }
    return data;
}
string Library::getFacultydata()
{
    string data;
    vector<Faculty*>::iterator it = faculty.begin();
    while(it != faculty.end())
    {
        data.append((*it)->getdata());
        it++;
    }
    return data;
}
string Library::getStaffdata()
{
    string data;
    vector<Staff*>::iterator it = staff.begin();
    while(it != staff.end())
    {
        data.append((*it)->getdata());
        it++;
    }
    return data;
}

string Library::getResourcedata()
{
    string data;
    vector<Resource*>::iterator it = resources.begin();
    while(it != resources.end())
    {
        data.append((*it)->getdata());
        ++it;
    }
    return data;
}

string Resource::getdata()
{
    string data = author+"\n"+title+"\n"+Id+"\n"+date_of_purchase+"\n"+to_string(Edition)+"\n"+to_string(rack_num)+"\n"+to_string(status)+"\n";
    vector<IssuedBy*>::iterator it = history.begin();
    data.append("history");
    data.append("\n");
    while(it != history.end())
    {
        data.append((*it)->getdata());
        data.append("\n");
        ++it;
    }
    data.append("\\history");
    data.append("\n");
    return data;
}

void savedata(Library &lib)
{
    string path = "data/NonPhd.txt";
    ofstream input(path);
    input << lib.getStudentNonPhddata();
    input.close();
    input.open("data/Phd.txt");
    input << lib.getStudentPhddata();
    input.close();
    input.open("data/Faculty.txt");
    input << lib.getFacultydata();
    input.close();
    input.open("data/Staff.txt");
    input << lib.getStaffdata();
    input.close();
    input.open("data/Resources.txt");
    input << lib.getResourcedata();
    input.close();
}

void loaddata(Library &lib)
{
    ifstream read;
    read.open("data/NonPhd.txt");
    string name, JoinDate, Id, address = "", password, emailId = "", department;
    long long ph_num;
    string data;
    vector<BookIssued*> history;
    vector<Phd*> phd;
    while(getline(read, data))
    {
        if(data == "Phd")
        {
            int i = 0;
            while(getline(read, data))
            {
                if(data == "\\Phd")
                    {
                        phd.push_back(Phd());
                        break;
                    }
                ++i;
                switch(i)
                {
                case 1:
                    {
                        name = data;
                        break;
                    }
                case 2:
                    {
                        Id = data;
                        break;
                    }
                case 3:
                    {
                        JoinDate = data;
                        break;
                    }
                case 4:
                    {
                        for(int j = 0 ; j < data.length; j++)
                        {
                            ph_num  = ph_num*10 + data[i] - '0';
                        }
                        break;
                    }
                case 5:
                    {
                        address = data;
                        break;
                    }
                case 6:
                    {
                        password  = data;
                        break;
                    }
                case 7:
                    {
                        emailId = data;
                        break;
                    }
                case 8:
                    {
                        while(getline(read, data))
                        {
                            string BookId, BookName, Author, IssuedDate, ReturnDate;
                            bool Status, renew;
                            long long Fine=0, FinePaid=0;
                            int max_days, j = 0;
                            while(data != "\\history")
                            {
                                ++j;
                                switch(j)
                                {
                                case 1:
                                    {
                                        BookId = data;
                                        break;
                                    }
                                case 2:
                                    {
                                        BookName = data;
                                        break;
                                    }
                                case 3:
                                    {
                                        Author = data;
                                        break;
                                    }
                                case 4:
                                    {
                                        Status = data[0]-'0';
                                        break;
                                    }
                                case 5:
                                    {
                                        IssuedDate = data;
                                        break;
                                    }
                                case 6:
                                    {
                                        ReturnDate = data;
                                        break;
                                    }
                                case 7:
                                    {
                                        for(int k = 0; k < data.length; k++)
                                        {
                                            Fine = Fine*10 + data[i] - '0';
                                        }
                                        break;
                                    }
                                case 8:
                                    {
                                        for(int k = 0; k < data.length; k++)
                                        {
                                            FinePaid = FinePaid*10 + data[i] - '0';
                                        }
                                        break;
                                    }
                                case 9:
                                    {
                                        renew = data[0] - '0';
                                        break;
                                    }
                                case 10:
                                    {
                                        for(int k = 0; k < data.length; k++)
                                        {
                                            max_days = max_days*10 + data[i] - '0';
                                        }
                                        break;
                                    }
                                    history.push_back(new BookIssued(BookId, BookName, ));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


int main()
{
    try{
        cout << "\t\tWelcome to IITJ Automated Library" << endl;
        cout << "\n" << endl;
        cout << "Authors:" << endl;
        cout << "Anurag Shah B16CS034" << endl;
        cout << "Chinmay Garg B16CS041" << endl;
        cout << "\n@All Copyrights reserved" << endl;
        cout << "\nPress any key to continue";
        cin_check;cin.get();
        cin.ignore(INT_MAX, '\n');
        system("CLS");
        Library mylib("IITJ", 8320130726LL);
        mylib.AddMember();
        while(1)
        {
            system("CLS");
            string Id;
            cout << "Please login...";
            cout << "\nEnter your Id" << endl;
            cin >> Id;
            switch(Id[0])
            {
            case 'S':
                {
                    Staff* staff = mylib.Login_as_Staff(Id);
                    if(!staff)
                    {
                        cout << "Invalid Id:" << endl;
                        break;
                    }
                    while(1)
                    {
                        system("CLS");
                        cout << "WELCOME\t" << staff->getname() << endl << endl;
                        cout << "\t\tInstructions:" << endl;
                        cout << "1. View your profile" << endl;
                        cout << "2. Edit your profile" << endl;
                        cout << "3. Add member" << endl;
                        cout << "4. Add Resource" << endl;
                        cout << "5. View Member" << endl;
                        cout << "6. View Resource" << endl;
                        cout << "7. View all members" << endl;
                        cout << "8. View all resources" << endl;
                        cout << "9. See user history" << endl;
                        cout << "10. See resource history" << endl;
                        cout << "11. Issue resource" << endl;
                        cout << "12. return resource" << endl;
                        cout << "13. Remove member" << endl;
                        cout << "14. Remove resource" << endl;
                        cout << "15. Log out" << endl;
                        int u;
                        cin_check;
                        cin >> u;
                        switch(u)
                        {
                        case 1:
                            {
                                staff->view_my_profile();
                                break;
                            }
                        case 2:
                            {
                                staff->edit_my_profile();
                                break;
                            }
                        case 3:
                            {
                                mylib.AddMember();
                                break;
                            }
                        case 4:
                            {
                                mylib.AddNewResource();
                                break;
                            }
                        case 5:
                            {
                                string Userid;
                                cout << "Enter User ID: ";
                                while(1)
                                {
                                    cin_check;
                                    cin >> Userid;
                                    if(mylib.VerifyMemberId(Userid))
                                        break;
                                    cout << "Invalid Input. Try again." << endl;
                                }
                                if(Userid[0] == 'F')
                                {
                                    Faculty* faculty = mylib.get_user_faculty(Userid);
                                    if(faculty)
                                        faculty->view_my_profile();
                                    else
                                        cout << "No such Faculty" << endl;
                                }
                                else if(Userid[0] == 'N')
                                {
                                    NonPhd* nphd = mylib.get_user_nonphd(Userid);
                                    if(nphd)
                                        nphd->view_my_profile();
                                    else
                                        cout << "No such student" << endl;
                                }
                                else if(Userid[0] == 'P')
                                {
                                    Phd* phd = mylib.get_user_phd(Userid);
                                    if(phd)
                                        phd->view_my_profile();
                                    else
                                        cout << "No such Phd student" << endl;
                                }
                                else if(Userid[0] == 'S')
                                {
                                    Staff* staff = mylib.get_user_staff(Userid);
                                    if(staff)
                                        staff->view_my_profile();
                                    else
                                        cout << "No such Staff is registered in the system" << endl;
                                }
                                break;
                            }
                        case 6:
                            {
                                system("CLS");
                                cout << "1. Search by id" << endl;
                                cout << "2. Search by Title" << endl;
                                cout << "3. Search by Author" << endl;
                                cout << "4. Search by Tag" << endl;
                                int option;
                                cout << "Select appropriately" << endl;
                                cin_check;cin >> option;
                                switch(option)
                                {
                                case 1:
                                    {
                                        cout << "Enter Id";
                                        string Resid;
                                        cin_check;
                                        cin >> Resid;
                                        Resource* res = mylib.search_by_Id(Resid);
                                        if(!res)
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        else
                                            res->getdetails();
                                        break;
                                    }
                                case 2:
                                    {
                                        cout << "Enter Title";
                                        string Title;
                                        cin_check;
                                        cin >> Title;
                                        set<Resource*> res = mylib.search_by_Title(Title);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 3:
                                    {
                                        cout << "Enter author";
                                        string author;
                                        cin_check;
                                        cin >> author;
                                        set<Resource*> res = mylib.search_by_author(author);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 4:
                                    {
                                        cout << "Enter tags. Press y when done." << endl;
                                        vector<string> tag;
                                        cin_check;
                                        string br = "y";
                                        while(1)
                                        {
                                            string tg;
                                            cin >> tg;
                                            if(tg == br)
                                                break;
                                            tag.push_back(tg);
                                        }
                                        set<Resource*> res = mylib.search_by_tag(tag);
                                        if(res.empty())
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                default:
                                    {
                                        cout << "Invalid Input" << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                        case 7:
                            {
                                mylib.ViewAllMembers();
                                break;
                            }
                        case 8:
                            {
                                mylib.ViewAllResource();
                                break;
                            }
                        case 9:
                            {
                                string Userid;
                                cout << "Enter User ID: ";
                                while(1)
                                {
                                    cin_check;
                                    cin >> Userid;
                                    if(mylib.VerifyMemberId(Userid))
                                        break;
                                    cout << "Invalid Input. Try again." << endl;
                                }
                                if(Userid[0] == 'F')
                                {
                                    Faculty* faculty = mylib.get_user_faculty(Userid);
                                    if(faculty)
                                        faculty->getHistory();
                                    else
                                        cout << "No such Faculty" << endl;
                                }
                                else if(Userid[0] == 'N')
                                {
                                    NonPhd* nphd = mylib.get_user_nonphd(Userid);
                                    if(nphd)
                                        nphd->getHistory();
                                    else
                                        cout << "No such student" << endl;
                                }
                                else if(Userid[0] == 'P')
                                {
                                    Phd* phd = mylib.get_user_phd(Userid);
                                    if(phd)
                                        phd->getHistory();
                                    else
                                        cout << "No such Phd student" << endl;
                                }
                                break;
                            }
                        case 10:
                            {
                                string resid;
                                cout << "Enter your resource id:" << endl;
                                while(1)
                                {
                                    cin_check;
                                    cin >>resid;
                                    if(mylib.VerifyResource(resid))
                                        break;
                                    cout << "No such Resource exists. Try again." << endl;
                                }
                                Resource* res = mylib.search_by_Id(resid);
                                res->gethistory(mylib);
                                break;
                            }
                        case 11:
                            {
                                cout << "Enter resource id" << endl;
                                string ResId;
                                int try_ = 5;
                                while(try_--)
                                {
                                    cin_check;cin >> ResId;
                                    if(mylib.VerifyResource(ResId))
                                       break;
                                    cout << "Invalid Id. Try again:" << endl;
                                }
                                if(try_ == -1)
                                {
                                    cout << "wrong input..." << endl;
                                    break;
                                }
                                string UserId;
                                cout << "Input User ID: ";
                                while(1)
                                {
                                    cin_check;cin >> UserId;
                                    if(mylib.VerifyMemberId(UserId) && UserId[0] != 'S')
                                       break;
                                    if(UserId[0] == 'S')
                                        cout << "Staff cannot issue any resource!" << endl;
                                    else
                                        cout << "Invalid Id. Try again:" << endl;
                                }
                                staff->IssueResource(UserId, ResId, mylib);
                                break;
                            }
                        case 12:
                            {
                                cout << "Enter resource id" << endl;
                                string ResId;
                                int try_ = 5;
                                while(try_--)
                                {
                                    cin_check;cin >> ResId;
                                    if(mylib.VerifyResource(ResId))
                                       break;
                                    cout << "Invalid Id. Try again:" << endl;
                                }
                                if(try_ == -1)
                                {
                                    cout << "Wrong input " << endl;break;
                                }
                                string UserId;
                                cout << "Enter User ID: " << endl;
                                while(1)
                                {
                                    cin_check;cin >> UserId;
                                    if(mylib.VerifyMemberId(UserId))
                                       break;
                                    cout << "Invalid Id. Try again:" << endl;
                                }
                                staff->ReturnResource(UserId, ResId, mylib);
                                break;
                            }
                        case 13:
                            {
                                string UserId;
                                cout << "Enter User ID: ";
                                cin >> UserId;
                                if(UserId == staff->getId())
                                {
                                    cout << "You cannot delete yourself" << endl;
                                    break;
                                }
                                if(UserId == "Sadmin")
                                {
                                    cout << "You cannot delete Admin GOD" << endl;
                                    break;
                                }
                                mylib.RemoveMember(UserId);
                                break;
                            }
                        case 14:
                            {
                                string Resid;
                                cout << "Enter Resource ID: ";
                                cin >> Resid;
                                mylib.RemoveResource(Resid);
                                break;
                            }
                        case 15:
                            {
                                goto outofthisloop;
                            }
                        default:
                            {
                                cout << "Invalid input" << endl;
                                break;
                            }
                        }
                        //char ch;
                        cout << "Enter to continue" << endl;
                        cin_check;
                        cin.ignore(INT_MAX, '\n');
                        cin.get();
                        cin.ignore(INT_MAX, '\n');
                        //cin >> ch;
                    }
                    break;
                }
            case 'N':
                {
                    NonPhd* nphd = mylib.Login_as_Non_Phd(Id);
                    if(!nphd)
                    {
                        cout << "Invalid Id:" << endl;
                        break;
                    }
                    while(1){
                        system("CLS");
                        cout << "1. See your history" << endl;
                        cout << "2. View Profile" << endl;
                        cout << "3. Edit your profile" << endl;
                        cout << "4. Pay fine" << endl;
                        cout << "5. Search book/Journal" << endl;
                        cout << "6. Log out" << endl;
                        int option;cin_check;
                        cin >> option;
                        cout << endl;
                        switch(option)
                        {
                        case 1:
                            {
                                nphd->getHistory();
                                break;
                            }
                        case 2:
                            {
                                nphd->view_my_profile();
                                break;
                            }
                        case 3:
                            {
                                nphd->edit_my_profile();
                                break;
                            }
                        case 4:
                            {
                                nphd->payfine();
                                break;
                            }
                        case 5:
                            {
                                system("CLS");
                                cout << "1. Search by id" << endl;
                                cout << "2. Search by Title" << endl;
                                cout << "3. Search by Author" << endl;
                                cout << "4. Search by Tag" << endl;
                                int option;
                                cout << "Select appropriately" << endl;
                                cin_check;cin >> option;
                                switch(option)
                                {
                                case 1:
                                    {
                                        cout << "Enter Id";
                                        string Resid;
                                        cin_check;
                                        cin >> Resid;
                                        Resource* res = mylib.search_by_Id(Resid);
                                        if(!res)
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        else
                                            res->getdetails();
                                        break;
                                    }
                                case 2:
                                    {
                                        cout << "Enter Title";
                                        string Title;
                                        cin_check;
                                        cin >> Title;
                                        set<Resource*> res = mylib.search_by_Title(Title);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 3:
                                    {
                                        cout << "Enter author";
                                        string author;
                                        cin_check;
                                        cin >> author;
                                        set<Resource*> res = mylib.search_by_author(author);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 4:
                                    {
                                        cout << "Enter tags. Press y when done." << endl;
                                        vector<string> tag;
                                        cin_check;
                                        string br = "y";
                                        while(1)
                                        {
                                            string tg;
                                            cin >> tg;
                                            if(tg == br)
                                                break;
                                            tag.push_back(tg);
                                        }
                                        set<Resource*> res = mylib.search_by_tag(tag);
                                        if(res.empty())
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                default:
                                    {
                                        cout << "Invalid Input" << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                        case 6:
                            {
                                goto outofthisloop;
                                break;
                            }
                        }
                        cout << "Enter to continue" << endl;
                        cin_check;
                        cin.ignore(INT_MAX, '\n');
                        cin.get();
                        cin.ignore(INT_MAX, '\n');
                    }
                    break;
                }
            case 'P':
                {
                    Phd* phd = mylib.Login_as_Phd(Id);
                    if(!phd)
                    {
                        cout << "Invalid Id" << endl;
                        break;
                    }
                    while(1){
                        system("CLS");
                        cout << "1. See your history" << endl;
                        cout << "2. View Profile" << endl;
                        cout << "3. Edit your profile" << endl;
                        cout << "4. Pay fine" << endl;
                        cout << "5. Renew book" << endl;
                        cout << "6. Search book/Journal" << endl;
                        cout << "7. Log out" << endl;
                        int option;cin_check;
                        cin >> option;
                        switch(option)
                        {
                        case 1:
                            {
                                phd->getHistory();
                                break;
                            }
                        case 2:
                            {
                                phd->view_my_profile();
                                break;
                            }
                        case 3:
                            {
                                phd->edit_my_profile();
                                break;
                            }
                        case 4:
                            {
                                phd->payfine();
                                break;
                            }
                        case 5:
                            {
                                cout << "Input the Resource Id that you want to renew" << endl;
                                string Resid;
                                cin_check;
                                cin >> Resid;
                                phd->RenewResource(Resid);
                                break;
                            }
                        case 6:
                            {
                                system("CLS");
                                cout << "1. Search by id" << endl;
                                cout << "2. Search by Title" << endl;
                                cout << "3. Search by Author" << endl;
                                cout << "4. Search by Tag" << endl;
                                int option;
                                cout << "Select appropriately" << endl;
                                cin_check;cin >> option;
                                switch(option)
                                {
                                case 1:
                                    {
                                        cout << "Enter Id";
                                        string Resid;
                                        cin_check;
                                        cin >> Resid;
                                        Resource* res = mylib.search_by_Id(Resid);
                                        if(!res)
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        else
                                            res->getdetails();
                                        break;
                                    }
                                case 2:
                                    {
                                        cout << "Enter Title";
                                        string Title;
                                        cin_check;
                                        cin >> Title;
                                        set<Resource*> res = mylib.search_by_Title(Title);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 3:
                                    {
                                        cout << "Enter author";
                                        string author;
                                        cin_check;
                                        cin >> author;
                                        set<Resource*> res = mylib.search_by_author(author);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 4:
                                    {
                                        cout << "Enter tags. Press y when done." << endl;
                                        vector<string> tag;
                                        cin_check;
                                        string br = "y";
                                        while(1)
                                        {
                                            string tg;
                                            cin >> tg;
                                            if(tg == br)
                                                break;
                                            tag.push_back(tg);
                                        }
                                        set<Resource*> res = mylib.search_by_tag(tag);
                                        if(res.empty())
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                default:
                                    {
                                        cout << "Invalid Input" << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                        case 7:
                            {
                                goto outofthisloop;
                                break;
                            }
                        }
                        cout << "Enter to continue" << endl;
                        cin_check;
                        cin.ignore(INT_MAX, '\n');
                        cin.get();
                        cin.ignore(INT_MAX, '\n');
                    }
                    break;
                }
            case 'F':
                {
                    Faculty* faculty = mylib.Login_as_Faculty(Id);
                    if(!faculty)
                    {
                        cout << "Invalid Id" << endl;
                        break;
                    }
                    while(1){
                        system("CLS");
                        cout << "1. See your history" << endl;
                        cout << "2. View Profile" << endl;
                        cout << "3. Edit your profile" << endl;
                        cout << "4. Pay fine" << endl;
                        cout << "5. Renew book" << endl;
                        cout << "6. Search Book/Journal" << endl;
                        cout << "7. Log out" << endl;
                        int option;cin_check;
                        cin >> option;
                        switch(option)
                        {
                        case 1:
                            {
                                faculty->getHistory();
                                break;
                            }
                        case 2:
                            {
                                faculty->view_my_profile();
                                break;
                            }
                        case 3:
                            {
                                faculty->edit_my_profile();
                                break;
                            }
                        case 4:
                            {
                                faculty->payfine();
                                break;
                            }
                        case 5:
                            {
                                cout << "Input the Resource Id that you want to renew" << endl;
                                string Resid;
                                cin_check;
                                cin >> Resid;
                                faculty->RenewResource(Resid);
                                break;
                            }
                        case 6:
                            {
                                system("CLS");
                                cout << "1. Search by id" << endl;
                                cout << "2. Search by Title" << endl;
                                cout << "3. Search by Author" << endl;
                                cout << "4. Search by Tag" << endl;
                                int option;
                                cout << "Select appropriately" << endl;
                                cin_check;cin >> option;
                                switch(option)
                                {
                                case 1:
                                    {
                                        cout << "Enter Id";
                                        string Resid;
                                        cin_check;
                                        cin >> Resid;
                                        Resource* res = mylib.search_by_Id(Resid);
                                        if(!res)
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        else
                                            res->getdetails();
                                        break;
                                    }
                                case 2:
                                    {
                                        cout << "Enter Title";
                                        string Title;
                                        cin_check;
                                        cin >> Title;
                                        set<Resource*> res = mylib.search_by_Title(Title);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 3:
                                    {
                                        cout << "Enter author";
                                        string author;
                                        cin_check;
                                        cin >> author;
                                        set<Resource*> res = mylib.search_by_author(author);
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                case 4:
                                    {
                                        cout << "Enter tags. Press y when done." << endl;
                                        vector<string> tag;
                                        cin_check;
                                        string br = "y";
                                        while(1)
                                        {
                                            string tg;
                                            cin >> tg;
                                            if(tg == br)
                                                break;
                                            tag.push_back(tg);
                                        }
                                        set<Resource*> res = mylib.search_by_tag(tag);
                                        if(res.empty())
                                        {
                                            cout << "No such resource exists" << endl;
                                            break;
                                        }
                                        for(set<Resource*>::iterator it = res.begin(); it != res.end(); it++)
                                        {
                                            (*it)->getdetails();
                                        }
                                        break;
                                    }
                                default:
                                    {
                                        cout << "Invalid Input" << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                        case 7:
                            {
                                goto outofthisloop;
                                break;
                            }
                        }
                        cout << "Enter to continue" << endl;
                        cin_check;
                        cin.ignore(INT_MAX, '\n');
                        cin.get();
                        cin.ignore(INT_MAX, '\n');
                    }
                    break;
                }
            default:
                {
                    cout << "Wrong Id" << endl;
                    break;
                }
            }
            cout << "Enter to continue" << endl;
            cin_check;
            cin.ignore(INT_MAX, '\n');
            cin.get();
            cin.ignore(INT_MAX, '\n');
            outofthisloop:;
            cout << "Successfully logged out!" << endl;
            savedata(mylib);
        }
    }
    catch(...)
    {
        system("CLS");
        cout << "Sorry there seems to be some technical error.\nDo not panic we'll fix it!" << endl;
    }
    return 0;
}
