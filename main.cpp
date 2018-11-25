#include <iostream>
#include <string>

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

    Logger logger = Logger::getInstance();
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

				cout << "1. login" << endl << "2. signup" << endl << "e. exit" << endl;
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
                            logger.log(loggedInUser);

                        } catch (WrongUsernameOrPasswordException &e) {
                            last_message = e.what();
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
                            logger.log(loggedInUser);
                            last_message = "User signed up!";
                        } catch (UsernameAlreadyExistsException &e) {
                            last_message = e.what();
                            break;

                        } catch (EmailAlreadyExistsException &e) {
                            last_message = e.what();
                        }
                        break;
                    }

                    case 'e': { // exit
                        menuState = MenuState::END;
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
                cout << "d.delete account\nl. logout\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case 'd': {
                        try {
                            loggedInUser->deleteAccount();
                            cout << "Account successfully deleted\n";
                            loggedInUser = nullptr;
                            menuState = MenuState::START;
                        }
                        catch (DeleteAdminException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case 'l': { // logout
                        loggedInUser = nullptr;
                        menuState = MenuState::START;
                        last_message = "GOODBYE";
                        break;
                    }
                    case 'e': { // exit
                        menuState = MenuState::END;
                        break;
                    }
                    default: { // unknown input
                        last_message = "Unknown Input";
                        break;
                    }

                }
            }
        }

		if (!last_message.empty())
			cout << last_message << endl;
		SystemPause;
    }
   
    logger.saveLogs();
    cout << "GOODBYE" << endl;
    return 0;
}
