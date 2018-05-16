
#include <iostream> 
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <stdio.h> 
#include <conio.h> 
#include <limits> 
#include <cstddef>
  using namespace std;

string getPassword() {
  char ch;
  string myPass = "";
  ch = _getch();
  int i = 0;
  while (ch != 13) {
    if (ch == '\b') {
      if (i == 0) {
        ch = _getch();
        continue;
      }

      myPass = myPass.substr(0, myPass.size() - 1);
      cout << "\b \b";
      ch = _getch();
      --i;
      continue;
    }
    myPass.push_back(ch);
    cout << '*';
    ch = _getch();
    ++i;
  }
  return myPass;
}
class Admin;

class Application;

class Customer;

void Cover_customer(Application, Customer, Admin);

class Design {

  int id;

  char des[11][38];

  public:
    virtual void show() {

      for (int i = 0; i < 11; i++)

      {
        cout << "                          ";

        for (int j = 0; j < 37; j++)

          cout << des[i][j];

        cout << "\n";

      }

    }
  friend Admin;

};

class Pattern: public Design {

  int id;

  char lpt[11][38];

  public:
    void show() {
      cout << id << endl;
      for (int i = 0; i < 11; i++)

      {
        cout << "                          ";

        for (int j = 0; j < 37; j++)

          cout << lpt[i][j];

        cout << "\n";

      }
    }
  friend Admin;

};

class Building: public Design {

  int id;

  char bp[11][38];

  Pattern lp[4];

  Design d[4];

  public:
    void show() {
      cout << id << endl;
      for (int i = 0; i < 11; i++)

      {
        cout << "                          ";

        for (int j = 0; j < 37; j++)

        {

          cout << bp[i][j];

        }
        cout << "\n";

      }
    }
  void show_patterns() {

    for (int i = 0; i < 4; i++)

    {
      cout << "\n";
      lp[i].show();
    }

  }

  friend Admin;

  friend void Cover_customer(Application p, Customer c, Admin a);

};

class Customer {

  char name[20];

  char contact_no[10];

  Design dc;

  public:
    void Enter_details() {
      int valid = 0, valid_cn = 0;
      cout << "\n                          Enter the name : ";

      while (!valid)

      {
        valid = 1;

        cin >> name;

        for (int i = 0; name[i] != '\0'; i++)

        {

          if (!isalpha(name[i]))

          {

            valid = 0;

            cout <<
              "\n                          Invalid name. Name should contain only alphabets without space. Re-enter.";

            break;

          }

        }

      }

      cout << "\n                          Enter the contact no : ";

      while (!valid_cn)

      {
        valid_cn = 1;

        cin >> contact_no;

        int len = 0;

        for (int i = 0; contact_no[i] != '\0'; i++)

        {
          len++;

          if (!isdigit(contact_no[i]))

          {

            valid_cn = 0;

            cout <<
              "\n                          Invalid Contact number. Contact number should contain only numbers without space. Re-enter.";

            break;

          }

        }

        if (len != 10 && valid_cn)

        {

          valid_cn = 0;

          cout <<
            "\n                          Invalid contact number. Contact number length must be equal to 10. Re-enter";

        }

      }

    }

  void SetDesign(Design x) {

    dc = x;

  }
  friend Admin;

};

class Admin {

  char name[20];

  char pass[20];

  Building bl[5];

  Design da[20];

  public:
    Admin() {

      strcpy(name, "none");

      strcpy(pass, "not");

      ifstream u;

      u.open("lightpatternsimulatorbuilding_pattern.txt");

      for (int e = 0; e < 5; e++)

      {

        u >> bl[e].id;

        for (int i = 0; i < 11; i++)

          for (int j = 0; j < 37; j++)

        u >> bl[e].bp[i][j];

      }
      for (int e = 0; e < 5; e++)

        for (int f = 0; f < 4; f++)

      {

        u >> bl[e].lp[f].id;

        for (int i = 0; i < 11; i++)

          for (int j = 0; j < 37; j++)

        u >> bl[e].lp[f].lpt[i][j];

      }
      u.close();

      ifstream v;

      v.open("lightpatternsimulatordesign.txt");

      for (int e = 0; e < 20; e++)

      {

        v >> da[e].id;

        for (int i = 0; i < 11; i++)

          for (int j = 0; j < 37; j++)

        v >> da[e].des[i][j];

      }
      // cout<<"here"<<da[1].id;

    }

  friend void Cover_customer(Application p, Customer c, Admin a);

  void write_to_file(Customer c) {
    Customer chk;
    ofstream f;

    f.open("custdatafinal.dat", ios:: in | ios::out );

    f.write((char * ) & c, sizeof(c));

  }

  void login(char n[], char p[]) {

    strcpy(name, n);

    strcpy(pass, p);

    cout << name << " " << pass;

  }
  void show_all_buildings() {

    for (int i = 0; i < 5; i++)

    {

      bl[i].show();

      cout << "\n\n";

    }
  }
  void Display_history() {
    system("CLS");

    int found = 0;

    Customer w;

    char c_name[20], c_contact_no[20];

    int choice;

    bool opt = false;

    cout << "\n                          Enter Customer name: ";

    cin >> c_name;

    cout << "\n\n                          Enter contact number: ";

    cin >> c_contact_no;

    ifstream file;

    file.open("custdatafinal.dat", ios:: in );
    system("CLS");

    while (file.read((char * ) & w, sizeof(w)))

    {

      if (!strcmp(w.name, c_name) && !strcmp(w.contact_no, c_contact_no))

      {
        found = 1;

        cout << "\n                          The design for requested customer is :\n";

        w.dc.show();

      }

    }

    if (!found)

    {

      cout << "\n                          The customer does not exist. ";

      cout << "\n\n                          1.Retry      2. Exit ";

      while (!opt) {

        cin >> choice;

        if (cin.fail()) {
          cin.clear();
          cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
        }
        switch (choice) {

        case 1:
          opt = true;

          ( * this).Display_history();
          break;

        case 2:
          opt = true;

          exit(0);
          break;

        default:
          cout << "\n\n                          Incorrect option. Enter again. :";

        }

      }

    }

  }

};

class Application {

  public:
    void verify_login() {

      char username[20], password[20], no[20], po[20];
      int x = 0;

      char ch;

      while (x == 0) {

        label: cout <<
          "\n                          Enter the username: ";

        cin >> username;

        cout << "\n\n                          Enter the password: ";

        string str = getPassword();
        for (int i = 0; i < str.length(); i++)
          password[i] = str[i];

        ifstream f;

        f.open("lightpatternsimulatoradmin_details.txt");

        f >> no;

        f >> po;

        x = !strcmp(no, username) && !strcmp(po, password);

        f.close();

        if (x == 0)

        {

          cout <<
            "\n\n                          Incorrect username or password.\n\n                          Press any key to retry.  ";

          _getch();

          system("CLS");

        }

      }

      Admin a;

      a.login(username, password);

      system("CLS");

      ( * this).Cover(a);

    }

  void Cover(Admin a) {
    system("CLS");
    int option;

    bool opt = false;

    cout << "\n                                         Choose the option : " << endl;

    cout <<
      "\n                          1. New User    2. Display user history   3. Exit" << endl;

    while (!opt) {
      cin >> option;
      if (cin.fail()) {
        cin.clear();

        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');

      }

      system("CLS");

      switch (option)

      {

      case 1:

        {

          opt = true;

          Customer c;

          c.Enter_details();

          Cover_customer( * this, c, a);
        }

        break;

      case 2:

        opt = true;

        a.Display_history();

        break;

      case 3:

        opt = true;

        exit(0);

        break;

      default:

        {

          cout <<
          "\n                          Incorrect option. Enter again.   ";

        }

      }

    }

  }

  friend void Cover_customer(Application p, Customer c, Admin a);

};

void
Cover_customer(Application p, Customer c, Admin a) {

  system("CLS");
  int buil_no, pattern_no, option;

  a.show_all_buildings();
  cout << "\n                          Select the building type: \n";

  cin >> buil_no;

  while (buil_no < 1 || buil_no > 5 || cin.fail())

  {
    cin.clear();

    cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');

    cout << "\n                          Incorrect option. Enter again. :";

    cin >> buil_no;

  }

  buil_no = buil_no - 1;

  system("CLS");

  a.bl[buil_no].show_patterns();
  cout << "\n                          Select the lighting pattern: \n";

  cin >> pattern_no;

  while (pattern_no < 1 || pattern_no > 4 || cin.fail())

  {
    cin.clear();

    cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');

    cout << "\n                          Incorrect option. Enter again. :";

    cin >> pattern_no;

  }

  pattern_no = pattern_no - 1;

  system("CLS");

  cout << "\n                          The simulated light pattern on building : \n";

  a.da[buil_no * 4 + pattern_no].show();

  cout << "\n                          1.Confirm   2.Home page 3.Back ";

  bool opt = false;

  while (!opt) {
    cin >> option;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
    }

    switch (option)

    {

    case 1:

      {

        opt = true;

        c.SetDesign(a.da[buil_no * 4 + pattern_no]);

        a.write_to_file(c);

        cout << "\n                          Lighting pattern confirmed.\n";

        p.Cover(a);
      }

      break;

    case 2:

      {
        opt = true;

        system("CLS");

        p.Cover(a);
      }

      break;
    case 3:
    	{
    		opt=true;
    		system("CLS");
    		Cover_customer(p, c, a);
		}
    default:

      {

        cout <<
        "\n                          Incorrect option. Choose again. \n";

      }

      break;

    }

  }

}

int
main() {

  Application q;

  q.verify_login();

}
