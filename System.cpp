#include "System.h"

// void System::getCommands(){
//     bool stop = false;
//     do{
//         std::cout << "Enter your command: " << std::endl;
//         char buffer[124];
//         std::cin.getline(buffer, 124);

//         CommandInfo command = Commands::recognizeCommand(buffer);
        
//         switch(command.getType()){
//             case Help : Commands::help(); break;
//             case Exit : stop = true; break;
//             case Login : Commands::login(userBase); break;
//             case Logout : Commands::logout(userBase); break;
//             case BooksAll : Commands::books_all(library); break;
//             case BooksFind : Commands::books_find(command); break;
//             case BooksAdd : Commands::books_add(); break;
//             case BooksRemove : Commands::books_remove(); break;
//             case SeriesAll : Commands::series_all(); break;
//             case SeriesFind : Commands::series_find(command); break;
//             case SeriesAdd : Commands::series_add(); break;
//             case SeriesRemove : Commands::series_remove(); break;
//             case ListAll : Commands::list_all(); break;
//             case ListFind : Commands::list_find(command); break;
//             case ListInfo : Commands::list_info(command); break;
//             case UserFind : Commands::user_find(command); break;
//             case UserAdd : Commands::user_add(command); break;
//             case UserRemove : Commands::user_remove(command); break;
//             case UserChange : Commands::user_change(command); break;
//             case Take : Commands::take(command); break;
//             case Return : Commands::return_(command); break;
//             case Invalid : std::cout << "Try again" << std::endl; break;
//             default : stop = true;
//     } 

//    }while(!stop);
// }