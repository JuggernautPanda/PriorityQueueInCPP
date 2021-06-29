#include <iostream>
#include <string> // for string class
#include <bits/stdc++.h>

struct InPut;

class Priority_Q
{
  public:
    Priority_Q();
    void insertToQueue(int priority ,string value);
    int getmaxpriority(void);
    int getlowpriority(void);
    void deleteFromQueue(void);
    void loadInPut(void);
    void outFunc1(int ind);
    void outFunc2(int ind);
};
