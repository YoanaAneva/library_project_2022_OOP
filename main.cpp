#include "Book.h"
#include "Series.h"
#include "System.h"
#include "Library.h"

int main(){
    Article articles1[3] = {{"How to loose 10pds in a week", "Gosho", "10pounds, fat, skinny"}, {"Madona has a new boyfriend", "AK", "hot, shocking, much younger than her"}, {"The food you should eat according to the moon phase", "L.S.", "potatoes, astrology, sun"}};
    Article articles2[2] = {{"How do we find shipwrecks?", "Linda and Amy", "adventures, treasures"}, {"The world of lemurs", "Andy Wooden", "lemurs, into the wild"}};

    Paper::setUniqueNumLib(247);
    Book* b1 = new Book("C++ book", "Ciela", "textbook", "boring", 3.5, "Ivan Ivanov", 1997, "c++, programming, for smart kids", "978-3-0453-8499-9");
    Book* b2 = new Book("Me", "Me", "Autobiography", "book about me", 3.1, "Me", 2022, "me, myself, I");
    Series* s1 = new Series("Vogue", "Vogue", "fashion", "the latest trends and celebrity bullshit", 4.6, "2022-4", 4, articles1, 3);
    Series* s2 = new Series("National Geographic", "NG", "photojournalism", "travel, educational, documentary magazine", 4.8, "2020-09", 45, articles2, 2, "3226-0504");
    Book* b3 = new Book("Harry Potter", "Helikon", "adventures", "quite childish and unoriginal story", 2.3, "J.K. Rowling", 2001, "magician, school, don't bother");

    Paper** inventar = new Paper*[6];
    inventar[0] = b1;
    inventar[1] = b2;
    inventar[2] = s1;
    inventar[3] = s2;
    inventar[4] = b3;

    // for(int i = 0; i < 5; i++){
    //     inventar[i]->print();
    //     std::cout << std::endl;
    // }

    Book b5("Me", "Me", "Autobiography", "book about me", 3.1, "Me", 2022, "me, myself, I");

    Date d1 = Date::getNow();
    Date d2 = d1;
    d2.addMonth();

    // BorrowedPaper** books = new BorrowedPaper*[4];
    // books[0] = new BorrowedBook("C++ book", "Ciela", "textbook", "boring", 3.5, "Ivan Ivanov", 1997, "c++, programming, for smart kids", "978-3-0453-8499-9", d1, d2);
    // books[1] = new BorrowedSeries("Vogue", "Vogue", "fashion", "the latest trends and celebrity bullshit", 4.6, "2022-4", 4, articles, 3, d1, d2);
    // books[2] =new BorrowedBook("Harry Potter", "Helikon", "adventures", "quite childish and unoriginal story", 2.3, "J.K. Rowling", 2001, "magician, school, don't bother", d1, d2);
    // books[3] = new BorrowedBook(b5);
    // // for(int i = 0; i < 4; ++i){
    // //     books[i]->print();
    // //     std::cout << std::endl;
    // // }

    // BorrowedPaper** papers = new BorrowedPaper*[4];
    // papers[0] = new BorrowedPaper(inventar[0], d1, d2);
    // papers[1] = new BorrowedPaper(inventar[1], d1, d2);
    // papers[2] = new BorrowedPaper(inventar[2], d1, d2);
    // papers[3] = new BorrowedPaper(inventar[3], d1, d2);

    // for(int i = 0; i < 4; ++i){
    //     papers[i]->print();
    //     std::cout << std::endl;
    // }

    Reader* gosho = new Reader("goshi69", "123456789abc", d1, d2);
    gosho->addItemToList(b1);
    gosho->addItemToList(s1);
    gosho->addItemToList(b2);

    std::ofstream output("users.txt");

    gosho->writeInFile(output);

    output.close();


    // User* ivan = new Reader("ivan123", "123456789abc", d1, d2);
    // dynamic_cast<Reader*>(ivan)->addItemToList(b3);
    // User* petar = new Administrator("pesho_we", "2489", d1, d2, "pesho1@gmail.com", "Series");
    // Reader* ivanka = new Reader("iv_it123", "7589437iii", d1, d2);
    // dynamic_cast<Reader*>(ivanka)->addItemToList(s2);
   
    // System s;
    // s.addUser(ivan);
    // s.addUser(petar);
    // s.addUser(gosho);
    // s.addUser(ivanka);
    // s.print();

    // std::cout << "\nAfter:\n";

    // s.removeUser("goshi69");
    // s.print();

    Library library;
    library.addItemToCatalog(inventar[0]);
    library.addItemToCatalog(inventar[1]);
    library.addItemToCatalog(inventar[2]);
    library.addItemToCatalog(inventar[3]);
    library.addItemToCatalog(inventar[4]);
    
    // library.print();

    // std::cout << "_____________________________________________" << std::endl;

    // library.removeItemFromCatalog("C++ book");
    // library.removeItemFromCatalog("Lord of the rings");
    // library.print();

    // std::ofstream out("library_catalog.txt");
    // library.writeInFile(out);
    // out.close();

    // Library l;
    // l.createFromFile();

    // std::ifstream input("library_catalog.txt");

    // char type[2];
    // while(input){
    //     input.get(type, 2);
    //     if(type[0] == 'B'){
    //         Book* newBook = new Book();
    //         newBook->readFromFile(input);
    //         l.addItemToCatalog(newBook);
    //     }
    //     if(type[0] == 'S'){
    //         Series* newSeries = new Series();
    //         newSeries->readFromFile(input);
    //         l.addItemToCatalog(newSeries);
    //     }
    // }
  
    // l.print();
    // input.close();
    
}       