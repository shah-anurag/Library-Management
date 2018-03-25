#include<iostream>
#include<vector>

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
        int GetEdition();
        void change_status(bool status);
        void update_history(string UserId, string IssueDate, bool status, int days);
};

class IssuedBy
{
    string Id;
    string IssueDate;
    int IssueFor;
public:
    string getId();
    string getIssueDate();
    int getNumOfDays();
    void EditId();
    string EditIssueDate();
};

class Book: private Resource
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
