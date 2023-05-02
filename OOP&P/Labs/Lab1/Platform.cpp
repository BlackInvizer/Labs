#include "Platform.h"
#include "Blog.h"

#include <iostream>
#include <stdio.h>

using namespace std;





Platform::Platform(const char* FileName) {
    fileName = FileName; // Обращается в Platform.h и присваивает адрес файла на адрес filename
}


void Platform::Run() {
    do {
        int c = Showmenu(); //Вызывает функцию и возвращает выбор пользователя, который присваивается с
        switch (c) {
        case 1: AddBlog(); break;
        case 2: ViewBlog(); break;
        case 4: DeleteBlog(); break;
        case 5: SearchByTheme(); break;
        case 6: FindOldest(); break;
        case 7: return; // Прекращение работы функции (выход из программы)
        default: cout << "Incorrect choice" << endl;
        }
    } 
    while (true);
}

int Platform::Showmenu() {

    cout << "\t1 : add blog" << endl;
    cout << "\t2 : view blog" << endl;
    cout << "\t3 : edit blog" << endl;
    cout << "\t4 : delete blog" << endl;
    cout << "\t5 : blog search by theme" << endl;
    cout << "\t6 : find oldest blog" << endl;
    cout << "\t7 : exit\n" << endl;
    cout << "Make choice: ";
    
    int choice;

    cin >> choice;
    cout << endl;

    return choice;
}

void Platform::AddBlog() {
    Blog blog(InputBlog()); // создается переменная типа Blog (Blog.h)
                              // Вызов функции Inputblog
    int amount;
    Blog* blogs= RdAllBlogs(amount);
    Blog* newBlogs = new Blog[amount + 1];
    for (int i = 0; i < amount; i++) {
        newBlogs[i].Clone(blogs[i]);
    }
    newBlogs[amount].Clone(blog);
    WrAllBlogs(newBlogs, amount + 1);
    delete[] blogs;
    delete[] newBlogs;
 }

Blog Platform::InputBlog() {
    
    char name[128];
    cout << "Enter name : ";
    cin >> name;

    char author[128];
    cout << "Enter author : ";
    cin >> author;

    char theme[128];
    cout << "Enter theme : ";
    cin >> theme;

    int d;
    int m;
    int y;
    cout << "Enter date (dd-mm-yyyy) : ";
    char c;
    cin >> d >> c >> m >> c >> y;
    cout << endl;

    Blog blog(d, m, y, name, author, theme);
    return blog;
}

void Platform::ShowBlog(Blog blog) {
    int d;
    int m;
    int y;

    cout << "\tBlog name: " << blog.GetName() << endl;
    cout << "\tBlog author: " << blog.GetAuthor() << endl;
    cout << "\tBlog theme: " << blog.GetTheme() << endl;
    blog.GetDate(&d, &m, &y);
    //cout << "\tBlog date: " << d << "-" << m << "-" << y << endl << endl;
    printf("\tBlog date: %02d-%02d-%d\n\n", d, m, y);
}

void Platform::ViewBlog() {
    FILE* f;
    fopen_s(&f, fileName, "rt"); // отурывает файл для чтения в текстовом режиме
    if (f == NULL) {
        cout << "\ncannot open file" << endl;
    }
    else {
        int blogNumber;
        int amount;
        Blog* blogs = RdAllBlogs(amount);

        cout << "Specify blog number from 1 to " << amount << ": "; 
        cin >> blogNumber;
        cout << endl;
        
        if (blogNumber > amount || blogNumber < 1) {
            cout << "Specified blog number doesnt exist\n" << endl;
        }
        else {
            ShowBlog(blogs[blogNumber-1]);

        }
        delete[] blogs;
        fclose(f);
    }
}

void Platform::WrBlog2File(FILE* f, Blog& b) {
    fputs(b.GetName(), f); //записывает значение, которое вернула GetName в файл f
    fputc('\n', f);// переводит указатель на следующую строку
    fputs(b.GetAuthor(), f);
    fputc('\n', f);
    fputs(b.GetTheme(), f);
    fputc('\n', f);
    int d;
    int m;
    int y;
    b.GetDate(&d, &m, &y);
    fprintf(f, "%02d-%02d-%d\n", d, m, y); //записывает в определенном формате (две цифры числа и месяца или, если одна, то перед ней 0) дату
}

void Platform::RdBlogFromFile(FILE* f, Blog &blog) {
  
    char buf[128];
    fgets(buf, 127, f);//считывает из f в buf 127 байт
    Trim(buf);
    blog.SetName(buf);
    fgets(buf, 127, f);
    Trim(buf);
    blog.SetAuthor(buf);
    fgets(buf, 127, f);
    Trim(buf);
    blog.SetTheme(buf);
    fgets(buf, 127, f);
    Trim(buf);
    buf[2] = '\0';//делит строку ,отделяя первые 2 символа (день)
    buf[5] = '\0';
    int d = atoi(buf);
    int m = atoi(buf + 3); //смещается на 3 символа вправо и превращает строку в число до следующего нуль-терминатора
    int y = atoi(buf + 6);
    blog.SetDate(d, m, y);
    //fgets(buf, 1, f);
}

Blog* Platform::RdAllBlogs(int &amount) {
    FILE* f;
    fopen_s(&f, fileName, "rt"); // отурывает файл для чтения в текстовом режиме
    if (f == NULL) {
        cout << "\ncannot open file" << endl;
        amount = -1;
        return NULL;
    }
    else {
        fscanf_s(f, "%d\n", &amount);
        Blog *blog = new Blog[amount];
        for (int i = 0; i < amount; i++) {
            RdBlogFromFile(f, blog[i]);
        }
        fclose(f);
        return blog;
    }
}

void Platform::WrAllBlogs(Blog* blogs, int amount) {
    FILE* f;
    fopen_s(&f, fileName, "wt"); // отурывает файл для чтения в текстовом режиме
    if (f == NULL) {
        cout << "\ncannot open file" << endl;
    }
    else {
        fprintf(f, "%d\n", amount);
        for (int i = 0; i < amount; i++) {
            WrBlog2File(f, blogs[i]);
        }
        fclose(f);
    }
}

void Platform::DeleteBlog() {
    int blogNumber;
    cin >> blogNumber;
    int amount;
    Blog* blogs = RdAllBlogs(amount);
    if (blogNumber > amount || blogNumber < 1) {
        cout << "Specified blog number doesnt exist\n" << endl;
    }
    else {
        ShowBlog(blogs[blogNumber - 1]);

        for (int i = blogNumber - 1; i < amount - 1; i++) {
            blogs[i] = blogs[i + 1];
        }

        amount--;
        WrAllBlogs(blogs, amount);
    }
    delete[] blogs;

}

void Platform::SearchByTheme() {
    char theme[128];
    cout << "Specify theme: ";
    cin >> theme;
    int amount;
    int count = 0;
    Blog* blogs = RdAllBlogs(amount);
    for (int i = 0; i < amount; i++) {
       // if (strcmp(theme, blogs[i].GetTheme()) == 0) {
        if (strstr(blogs[i].GetTheme(), theme) != NULL) {
            ShowBlog(blogs[i]);
            count++;
        }
    }
    if (count == 0) {
        cout << "There are no blogs..."<< endl;
    }
    else {
        cout << "Total blogs found = " << count << endl;
    }
    delete[] blogs;
}

void Platform::FindOldest(){
    int amount;
    Blog* blogs = RdAllBlogs(amount);
    if (amount <= 0) {
        cout << "There is no blogs...";
        
    }
    else {
        int minIndex = -1;
        int minDay = 32;
        int minMonth = 13;
        int minYear = 9999;
        for (int i = 0; i < amount; i++) {
            int d;
            int m;
            int y;
            blogs[i].GetDate(&d, &m, &y);
            if (y < minYear || (y == minYear && m < minMonth) || (y == minYear && m == minMonth && d < minDay)) {
                minIndex = i;
                minDay = d;
                minMonth = m;
                minYear = y;
           }
        }
        ShowBlog(blogs[minIndex]);
    }
    delete[] blogs;
}


void Platform::Trim(char* str) { // зачем?
    int pos = 0;
    while (str[pos] != '\0') {
        if (str[pos] == '\n') {
            str[pos] = '\0';
            return;
        }
        pos++;
    }
}

