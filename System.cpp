#include "System.h"

void System::getCommands(){
    bool stop = false;
    do{
        std::cout << "Enter your command: " << std::endl;
        char buffer[1024];
        std::cin.getline(buffer, 1024);

        CommandInfo command = Commands::recognizeCommand(buffer);

        User* user = userBase.getLoggedUser();
        switch(command.getType()){
            case Help : Commands::help();
                break;
            case Exit : stop = true; 
                break;
            case Login : Commands::login(userBase); 
                break;
            case Logout : Commands::logout(userBase); 
                break;
            case BooksAll : 
                if(userBase.showIfHasLoggedIn())
                    Commands::books_all(library);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case BooksFind : 
                if(userBase.showIfHasLoggedIn())
                    Commands::books_find(library, command);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case BooksAdd : 
                if(userBase.showIfHasLoggedIn() && user->getType() == ADMINISTRATOR)
                    Commands::books_add(library); 
                else
                    std::cout << "\nYou do not have access to this command (only for administrators)\n\n";    
                break;
            case BooksRemove : 
                if(userBase.showIfHasLoggedIn() && user->getType() == ADMINISTRATOR)
                    Commands::books_remove(library); 
                else
                    std::cout << "\nYou do not have access to this command (only for administrators)\n\n";    
                break;
            case BooksView :
                 if(userBase.showIfHasLoggedIn())
                    Commands::books_view(library, command);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case SeriesAll : 
                if(userBase.showIfHasLoggedIn())
                    Commands::series_all(library);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case SeriesFind :
                if(userBase.showIfHasLoggedIn())
                    Commands::series_find(library, command);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case SeriesAdd :
                if(userBase.showIfHasLoggedIn() && user->getType() == ADMINISTRATOR)
                    Commands::series_add(library); 
                else
                    std::cout << "\nYou do not have access to this command (only for administrators)\n\n";    
                break;
            case SeriesRemove :
                if(userBase.showIfHasLoggedIn() && user->getType() == ADMINISTRATOR)
                    Commands::series_remove(library); 
                else
                    std::cout << "\nYou do not have access to this command (only for administrators)\n\n";    
                break;
            case SeriesView :
                if(userBase.showIfHasLoggedIn())
                    Commands::series_view(library, command);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case ListAll :
                if(userBase.showIfHasLoggedIn())
                    Commands::list_all(library);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case ListFind :
                if(userBase.showIfHasLoggedIn())
                    Commands::list_find(library, command);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case ListInfo : 
                if(userBase.showIfHasLoggedIn())
                    Commands::list_info(library, command);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case UserFind :
                if(userBase.showIfHasLoggedIn() && user->getType() == ADMINISTRATOR)
                    Commands::user_find(library, userBase, command);
                else
                    std::cout << "\nYou do not have access to this command (only for administrators)\n\n";
                break;
            case UserAdd : 
                if(userBase.showIfHasLoggedIn() && user->getType() == ADMINISTRATOR)
                    Commands::user_add(userBase, command);
                else
                    std::cout << "\nYou do not have access to this command (only for administrators)\n\n";
                break;
            case UserRemove : 
                if(userBase.showIfHasLoggedIn() && user->getType() == ADMINISTRATOR)
                    Commands::user_remove(userBase, command);
                else
                    std::cout << "\nYou do not have access to this command (only for administrators)\n\n";
                break;
            case UserChange : 
                if(userBase.showIfHasLoggedIn())
                    Commands::user_change(userBase, command);
                else
                    std::cout << "\nYou do not have access to this command, must login\n\n";
                break;
            case Take : 
                if(userBase.showIfHasLoggedIn() && user->getType() == READER)
                    Commands::take(library, userBase, command);
                else
                    std::cout << "\nYou do not have access to this command, only for logged in readers\n\n";
                break;
            case Return :
                if(userBase.showIfHasLoggedIn() && user->getType() == READER)
                    Commands::return_(library, userBase, command);
                else
                    std::cout << "\nYou do not have access to this command, only for logged in readers\n\n";
                break;
            case LoadData : loadDataFromFile(); break;
            case Invalid : std::cout << "Try again" << std::endl; break;
            default : stop = true;
        } 

   }while(!stop);
}

void System::writeInFile(){
    library.writeInFile();
    userBase.writeInFile();
}

void System::loadDataFromFile(){
    std::ifstream itemsFile("items.txt");
    std::ifstream usersFile("users.txt");

    library.readFromFile(itemsFile);
    userBase.readFromFile(usersFile);

    itemsFile.close();
    usersFile.close();

    library.writeInFile();
    userBase.writeInFile();
}

void System::loadData(){
    Article articles1[3] = {{"How to loose 10pds in a week", "Michael Smith", "10pounds, lifechanging, skinny"}, {"Madona has a new boyfriend", "Ana K", "hot, shocking, trending"}, {"The food you should eat according to the moon phase", "L.S.", "healthy, astrology, moon"}};
    Article articles2[2] = {{"How do we find shipwrecks?", "Ana K", "adventures, treasures"}, {"The world of lemurs", "Andy Woods", "school outdoors, lemurs, into the wild"}};
    Article articles3[2] = {{"Antarctica-the unknown world", "Josh L", "extreme temperatures, Antarctica, dive into the unknown"}, {"In the eye of the storm", "Andy Woods", "storm, cyclons, unbelievable shots"}};

    Item::setUniqueNumLib(247);
    Book* b1 = new Book("C++ book", "Ciela", "textbook", "Learn the basics of C++", 3.5, "Ivan Ivanov", 1999, "c++, programming, school", "978-3-0453-8499-9");
    Book* b2 = new Book("Me and My story", "Collins", "Autobiography", "Book about my life journey", 3.1, "Ana K", 2022, "jouney, self discovery");
    Book* b3 = new Book("Harry Potter", "Helikon", "adventures", "Story about magic and adventures", 2.3, "J.K. Rowling", 2001, "magician, school, don't bother");
    Book* b4 = new Book("Catch 22", "Helikon", "satirical war novel", "The story of a soldier who is not insane", 4.9, "Joseph Heller", 1982, "World War 2, satire, soldiers");
    Book* b5 = new Book("The Idiot", "Hermes", "novel", "classic Russian novel", 4.7, "F. Dostoevsky", 1992, ", classics, Russia, love and faith, nihilism");
    Book* b6 = new Book("Alice in Wonderland", "Ciela", "adventures", "a magical story about a magic land", 3.2, "Lewis Carroll", 2003, "children stories, adventures, classics");
    Series* s1 = new Series("Vogue", "Conde Nast", "fashion", "the latest trends and celebrity news", 4.6, "2021-4", 4, articles1, 3);
    Series* s2 = new Series("National Geographic", "Penguin House", "photojournalism", "school, travel, educational, documentary magazine", 4.8, "2020-09", 45, articles2, 2, "3226-0504");
    Series* s3 = new Series("National Geographic", "Penguin House", "photojournalism", "travel, educational, documentary magazine", 3.2, "2020-12", 48, articles3, 2, "3226-0504");    
    Series* s4 = new Series("Vogue", "Conde Nast", "fashion", "The latest trends and celebrity news", 4.6, "2009-5", 5, articles1, 3);
    b5->setIsTaken(true);
    s4->setIsTaken(true);

    this->library.addItemToCatalog(b1);
    this->library.addItemToCatalog(b2);
    this->library.addItemToCatalog(b3);
    this->library.addItemToCatalog(b4);
    this->library.addItemToCatalog(b5);
    this->library.addItemToCatalog(s1);
    this->library.addItemToCatalog(s2);
    this->library.addItemToCatalog(s3);
    this->library.addItemToCatalog(s4);
    this->library.addItemToCatalog(b6);

    Date d1(2016, 4, 26);
    Date d2(2018, 9, 17);
    Date d3(2018, 12, 2);
    Date d4(2019, 2, 5);
    Date d5(2021, 7, 8);
    Date d6(2021, 12, 3);
    Date d7(2022, 2, 15);
    Date d8(2022, 5, 29);
    Date d9(2022, 6, 1);
    Date d10 = d9;
    Date d11 = d8;
    d10.addMonth();
    d11.addMonth();
    Date d12 = d8;
    d12.removeMonth();

    BorrowedItem bp1(b1, d9, d10);
    BorrowedItem bp2(b2, d2, d3);
    BorrowedItem bp3(b1, d5, d6);
    BorrowedItem bp4(b3, d4, d5);
    BorrowedItem bp5(b4, d8, d11);
    BorrowedItem bp6(s1, d7 ,d8);
    BorrowedItem bp7(s3, d8, d9);
    BorrowedItem bp8(b5, d12, d8); //is overdue
    BorrowedItem bp9(s4, d8 , d9); //is overdue

    Reader* georgi = new Reader("georgi_123", "123456789abc", d1, d8);
    georgi->addItemToList(bp2);
    georgi->addItemToList(bp4);
    Reader* ivan = new Reader("ivan_123", "123ivan", d1, d7);
    ivan->addItemToList(bp3);
    ivan->addItemToList(bp8);
    ivan->addItemToList(bp7);
    ivan->borrowItem(b1);
    ivan->borrowItem(b2);
    ivan->borrowItem(s3);
    ivan->borrowItem(b4);
    ivan->borrowItem(s2);
    User* admin1 = new Administrator("dimitar.ivanov", "admin1123", d5, d12, "dim_ivanov@gmail.com", "Series");
    Administrator* admin2 = new Administrator("ivailo_s", "admin2123", d4, d7, "ivailo.ivailo@abv.bg", "Computer Science");
    Reader* ivana = new Reader("iv_it123", "12345iii", d4, d7);
    ivana->addItemToList(bp9);
    ivana->addItemToList(bp4);
   
    this->userBase.addUser(georgi);
    this->userBase.addUser(ivan);
    this->userBase.addUser(admin1);
    this->userBase.addUser(admin2);
    this->userBase.addUser(ivana);

    this->userBase.logInUser(ivan);
    this->userBase.setHasLoggedIn(true);
}