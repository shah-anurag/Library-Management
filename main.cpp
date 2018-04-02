#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
#include<limits.h>
#include<stdlib.h>
#include<sstream>
#include<iomanip>

#define cin_check if(cin.fail()){cin.clear();cin.ignore(INT_MAX, '\n');}

using namespace std;

bool first = 1;

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
    Phd* get_user_phd(string UserId);
    NonPhd* get_user_nonphd(string UserId);
    Faculty* get_user_faculty(string UserId);
    Staff* get_user_staff(string UserId);
    NonPhd* Login_as_Non_Phd(string);
    Phd* Login_as_Phd(string);
    Staff* Login_as_Staff(string);
    Faculty* Login_as_Faculty(string);
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
        Resource(string author,string title,string Id,string DateOfPurchase, int Edition, double RackNumber):
            author(author), title(title), Id(Id), date_of_purchase(DateOfPurchase), Edition(Edition), rack_num(RackNumber)
            {
                status = true;
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
    int SubjectCode;
    string name;

public:
    Book(string author,string title,string Id,string DateOfPurchase,int Edition,double RackNumber,string SubjectName,int SubCode):
    Resource(author, title, Id, DateOfPurchase, Edition, RackNumber), SubjectCode(SubjectCode), name(title){}
    void Update();
    void AddSubject();
    void DeleteSubject(string subject);
    string getSubjectName();
    int getSubjectCode();
    vector<string> getTopic();
    void getdetails();
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
        cout << "Enter the date of purchase: ";
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
    cout << "\nUpdated!\n";
    return;
}
void Book::AddSubject()                             //Implement
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
    Journal(string author,string title,string Id,string DateOfPurchase,int Edition,double RackNumber,string PublicationDate,vector<string> topic):
    Resource(author, title, Id, DateOfPurchase, Edition, RackNumber),PublicationDate(PublicationDate)
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
    void getdetails();
};


void Journal::getdetails()
{
    cout << "Author: " << getAuthor() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Id: " << getId() << endl;
    cout << "Topics: " << endl;
    for(int i = 0; i < topic.size(); i++) cout << i+1 << " " << topic[i] << endl;
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
        cout << "Enter the date of purchase: ";
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
    cout << "Enter Topics you want to add:\n";
    cout << "Enter y when you are done:)\n";
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
    long long ph_num;
    string address;
    string password;
    string emailId;
public:
    Member(string name, string JoinDate, string Id, long long ph_num, string password, string address = "", string emailId = ""):
        name(name), Id(Id), JoinDate(JoinDate), ph_num(ph_num), address(address), password(password), emailId(emailId){}
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
    BookIssued(Resource* Res)
    {
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
            cout << "Invalid input\nTry again\n";
        }
        ReturnDate = "";
    }
    void getDetails();
    string getId(){return BookId;}
    void setReturnDate(string UserId, string Date);             //CORRECTION
    long long CalculateFine(string);                                 //CORRECTION
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
    cout << "Id: " << setw(10) << BookId << endl;
    cout << "Title: " << setw(10) << BookName << endl;
    cout << "Author: " << setw(10) << Author << endl;
    cout << "Status: " << setw(10) << Status << endl;
    cout << "Issue date: " << setw(10) << IssueDate << endl;
    cout << "Return date: " << setw(10) << ReturnDate << endl;
    cout << "Fine: " << setw(10) << Fine << endl;
    cout << "Fine Paid: " << setw(10) << FinePaid << endl;
    renew? cout << "Renewed\n": cout << "Non Renewed\n";
    return;
}
void BookIssued::setReturnDate(string UserId, string Date)
{
    ReturnDate = Date;
    Fine = CalculateFine(UserId);
}
long long BookIssued::CalculateFine(string UserId)
{
    int year = 0, month = 0, days = 0;
    string y,m,d;
    bool undo = 0;
    if(ReturnDate == "")
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
    cout << "RETURN DATE\n";
    cout << days << " " << month << " " << year << endl;
    int issue_year = 0, issue_month = 0, issue_day = 0;
    string y1,m1,d1;
    for(int i = 0; i < 2; i++) d1.push_back(IssueDate[i]);
    for(int i = 3; i < 5; i++) m1.push_back(IssueDate[i]);
    for(int i = 6; i < 10; i++) y1.push_back(IssueDate[i]);
    stringstream iconvert_days(d1), iconvert_month(m1), iconvert_year(y1);
    iconvert_days >> issue_day;
    iconvert_month >> issue_month;
    iconvert_year >> issue_year;
    int days_kept = 0;
    int cur_day = issue_day, cur_mon = issue_month, cur_year = issue_year;
    int d30[] = {4,6,9,11};
    while(issue_day != days && issue_month != month && issue_year != year)
    {
        days_kept++;
        cur_day++;
        if(cur_mon == 2 && cur_day == 29)
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
    }
    if(undo)
    {
        ReturnDate = "";
    }
    return max((days_kept-max_days*((int)isRenew()+1))*5,0);
}
void BookIssued::AcceptFine(long long fine)
{
    FinePaid = min(fine, Fine);
    if(fine > Fine)
    {
        cout << "Extra amount worth Rs " << fine-Fine << " paid. Please take it back!\n";
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
    :Department(Department), num_of_books_issued(0), Member(name, JoinDate, Id, ph_num, address, password, emailId){}
    void editDepartment(string dep);
    void payfine();
    void payfine(int);                                          //CORRECTION
    void inc_num_of_books(){num_of_books_issued++;}
    void dec_num_of_books(){num_of_books_issued--;}
    int getBooksIssued()
    {
        return num_of_books_issued;
    }
    void getHistory();      //CORRECTION
    void updateHistory(string Resid, Library &);
    void change_history_status(string ResId, string Date);
    void RenewResource(string ResId);
    virtual int getJournalsIssued() = 0;
    virtual void view_my_profile() = 0;
    virtual void edit_my_profile() = 0;
};

void User::getHistory()
{
    vector<BookIssued*>::iterator it = history.begin();
    while(it != history.end())
    {
        (*it)->getDetails();
        it++;
    }
}

void User::updateHistory(string Resid, Library &lib)
{
    Resource* res = lib.search_by_Id(Resid);
    history.push_back(new BookIssued(res));
    return;
}
void User::RenewResource(string ResId)
{
    if(getId()[0] == 'N')
    {
        cout << "You cannot renew :'(\n";
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
                        cout << "Renewed!\n";
                        return;
                    }
                    break;
                }
            }
        }
    }
    cout << "Cannot Renew:(\n";
    return;
}

void User::payfine(int fine)
{
    vector<BookIssued*>::iterator it = history.begin();
    long long int sum = fine;
    while(it != history.end())
    {
        sum += (*it)->CalculateFine(getId());
        it++;
        (*it)->getDetails();
        it++;
    }
    it--;
    while(sum && it != history.begin()-1)
    {
        (*it)->AcceptFine(min(sum, (*it)->CalculateFine(getId())));
        sum -= min(sum, (*it)->CalculateFine(getId()));
        (*it)->getDetails();
        it--;
    }
    if(sum > 0)
    {
        cout << "Extra money Rs. " << sum << " paid. Please take it back :)\n";
    }
    return;
}

void User::payfine()
{
    vector<BookIssued*>::iterator it = history.begin();
			long long int sum = 0;
			while(it != history.end())
			{
				sum += (*it)->CalculateFine(getId());
				(*it)->getDetails();
				//cout << " Fine = " << (*it)->CalculateFine(getId()) << "\n";
				it++;
			}
			cout << "Total fine = " << sum << endl;
			cout << "Enter amount paid\n";
			cin_check;cin >> sum;
			it--;
			while(sum && it != history.begin()-1)
			{
				(*it)->AcceptFine(min(sum, (*it)->CalculateFine(getId())));
				sum -= min(sum, (*it)->CalculateFine(getId()));
				(*it)->getDetails();
				cout << " Fine = " << (*it)->CalculateFine(getId()) << "\n";
				it--;
			}
			if(sum > 0)
			{
				cout << "Extra money Rs. " << sum << " paid\n";
			}
			return;
}

void User::change_history_status(string ResId, string Date)
{
    vector<BookIssued*>::iterator it = history.begin();
    while(it != history.end())
    {
        if((*it)->getId() == ResId)
        {
            (*it)->setStatus(!(*it)->getStatus());
            (*it)->CalculateFine(ResId);
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
     User(name, JoinDate, Id, ph_num, address, password, emailId, Department){}
    static int getBookLimit()
    {
        return MaxBookLimit;
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
    int NumOfJournalsIssued;
public:
    Faculty(string name, string JoinDate, string Id, long long ph_num, string password, string Department, string address = "", string emailId = ""):
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
    void view_my_profile();
    void edit_my_profile();
};
int Faculty::maxBookLimit = 10;
int Faculty::maxJournalLimit = 10;

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
    cout << "\n-------------------------------------\n";
    cout << "name: " << setw(10) << name << endl;
    cout << "Id: " << setw(10) << Id << endl;
    cout << "Phone number: " << setw(10) << ph_num << endl;
    cout << "Address: " << setw(10) << address << endl;
    cout << "Email Id: " << setw(10) << emailId << endl;
    cout << "Department: " << setw(10) << Department << endl;
    cout << "---------------------------------------\n";
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
    else
    {
        string cur_name;
        cout << "Enter your name: ";
        cin_check;cin >> cur_name;
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
    else
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
    else
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
    else
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
    else
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
    else
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
public:
    NonPhd(string name, string JoinDate, string Id, long long ph_num, string password, string Department, int year, string address = "", string emailId = ""):
    Student(name, JoinDate, Id, ph_num, address, password, emailId, Department), year(year)
    {}
    int getYear();
    int editYear();
    void view_my_profile();
    void edit_my_profile();
    int getJournalsIssued()
    {
        return 0;
    }
};

int NonPhd::getYear()
{
    return year;
}
int NonPhd::editYear()
{
    cout << "Enter your year: ";
    cin_check;cin >> year;
}
void NonPhd::view_my_profile()
{
    cout << "\n-------------------------------------\n";
    cout << "name: " << setw(10) << name << endl;
    cout << "Id: " << setw(10) << Id << endl;
    cout << "Phone number: " << setw(10) << ph_num << endl;
    cout << "Address: " << setw(10) << address << endl;
    cout << "Email Id: " << setw(10) << emailId << endl;
    cout << "Department: " << setw(10) << Department << endl;
    cout << "Year: " << year << endl;                           //-_-
    cout << "---------------------------------------\n";
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
    else
    {
        string cur_name;
        cout << "Enter your name: ";
        cin_check;cin >> cur_name;
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
    else
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
    else
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
    else
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
    else
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
    else
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
public:
    Phd(string name, string JoinDate, string Id, long long ph_num, string password, string Department, string address = "", string emailId = ""):
    Student(name, JoinDate, Id, ph_num, address, password, emailId, Department), num_of_journals_issued(0)
    {}
    static int getMaxJournalLimit()
    {
        return maxJournalLimit;
    }
    int getJournalsIssued(){return num_of_journals_issued;}
    void inc_num_of_journals();
    void dec_num_of_journals();
    void view_my_profile();
    void edit_my_profile();
};
int Phd::maxJournalLimit = 5;

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
    cout << "\n-------------------------------------\n";
    cout << "name: " << setw(10) << name << endl;
    cout << "Id: " << setw(10) << Id << endl;
    cout << "Phone number: " << setw(10) << ph_num << endl;
    cout << "Address: " << setw(10) << address << endl;
    cout << "Email Id: " << setw(10) << emailId << endl;
    cout << "Department: " << setw(10) << Department << endl;
    cout << "---------------------------------------\n";
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
        cin_check;cin >> cur_name;
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
bool Library::CheckLimit(string Id)
{
    if(Id[0] == 'N')
    {
        NonPhd* current = Library::get_user_nonphd(Id);
        if(current)
            return Student::getBookLimit()>current->getBooksIssued();
        throw;
    }
    else if(Id[0] == 'P')
    {
        Phd* current = Library::get_user_phd(Id);
        if(!current) throw;
        cout << "You want to check limit for\n1. Journal\n2.Book\nPress 1 or 2" << endl;
        int ch;
        cin_check;cin >> ch;
        cout << "ch = " << ch << " Student::getBookLimit() = " << Student::getBookLimit() << " current->getBooksIssued() = " << current->getBooksIssued() << endl;
        if(ch == 1)
            return Phd::getMaxJournalLimit() > current->getJournalsIssued();
        else if(ch == 2)
            return Student::getBookLimit()>current->getBooksIssued();
        else {
                cout << "Invalid Input\n";
                return false;
        }
    }
    else if(Id[0] == 'F')
    {
        Faculty* current = Library::get_user_faculty(Id);
        if(!current) throw;
        cout << "You want to check limit for\n1. Journal\n2.Book\nPress 1 or 2";
        char ch;
        cin_check;cin >> ch;
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
    Member* mem = nullptr;
    cout << "1 Phd Student\n2 NonPhd Student\n3Faculty\n4.Staff\nSelect appropriately\n";
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
            cin >> name;
            cout << "Enter Id: ";
            cin_check;
            cin >> Id;
            while(Id[0] != 'P')
            {
                cout << "First alphabet should be 'P'\nTry again.";
                cin_check;cin >> Id;
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
            cin >> name;
            cout << "Enter Id: ";
            cin >> Id;
            while(Id[0] != 'N')
            {
                cout << "First alphabet should be 'N'\nTry again.";
                cin >> Id;
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
            cin >> name;
            cout << "Enter Id: ";
            cin >> Id;
            while(Id[0] != 'F')
            {
                cout << "First alphabet should be 'F'\nTry again.";
                cin >> Id;
            }
            cout << "Enter phone number: ";cin_check;
            cin >> ph_num;
            cout << "Enter address: ";cin_check;cin.ignore(INT_MAX, '\n');
            cin >> address;
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
            cin >> name;
            cout << "Enter Id: ";
            cin_check;
            cin >> Id;
            while(Id[0] != 'S')
            {
                cout << "First alphabet should be 'S'\nTry again.";
                cin >> Id;
            }
            cout << "Enter phone number: ";
            cin_check;
            cin >> ph_num;
            cout << "Enter address: ";
            cin_check;
            cin.ignore(INT_MAX, '\n');
            cin >> address;
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
            cout << "Invalid ID: ID should start with 'B', Try again...\n";
            cin_check;cin >> Id;
        }
        if(Library::search_by_Id(Id))
        {
            cout << "This Id already exists\n";
            goto tp;
        }
        cout << "Enter Date of Purchase: ";
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
            cout << "Invalid ID: ID should start with 'J', Try again...\n";
            cin_check;cin >> Id;
        }
        if(!Library::search_by_Id(Id));
        {
            cout << "This Id already exists\n";
            goto up;
        }
        cout << "Enter Date of Purchase: ";
        cin_check;cin >> DateOfPurchase;
        cout << "Enter Publication date: ";
        cin_check;cin >> PubDate;
        cout << "Enter Edition: ";
        cin_check;cin >> Edition;
        cout << "Enter Rack Number: ";
        cin_check;cin >> RackNumber;
        vector<string> topic;
        cout << "Enter the topics related to this journal\nPress ENTER while adding new topic\nPress 'y' when done\n";
        int num_of_topics = 0;
        string last = "y";
        while(1)
        {
            cin_check;cin >> topic[num_of_topics];
            if(topic[num_of_topics] == last)
                break;
        }
        resources.push_back(new Journal(author, title, Id, DateOfPurchase, Edition, RackNumber, DateOfPurchase, topic));
    }
    return;
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
        it++;
    }
}
void Library::ViewAllResource()
{
    for(int i = 0; i < resources.size(); i++)
    {
        resources[i]->getdetails();
    }
    cout << "------------------\n";
    return;
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
Phd* Library::get_user_phd(string UserId)
{
    vector<Phd*>::iterator phd = Library::phd.begin();
    while(phd != Library::phd.end())
        if((*phd)->getId() == UserId)
            return *phd;
    return nullptr;
}
NonPhd* Library::get_user_nonphd(string UserId)
{
    vector<NonPhd*>::iterator nphd = Library::nphd.begin();
    while(nphd != Library::nphd.end())
    {
        if((*nphd)->getId() == UserId)
            return *nphd;
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
            return *faculty;
        faculty++;
    }
    return nullptr;
}

NonPhd* Library::Login_as_Non_Phd(string Id)
{
    vector<NonPhd*>::iterator it = nphd.begin();
    while(it != nphd.end())
    {
        if((*it)->getId() == Id)
            return *it;
        it++;
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
                cout << "Enter Password: ";
                cin_check;
                cin >> password;
                while(password != (*it)->getpassword())
                {
                    cout << "Incorrect password. Try again...\n";
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
                while(password != (*it)->getpassword())
                {
                    cout << "Incorrect password. Try again...\n";
                    cin_check;cin >> password;
                }
                return *it;
            }
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
                    cout << "Incorrect password. Try again...\n";
                    cin_check;cin >> password;
                }
                return *it;
            }
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
                    cout << "Incorrect password. Try again...\n";
                    cin_check;cin >> password;
                }
                return *it;
            }
    }
    return nullptr;
}

bool Staff::IssueResource(string UserId, string ResourceId, Library &lib)
{
    if(lib.VerifyMemberId(UserId) && lib.VerifyResource(ResourceId))
    {
        if(lib.CheckLimit(UserId))
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
                cout << "HERE\n";
                cout << resource->getTitle() << " Not Available\n";
                return false;
            }
            if(resource){
                resource->update_history(UserId, Date, true, days);
                if(UserId[0] == 'N')
                {
                    NonPhd* nphd = lib.get_user_nonphd(UserId);
                    if(!nphd)
                    {
                        cout << "No such Non phd student exists.\n";
                        return false;
                    }
                    nphd->updateHistory(ResourceId, lib);
                    if(ResourceId[0] == 'B')
                        nphd->inc_num_of_books();
                }
                else if(UserId[0] == 'P')
                {
                    Phd* phd = lib.get_user_phd(UserId);
                    if(!phd)
                    {
                        cout << "No such phd student exists\n";
                    }
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
                        cout << "No such faculty\n";
                        return false;
                    }
                    facl->updateHistory(ResourceId, lib);
                    if(ResourceId[0] == 'B')
                        facl->inc_num_of_books();
                    else if(ResourceId[0] == 'J')
                        facl->inc_num_of_journals();
                }
                return true;
            }
        }
    }
    return false;
}
void Staff::ReturnResource(string UserId, string ResId, Library &lib)
{
    if(lib.VerifyMemberId(UserId) && lib.VerifyResource(ResId) && (UserId[0] == 'P' || UserId[0] == 'N' || UserId[0] == 'F'))
    {
        string date;
        cout << "Enter today's date(dd/mm/yyyy): ";
        cin >> date;
        Resource* resource = lib.search_by_Id(ResId);
        resource->change_status(false);
        if(UserId[0] == 'P')
        {
            Phd* phd = lib.get_user_phd(UserId);
            if(phd)
            {
                phd->change_history_status(ResId, date);
                if(ResId[0] == 'B')
                    phd->dec_num_of_books();
                else
                    phd->dec_num_of_journals();
            }
            else
                cout << "No such Phd student\n";
        }
        else if(UserId[0] == 'N')
        {
            NonPhd* nphd = lib.get_user_nonphd(UserId);
            if(nphd)
                {
                    nphd->change_history_status(ResId, date);
                    nphd->dec_num_of_books();
                }
            else
                cout << "No such Non Phd student\n";
        }
        else
        {
            Faculty* faculty = lib.get_user_faculty(UserId);
            if(faculty)
                {
                    faculty->change_history_status(ResId, date);
                    if(ResId[0] == 'B')
                        faculty->dec_num_of_books();
                    else if(ResId[0] == 'J')
                        faculty->dec_num_of_journals();
                }
            else
                cout << "No such faculty\n";
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
        cout << "Invalid Id\n";
    }
    return;
}
void Staff::UpdateHistory(string UserId, string ResId, Library& lib){}
void Staff::view_my_profile()
{
    cout << "\n-------------------------------------\n";
    cout << "name: " << setw(10) << name << endl;
    cout << "Id: " << setw(10) << Id << endl;
    cout << "Phone number: " << setw(10) << ph_num << endl;
    cout << "Address: " << setw(10) << address << endl;
    cout << "Email Id: " << setw(10) << emailId << endl;
    cout << "---------------------------------------\n";
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
        cin_check;cin >> cur_name;
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
    for(int i = 0; i < Resource::history.size(); i++)
    {
        history[i]->getdetails(lib);
    }
    return;
}

int main()
{
    try{
        cout << "\t\tWelcome to IITJ Automated Library\n";
        cout << "\n\n";
        cout << "Authors:\n";
        cout << "Anurag Shah B16CS034\n";
        cout << "Chinmay Garg B16CS041\n";
        cout << "\n@All Copyrights reserved\n";
        cout << "\nPress any key to continue";
        cin_check;cin.get();
        system("CLS");
        Library mylib("IITJ", 8320130726LL);
        mylib.AddMember();
    	//mylib.AddMember();
    	//string id = "NC", iid = "Sadmin";
    	//NonPhd* chinmay = mylib.Login_as_Non_Phd(id);
        //Staff* st = mylib.Login_as_Staff(iid);
        while(1)
        {
            system("CLS");
            string Id;
            cout << "Please login...";
            cout << "\nEnter your Id\n";
            cin >> Id;
            switch(Id[0])
            {
            case 'S':
                {
                    Staff* staff = mylib.Login_as_Staff(Id);
                    while(1)
                    {
                        system("CLS");
                        cout << "WELCOME\t" << staff->getname() << endl << endl;
                        cout << "\t\tInstructions:\n";
                        cout << "1. View your profile" << endl;
                        cout << "2. Edit your profile" << endl;
                        cout << "3. Add member" << endl;
                        cout << "4. Add Resource" << endl;
                        cout << "5. View Resource" << endl;
                        cout << "6. View all members" << endl;
                        cout << "7. View all resources" << endl;
                        cout << "8. See user history" << endl;
                        cout << "9. See resource history" << endl;
                        cout << "10. Issue resource" << endl;
                        cout << "11. return resource" << endl;
                        cout << "12. Remove member" << endl;
                        cout << "13. Remove resource" << endl;
                        cout << "14. Log out" << endl;
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
                                system("CLS");
                                cout << "1. Search by id" << endl;
                                cout << "2. Search by Title" << endl;
                                cout << "3. Search by Author" << endl;
                                cout << "4. Search by Tag" << endl;
                                int option;
                                cout << "Select appropriately\n";
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
                                            cout << "No such resource exists\n";
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
                                        Resource* res = mylib.search_by_Title(Title);
                                        if(!res)
                                        {
                                            cout << "No such resource exists\n";
                                            break;
                                        }
                                        else
                                            res->getdetails();
                                        break;
                                    }
                                case 3:
                                    {
                                        cout << "Enter author";
                                        string author;
                                        cin_check;
                                        cin >> author;
                                        Resource* res = mylib.search_by_author(author);
                                        if(!res)
                                        {
                                            cout << "No such resource exists\n";
                                            break;
                                        }
                                        else
                                            res->getdetails();
                                        break;
                                    }
                                case 4:
                                    {
                                        cout << "Enter tags. Press y when done.\n";
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
                                            cout << "No such resource exists\n";
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
                                        cout << "Invalid Input\n";
                                        break;
                                    }
                                }
                                break;
                            }
                        case 6:
                            {
                                mylib.ViewAllMembers();
                                break;
                            }
                        case 7:
                            {
                                mylib.ViewAllResource();
                                break;
                            }
                        case 8:
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
                        case 9:
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
                        case 10:
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
                                if(!try_)
                                {
                                    cout << "wrong input..." << endl;break;
                                }
                                string UserId;
                                cout << "Input User ID: ";
                                while(1)
                                {
                                    cin_check;cin >> UserId;
                                    if(mylib.VerifyMemberId(UserId))
                                       break;
                                    cout << "Invalid Id. Try again:" << endl;
                                }
                                staff->IssueResource(UserId, ResId, mylib);
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
                                if(!try_)
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
                        case 12:
                            {
                                string UserId;
                                cout << "Enter User ID: ";
                                cin >> UserId;
                                mylib.RemoveMember(UserId);
                                break;
                            }
                        case 13:
                            {
                                string Resid;
                                cout << "Enter Resource ID: ";
                                cin >> Resid;
                                mylib.RemoveResource(Resid);
                                break;
                            }
                        case 14:
                            {
                                goto outofthisloop;
                            }
                        default:
                            {
                                cout << "Invalid input\n";
                                break;
                            }
                        }
                        char ch;
                        cout << "Enter to continue\n";
                        cin_check;
                        cin >> ch;
                    }
                }
            case 'N':
                {
                    while(1){
                        system("CLS");
                        cout << "1. See your history" << endl;
                        cout << "2. View Profile" << endl;
                        cout << "3. Edit your profile" << endl;
                        cout << "4. Pay fine" << endl;
                        cout << "5. Log out" << endl;
                        int option;cin_check;
                        cin >> option;
                        NonPhd* nphd = mylib.Login_as_Non_Phd(Id);
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
                        }
                        char ch;
                        cout << "Enter to continue\n";
                        cin_check;
                        cin >> ch;
                    }
                }
            case 'P':
                {
                    while(1){
                        system("CLS");
                        cout << "1. See your history" << endl;
                        cout << "2. View Profile" << endl;
                        cout << "3. Edit your profile" << endl;
                        cout << "4. Pay fine" << endl;
                        cout << "5. Renew book" << endl;
                        cout << "6. Log out" << endl;
                        int option;cin_check;
                        cin >> option;
                        Phd* phd = mylib.get_user_phd(Id);
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
                                goto outofthisloop;
                                break;
                            }
                        }
                        char ch;
                        cout << "Enter to continue\n";
                        cin_check;
                        cin >> ch;
                    }
                }
            }
            char ch;
            cout << "Enter to continue\n";
            cin_check;
            cin >> ch;
        outofthisloop:;
        cout << "Successfully logged out!\n";
        }
    }
    catch(...)
    {
        system("CLS");
        cout << "Sorry there seems to be some technical error.\nDo not panic we'll fix it!\n";
    }
    return 0;
}
