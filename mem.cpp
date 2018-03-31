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
		
		string IssueDate;
		string ReturnDate;
		long Fine;
		long FinePaid;
		bool renew;
	public:
		bool Status;
		string BookId;
		void getDetails();
		void setReturnDate(string Date);
		int CalculateFine(){
			return 1;
		}
		void AcceptFine(long fine);
		bool isRenew();
		void ChangeRenew();
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
		
		void update_history(string Resid)										//doubt, change
		{
			BookIssued* book;
			history.push_back(book);																			//DOUBT
		}
		
		void change_history_status(string ResId, string Date)					//doubt
		{
			vector<BookIssued*>::iterator it;
			it = history.end();
			while((*it)->BookId != ResId){
				it--;
			}
			(*it)->Status = 0;													//note
			(*it)->setReturnDate(Date);
			//*it->Fine += 														//include<ctime> ???
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
