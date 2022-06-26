#include "Commands.h"

void Commands::help(){
    std::cout << "\nSupportedCommands:\n\n";
    std::cout << "[1]login\n[2]logout\n[3]books all\n[4]books find <option> <option string> [sort <key> [asc|desc]]" <<
    "\n    where <option> is title/author/tag, <option string> is the filter value,\n    <key> is the sort key(title/author/year/rating)\n" <<
    "[5]books add\n[6]books remove\n[7]books view <ID>\n[8]series all\n[9]series find <option> <option string> [sort <key> [asc|desc]]" <<
    " where sort key is title/issue/date/rating\n[10]series add\n[11]series remove\n" <<
    "[12]series view <ID>\n[13]list all\n[14]list find <option> <option string> [sort <key> [asc|desc]]" << 
    " where sort key is title/publisher/genre/rating/id\n[15]list info <isbn/issn>\n" <<
    "[16]user find <option> <option string> where <option> is name/ID/state,\n    <option string> is respectively <username>/<item's id>/<overdue/reader/inactive>\n" << 
    "[17]user add <username> <password> [admin]\n[18]user remove <username>\n[19]user change [<username>] where typing <username> changes user's password(only for admins)" <<
    ", without it you change logged user's password\n[20]take <ID>\n[21]return <ID>\n[22]exit\n\n";
}

void Commands::login(UserBase& userBase){
    if(userBase.showIfHasLoggedIn() == true){
        std::cout << "\nYou are already logged in.\n\n";
        return;
    }
    String username, password;
    std::cout << "\nEnter your username: " << std::endl;
    std::cin >> username;
    std::cout << "\nEnter your password: " << std::endl;
    std::cin >> password;

    User* user;
    unsigned size = userBase.getUsersCount();
    for(int i = 0; i < size; ++i){
        if(userBase[i]->getUsername() == username && userBase[i]->getPassword() == password){
            std::cout << "\nWelcome " << username << "!\n\n";
            userBase.logInUser(userBase[i]);
            userBase.setHasLoggedIn(true);
            return;
        }
    }
    std::cout << "\nIncorrect username or password\n\n";
}

void Commands::logout(UserBase& userBase){
    if(!userBase.showIfHasLoggedIn()){
        std::cout << "\nThere is no logged in user\n\n";
        return;
    }
    userBase.logOutUser();
    userBase.setHasLoggedIn(false);
    std::cout << "\nYou have logged out\n\n";
    return;
}

void Commands::books_all(const Library& library){
    if(library.getCatalogSize() == 1){
        std::cout << "\nEmpty\n\n";
        return;
    }

    for(int i = 0; library[i]->getTitle() != "Divider1"; ++i){
        library[i]->listAll();
    }
    std::cout << std::endl;
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
            if(Item::isAmongKeywords(dynamic_cast<Book*>(library[i])->getKeywords(), optionStr)){
                tempLib.addItemToCatalog(library[i]);
            }
        }
    }
    if(command.getHasSort()){
        String sortKey = command.getSortKey();
        if(sortKey == "title"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(strcmp(tempLib[j]->getTitle().getData(), tempLib[i]->getTitle().getData()) < 0){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }   
        }
        if(sortKey == "author"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    String surname1 = String::getSurname(dynamic_cast<Book*>(tempLib[j])->getAuthor());
                    String surname2 = String::getSurname(dynamic_cast<Book*>(tempLib[i])->getAuthor());
                    if(strcmp(surname1.getData(), surname2.getData()) < 0){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }  
        }
        if(sortKey == "year"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(dynamic_cast<Book*>(tempLib[j])->getYearOfPublishing() < dynamic_cast<Book*>(tempLib[i])->getYearOfPublishing()){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }
        }
        if(sortKey == "rating"){
            for(int i = 0; i < tempLib.getDividerInd() - 1; ++i){
                for(int j = i + 1; j < tempLib.getDividerInd(); ++j){
                    if(tempLib[j]->getRating() < tempLib[i]->getRating()){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }
        }
        if(!command.getIsAscending()){
            reverseArr(tempLib.getItems(), tempLib.getDividerInd());
            for(int i = 1; i < tempLib.getDividerInd(); ++i){
                tempLib[i]->print();
                std::cout << std::endl;
            }
            return;
        }   
    }
    
    for(int i = 0; i < tempLib.getDividerInd(); ++i){
        tempLib[i]->print();
        std::cout << std::endl;
    }
}

void Commands::books_add(Library& library){
    Book* newBook = new Book();
    newBook->readFromUser();
    library.addItemToCatalog(newBook);
    library.writeInFile();
    std::cout << "\nItem " << newBook->getTitle() << " with id:" << newBook->getId() << " added to catalog\n\n";
}

void Commands::books_remove(Library& library){
    String idStr;
    do{
        std::cout << "\nEnter the id of the book you would like to remove: ";
        std::cin >> idStr;
    }while(String::convertToNumber(idStr) == -1);

    unsigned id = String::convertToNumber(idStr);


    if(library.getItemById(id) == nullptr){
        std::cout << "\nNo item from our catalog matches id: " << id << "\n\n";
        return;
    } 
    if(library.getItemById(id)->getType() != BOOK){
        std::cout << "\nNo book from our catalog matches id: " << id << ", perhaps you mean series?\n\n";
        return;
    }   

    library.removeItemFromCatalog(id);
    library.writeInFile();
    std::cout << "\nItem with id: " << id << " successfully removed from catalog\n\n";
}

void Commands::books_view(const Library& library, const CommandInfo& command){
    String idStr = command.getValues()[0];
    int id = String::convertToNumber(idStr);
    if(id == -1){
        return;
    }
    if(library.getItemById(id) == nullptr || library.getItemById(id)->getType() != BOOK){
        std::cout << "\nNo book in our system with id: " << id << "\n\n";
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
            for(int j = 0; j < series->getArticlesCount(); ++j){
                if(Item::isAmongKeywords(series->getContent()[j].getKeywords(), optionStr)){
                    tempLib.addItemToCatalog(library[i]);
                }
            }
        }
    }
    
    if(command.getHasSort()){
        String sortKey = command.getSortKey();
        if(sortKey == "title"){
            for(int i = 1; i < tempLib.getCatalogSize(); ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if(strcmp(tempLib[j]->getTitle().getData(), tempLib[i]->getTitle().getData()) < 0){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }   
        }
        if(sortKey == "issue"){
            for(int i = 1; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if(dynamic_cast<Series*>(tempLib[j])->getIssue() < dynamic_cast<Series*>(tempLib[i])->getIssue()){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }
        }
        if(sortKey == "date"){
            for(int i = 1; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    Series* series = dynamic_cast<Series*>(tempLib[j]);
                    Series* seriesMin = dynamic_cast<Series*>((tempLib[i]));
                    if(Date::convertToDate(series->getDatePublishing()) < Date::convertToDate(seriesMin->getDatePublishing())){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }
        }
        if(sortKey == "rating"){
            for(int i = 1; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if((tempLib[j]->getRating()) < (tempLib[i]->getRating())){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }
        }
        if(!command.getIsAscending()){
            reverseArr(tempLib.getItems(), tempLib.getCatalogSize());
            for(int i = 0; i < tempLib.getCatalogSize() - 1; ++i){
                tempLib[i]->print();
                std::cout << std::endl;
            }
            return;
        }
    }
    for(int i = 1; i < tempLib.getCatalogSize(); ++i){
        tempLib[i]->print();
        std::cout << std::endl;
    }
}

void Commands::series_all(const Library& library){
    if(library.getCatalogSize() == 1){
        std::cout << "\nEmpty\n\n";
        return;
    }
    for(int i = library.getDividerInd() + 1; i < library.getCatalogSize(); ++i){
        library[i]->listAll();
    }
    std::cout << std::endl;
}

void Commands::series_add(Library& library){
    Series* newSeries = new Series();
    newSeries->readFromUser();
    library.addItemToCatalog(newSeries);
    library.writeInFile();
    std::cout << "\nItem " << newSeries->getTitle() << " with id:" << newSeries->getId() << " added to catalog\n\n";
}

void Commands::series_remove(Library& library){
    String idStr;
    unsigned id = String::convertToNumber(idStr);

    do{
        std::cout << "\nEnter the id of the series you would like to remove: ";
        std::cin >> idStr;
    }while(String::convertToNumber(idStr) == -1);

    if(library.getItemById(id) == nullptr){
        std::cout << "\nNo item with id: " << id << "found in our catalog\n\n";
        return;
    }

    if(library.getItemById(id)->getType() != SERIES){
        std::cout << "\nNo series with id: " << id << "found in our catalog, perhaps you mean book?\n\n";
        return;
    }

    library.removeItemFromCatalog(id);   
    library.writeInFile();
    std::cout << "\nItem with id: " << id << "successfully removed from catalog\n\n";
}

void Commands::series_view(const Library& library, const CommandInfo& command){
    String idStr = command.getValues()[0];
    int id = String::convertToNumber(idStr);
    if(id == -1){
        return;
    }
    if(library.getItemById(id) == nullptr || library.getItemById(id)->getType() != SERIES){
        std::cout << "\nNo series in our system with id: " << id << "\n\n";
        return;  
    }
    library.getItemById(id)->print();
}

void Commands::list_find(const Library& library, const CommandInfo& command){
    String option = command.getValues()[0];
    String optionStr = command.getValues()[1];
    unsigned booksCount = library.getDividerInd();
    Library tempLib;

    if(option == "title"){
        for(int i = 0; i < library.getCatalogSize(); ++i){
            if(library[i]->getTitle() == optionStr){
                tempLib.addItemToCatalog(library[i]);
            }
        }
    }
    if(option == "author"){
        for(int i = 0; i < booksCount; ++i){
            if(dynamic_cast<Book*>(library[i])->getAuthor() == optionStr){
                tempLib.addItemToCatalog(library[i]);
            }
        }
        for(int i = booksCount + 1; i < library.getCatalogSize(); ++i){
            Series* series = dynamic_cast<Series*>(library[i]);
            for(int j = 0; j < series->getArticlesCount(); ++j){
                if(series->getContent()[j].getAuthor() == optionStr){
                    tempLib.addItemToCatalog(library[i]);
                }
            }
        }
    }
    if(option == "tag"){
        for(int i = 0; i < booksCount; ++i){
            if(Item::isAmongKeywords(dynamic_cast<Book*>(library[i])->getKeywords(), optionStr)){
                tempLib.addItemToCatalog(library[i]);
            }
        }
        for(int i = booksCount + 1; i < library.getCatalogSize(); ++i){
            Series* series = dynamic_cast<Series*>(library[i]);
            for(int j = 0; j < series->getArticlesCount(); ++j){
                if(Item::isAmongKeywords(series->getContent()[j].getKeywords(), optionStr)){
                    tempLib.addItemToCatalog(library[i]);
                }
            }
        }
    }
    if(command.getHasSort()){
        String sortKey = command.getSortKey();
        if(sortKey == "title"){
            for(int i = 0; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if(strcmp(tempLib[j]->getTitle().getData(), tempLib[i]->getTitle().getData()) < 0){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }   
        }
        if(sortKey == "genre"){
            for(int i = 0; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if(strcmp(tempLib[j]->getGenre().getData(), tempLib[i]->getGenre().getData()) < 0){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            } 
        }
        if(sortKey == "publisher"){
            for(int i = 0; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if(strcmp(tempLib[j]->getPublisher().getData(), tempLib[i]->getPublisher().getData()) < 0){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            } 
        }
        if(sortKey == "rating"){
            for(int i = 0; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if((tempLib[j]->getRating()) < (tempLib[i]->getRating())){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }
        }
        if(sortKey == "id"){
            for(int i = 0; i < tempLib.getCatalogSize() - 1; ++i){
                for(int j = i + 1; j < tempLib.getCatalogSize(); ++j){
                    if(tempLib[j]->getId() < tempLib[i]->getId()){
                        Item* temp = tempLib[i];
                        tempLib[i] = tempLib[j];
                        tempLib[j] = temp;
                    }
                }
            }
        }
        if(!command.getIsAscending()){
            reverseArr(tempLib.getItems(), tempLib.getCatalogSize());
        }
    }
    for(int i = 0; i < tempLib.getCatalogSize(); ++i){
        if(tempLib[i]->getTitle() == "Divider1")
            continue;
        tempLib[i]->print();
        std::cout << std::endl;
    }
}

void Commands::list_all(const Library& library){
    if(library.getCatalogSize() == 1){
        std::cout << "\nEmpty\n\n";
        return;
    }
    for(int i = 0; i < library.getCatalogSize(); ++i){
        if(i == library.getDividerInd())
            continue;
        library[i]->listAll();
    }
    std::cout << std::endl;
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
        std::cout << "\nNo title from catalog matches ISBN number:" << str << "\n\n";
    }

    if(isIssn){
        for(int i = library.getDividerInd() + 1; i < library.getCatalogSize(); ++i){
            if(dynamic_cast<Series*>(library[i])->getIssn() == str){
                library[i]->print();
                return;
            }
        }
        std::cout << "\nNo title from catalog matches ISSN number:" << str << "\n\n";
        return; 
    }
    std::cout << "\nInvalid ISBN/ISNN\n\n";
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
        std::cout << "\nNo user with username: " << optionStr << " in our system\n\n";
        return;
    }

    unsigned readersCount = userBase.getFirstAdminInd();
    if(option == "ID"){
        int optionId = String::convertToNumber(optionStr);
        if(optionId == -1){
            return;
        }
        for(int i = 0; i < readersCount; ++i){
            Reader* user = dynamic_cast<Reader*>(userBase[i]);
            for(int j = 0; j < user->getBItemsCount(); ++j){
                if(user->getBItem(j).getItemPtr()->getId() == optionId){
                    userBase[i]->print();
                }
            }
        }
    }

    if(option == "state"){
        Date now;
        if(optionStr == "overdue"){
            for(int i = 0, k = 1; i < readersCount; ++i){
                Reader* user = dynamic_cast<Reader*>(userBase[i]);
                bool hasOverdue = false;
                for(int j = 0; j < user->getBItemsCount() && !hasOverdue; ++j){
                    if(user->getBItem(j).getReturnDate() < now  && library.getItemById(user->getBItem(j).getItemPtr()->getId())->getIsTaken()){
                        hasOverdue = true;
                    }
                }
                if(hasOverdue){
                    std::cout << k << ") ";
                    ++k;
                    user->print();
                }
            }
        }
        
        if(optionStr == "reader"){
            Date monthAgo;
            monthAgo.removeMonth();
            for(int i = 0, k = 1; i < readersCount; ++i){
                Reader* user = dynamic_cast<Reader*>(userBase[i]);
                unsigned countItems = 0;
                for(int j = 0; j < user->getBItemsCount(); ++j){
                    if(user->getBItem(j).getCheckoutDate() >= monthAgo){
                        countItems++;
                    }
                }
                if(countItems > 5){
                    std::cout << k << ") ";
                    user->print();
                    ++k;
                }
            }
        }

        if(optionStr == "inactive"){
            Date threeMonthsAgo;
            for(int i = 0; i < 3; ++i)
                threeMonthsAgo.removeMonth();
            std::cout << "\nUsers that have not borrowed an item since: " << threeMonthsAgo << "\n\n";

            for(int i = 0, k = 1; i < readersCount; ++i){
                Reader* user = dynamic_cast<Reader*>(userBase[i]);
                bool hasBorrowedTheseThreeMonths = false;
                for(int j = 0; j < user->getBItemsCount(); ++j){
                    if(user->getBItem(j).getCheckoutDate() >= threeMonthsAgo){
                        hasBorrowedTheseThreeMonths = true;
                        break;
                    }
                }
                if(!hasBorrowedTheseThreeMonths){
                    std::cout << k << ") ";
                    ++k;
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
        std::cout << "\nUsername: " << username << " is taken\n\n";
        return;
    }
    if(userBase.samePasswordExists(password)){
        std::cout << "\nThis password is taken\n\n";
        return;
    }
    if(!User::isValidPasswords(password)){
        return;
    }

    User* newUser;
    Date date;
    if(isAdmin){
        String email, department;
        do{
            std::cout << "\nEnter work email: ";
            std::cin >> email;
        }while(!Administrator::isValidEmail(email));

        do{
            std::cout << "\nEnter department: ";
            std::cin >> department;
        }while(!Administrator::isValidDepartment(department));

        newUser = new Administrator(username, password, date, date, email, department);
    }
    else{
        newUser = new Reader(username, password, date, date);
    }
    userBase.addUser(newUser);
    userBase.writeInFile();
    std::cout << "\nUser " << username << " successfully added to the system\n\n";
}

void Commands::user_remove(UserBase& userBase, const CommandInfo& command){
    String username = command.getValues()[0];

    if(!userBase.sameUsernameExists(username)){
        std::cout << "\nNo user with username: " << username << " found in our system\n\n";
        return;
    }

    userBase.removeUser(username);
    userBase.writeInFile();
    std::cout << "\nUser " << username << " successfully removed from system\n\n";
}

void Commands::user_change(UserBase& userBase, const CommandInfo& command){
    if(command.getValuesCount() == 0){
        String password;
        do{
        std::cout << "\n(If you'd like to refuse the command press 1)\nEnter old password: ";
        std::cin >> password;
        }while(password != "1" && !User::areSamePasswords(password, userBase.getLoggedUser()->getPassword()));
        
        if(password == "1")
            return;

        do{
            std::cout << "\nEnter new password(should be at least 5 characters): ";
            std::cin >> password;
        }while(!User::isValidPasswords(password));

        for(int i = 0; i < userBase.getFirstAdminInd(); ++i){
            if(userBase[i]->getUsername() == userBase.getLoggedUser()->getUsername()){
                userBase[i]->setPassword(password);
                std::cout << "\nPassword successfully changed for user " << userBase[i]->getUsername() << "\n\n";
                userBase.writeInFile();
                return;
            }
        }
    }
    if(userBase.getLoggedUser()->getType() != ADMINISTRATOR){
        std::cout << "\nYou do not have access to this command (only for administrators)\n\n";
        return;
    }

    String username = command.getValues()[0];
    String password;
    do{
        std::cout << "\nEnter new password: ";
        std::cin >> password;
    }while(!User::isValidPasswords(password));
    for(int i = 0; i < userBase.getUsersCount(); ++i){
        if(userBase[i]->getUsername() == username){
            userBase[i]->setPassword(password);
            std::cout << "\nYou have successfully changed the password for user " << username << "\n\n";
            userBase.writeInFile();
            return;
        }
    }
    std::cout << "\nNo user with username: " << username << "found\n\n"; 
}

void Commands::take(Library& library, UserBase& userBase, const CommandInfo& command){
    String idStr = command.getValues()[0];
    int id = String::convertToNumber(idStr);
    ///Проверява дали id-то е валидно, функцията String::convertToNumber() връща -1, ако й е подаден низ, съдържащ символи, различни от цифри.
    if(id == -1){
        std::cout << "\nInvalid value for id\n\n";
        return;
    }

    if(library.getItemById(id) == nullptr){
        std::cout << "\nNo item from our catalog with id: " << id << "\n\n";
        return;
    }
    if(library.getItemById(id)->getIsTaken()){
        std::cout << "\nThe item is already taken\n\n";
        return;
    }
    
    Item* newItem = library.getItemById(id);

    library.getItemById(id)->setIsTaken(true);
    for(int i = 0; i < userBase.getUsersCount(); ++i){
        if(userBase[i]->getUsername() == userBase.getLoggedUser()->getUsername()){
            dynamic_cast<Reader*>(userBase[i])->borrowItem(library.getItemById(id));
        }
    }

    std::cout << "\nYou have successfully taken the item with id:" << id << "\n\n";
    userBase.writeInFile();
    library.writeInFile();
}

void Commands::return_(Library& library, UserBase& userBase, const CommandInfo& command){
    String idStr = command.getValues()[0];
    int id = String::convertToNumber(idStr);
    if(id == -1){
       std::cout << "\nInvalid value for id\n\n";
        return;
    }
    if(library.getItemById(id) == nullptr){
        std::cout << "\nNo item from our catalog matches id:" << id << "\n\n";
        return;
    }

    bool hasBorrowedTheItem = false;

    Reader* user = dynamic_cast<Reader*>(userBase.getLoggedUser());
    for(int i = 0; i < user->getBItemsCount(); ++i){
        if(user->getBItem(i).getItemPtr()->getId() == id){
            hasBorrowedTheItem = true;
        }
    }

    if(!hasBorrowedTheItem){
        std::cout << "\nYou have not borrowed an item with id:" << id << "\n\n";
        return; 
    }

    if(hasBorrowedTheItem && library.getItemById(id)->getIsTaken()){
        user->getBItemById(id).getItemPtr()->setIsTaken(false);
        library.getItemById(id)->setIsTaken(false);
        std::cout << "\nYou have successfully returned item with id: " << id << "\n\n";
        userBase.writeInFile();
        library.writeInFile();
        return;
    }
    std::cout << "\nYou have already returned this item\n\n";
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
        for(; str[k] != ' ' && str[k] != '\0'; ++k){
            words[i] += str[k];
        }
        k++;
    }

    if(words[0] == "load")
        return CommandInfo(LoadData, "loadData");
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
            std::cout << "\nIncomplete command\n\n";
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
                std::cout << "\nIncomplete command, you should specify the book id\n\n";
                return CommandInfo(Invalid, "invalid command");
            }
            String values[1]; values[0] = words[2];
            return CommandInfo(BooksView, "books_view", values, 1, 0, 0, "none");
        }
        if(words[1] == "find"){
            if(numOfWords == 2 || numOfWords == 3){
                std::cout << "\nIncomplete command, correct command format: books find <option><option_string>[sort <key> [asc|desc]]\n\n";
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
                    std::cout << "\nWrong sort command order or wrong sort key, correct command format: books find <option>" <<
                    "<option_string>[sort <key> [asc|desc]], where key is: title/author/publisher/year/genre/rating\n\n";
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
            std::cout << "\nWrong command, right command format: books find <option> <option_string> [sort <key> [asc|desc]], where <option> should be: title/author/tag\n\n";
            return CommandInfo(Invalid, "invalid command");
        }
        std::cout << "\nUnrecognized command, perhaps you mean books find/books all/books add/books remove/books view?\n\n";
        return CommandInfo(Invalid, "invalid command");
    }

    if(words[0] == "series"){
        if(numOfWords == 1){
            std::cout << "\nIncomplete command\n\n";
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
                std::cout << "\nIncomplete command, you should specify the series id\n\n";
                return CommandInfo(Invalid, "invalid command");
            }
            String values[1]; values[0] = words[2];
            return CommandInfo(SeriesView, "series_view", values, 1, 0, 0, "none");
        }
        if(words[1] == "find"){
            if(numOfWords == 2 || numOfWords == 3){
                std::cout << "\nIncomplete command, correct command format: series find <option><option_string>[sort <key> [asc|desc]]\n\n";
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
                    std::cout << "\nWrong sort command order or wrong sort key, correct command format: series find <option>" <<
                    "<option_string>[sort <key> [asc|desc]], where key is: title/publisher/year/issue/genre/rating\n\n";
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
            std::cout << "\nWrong command, right command format: series find <option> <option_string> [sort <key> [asc|desc]], where <option> should be: title/author/tag\n\n";
            return CommandInfo(Invalid, "invalid command");

        }
        std::cout << "\nUnrecognized command, perhaps you mean series find/series all/series add/series remove/series view?\n\n";
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
                std::cout << "\nIncomplete command, correct command format: list find <option><option_string>[sort <key> [asc|desc]]\n\n";
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
                    std::cout << "\nWrong sort command order or wrong sort key, correct command format: list find <option>" <<
                    "<option_string>[sort <key> [asc|desc]], where key is: title/publisher/genre/rating\n\n";
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
            std::cout << "\nWrong command, right command format: list find <option> <option_string> [sort <key> [asc|desc]], where <option> should be: title/author/tag\n\n";
            return CommandInfo(Invalid, "invalid command");
        }
        std::cout << "\nUnrecognized command, perhaps you mean list find/list all/list info?\n\n";
        return CommandInfo(Invalid, "invalid command");
    }

    if(words[0] == "user"){
        if(numOfWords == 1){
            std::cout << "Incomplete command" << std::endl;
            return CommandInfo(Invalid, "invalid command");
        }
        if(words[1] == "find"){
            if(numOfWords == 2 || numOfWords == 3){
                std::cout << "\nIncomplete command,  correct command format: user find <option><option string>\n\n";
                return CommandInfo(Invalid, "invalid command");
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
                std::cout << "\nUnrecognozed command, correct command format: user find state <option_string>, where <option_string> is overdue/reader/inactive\n\n";
                return CommandInfo(Invalid, "invalid command");
            }
            std::cout << "\nUnrecognozed command, correct command format: user find <option><option_string>, where option is name/ID/state\n\n";
            return CommandInfo(Invalid, "invalid command");
        }
        if(words[1] == "add"){
            if(numOfWords < 4){
                std::cout << "\nIncomplete command\n\n";
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
            if(numOfWords == 2){
                std::cout << "\nIncomplete command\n\n";
                return CommandInfo(Invalid, "invalid command");
            }
            String values[1]; values[0] = words[2];
            return CommandInfo(UserRemove, "user remove", values, 1, false, false, "none");
        }
        if(words[1] == "change"){
            if(numOfWords >= 3){
                String values[1]; values[0] = words[2];
                return CommandInfo(UserChange, "user change", values, 1, false, false, "none");
            }
            return CommandInfo(UserChange, "user change");
        }
        std::cout << "\nUnrecognozed command, perhaps you mean user find/user add/ user remove/user change?\n\n";
        return CommandInfo(Invalid, "invalid command");
    }
    if(words[0] == "take"){
        if(numOfWords == 1){
            std::cout << "\nIncomplete command, correct command format: take <ID>\n\n";
            return CommandInfo(Invalid, "invalid command");
        }
        String values[1]; values[0] = words[1];
        return CommandInfo(Take, "take", values, 1, false, false, "none");
    }
    if(words[0] == "return"){
        if(numOfWords == 1){
            std::cout << "\nIncomplete command, correct command format: return <ID>\n\n";
            return CommandInfo(Invalid, "invalid command");
        }
        String values[1]; values[0] = words[1];
        return CommandInfo(Return, "return", values, 1, false, false, "none");
    }

    std::cout << "\nUnrecognized command\n\n";
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

void Commands::reverseArr(Item** arr, unsigned size){
    Item* temp;
    for(int i = 0; i < size / 2; ++i){
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}