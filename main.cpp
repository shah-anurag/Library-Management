#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
#include<sstream>

using namespace std;

class Resource;
class Member;
class IssuedBy;
class Phd;
class NonPhd;

class Library
{
    string name;
    long PhoneNumber;
    vector<Resource*> resources;
    vector<Phd*> phd;
    vector<NonPhd*> nphd;
    vector<Member*> member;

public:
    Library(string name, long PhoneNumber): name(name), PhoneNumber(PhoneNumber){}
    string getLibraryName()
    {
        return name;
    }
    long getPhoneNum()
    {
        return PhoneNumber;
    }
    bool VerifyMemberId(string Id);
    bool VerifyResource(string Id);
    bool CheckLimit(string Id);
    void AddMember();
    void AddNewResource();
    void RemoveMember(string Id);
    void RemoveResource(string Id);
    Resource* search_by_author(string author);
    Resource* search_by_Title(string title);
    Resource* search_by_Id(string Id);
    set<Resource*> search_by_tag(const vector<string> &tags);   //CORRECTION
    void ViewAllMembers();
    void ViewAllResource();
    bool RenewBook(string userId, string resId);
};

class Resource
{
    protected:
        string author;
        string title;
        string Id;
        int Edition;
        string date_of_purchase;
        double rack_num;
        bool status;
        vector<IssuedBy*> history;
    public:
        Resource(string author,string title,string Id,string DateOfPurchase, int Edition, bool status, double RackNumber):
            author(author), title(title), Id(Id), date_of_purchase(DateOfPurchase), Edition(Edition), status(status), rack_num(RackNumber){}
        bool getStatus();
        string getAuthor();
        string getTitle();
        string getId();
        string getDateOfPurchase();
        double getRackNumber();
        int GetEdition();        //CORRECTION
        void change_status(bool status);
        void update_history(string UserId, string IssueDate, bool status, int days);
        virtual vector<string> getTopic() = 0;
};

class IssuedBy
{
    string Id;
    string IssueDate;
    int IssueFor;
public:
    IssuedBy(string Id, string IssueDate): Id(Id), IssueDate(IssueDate){}
    string getId();
    string getIssueDate();
    int getNumOfDays();
    void EditId();
    void EditIssueDate(string);       //CORRECTION
    void setDays(int);
};

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
    vector<IssuedBy*>::iterator it = history.begin();
    while(it != history.end() && strcmp((*it)->getIssueDate().c_str(),UserId.c_str()) == 0)
        it++;
    if(it == history.end())
    {
        IssuedBy* issuedby = new IssuedBy(UserId, IssueDate);
        history.push_back(issuedby);
        Resource::change_status(true);
        return;
    }
    (*it)->IssuedBy::EditIssueDate(IssueDate);
    (*it)->IssuedBy::setDays(days);
    Resource::change_status(status);
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
    cin >> Id;
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
    int SubjectCode;
    string name;

public:
    Book(string author,string title,string Id,string DateOfPurchase,int Edition,bool status,double RackNumber,string SubjectName,int SubCode):
    Resource(author, title, Id, DateOfPurchase, Edition, status, RackNumber), SubjectCode(SubjectCode), name(title){}
    void Update();
    void AddSubject();
    void DeleteSubject(string subject);
    string getSubjectName();
    int getSubjectCode();
    vector<string> getTopic();
};

void Book::Update()
{
    char update;
    cout << "Author: " << getAuthor() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
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
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string title;
        cout << "Enter the Title: ";
        cin >> title;
        Resource::title = title;
    }
    cout << "Edition: " << GetEdition() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else
    {
        int edition;
        cout << "Enter the Edition: ";
        cin >> edition;
        Resource::Edition = edition;
    }
    cout << "Date of Purchase: " << getDateOfPurchase() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string date;
        cout << "Enter the date of purchase: ";
        cin >> date;
        Resource::date_of_purchase = date;
    }
    cout << "Rack number: " << getRackNumber() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        double rack;
        cout << "Enter the rack number: ";
        cin >> rack;
        Resource::rack_num = rack;
    }
    cout << "Subject Code: " << SubjectCode << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        int sub_code;
        cout << "Enter the subject code: ";
        cin >> sub_code;
        Book::SubjectCode = sub_code;
    }
    cout << "Subject Name: " << Book::name;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string name;
        cout << "Enter the name of Book: ";
        cin >> name;
        Book::name = name;
    }
    cout << "\nUpdated!\n";
    return;
}
void Book::AddSubject()
{

}
vector<string> Book::getTopic()
{
    vector<string> topic;
    topic.push_back(name);
    std::ostringstream stm ;
    stm << SubjectCode;
    topic.push_back(stm.str());
    return topic;
}
void DeleteSubject(string subject);
string getSubjectName();
int getSubjectCode();

class Journal: public Resource
{
    string PublicationDate;
    vector<string> topic;

public:
    Journal(string author,string title,string Id,string DateOfPurchase,int Edition,bool status,double RackNumber,string PublicationDate,vector<string> topic):
    Resource(author, title, Id, DateOfPurchase, Edition, status, RackNumber),PublicationDate(PublicationDate)
    {
        int idx = 0;
        string last = "y";
        while(topic[idx] != last)
            Journal::topic[idx] = topic[idx++];
    }
    void Update();
    void AddTopic(string topic);
    void DeleteTopic(string topic);
    string getPublicDate()
    {
        return PublicationDate;
    }
    vector<string> getTopic();
};

void Journal::Update()
{
    char update;
    cout << "Author: " << getAuthor() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
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
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string title;
        cout << "Enter the Title: ";
        cin >> title;
        Resource::title = title;
    }
    cout << "Edition: " << GetEdition() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input";
        return;
    }
    else
    {
        int edition;
        cout << "Enter the Edition: ";
        cin >> edition;
        Resource::Edition = edition;
    }
    cout << "Date of Purchase: " << getDateOfPurchase() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string date;
        cout << "Enter the date of purchase: ";
        cin >> date;
        Resource::date_of_purchase = date;
    }
    cout << "Rack number: " << getRackNumber() << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        double rack;
        cout << "Enter the rack number: ";
        cin >> rack;
        Resource::rack_num = rack;
    }
    cout << "Publication date : " << PublicationDate << endl;
    cout << "Update? Enter y or n: ";
    cin >> update;
    if(update != 'y' || update != 'n')
    {
        cout << "Invalid input ";
        return;
    }
    else
    {
        string pub_date;
        cout << "Enter the publication date: ";
        cin >> pub_date;
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
    cout << "Enter Topics you want to add:\n";
    cout << "Enter y when you are done:)\n";
    while(1)
    {
        string topic;
        cout << "Enter topic: ";
        cin >> topic;
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
        cout << topic << " Already Exists\n";
    }
    return;
}

void Journal::DeleteTopic(string topic)
{
    Journal::getTopic();
    auto it = find(Journal::topic.begin(), Journal::topic.end(), topic);
    if(it == Journal::topic.end())
    {
        cout << "Topic does not exist\n";
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
    string JoinDate;
    string Id;
    long ph_num;
    string address;
    string password;
    string emailId;
public:
    Member(string name, string JoinDate, string Id, long ph_num, string password, string address = "", string emailId = ""):
        name(name), JoinDate(JoinDate), ph_num(ph_num), address(address), password(password), emailId(emailId){}
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
    virtual int getJournalsIssued() = 0;
    void edit_password();
    string getId()
    {
        return Id;
    }
    virtual int getBooksIssued() = 0;
};

class Staff: public Member
{
public:
    void ViewProfile(string Id);    //CORRECTION
    bool IssueResource(string UserId, string ResourceId);
    void ReturnResoure(string UserId, string ResId);
    void CollectFine(string studId, long fine);
    void UpdateHistory(string UserId, string ResId);
    int getJournalsIssued()
    {
        return 0;
    }
    void view_my_profile()
    {

    }
    void edit_my_profile()
    {

    }
};

class BookIssued
{
    string BookId;
    string BookName;
    string Author;
    bool Status;
    string IssueDate;
    string ReturnDate;
    long Fine;
    long FinePaid;
    bool renew;

public:
    void getDetails();
    void setReturnDate(string Date);
    long CalculateFine();
    void AcceptFine(long fine);
    bool isRenew();
    void ChangeRenew();
};

class User: public Member
{
private:
    vector<BookIssued*> history;
protected:
    string Department;
    int num_of_books_issued;
public:
    User(string name, string JoinDate, string Id, long ph_num, string password, string Department, string address = "", string emailId = "")
    :Department(Department), num_of_books_issued(0), Member(name, JoinDate, Id, ph_num, address, password, emailId){}
    void editDepartment(string dep);
    void payfine();
    void inc_num_of_books();
    void dec_num_of_books();
    int getBooksIssued()
    {
        return num_of_books_issued;
    }
    void getHistory();      //CORRECTION
    void updateHistory(string Resid);
    void change_history_status(string ResId, string Date);
    virtual int getJournalsIssued() = 0;
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
};

class Student: public User
{
    static const int MaxBookLimit;
public:
    Student(string name, string JoinDate, string Id, long ph_num, string password, string Department, string address = "", string emailId = ""):
     User(name, JoinDate, Id, ph_num, address, password, emailId, Department){}
    static int getBookLimit()
    {
        return MaxBookLimit;
    }
    bool isEligible(string BookId);
    virtual int getJournalsIssued() = 0;
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
};

const int Student::MaxBookLimit = 5;

class Faculty: public User
{
    static int maxBookLimit;
    static int maxJournalLimit;
    int NumOfJournalsIssued;
public:
    Faculty(string name, string JoinDate, string Id, long ph_num, string password, string Department, string address = "", string emailId = ""):
        User(name, JoinDate, Id, ph_num, address, password, emailId, Department), NumOfJournalsIssued(0){}
    void SuggestResource();
    static int getBookLimit()
    {
        return maxBookLimit;
    }
    static int getJournalLimit()
    {
        return maxJournalLimit;
    }
    int getJournalsIssued(){return NumOfJournalsIssued;}
    bool isEligible(string BookId);
    void inc_num_of_journals();
    void dec_num_of_journals();
    void view_my_profile(){}
    void edit_my_profile(){}
};
int Faculty::maxBookLimit = 10;
int Faculty::maxJournalLimit = 10;
class NonPhd: public Student
{
    int year;
public:
    NonPhd(string name, string JoinDate, string Id, long ph_num, string password, string Department, int year, string address = "", string emailId = ""):
    Student(name, JoinDate, Id, ph_num, address, password, emailId, Department), year(year)
    {}
    int getYear();
    int editYear();
    void view_my_profile(){}
    void edit_my_profile(){}
    int getJournalsIssued()
    {
        return 0;
    }
};

class Phd:public Student
{
    static int maxJournalLimit;
    int num_of_journals_issued;
public:
    Phd(string name, string JoinDate, string Id, long ph_num, string password, string Department, string address = "", string emailId = ""):
    Student(name, JoinDate, Id, ph_num, address, password, emailId, Department), num_of_journals_issued(0)
    {}
    static int getMaxJournalLimit()
    {
        return maxJournalLimit;
    }
    int getJournalsIssued(){return num_of_journals_issued;}
    void inc_num_of_journals();
    void dec_num_of_journals();
    void view_my_profile(){}
    void edit_my_profile(){}
};
int Phd::maxJournalLimit = 5;
bool Library::VerifyMemberId(string Id)
{
    auto it = member.begin();
    while(it != member.end())
        if((*it)->getId() == Id)
            return true;
    return false;
}
bool Library::VerifyResource(string Id)
{
    auto it = resources.begin();
    while(it != resources.end())
        if((*it)->getId() == Id)
            return true;
    return false;
}
bool Library::CheckLimit(string Id)
{
    Member* current = nullptr;
    auto it = member.begin();
    while(it != member.end())
    {
        if((*it)->getId() == Id)
        {
            current = *it;
            break;
        }
        it++;
    }
    if(it == member.end())
    {
        cout << "Invalid Id\n";
        return false;
    }
    if(Id[0] == 'S' && Id[1] == 'N')
    {
        return Student::getBookLimit()>current->getBooksIssued();
    }
    else if(Id[0] == 'S' && Id[1] == 'P')
    {
        cout << "You want to check limit for\n1. Journal\n2.Book\nPress 1 or 2";
        char ch;
        cin >> ch;
        if(ch == '1')
            return Phd::getMaxJournalLimit() > current->getJournalsIssued();
        else if(ch == '2')
            return Student::getBookLimit()>current->getBooksIssued();
        else {
                cout << "Invalid Input\n";
                return false;
        }
    }
    else if(Id[0] == 'F')
    {
        cout << "You want to check limit for\n1. Journal\n2.Book\nPress 1 or 2";
        char ch;
        cin >> ch;
        if(ch == '1')
            return Faculty::getJournalLimit() > current->getJournalsIssued();
        else if(ch=='2')
            return Faculty::getBookLimit() > current->getBooksIssued();
        else{
                cout << "Invalid Input\n";
                return false;
        }
    }
    else
    {
        cout << "Invalid Id\n";
    }
}
void Library::AddMember()
{
    Member* mem = nullptr;
    cout << "1 Phd Student\n2 NonPhd Student\n 3Faculty\n Select kr le\n";
    int x;
    cin >> x;
    switch(x)
    {
    case 1:
        {
            string name, JoinDate, Id, address = "", password, emailId = "", department;
            long ph_num;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter Id: ";
            cin >> Id;
            cout << "Enter phone number: ";
            cin >> ph_num;
            cout << "Enter address: ";
            cin >> address;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter email id: ";
            cin >> emailId;
            cout << "Enter Department: ";
            cin >> department;
            mem = new Phd(name, JoinDate, Id, ph_num, password, department, address, emailId);
            member.push_back(mem);
            break;
        }
    case 2:
        {
            string name, JoinDate, Id, address = "", password, emailId = "", department;
            long ph_num;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter Id: ";
            cin >> Id;
            cout << "Enter phone number: ";
            cin >> ph_num;
            cout << "Enter address: ";
            cin >> address;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter email id: ";
            cin >> emailId;
            cout << "Enter Department: ";
            cin >> department;
            mem = new NonPhd(name, JoinDate, Id, ph_num, password, department, 1, address, emailId);
            member.push_back(mem);
            break;
        }
    case 3:
        {
            string name, JoinDate, Id, address = "", password, emailId = "", department;
            long ph_num;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter Id: ";
            cin >> Id;
            cout << "Enter phone number: ";
            cin >> ph_num;
            cout << "Enter address: ";
            cin >> address;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter email id: ";
            cin >> emailId;
            cout << "Enter Department: ";
            cin >> department;
            mem = new Faculty(name, JoinDate, Id, ph_num, password, department, address, emailId);
            member.push_back(mem);
            break;
        }
    default:
        {
            cout << "Invalid Input\n";
            break;
        }
    }
    return;
}
void Library::AddNewResource()
{
    cout << "You want to add\n1book\n2journal\nto the library?\n    \
    Press 1 or 2 and then press enter";
    char ch;
    cin >> ch;
    if(ch == '1')
    {
        string author, title, Id, DateOfPurchase, SubjectName;
        int Edition, SubCode;
        bool status = false;
        double RackNumber;
        cout << "Enter Author: ";
        cin >> author;
        cout << "Enter title: ";
        cin >> title;
        cout << "Enter Id: ";
        cin >> Id;
        cout << "Enter Date of Purchase: ";
        cin >> DateOfPurchase;
        cout << "Enter Subject Name: ";
        cin >> SubjectName;
        cout << "Enter Subject code: ";
        cin >> SubCode;
        cout << "Enter Edition: ";
        cin >> Edition;
        cout << "Enter Rack Number: ";
        cin >> RackNumber;
        resources.push_back(new Book(author, title, Id, DateOfPurchase, Edition, status, RackNumber, SubjectName, SubCode));
    }
    else if(ch == '2')
    {
        string author, title, Id, DateOfPurchase, PubDate;
        int Edition;
        bool status = false;
        double RackNumber;
        cout << "Enter Author: ";
        cin >> author;
        cout << "Enter title: ";
        cin >> title;
        cout << "Enter Id: ";
        cin >> Id;
        cout << "Enter Date of Purchase: ";
        cin >> DateOfPurchase;
        cout << "Enter Publication date: ";
        cin >> PubDate;
        cout << "Enter Edition: ";
        cin >> Edition;
        cout << "Enter Rack Number: ";
        cin >> RackNumber;
        vector<string> topic;
        cout << "Enter the topics related to this journal\nPress ENTER while adding new topic\nPress 'y' when done\n";
        int num_of_topics = 0;
        string last = "y";
        while(1)
        {
            cin >> topic[num_of_topics];
            if(topic[num_of_topics] == last)
                break;
        }
        resources.push_back(new Journal(author, title, Id, DateOfPurchase, Edition, status, RackNumber, DateOfPurchase, topic));
    }
}
void Library::RemoveMember(string Id)
{
    vector<Member*>::iterator it = member.begin();
    while(it != member.end())
    {
        if((*it)->getId() == Id)
        {
            delete *it;
            member.erase(it);
            cout << "Successfully deleted!\n";
            return;
        }
        it++;
    }
    cout << "No such member exists\n";
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
            cout << "Successfully deleted!\n";
            return;
        }
        it++;
    }
    cout << "No such Book/Journal exists\n";
    return;
}
Resource* Library::search_by_author(string author)
{
    vector<Resource*>::iterator it = resources.begin();
    while(it != resources.end())
    {
        if((*it)->getAuthor() == author)
        {
            return *it;
        }
        it++;
    }
    cout << "No such Book/Journal exists\n";
    return nullptr;
}
Resource* Library::search_by_Title(string title)
{
    vector<Resource*>::iterator it = resources.begin();
    while(it != resources.end())
    {
        if((*it)->getTitle() == title)
        {
            return *it;
        }
        it++;
    }
    cout << "No such Book/Journal exists\n";
    return nullptr;
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
    cout << "No such Book/Journal exists\n";
    return nullptr;
}
set<Resource*> Library::search_by_tag(const vector<string> &tags)
{
    vector<Resource*>::iterator it = resources.begin();
    set<Resource*> matches;
    while(it != resources.end())
    {
        for(auto idx = 0; idx < tags.size(); idx++)
        {
            auto it = resources.begin();
            vector<string> c_tags = (*it)->getTopic();
            for(int i = 0; i < c_tags.size(); i++)
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
        cout << "------------------\n";
    }
}
void Library::ViewAllResource()
{
    auto it = resources.begin();
    while(it != resources.end())
    {
        (*it)->getTitle();
        cout << "------------------\n";
    }
}
bool Library::RenewBook(string userId, string resId)
{
    Resource* resource = search_by_Id(resId);
    Member* member = nullptr;
    for(vector<Member*>::iterator it = Library::member.begin(); it != Library::member.end(); it++)
        if((*it)->getId() == userId)
        {
            member = *it;
            break;
        }
    if(member == nullptr)
    {
        cout << "No such User Exists\n";
        return false;
    }
    if((userId[0] == 'S' && userId[1] == 'P') || userId[0] == 'F')
    {
        //if()
    }
    return false;
}

int main()
{

}
