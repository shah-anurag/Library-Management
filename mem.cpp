#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
using namespace std;

class BookIssued{
	//protected:
		string BookName;
		string Author;
		long FinePaid;
		bool renew;
	public:
		long Fine;
		int ReturnDate[3];
		int IssueDate[3];
		bool Status;
		string BookId;
		BookIssued(Resource* Res, int Date[3])
		{
			BookName = Res->getTitle();
			Author = Res->getAuthor();
			FinePaid = 0;
			Fine = 0;
			Status = true;
			BookId = Res->getId();
			renew = false;
			for(int i = 0; i < 3; IssueDate[i] = Date[i], ReturnDate[i] = 0, i++); 			
		}
		
		void getDetails(){
			cout<<BookId<<" "<<BookName<<" "<<Author;
			cout<<" Issued: "<<IssueDate[0]<<"/"<<IssueDate[1]<<"/"<<IssueDate[2];
			cout<<" Returned: "<<ReturnDate[0]<<"/"<<ReturnDate[1]<<"/"<<ReturnDate[2];
			cout<<" Fine: "<<Fine<<" Fine Paid: "<<FinePaid<<endl;
		}
		
		void setReturnDate(int Date[3]){
			for(int i = 0; i < 3; ReturnDate[i] = Date[i], i++);
		}
		
		int CalculateFine(){
			return (Fine - FinePaid);
		}
		
		void AcceptFine(int fine){
			FinePaid += fine;
		}
		
		bool isRenew(){
			return renew;
		}
		
		void ChangeRenew(){
			renew = 1;
		}
};

class Member{
	protected:
		string name;
		string join_date;
		string Id;
		long ph_no;
		string address;
		string password;
		string email_id;
	public:
		virtual void view_my_profile() = 0;											//virtual
		
		virtual void edit_my_profile() = 0;											//virtual
		
		void edit_password(){
			int a = 1, b = 1;
			cout<<"\nEnter the current password.\n";
			string pass;
			cin>>pass;
			while(a){
				if(pass == password){
					while(b){
						a = 0;
						cout<<"\nEnter new password.\n";
						string pass1, pass2;
						cin>>pass1;
						cout<<"\nEnter the new password again.\n";
						cin>>pass2;
						if(pass1 == pass2){
							password = pass1;
							b = 0;
						}
						else
							cout<<"\nPasswords don't match.\n";
					}
				}
				else{
					cout<<"\nIncorrect password. Re-enter the current password.\n";
					cin>>pass;
				}
			}
		}
};

class User : public Member{
	protected:
		string Department;
		int num_of_books_issued;
		vector<BookIssued*> history;
		vector<BookIssued*>::iterator it;
	public:
		void editDepartment(string dep){
			Department = dep;
		}
		
		void payfine()															//doubt
		{
			
			/*auto*/ it = history.begin();
			int sum = 0;
			while(it != history.end() && !(*it)->CalculateFine())
			{
				sum += (*it)->CalculateFine();
				it++;
				(*it)->getDetails(); 
				cout << " Fine = " << (*it)->CalculateFine() << "\n";
			}
			cout << "Total fine = " << sum << endl;
			cout << "Enter amount paid\n";
			cin >> sum;
			it--;
			while(sum && it != history.begin()-1)
			{
				(*it)->AcceptFine(min(sum, (*it)->CalculateFine()));
				sum -= min(sum, (*it)->CalculateFine());
				(*it)->getDetails();
				cout << " Fine = " << (*it)->CalculateFine() << "\n";
				it--;
			}
			if(sum > 0)
			{
				cout << "Extra money Rs. " << sum << " paid\n";
			}
			return;
		}
		void inc_num_of_books(int i){
			num_of_books_issued += i;
		}
		
		void dec_num_of_books(int i){
			num_of_books_issued -= i;
		}
		
		int getbooksissued(){
			return num_of_books_issued;
		}
		
		void gethistory()														//doubt
		{
			vector<BookIssued*>::iterator it;
			it = history.begin();
			while(it != history.end()){
				(*it)->getDetails();
				it++;
			}
		}
		
		void search_history(string Resid)											//doubt,change
		{
			vector<BookIssued*>::iterator it;
			it = history.begin();
			bool flag = 0;
			while(it != history.end()){
				if((*it)->BookId == Resid){
					(*it)->getDetails();
					flag = 1;
				}
				it++;
			}
			if(!flag){
				cout<<"You have never issued the book\n";
			}
		}
		
		void update_history(string Resid, int Date[3])										//doubt, change
		{
			Resource* book = search_by_Id(Resid);
			history.push_back(BookIssued(book, Date));																			//DOUBT
		}
		
		void change_history_status(string ResId, int Date[3])					//doubt
		{
			vector<BookIssued*>::iterator it;
			it = history.end();
			while((*it)->BookId != ResId){
				it--;
			}
			(*it)->Status = 0;													//note
			(*it)->setReturnDate(Date);
			struct tm iss = {0, 0, 0, (*it)->IssueDate[0], (*it)->IssueDate[1] - 1, (*it)->IssueDate[0] - 1900};
			struct tm ret = {0, 0, 0, (*it)->ReturnDate[0], (*it)->ReturnDate[1] - 1, (*it)->ReturnDate[0] - 1900};
			time_t iss_t = mktime(&iss);
			time_t ret_t = mktime(&ret);
			double difference = difftime(ret_t, iss_t) / (60 * 60 * 24);
			(*it)->Fine += (5*difference);														//include<ctime> ???
		}
};

class Student : public User{
		int MaxBookLimit;
	
	public:
		int getBookLimit(){
			return MaxBookLimit;
		}
		
		bool isEligible()											//doubt,change			//yaha student_id nahi aayegi?
		{
			if(getBookLimit()-getbooksissued())
				return 1;
			else
				return 0;
		}
};

class Non_Phd : public Student{
		int Year;
	
	public:
		int getYear(){
			return Year;
		}
		
		void editYear(){
			cout<<"\nEnter the current year of the student:\n";
			int i;
			cin>>i;
			Year = i;
		}
};

class Phd : public Student{
		int maxJournalLimit;
	
	public:
		int getMaxJournalLimit(){
			return maxJournalLimit;
		}
		
		void inc_num_of_journals(int i){
			maxJournalLimit += i;
		}
		
		void dec_nun_of_journals(int i){
			maxJournalLimit -= i;
		}
};

class Faculty : public User{
		int maxBookLimit;
		int maxJournalLimit;
		int numofjournalsissued;
	public:
		void SuggestResource();
		
		int getBookLimit(){
			return maxBookLimit;
		}
		
		int getJournalLimit(){
			return maxJournalLimit;
		}
		
		bool IsEligible()											//doubt, change
		{
			if(getBookLimit()-getbooksissued())
				return 1;
			else
				return 0;
		}
		
		void inc_num_of_journals(int i){
			numofjournalsissued += i;
		}
		
		void dec_nun_of_journals(int i){
			numofjournalsissued -= i;
		}
};

class Staff : public Member{
	public:
		/*	Library mai 3 vectors bane hue honge....
			1. vector<Faculty*>faculty;
			2. vector<Phd*>phd;
			3. vector<Non_Phd*>nonphd;
			ab hoga ye ki view profile mai in teeno m hi search karna padega
			okay?
		*/
		void ViewProfile(string Id)											//doubt, change
		{
			
		}
		
		bool IssueResource(string UserId, string ResId);						//doubt
		
		void ReturnResource(string UserId, string ResId);						//doubt
		
		void CollectFine(string studId, long fine);								//doubt
		
		void UpdateHistory(string UserId, string ResId);						//doubt
};

int main(){
	
}
