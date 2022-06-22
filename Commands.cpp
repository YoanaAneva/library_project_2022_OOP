#include "Commands.h"

void Commands::login(UserBase& userBase){
    if(userBase.showIfHasLoggedIn() == true){
        std::cout << "You are already logged in." << std::endl;
        return;
    }
    String username, password;
    std::cout << "Enter your username: " << std::endl;
    std::cin >> username;
    std::cout << "Enter your password: " << std::endl;
    std::cin >> password;

    User* user;
    unsigned size = userBase.getUsersCount();
    for(int i = 0; i < size; ++i){
        if(userBase[i]->getUsername() == username && userBase[i]->getPassword() == password){
            std::cout << "Welcome " << username << "!" << std::endl;
            userBase.logUser(userBase[i]);
            userBase.setHasLoggedIn(true);
            return;
        }
    }
    std::cout << "Incorrect username or password." << std::endl;
}

void Commands::logout(UserBase& userBase){
    userBase.logUser(nullptr);
    userBase.setHasLoggedIn(false);
    std::cout << "You have logged out" << std::endl;
}

void Commands::books_all(const Library& library){
    for(int i = 0; library[i]->getTitle() != "Divider1"; ++i){
        library[i]->listAll();
    }
}

void Commands::books_find(const Library& library, const CommandInfo& command){
    Library tempLib;
    String option = command.getValues()[0];
    String optionStr = command.getValues()[1];

    if(option == "title"){
        for(int i = 0; i < library.getDividerInd(); ++i){
            if(library[i]->getTitle() == optionStr){
                tempLib.addItemToCatalog(library[i]);
            }
        }
    }
    if(option == "author"){
        for(int i = 0; i < library.getDividerInd(); ++i){
            if(dynamic_cast<Book*>(library[i])->getAuthor() == optionStr){
                tempLib.addItemToCatalog(library[i]);
            }
        }
    }
    if(option == "tag"){
        for(int i = 0; i < library.getDividerInd(); ++i){
            if(Paper::isAmongKeywords(dynamic_cast<Book*>(library[i])->getKeywords(), optionStr)){
                tempLib.addItemToCatalog(library[i]);
            }
        }
    }
    if(command.getHasSort()){
        String sortKey = command.getSortKey();
        if(sortKey == "title"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(strcmp(tempLib[j]->getTitle().getData(), tempLib[min]->getTitle().getData()) < 0){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }   
        }
        if(sortKey == "author"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    String surname1 = String::getSurname(dynamic_cast<Book*>(tempLib[j])->getAuthor());
                    String surname2 = String::getSurname(dynamic_cast<Book*>(tempLib[min])->getAuthor());
                    if(strcmp(surname1.getData(), surname2.getData()) < 0){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }  
        }
        if(sortKey == "year"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(dynamic_cast<Book*>(tempLib[j])->getYearOfPublishing() < dynamic_cast<Book*>(tempLib[min])->getYearOfPublishing()){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }
        }
        if(sortKey == "rating"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(tempLib[j]->getRating() < tempLib[min]->getRating()){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }
        }
    }
    if(!command.getIsAscending()){
        reverseArr(tempLib.getItems(), tempLib.getDividerInd());
    }
    for(int i = 0; i < tempLib.getDividerInd(); ++i){
        tempLib[i]->print();
    }
}

void Commands::books_add(Library& library){
    Book* newBook = new Book();
    newBook->readFromUser();
    library.addItemToCatalog(newBook);
    std::cout << "Item " << newBook->getTitle() << " with id:" << newBook->getId() << " added to catalog" << std::endl;
}

void Commands::books_remove(Library& library){
    String idStr;
    do{
        std::cout << "Enter the id of the book you would like to remove: ";
        std::cin >> idStr;
    }while(String::convertToNumber(idStr) == -1);

    unsigned id = String::convertToNumber(idStr);
    library.removeItemFromCatalog(id);
}

void Commands::books_view(const Library& library, const CommandInfo& command){
    String idStr = command.getValues()[0];
    int id = String::convertToNumber(idStr);
    if(id == -1){
        return;
    }
    if(library.getItemById(id) == nullptr || library.getItemById(id)->getType() != BOOK){
        std::cout << "No book in our system with id: " << id << std::endl;
        return;  
    }
    library.getItemById(id)->print();
}

void Commands::series_find(const Library& library, const CommandInfo& command){
    Library tempLib;
    String option = command.getValues()[0];
    String optionStr = command.getValues()[1];

    if(option == "title"){
        for(int i = library.getDividerInd() + 1; i < library.getCatalogSize(); ++i){
            if(library[i]->getTitle() == optionStr){
                tempLib.addItemToCatalog(library[i]);
            }
        }
    }
    if(option == "author"){
        for(int i = library.getDividerInd() + 1; i < library.getCatalogSize(); ++i){
            Series* series = dynamic_cast<Series*>(library[i]);
            for(int j = 0; j < series->getArticlesCount(); ++j){
                if(series->getContent()[j].getAuthor() == optionStr){
                    tempLib.addItemToCatalog(library[i]);
                }
            }
        }
    }
    if(option == "tag"){
        for(int i = library.getDividerInd() + 1; i < library.getCatalogSize(); ++i){
            Series* series = dynamic_cast<Series*>(library[i]);
            if(Paper::isAmongKeywords(series->getContent()[i].getKeywords(), optionStr)){
                tempLib.addItemToCatalog(library[i]);
            }
        }
    }
    if(command.getHasSort()){
        String sortKey = command.getSortKey();
        if(sortKey == "title"){
            for(int i = 0; i < tempLib.getCatalogSize(); ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(strcmp(tempLib[j]->getTitle().getData(), tempLib[min]->getTitle().getData()) < 0){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }   
        }
        if(sortKey == "author"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    String surname1 = String::getSurname(dynamic_cast<Book*>(tempLib[j])->getAuthor());
                    String surname2 = String::getSurname(dynamic_cast<Book*>(tempLib[min])->getAuthor());
                    if(strcmp(surname1.getData(), surname2.getData()) < 0){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }  
        }
        if(sortKey == "year"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(dynamic_cast<Book*>(tempLib[j])->getYearOfPublishing() < dynamic_cast<Book*>(tempLib[min])->getYearOfPublishing()){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }
        }
        if(sortKey == "rating"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                int min = i;
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(tempLib[j]->getRating() < tempLib[min]->getRating()){
                        min = j;
                        Paper* temp = tempLib[i];
                        tempLib[i] = tempLib[min];
                        tempLib[min] = temp;
                    }
                }
            }
        }
    }
    if(!command.getIsAscending()){
        reverseArr(tempLib.getItems(), tempLib.getDividerInd());
    }
    for(int i = 0; i < tempLib.getDividerInd(); ++i){
        tempLib[i]->print();
    }
}

void Commands::series_all(const Library& library){
    for(int i = library.getDividerInd() + 1; i < library.getCatalogSize(); ++i){
        library[i]->listAll();
    }
}

void Commands::series_add(Library& library){
    Series* newSeries = new Series();
    newSeries->readFromUser();
    library.addItemToCatalog(newSeries);
    std::cout << "Item " << newSeries->getTitle() << " with id:" << newSeries->getId() << " added to catalog" << std::endl;
}

void Commands::series_remove(Library& library){
    String idStr;
    do{
        std::cout << "Enter the id of the series you would like to remove: ";
        std::cin >> idStr;
    }while(String::convertToNumber(idStr) == -1);

    unsigned id = String::convertToNumber(idStr);
    library.removeItemFromCatalog(id);   
}

void Commands::series_view(const Library& library, const CommandInfo& command){
    String idStr = command.getValues()[0];
    int id = String::convertToNumber(idStr);
    if(id == -1){
        return;
    }
    if(library.getItemById(id) == nullptr || library.getItemById(id)->getType() != SERIES){
        std::cout << "No series in our system with id: " << id << std::endl;
        return;  
    }
    library.getItemById(id)->print();
}

void Commands::list_all(const Library& library){
    for(int i = 0; i < library.getCatalogSize(); ++i){
        if(i == library.getDividerInd())
            continue;
        library[i]->listAll();
    }
}

void Commands::list_info(const Library& library, const CommandInfo& command){
    String str = command.getValues()[0];
    bool isIsbn = false, isIssn = false;

    if(Book::isValidIsbn(str.getData()));
        isIsbn = true;
    if(Series::isValidIssn(str.getData()))
        isIssn = true;
    
    if(isIsbn){
        for(int i = 0; i < library.getDividerInd(); ++i){
            if(dynamic_cast<Book*>(library[i])->getIsbn() == str){
                library[i]->print();
                return;
            }
        }
        std::cout << "No title from catalog matches ISBN number:" << str << std::endl;
    }

    if(isIssn){
        for(int i = library.getDividerInd() + 1; i < library.getCatalogSize(); ++i){
            if(dynamic_cast<Series*>(library[i])->getIssn() == str){
                library[i]->print();
                return;
            }
        }
        std::cout << "No title from catalog matches ISSN number:" << str << std::endl;
        return; 
    }
    std::cout << "Invalid ISBN/ISNN" << std::endl;
}

void Commands::user_find(const Library& library, const UserBase& userBase, const CommandInfo& command){
    String option = command.getValues()[0];
    String optionStr = command.getValues()[1];

    if(option == "name"){
        for(int i = 0; i < userBase.getUsersCount(); ++i){
            if(userBase[i]->getUsername() == optionStr){
                userBase[i]->print();
                return;
            }
        }
        std::cout << "No user with username: " << optionStr << " in our system" << std::endl;
        return;
    }

    unsigned readersCount = userBase.getFirstAdminInd();
    if(option == "ID"){
        if(String::convertToNumber(optionStr) == -1){
            std::cout << "You have passed invalid id" << std::endl;
            return;
        }
        unsigned optionId = String::convertToNumber(optionStr);
        for(int i = 0; i < readersCount; ++i){
            Reader* user = dynamic_cast<Reader*>(userBase[i]);
            for(int j = 0; j < user->getBItemsCount(); ++j){
                if(user->getBItem(j).getItemPtr()->getId() == optionId){
                    userBase[i]->print();
                    return;
                }
            }
        }
        std::cout << "No user borrowed item with id:" << optionId << " found" << std::endl;
        return; 
    }

    if(option == "state"){
        Date now;
        if(optionStr == "overdue"){
            for(int i = 0; i < readersCount; ++i){
                Reader* user = dynamic_cast<Reader*>(userBase[i]);
                for(int j = 0; j < user->getBItemsCount(); ++j){
                    if(user->getBItem(j).getReturnDate() < now  && library.getItemById(user->getBItem(j).getItemPtr()->getId())->getIsTaken()){
                        user->print();
                    }
                }
            }
        }
        
        if(optionStr == "reader"){
            Date monthAgo;
            monthAgo.removeMonth();
            for(int i = 0; i < readersCount; ++i){
                Reader* user = dynamic_cast<Reader*>(userBase[i]);
                unsigned countItems = 0;
                for(int j = 0; j < user->getBItemsCount(); ++j){
                    if(user->getBItem(j).getCheckoutDate() >= monthAgo){
                        countItems++;
                    }
                }
                if(countItems > 5){
                    user->print();
                }
            }
        }

        if(optionStr == "inactive"){
            Date threeMonthsAgo;
            for(int i = 0; i < 3; ++i)
                threeMonthsAgo.removeMonth();

            for(int i = 0; i < readersCount; ++i){
                Reader* user = dynamic_cast<Reader*>(userBase[i]);
                bool hasBorrowedTheseThreeMonths;
                for(int j = 0; j < user->getBItemsCount(); ++j){
                    if(user->getBItem(j).getCheckoutDate() >= threeMonthsAgo){
                        hasBorrowedTheseThreeMonths = false;
                        break;
                    }
                }
                if(!hasBorrowedTheseThreeMonths){
                    user->print();
                }
            }
        }
    }
}

void Commands::user_add(UserBase& userBase, const CommandInfo& command){
    String username = command.getValues()[0], password = command.getValues()[1];
    bool isAdmin = command.getValuesCount() == 3;

    if(userBase.sameUsernameExists(username)){
        std::cout << "Username: " << username << " is taken" << std::endl;
        return;
    }
    if(userBase.samePasswordExists(password)){
        std::cout << "This password is taken" << std::endl;
        return;
    }

    User* newUser;
    Date date;
    if(isAdmin){
        String email, department;
        do{
            std::cout << "Enter work email: ";
            std::cin >> email;
        }while(!Administrator::isValidEmail(email));

        do{
            std::cout << "Enter department: ";
            std::cin >> department;
        }while(!Administrator::isValidDepartment(department));

        newUser = new Administrator(username, password, date, date, email, department);
    }
    else{
        newUser = new Reader(username, password, date, date);
    }
    userBase.addUser(newUser);
    std::cout << "User " << username << " successfully added to the system" << std::endl;
}

void Commands::user_remove(UserBase& userBase, const CommandInfo& command){
    String username = command.getValues()[0];

    if(!userBase.sameUsernameExists(username)){
        std::cout << "No user with username: " << username << " found in our system" <<std::endl;
        return;
    }

    userBase.removeUser(username);
    std::cout << "User " << username << " successfully removed from system" << std::endl;
}

void Commands::user_change(UserBase& userBase, const CommandInfo& command){
    if(command.getValuesCount() == 0){
        String password;
        do{
        std::cout << "(If you'd like to refuse the command press 1)\nEnter old password: ";
        std::cin >> password;
        }while(!User::areSamePasswords(password, userBase.getLoggedUser()->getPassword()) && password != "1");
        
        if(password == "1")
            return;

        do{
            std::cout << "Enter new password: ";
            std::cin >> password;
        }while(password == " " || password == "" || password.getSize() == 5);

        for(int i = 0; i < userBase.getFirstAdminInd(); ++i){
            if(userBase[i]->getUsername() == userBase.getLoggedUser()->getUsername()){
                userBase[i]->setPassword(password);
                std::cout << "Password successfully changed for user " << userBase[i]->getUsername() << std::endl;
                return;
            }
        }
    }
    if(userBase.getLoggedUser()->getType() != ADMINISTRATOR){
        std::cout << "You do not have access to this command" << std::endl;
        return;
    }

    String username = command.getValues()[0];
    String password;
    do{
        std::cout << "Enter new password: ";
        std::cin >> password;
    }while(password == "" || password == " " || password.getSize() < 5);
    for(int i = 0; i < userBase.getUsersCount(); ++i){
        if(userBase[i]->getUsername() == username){
            userBase[i]->setPassword(password);
            std::cout << "You have successfully changed the password for user " << username << std::endl;
            return;
        }
    }
    std::cout << "No user with username: " << username << "found" << std::endl; 
}

void Commands::take(Library& library, UserBase& userBase, const CommandInfo& command){
    String idStr = command.getValues()[0];
    int id = String::convertToNumber(idStr);
    if(id == -1){
        std::cout << "Invalid value for id" << std::endl;
        return;
    }

    for(int i = 0; i < library.getCatalogSize(); ++i){
        if(library[i]->getId() == id && !library[i]->getIsTaken()){
            library[i]->setIsTaken(true);
            dynamic_cast<Reader*>(userBase.getLoggedUser())->borrowItem(library[i]);
            std::cout << "Item with id:" << id << " borrowed successfully by user " << userBase.getLoggedUser()->getUsername() << std::endl; 
            return;
        }
    }
    std::cout << "No title from our catalog matches id:" << id << " or it is taken" << std::endl;
}

void Commands::return_(Library& library, UserBase& userBase, const CommandInfo& command){
    String idStr = command.getValues()[0];
    if(String::convertToNumber(idStr) == -1){
        std::cout << "Invalid value for id" << std::endl;
        return;
    }
    unsigned id = String::convertToNumber(idStr);

    bool hasBorrowedTheItem = false;

    Reader* user = dynamic_cast<Reader*>(userBase.getLoggedUser());
    for(int i = 0; i < user->getBItemsCount(); ++i){
        if(user->getBItem(i).getItemPtr()->getId() == id){
            hasBorrowedTheItem = true;
        }
    }

    if(hasBorrowedTheItem){
        user->removeItemFromList(id);
        library.removeItemFromCatalog(id);
        return;
    }
    std::cout << "You have not borrowed an item with id:" << id << std::endl;
}



CommandInfo Commands::recognizeCommand(const char* str){
    int spacesCount = 0;

    for(int i = 0; str[i] != '\0'; ++i){
        if(str[i] == ' ') 
            spacesCount++;
    }

    unsigned numOfWords = spacesCount + 1;
    String* words = new String[numOfWords];

    int k = 0;
    for(int i = 0; i < numOfWords; ++i){
        for(; str[k] != ' '; ++k){
            words[i] += str[k];
        }
        ++k;
    }

    if(words[0] == "help")
        return CommandInfo(Help, "help");
    if(words[0] == "login")
        return CommandInfo(Login, "login");
    if(words[0] == "logout")
        return CommandInfo(Logout, "logout");
    if(words[0] == "exit")
        return CommandInfo(Exit, "exit");

    if(words[0] == "books" || words[0] == "book"){
        if(numOfWords == 1){
            std::cout << "Incomplete command" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        if(words[1] == "all"){
            return CommandInfo(BooksAll, "books all");
        }
        if(words[1] == "add"){
            return CommandInfo(BooksAdd, "books add");
        }
        if(words[1] == "remove"){
            return CommandInfo(BooksRemove, "books remove");
        }
        if(words[1] == "view"){
            if(numOfWords == 2){
                std::cout << "Incomplete command, you should specify the book id" << std::endl;
                return CommandInfo(Invalid, "invalid command");
            }
            String values[1]; values[0] = words[2];
            return CommandInfo(BooksView, "books_view", values, 1, 0, 0, "none");
        }
        if(words[1] == "find"){
            if(numOfWords == 2 || numOfWords == 3){
                std::cout << "Incomplete command, correct command format: books find <option><option_string>[sort <key> [asc|desc]]" << std::endl;
                return CommandInfo(Invalid, "invalid command");
            }
            if(words[2] == "title" || words[2] == "author" || words[2] == "tag"){
                if(words[numOfWords - 1] == "asc" || words[numOfWords - 1] == "desc"){
                    if((words[numOfWords - 2] == "title" || words[numOfWords - 2] == "author" || words[numOfWords - 2] == "publisher" || words[numOfWords - 2] == "year" || words[numOfWords - 2] == "genre" || words[numOfWords - 2] == "rating") && words[numOfWords - 3] == "sort"){
                        String optionStr;
                        for(int i = 3; i < numOfWords - 3; ++i){
                            optionStr += words[i];
                            if(i != numOfWords - 4)
                                optionStr += ' ';
                        }
                        String values[2];
                        values[0] = words[2]; values[1] = optionStr;
                        bool isAscending = words[numOfWords - 1] == "asc";
                        return CommandInfo(BooksFind, "books find", values, 2, true, isAscending, words[numOfWords - 2]);
                    }
                    std::cout << "Wrong sort command order or wrong sort key, correct command format: books find <option>" <<
                    "<option_string>[sort <key> [asc|desc]], where key is: title/author/publisher/year/genre/rating" << std::endl;
                    return CommandInfo(Invalid, "invalid command");
                }
                if(words[numOfWords - 1] == "title" || words[numOfWords - 1] == "author" || words[numOfWords - 1] == "publisher" || words[numOfWords - 1] == "year" || words[numOfWords - 1] == "genre" || words[numOfWords - 1] == "rating"){
                    if(words[numOfWords - 2] == "sort"){
                        String optionStr;
                        for(int i = 3; i < numOfWords - 2; ++i){
                            optionStr += words[i];
                            if(i != numOfWords - 3)
                                optionStr += ' ';
                        }
                        String values[2];
                        values[0] = words[2]; values[1] = optionStr;
                        return CommandInfo(BooksFind, "books find", values, 2, true, true, words[numOfWords - 1]);
                    }
                }
                String optionStr;
                for(int i = 3; i < numOfWords; ++i){
                    optionStr += words[i];
                    if(i != numOfWords - 1)
                        optionStr += ' ';
                }
                String values[2];
                values[0] = words[2]; values[1] = optionStr;
                return CommandInfo(BooksFind, "books find", values, 2, false, false, "no");
            }
            std::cout << "Wrong command, right command format: books find <option> <option_string> [sort <key> [asc|desc]], where <option> should be: title/author/tag" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        std::cout << "Unrecognozed command, perhaps you mean books find/books all/books add/books remove/books view?" << std::endl;
        return CommandInfo(Invalid, "invalid command");
    }

    if(words[0] == "series"){
        if(numOfWords == 1){
            std::cout << "Incomplete command" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        if(words[1] == "all"){
            return CommandInfo(SeriesAll, "series all");
        }
        if(words[1] == "add"){
            return CommandInfo(SeriesAdd, "series add");
        }
        if(words[1] == "remove"){
            return CommandInfo(SeriesRemove, "series remove");
        }
        if(words[1] == "view"){
            if(numOfWords == 2){
                std::cout << "Incomplete command, you should specify the series id" << std::endl;
                return CommandInfo(Invalid, "invalid command");
            }
            String values[1]; values[0] = words[2];
            return CommandInfo(SeriesView, "series_view", values, 1, 0, 0, "none");
        }
        if(words[1] == "find"){
            if(numOfWords == 2 || numOfWords == 3){
                std::cout << "Incomplete command, correct command format: series find <option><option_string>[sort <key> [asc|desc]]" << std::endl;
                return CommandInfo(Invalid, "invalid command");
            }
            if(words[2] == "title" || words[2] == "author" || words[2] == "tag"){
                if(words[numOfWords - 1] == "asc" || words[numOfWords - 1] == "desc"){
                    if((words[numOfWords - 2] == "title" || words[numOfWords - 2] == "issue" || words[numOfWords - 2] == "publisher" || words[numOfWords - 2] == "year" || words[numOfWords - 2] == "genre" || words[numOfWords - 2] == "rating") && words[numOfWords - 3] == "sort"){
                        String optionStr;
                        for(int i = 3; i < numOfWords - 3; ++i){
                            optionStr += words[i];

                            if(i != numOfWords - 4)
                                optionStr += ' ';
                        }
                        String values[2];
                        values[0] = words[2]; values[1] = optionStr;
                        bool isAscending = words[numOfWords - 1] == "asc";
                        return CommandInfo(SeriesFind, "series find", values, 2, true, isAscending, words[numOfWords - 2]);
                    }
                    std::cout << "Wrong sort command order or wrong sort key, correct command format: series find <option>" <<
                    "<option_string>[sort <key> [asc|desc]], where key is: title/publisher/year/issue/genre/rating" << std::endl;
                    return CommandInfo(Invalid, "invalid command");
                }
                if(words[numOfWords - 1] == "title" || words[numOfWords - 1] == "issue" || words[numOfWords - 1] == "publisher" || words[numOfWords - 1] == "year" || words[numOfWords - 1] == "genre" || words[numOfWords - 1] == "rating"){
                    if(words[numOfWords - 2] == "sort"){
                        String optionStr;
                        for(int i = 3; i < numOfWords - 2; ++i){
                            optionStr += words[i];
                            if(i != numOfWords - 3)
                                optionStr += ' ';
                        }
                        String values[2];
                        values[0] = words[2]; values[1] = optionStr;
                        return CommandInfo(SeriesFind, "series find", values, 2, true, true, words[numOfWords - 1]);
                    }
                }
                String optionStr;
                for(int i = 3; i < numOfWords; ++i){
                    optionStr += words[i];
                    if(i != numOfWords - 1)
                        optionStr += ' ';
                }
                String values[2]; 
                values[0] = words[2]; values[1] = optionStr;
                return CommandInfo(SeriesFind, "series find", values, 2, false, false, "no");
            }
            std::cout << "Wrong command, right command format: series find <option> <option_string> [sort <key> [asc|desc]], where <option> should be: title/author/tag" << std::endl;
            return CommandInfo(Invalid, "invalid command");

        }
        std::cout << "Unrecognozed command, perhaps you mean series find/ series all/ series add/ series remove?" << std::endl;
    }

    if(words[0] == "list"){
        if(numOfWords == 1){
            std::cout << "Incomplete command" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        if(words[1] == "all"){
            return CommandInfo(ListAll, "list all");
        }
        if(words[1] == "info"){
            String values[1];
            values[0] = words[2];
            return CommandInfo(ListInfo, "list info", values, 1, false, false, "none"); 
        }
        if(words[1] == "find"){
            if(numOfWords == 2 || numOfWords == 3){
                std::cout << "Incomplete command, correct command format: list find <option><option_string>[sort <key> [asc|desc]]" << std::endl;
                return CommandInfo(Invalid, "invalid command");
            }
            if(words[2] == "title" || words[2] == "author" || words[2] == "tag"){
                if(words[numOfWords - 1] == "asc" || words[numOfWords - 1] == "desc"){
                    if((words[numOfWords - 2] == "title" || words[numOfWords - 2] == "publisher" || words[numOfWords - 2] == "genre" || words[numOfWords - 2] == "rating") && words[numOfWords - 3] == "sort"){
                        String optionStr;
                        for(int i = 3; i < numOfWords - 3; ++i){
                            optionStr += words[i];
                            if(i != numOfWords - 4)
                                optionStr += ' ';
                        }
                        String values[2];
                        values[0] = words[2]; values[1] = optionStr;
                        bool isAscending = words[numOfWords - 1] == "asc";
                        return CommandInfo(ListFind, "list find", values, 2, true, isAscending, words[numOfWords - 2]);
                    }
                    std::cout << "Wrong sort command order or wrong sort key, correct command format: list find <option>" <<
                    "<option_string>[sort <key> [asc|desc]], where key is: title/publisher/genre/rating" << std::endl;
                    return CommandInfo(Invalid, "invalid command");
                }
                if(words[numOfWords - 1] == "title" || words[numOfWords - 1] == "publisher" || words[numOfWords - 1] == "genre" || words[numOfWords - 1] == "rating"){
                    if(words[numOfWords - 2] == "sort"){
                        String optionStr;
                        for(int i = 3; i < numOfWords - 2; ++i){
                            optionStr += words[i];
                            if(i != numOfWords - 3)
                                optionStr += ' ';
                        }
                        String values[2];
                        values[0] = words[2]; values[1] = optionStr;
                        return CommandInfo(ListFind, "list find", values, 2, true, true, words[numOfWords - 1]);
                    }
                }
                String optionStr;
                for(int i = 3; i < numOfWords; ++i){
                    optionStr += words[i];
                    if(i != numOfWords - 1)
                        optionStr += ' ';
                }
                String values[2];
                values[0] = words[2]; values[1] = optionStr;
                return CommandInfo(ListFind, "list find", values, 2, false, false, "no");
            }
            std::cout << "Wrong command, right command format: list find <option> <option_string> [sort <key> [asc|desc]], where <option> should be: title/author/tag" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        std::cout << "Unrecognized command, perhaps you mean list find/list all/list info?" << std::endl;
    }

    if(words[0] == "user"){
        if(numOfWords == 1){
            std::cout << "Incomplete command" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        if(words[1] == "find"){
            if(numOfWords == 2 || numOfWords == 3){
                std::cout << "Incomplete command,  correct command format: user find <option><option string>" << std::endl;
            }
            if(words[2] == "name"){
                String values[2];
                values[0] = "name"; values[1] = words[3];
                return CommandInfo(UserFind, "user find", values, 2, false, false, "none");
            }
            if(words[2] == "ID"){
                String values[2];
                values[0] = "ID"; values[1] = words[3];
                return CommandInfo(UserFind, "user find", values, 2, false, false, "none");
            }
            if(words[2] == "state"){
                if(words[3] == "overdue" || words[3] == "reader" || words[3] == "inactive"){
                    String values[2];
                    values[0] = "state"; values[1] = words[3];
                    return CommandInfo(UserFind, "user find", values, 2, false, false, "none");
                }
                std::cout << "Unrecognozed command, correct command format: user find state <option_string>, where <option_string> is overdue/reader/inactive" << std::endl;
                return CommandInfo(Invalid, "invalid command");
            }
            std::cout << "Unrecognozed command, correct command format: user find <option><option_string>, where option is name/ID/state" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        if(words[1] == "add"){
            if(numOfWords < 4){
                std::cout << "Incomplete command" << std::endl;
                return CommandInfo(Invalid, "invalid command");
            }
            if(numOfWords >= 5 && words[4] == "admin"){
                String values[3];
                values[0] = words[2]; values[1] = words[3]; values[2] = "admin";
                return CommandInfo(UserAdd, "user add", values, 3, false, false, "none");
            }
            String values[2];
            values[0] = words[2]; values[1] = words[3];
            return CommandInfo(UserAdd, "user add", values, 2, false, false, "none");
        }
        if(words[1] == "remove"){
            String values[1]; values[0] == words[2];
            return CommandInfo(UserRemove, "user remove", values, 1, false, false, "none");
        }
        if(words[1] == "change"){
            if(numOfWords >= 3){
                String values[1]; values[0] = words[2];
                return CommandInfo(UserChange, "user change", values, 1, false, false, "none");
            }
            return CommandInfo(UserChange, "user change");
        }
        std::cout << "Unrecognozed command, perhaps you mean user find/user add/ user remove/user change?" << std::endl;
        return CommandInfo(Invalid, "invalid command");
    }
    if(words[0] == "take" || words[0] == "return"){
        if(numOfWords == 1){
            std::cout << "Incomplete command" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        String values[1]; values[0] == words[1];
        if(words[0] == "take")
            return CommandInfo(Take, "take", values, 1, false, false, "none");
        return CommandInfo(Return, "return", values, 1, false, false, "none");
    }

    std::cout << "Unrecognized command" << std::endl;
    return CommandInfo(Invalid, "invalid command");
}

CommandInfo::CommandInfo(const SupportedCommands& type, const String& title, String* values, unsigned valuesCount, bool hasSort, bool isAscending, const String& sortKey){
   this->type = type;
   this->title = title;

   this->values = new String[valuesCount];
   for(int i = 0; i < valuesCount; ++i){
        this->values[i] = values[i];
    }
    this->valuesCount = valuesCount;
    this->hasSort = hasSort;
    this->isAscending = isAscending;
    this->sortKey = sortKey;
}

CommandInfo::CommandInfo(const SupportedCommands& type, const String& text){
    this->type = type;
    this->title = text;
    this->values = nullptr;
    this->valuesCount = 0;
    this->hasSort = false;
    this->isAscending = false;
    this->sortKey = "none";
}

const SupportedCommands& CommandInfo::getType() const{ return this->type; }
const String* CommandInfo::getValues() const{ return this->values; }
unsigned CommandInfo::getValuesCount() const{ return this->valuesCount; }
bool CommandInfo::getHasSort() const{ return this->hasSort; }
bool CommandInfo::getIsAscending() const{ return this->isAscending; }
const String& CommandInfo::getSortKey() const{ return this->sortKey; }

void CommandInfo::print() const{
    std::cout << title << "|" << valuesCount << "|";
    for(int i = 0; i < valuesCount; ++i){
        std::cout << values[i] << "|";
    }
    std::cout << (hasSort ? "sort" : "no sort") << "|";
    if(hasSort){
        std::cout << (isAscending ? "asc" : "desc") << "|" << sortKey << "|";
    }
    std::cout << std::endl;
}

void Commands::reverseArr(Paper** arr, unsigned size){
    Paper* temp;
    for(int i = 0; i < size / 2; ++i){
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}