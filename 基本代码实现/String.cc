/*
 * @Author: ZeroOneTaT
 * @Date: 2023-06-03 15:41:09
 * @LastEditTime: 2023-06-03 16:41:23
 * @FilePath: \MyTest\coding\String.cc
 * @Description: 自己实现 String 类， 需要注意的是 String 类采用 COW 技术
 *
 * =========================================================
 * 在空间的头部维护四个字节的空间，记录引用的个数。
 * 放在头部维护效率能高一些，如果放在尾部维护的话，每次开辟新的空间都要讲这四个字节也向后挪动相应的位置，所以放在前面效率高点。
 * =========================================================
 *
 * Copyright (c) 2023 by ZeroOneTaT, All Rights Reserved.
 */

#include <bits/stdc++.h>
using namespace std;

class String
{
public:
    // 构造函数
    String(const char *str) : str_(new char[strlen(str) + 4 + 1])
    {
        str_ += 4;
        strcpy(str_, str);
        GetRefCount() = 1;
    }

    // 拷贝构造函数
    String(const String &str) : str_(str.str_)
    {
        ++GetRefCount(); // 计数器 + 1
    }

    // 重载赋值函数
    String &operator=(const String &str)
    {
        if (str_ != str.str_)
        {
            // 删除之前的 String
            if (--GetRefCount() == 0)
            {
                delete[] (str_ - 4);
            }
            // 赋新值
            str_ = str.str_;
            ++GetRefCount();
        }
    }

    // 重载析构函数
    ~String()
    {
        if (--GetRefCount() == 0)
        {
            delete[] (str_ - 4);
            str_ = nullptr;
        }
    }

    // 重载 [] 函数, 修改使用 COW
    char &operator[](size_t pos)
    {
        if (GetRefCount() > 1)
        {
            --GetRefCount();
            char *newStr = new char[strlen(str_) + 4 + 1];
            newStr += 4;
            strcpy(newStr, str_);
            str_ = newStr;
            GetRefCount() = 1;
        }
        return str_[pos];
    }

    const char *c_str()
    {
        return str_;
    }

    int &GetRefCount()
    {
        return *((int *)(str_ - 4)); // 前四个字节为引用计数
    }

private:
private:
    char *str_;
};

// 测试一下
int main()
{
    String s = "123";
    String st = s;
    puts(s.c_str());
    puts(st.c_str());
    printf("%d\n", st.GetRefCount());
    printf("%d\n", s.GetRefCount());
    printf("%d\n", st.c_str());
    printf("%d\n", s.c_str());
    s[1] = '3';
    puts(s.c_str());
    puts(st.c_str());
    printf("%d\n", st.GetRefCount());
    printf("%d\n", s.GetRefCount());
    printf("%d\n", st.c_str());
    printf("%d\n", s.c_str());
}