#include <iostream>
#include <string>
#include <sstream>

#include "AbstractUser.h"
#include "Exceptions.h"

#include "User.h"
#include "Logger.h"

#include "GeneralFunctions.h"


using namespace std;


enum MenuState {
	START,
	LOGGED_IN,
	END
};

Logger& logger = Logger::getInstance(); // Create current time logger file
MenuState menuState = MenuState::START;
User * loggedInUser = nullptr;


//TODO: Open loggedin_menu and go to ManageQuestions case and add your written "function" (# Seyed Mohmmad Reza)
//TODO: Open loggedin_menu and go to MakeNewQuestion case and add your written "function" (# Seyed Ali)


void start_menu() {

	enum StartMenuOptions {
		Login = '1',
		Signup = '2',
		Exit = '3',
		WrongChoice
	};
	char choice;


	do {

		system(CLEAR);
		cout << "***** Welcome to system *****" << endl;
		cout << "1. Login" << endl << "2. Signup" << endl << "3. Exit" << endl;

		cin >> choice; cleanBuf();
		system(CLEAR);

		switch (choice) {

		case StartMenuOptions::Login: {
			try {
				string username, password;

				cout << "Enter Username: ";
				getline(cin, username);
				cout << "Enter Password: ";
				getline(cin, password);

				loggedInUser = &User::login(username, password);
				menuState = MenuState::LOGGED_IN;

				showMessageToUser("User successfuly logged in!");
				logger.login_log(*loggedInUser);

			}
			catch (WrongUsernameOrPasswordException &e) {
				showMessageToUser(e.what());
				logger.unsuccessfulLogin_log();
			}
			break;
		}

		case StartMenuOptions::Signup: {
			try {
				string username, password, email;

				cout << "Enter Email: ";
				getline(cin, email);
				cout << "Enter Username: ";
				getline(cin, username);
				cout << "Enter Password: ";
				getline(cin, password);

				loggedInUser = &User::signup(username, password, email);
				menuState = MenuState::LOGGED_IN;

				showMessageToUser("User successfuly signed up!");
				logger.signup_log(*loggedInUser);

			}
			catch (UsernameAlreadyExistsException &e) {
				showMessageToUser(e.what());
				logger.unsuccessfulSignup_log();
				break;

			}
			catch (EmailAlreadyExistsException &e) {
				showMessageToUser(e.what());
				logger.unsuccessfulSignup_log();
			}
			break;
		}

		case StartMenuOptions::Exit: { // exit
			menuState = MenuState::END;
			showMessageToUser("Goodbye ;)");
			logger.endApp_log();
			break;
		}

		default: { 
			
			choice = StartMenuOptions::WrongChoice;
			showMessageToUser("Unknown Input");
		}

		}

	} while (choice == StartMenuOptions::WrongChoice);
}


void accountSetting_menu() {

	enum AccountSettingOptions {
		DeleteAccount = '1',
		Back = '2',
		WrongChoice
	};
	char choice;

	do {
		system(CLEAR);
		cout << "1. Delete Account" << endl << "2. Back" << endl;

		cin >> choice; cleanBuf();

		switch (choice) {

		case AccountSettingOptions::DeleteAccount: {

			std::stringstream userInfo;
			userInfo << *loggedInUser;
			try {
				loggedInUser->deleteAccount();

				loggedInUser = nullptr;
				menuState = MenuState::START;

				showMessageToUser("Account successfully deleted");
				logger.deleteAccount_log(userInfo.str());
			}
			catch (DeleteAdminException &e) {
				showMessageToUser(e.what());

				logger.unsuccessfulDeleteAccount_log(userInfo.str());
			}

			break;
		}

		case AccountSettingOptions::Back: {

			break;
		}

		default: {
			choice = AccountSettingOptions::WrongChoice;
			showMessageToUser("Unknown Input");
		}

		}



	} while (choice == AccountSettingOptions::WrongChoice);

}
bool check_size(int i){
	return loggedInUser->kick_size()>=i;
}
void ManageQuestions_menu(){
	enum ManageQuestionsOptions {
		EditQuestion = '1',
		DeleteQuestion='2',
		Back = '3',
		WrongChoice
	};
	char choice;

	do{
		system(CLEAR);
		cout<<"1.Edit Question"<<endl
			<<"2.Delete Question"<<endl
			<<"3.back"<<endl;
		cin>>choice;cleanBuf();
		switch(choice){
			case ManageQuestionsOptions::EditQuestion:{
				system(CLEAR);
				loggedInUser->showMyQuestions();
				int i;
				cout<<endl<<"Please Enter the NO of the Question: "<<endl;
				cin>>i;cleanBuf();
				if(check_size(i)){
					string topic;
					string body;
					cout<<"Please enter the topic of your Question:"<<endl;
					getline(cin,topic);
					cout<<"please enter your question:"<<endl;
					getline(cin,body);
					loggedInUser->editQuestion(i,topic,body);
					showMessageToUser("You have successfully edited your question");
					break;
				}
				else{
					showMessageToUser("You did not create this amount of Questions");
					break;
				}

			}
			case ManageQuestionsOptions::DeleteQuestion:{
				system(CLEAR);
				loggedInUser->showMyQuestions();
				int i;
				cout<<endl<<"Please Enter the NO of the Question: ";
				cin>>i;cleanBuf();
				if(check_size(i)){
					loggedInUser->deleteQuestion(i);
					showMessageToUser("Question successfully deleted");
					break;
				}
				else{
					showMessageToUser("You did not create this amount of Questions");
					break;
				}

			}
			case ManageQuestionsOptions::Back:{
				break;
			}
			default: { // unknown input
				choice = ManageQuestionsOptions::WrongChoice;
				showMessageToUser("Unknown Input");
			}
		}
	}while(choice == ManageQuestionsOptions::WrongChoice);
}
void loggedin_menu() {

	enum LoggedinMenuOptions {
		MakeNewQuestion = '1',
		ManageQuestions = '2',
		ShowAllQuestions = '3',
		AccountSetting = '4',
		Logout = '5',
		Exit = '6',
		WrongChoice
	};
	char choice;

	do {

		system(CLEAR);
		cout << "***** Welcome " << loggedInUser->username << " *****" << endl;

		cout << "1. Make new question" << endl
			<< "2. Manage your questions" << endl
			<< "3. Show all questions" << endl
			<< "4. Account setting" << endl
			<< "5. Logout" << endl
			<< "6. Exit" << endl;

		
		cin >> choice; cleanBuf();


		switch (choice) {

		case LoggedinMenuOptions::MakeNewQuestion:{

			string topic;
			string body;

			system(CLEAR);
			cout << "Please enter the topic of your question:" << endl;
			getline(cin,topic);
			cout << "Please enter your question:" << endl;
			getline(cin,body);

			loggedInUser->makeQuestion(topic,body);
			showMessageToUser("Question successfully created");
			break;
		}
		case LoggedinMenuOptions::ManageQuestions:{

			ManageQuestions_menu();

			// you should write function for manage questions in there (# Seyed Mohammad Reza)
			break;
		}
		case LoggedinMenuOptions::ShowAllQuestions:{
			
			system(CLEAR);
			User::showAllQuestions();
			SystemPause;
			break;
		}
		case LoggedinMenuOptions::AccountSetting:{

			accountSetting_menu();
			break;
		}
		case LoggedinMenuOptions::Logout: {

			logger.logout_log(*loggedInUser);

			loggedInUser = nullptr;
			menuState = MenuState::START;

			showMessageToUser("Successfuly logout");
			break;
		}
		case LoggedinMenuOptions::Exit: {

			menuState = MenuState::END;
			logger.endApp_log();
			showMessageToUser("Goodbye ;)");
			break;

		}
		default: { // unknown input
			choice = LoggedinMenuOptions::WrongChoice;
			showMessageToUser("Unknown Input");
		}

		}

	} while (choice == LoggedinMenuOptions::WrongChoice);
}


int main() {
	
	logger.startApp_log();
    User::init("SECRET_KEY");

    while(menuState != MenuState::END) {

 
        switch (menuState) {

            case MenuState::START: {

				start_menu();
                break;
            }
            case MenuState::LOGGED_IN: {

				loggedin_menu();
            }
        }

    }

    logger.closeLogFile();
    return 0;
}
