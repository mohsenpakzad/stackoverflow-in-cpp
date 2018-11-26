#include <iostream>
#include <string>
#include <sstream>

#include "AbstractUser.h"
#include "Exceptions.h"

#include "User.h"
#include "Logger.h"

#include "GeneralFunctions.h"


#ifdef _WIN32
#define CLEAR "cls" // Clear screen for Windows OS
#else 
#define CLEAR "clear" // Clear screen for Linux OS
#endif

using namespace std;


enum MenuState {
    START,
    LOGGED_IN,
    END
};


int main() {

    Logger& logger = Logger::getInstance(); // Create current time logger file
	logger.startApp_log();

    User::init("SECRET_KEY");
    User * loggedInUser = nullptr;
    MenuState menuState = MenuState::START;
    string last_message;

    char choice;
    while(menuState != MenuState::END) {

        system(CLEAR);
		

        last_message = "";
        switch (menuState) {

            case MenuState::START: {

				cout << "***** Welcome to system *****" << endl;
				cout << "1. Login" << endl << "2. Signup" << endl << "e. Exit" << endl;

				cin >> choice; cleanBuf();
				system(CLEAR);

                switch (choice) {

                    case '1': { // login
                        try {
                            string username, password;

                            cout << "Enter Username: ";
							getline(cin, username);
                            cout << "Enter Password: ";
							getline(cin, password);

                            loggedInUser = &User::login(username,password);
                            menuState = MenuState::LOGGED_IN;

							last_message = "User successfuly logged in!";
                            logger.login_log(*loggedInUser);

                        } catch (WrongUsernameOrPasswordException &e) {
                            last_message = e.what();
							logger.unsuccessfulLogin_log();
                        }
                        break;
                    }

                    case '2': { // signup
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

                            last_message = "User successfuly signed up!";
							logger.signup_log(*loggedInUser);

                        } catch (UsernameAlreadyExistsException &e) {
                            last_message = e.what();
							logger.unsuccessfulSignup_log();
                            break;

                        } catch (EmailAlreadyExistsException &e) {
                            last_message = e.what();
							logger.unsuccessfulSignup_log();
                        }
                        break;
                    }

                    case 'e': { // exit
                        menuState = MenuState::END;
						last_message = "Goodbye ;)";
						logger.endApp_log();
                        break;
                    }

                    default: { // unknown input
                        last_message = "Unknown Input";
                        break;
                    }
                }
                break;
            }
            case MenuState::LOGGED_IN: {

				cout << "***** Welcome " << loggedInUser->username << " *****" << endl;
				cout << "d. Delete account" << endl << "l. Logout" << endl << "e. Exit" << endl;

				cin >> choice; cleanBuf();

                switch (choice) {

                    case 'd': {

						std::stringstream userInfo;
						userInfo << *loggedInUser;
                        try {
							loggedInUser->deleteAccount();
							
                            loggedInUser = nullptr;
                            menuState = MenuState::START;

							last_message = "Account successfully deleted";
							logger.deleteAccount_log(userInfo.str());
                        }
                        catch (DeleteAdminException &e) {
                            last_message = e.what();
							logger.unsuccessfulDeleteAccount_log(userInfo.str());
                        }
                        break;
                    }

                    case 'l': { // logout
						logger.logout_log(*loggedInUser);

                        loggedInUser = nullptr;
                        menuState = MenuState::START;

                        last_message = "Successfuly logout";
                        break;
                    }
                    case 'e': { // exit
                        menuState = MenuState::END;
						logger.endApp_log();
						last_message = "Goodbye ;)";
                        break;
                    }
                    default: { // unknown input
                        last_message = "Unknown Input";
                        break;
                    }

                }
            }
        }

		if (!last_message.empty()) { // jsut for exit the message is empty 
			system(CLEAR);
			cout << last_message << endl;
			SystemPause;
		}
    }
   
    logger.closeLogFile();
    return 0;
}
