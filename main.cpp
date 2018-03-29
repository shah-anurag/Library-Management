#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

class Resource;
class Member;
class IssuedBy;

class Library
{
    string name;
    long PhoneNumber;
    vector<Resource*> resources;
    vector<Member*> member;

public:
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
    Resource search_by_Id(string Id);
    Resource* search_by_tag(string tags[]);
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
        string Edition;
        string date_of_purchase;
        double rack_num;
        bool status;
        vector<IssuedBy*> history;
    public:
        bool getStatus();
        string getAuthor();
        string getTitle();
        string getId();
        string getDateOfPurchase();
        double getRackNumber();
        string GetEdition();        //CORRECTION
        void change_status(bool status);
        void update_history(string UserId, string IssueDate, bool status, int days);
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
string Resource::GetEdition()
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
    void Update();
    void AddSubject();
    void DeleteSubject(string subject);
    string getSubjectName();
    int getSubjectCode();
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
        string edition;
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
void DeleteSubject(string subject);
string getSubjectName();
int getSubjectCode();

class Journal: private Resource
{
    string PublicationDate;
    vector<string> topic;

public:
    void Update();
    void AddTopic(string topic);
    void DeleteTopic(string topic);
    string getPublicDate()
    {
        return PublicationDate;
    }
    void getTopic(); // CORRECTION
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
        string edition;
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

void Journal::getTopic()
{
    cout << "Topics: ";
    for(int i = 0; i < topic.size(); i++) cout << topic[i] << " , ";
    cout << endl;
    return;
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
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
    void edit_password();
};

class Staff: public Member
{
public:
    void ViewProfile(string Id);    //CORRECTION
    bool IssueResource(string UserId, string ResourceId);
    void ReturnResoure(string UserId, string ResId);
    void CollectFine(string studId, long fine);
    void UpdateHistory(string UserId, string ResId);
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
    vector<BookIssued> *v;
protected:
    string Department;
    int num_of_books_issued;
public:
    void editDepartment(string dep);
    void payfine();
    void inc_num_of_books();
    void dec_num_of_books();
    int getBooksIssued();
    void getHistory();      //CORRECTION
    void updateHistory(string Resid);
    void change_history_status(string ResId, string Date);
};

class Student: public User
{
    static const int MaxBookLimit;
public:
    int getBookLimit();
    bool isEligible(string BookId);
};

const int Student::MaxBookLimit = 5;

class Faculty: public User
{
    int maxBookLimit;
    int maxJournalLimit;
    int NumOfJournalsIssued;
public:
    void SuggestResource();
    int getBookLimit();
    int getJournalLimit();
    bool isEligible(string BookId);
    void inc_num_of_journals();
    void dec_num_of_journals();
};

class NonPhd: public Student
{
    int year;
public:
    int getYear();
    int editYear();
};

class Phd:public Student
{
    int maxJournalLimit;
public:
    void getMaxJournalLimit();
    void inc_num_of_journals();
    void dec_num_of_journals();
};

int main()
{

}
