#pragma once
#include "Blog.h"


class Platform { // ������, ��������� � Platform.cpp
    int Showmenu();
    void AddBlog();
    Blog InputBlog();
    void ViewBlog();
    void ShowBlog(Blog blog);
    void WrBlog2File(FILE* f, Blog& blog);
    void RdBlogFromFile(FILE* f, Blog &blog);// ����� ��������� �����???
    Blog* RdAllBlogs(int &amount);
    void WrAllBlogs(Blog* blogs, int amount);
    void DeleteBlog();
    void SearchByTheme();
    void FindOldest();
    void Trim(char* str);

    const char* fileName; // ���������?
    

public:

    Platform(const char* FileName);
    void Run(); 
    
};