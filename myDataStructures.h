//Coded by Muhammad Arfat i210554@nu.edu.pk
#pragma once
#include<iostream>

using namespace std;

namespace myDS
{
//prioriy queue using linked list
    template <typename T>
    class QNode
    {

    public:
        T data;
        QNode *next;
        int priority;

        QNode(){next = NULL;
            priority = 0;}
        QNode(T data)
        {
            this->data = data;
            priority=0;
            next = NULL;
        }
        QNode(T data, int priority)
        {
            this->data = data;
            this->priority = priority;
            next = NULL;
        }
        T getData(){return data;}
        QNode* getNext(){return next;}


    };

    template <typename T>
    class Queue
    {
        QNode<T> *front;
        QNode<T> *rear;
        int capacity;
        int size;
    public:
        Queue()
        {
            front = NULL;
            rear = NULL;
            capacity = -1;
            size = 0;
        }
        Queue(int capacity)
        {
            front = NULL;
            rear = NULL;
            this->capacity = capacity;
            size = 0;

        }
        void enqueue(T data)
        {
            if(isFull())
            {
                cout<<"Queue is full"<<endl;
                return;
            }
            QNode<T> *temp = new QNode<T>(data);
            if(front == NULL)
            {
                front = temp;
                rear = temp;
            }
            else
            {
                rear->next = temp;
                rear = temp;
            }
            size++;
        }
        T dequeue()
        {
            if(isEmpty())
            {
                cout<<"Queue is empty"<<endl;
                return NULL;
            }

            else
            {
                if(front == rear)
                {
                    T data = front->data;
                    delete front;
                    front = NULL;
                    rear = NULL;
                    size--;
                    return data;
                }
                else
                {
                    QNode<T> *temp = front;
                    front = front->next;
                    T data = temp->data;
                    delete temp;
                    size--;
                    return data;
                }

            }

        }
        bool isEmpty()
        {
            if(front == NULL)
                return true;
            else
                return false;
        }
        bool isFull()
        {
            if(size == capacity)
                return true;
            else
                return false;
        }
        void priorityInsert(T data,int priority)
        {
            if(isFull())
            {
                cout<<"Queue is full"<<endl;
                return;
            }

            QNode<T> *temp = new QNode<T>(data,priority);

            if(front == NULL)
            {
                front = temp;
                rear = temp;
            }
            else
            {
                QNode<T> *current = front;
                QNode<T> *prev = NULL;
                while(current != NULL && current->priority >= priority)
                {
                    prev = current;
                    current = current->next;
                }

                if(prev == NULL)
                {
                    temp->next = front;
                    front = temp;
                }
                else
                {
                    // if(current &&  current->priority == priority)
                    // {
                    //     temp->next = current->next;
                    //     current->next = temp;
                    // }
                    // else
                    {
                        temp->next = current;
                        prev->next = temp;
                    }



                }

            }



            size++;


        }
        void clearQ()
        {
            while(!isEmpty())
                dequeue();
        }
        void display()
        {
            QNode<T> *temp = front;
            cout<<"Queue: F--> ";
            while(temp != NULL)
            {
                cout<<temp->getData()<<" ";
                temp = temp->next;
            }
            cout<<" -->R"<<endl;
            cout<<endl;
        }
        bool remove(T data)
        {
            if(front == NULL)
            {
                cout<<"Queue is empty"<<endl;
                return false;
            }
            else
            {
                QNode<T> *current = front;
                QNode<T> *prev = NULL;
                while(current != NULL && current->data != data)
                {
                    prev = current;
                    current = current->next;
                }
                if(current == NULL)
                {
                    cout<<"Data not found"<<endl;
                    return false;
                }
                else
                {
                    if(prev == NULL)
                    {
                        front = front->next;
                        delete current;
                        size--;


                        return true;
                    }
                    else
                    {
                        prev->next = current->next;
                        delete current;
                        size--;

                        return true;
                    }

                }
            }

            return true;
        }
        bool isPresent(T data)
        {
            QNode<T> *temp = front;
            while(temp != NULL)
            {
                if(temp->data == data)
                    return true;
                temp = temp->next;
            }
            return false;
        }
        void setCapacity(int capacity)
        {
            this->capacity = capacity;
        }
        int getSize()
        {
            return size;
        }
        QNode<T>* getFront(){return front;}
        QNode<T>* getRare(){return rear;}
    };





    template <class T>
    class node
    {
    public:
        T val;
        node* next;
        node* prev;

        node()
        {
            next = NULL;
            prev=NULL;
        }

        node(T d, node* n,node* p)
        {
            val = d;
            next = n;
            prev = p;


        }

        node(T d)
        {
            val = d;
            next = NULL;

        }

        void setData(T d)
        {
            val = d;

        }

        void setNext(node* n)
        {
            next = n;


        }

        T getData()
        {
            return val;


        }

        node* getNext()
        {
            return next;


        }

    };
    template <class T>
    class SLinkedList{

    public:

        node<T>* head;




        bool insert(T d)
        {
            node<T>* newNode = new node<T>;
            newNode->val = d;
            newNode->next = NULL;

            if (head == NULL)
            {
                head = newNode;
            }
            else
            {
                node<T>* currentNode = head;
                while (currentNode->next != NULL)
                {
                    currentNode = currentNode->next;
                }

                currentNode->next = newNode;
            }

            return true;
        }

        bool insertAtHead(T d)
        {
            node<T>* newNode = new node<T>;
            newNode->val = d;
            newNode->next = NULL;

            if (head == NULL)
            {
                head = newNode;
            }
            else
            {
                newNode->next = head;
                head = newNode;
            }

            return true;
        }

        bool isEmpty()
        {
            if(head==NULL)
                return true;
            return false;


        }
        int search(T d)
        {
            node<T>*  tmp = head;
            int index = 0;
            while (tmp != NULL )
            {
                if (tmp->val == d)
                {
                    return index;
                }
                tmp = tmp->next;
                index++;
            }

            return -1;
        }
        bool update(T d1,T d2)
        {


            node<T>* temp = head;

            while(temp && temp->val!=d1)
            {
                temp = temp->next;

            }
            if(temp)
            {
                temp->val = d2;
                return true;
            }

            return false;




        }
        bool InsertAtIndex(T d ,int index)
        {
            if(index<0)
                return false;

            node<T>* newNode = new node<T>;
            newNode->val = d;
            newNode->next = NULL;



            node<T>* currentNode = head;
            int i = 0;
            while (currentNode  && i!=index)
            {
                currentNode = currentNode->next;
                i++;
            }
            if(currentNode)
            {
                newNode->next = currentNode->next;
                currentNode->next = newNode;
                return true;
            }
            else
            {
                return false;
            }






        }

        bool print()
        {
            node<T>* currentNode = head;
            while (currentNode != NULL)
            {
                cout << currentNode->val << " ";
                currentNode = currentNode->next;
            }
            cout << endl;
            return true;
        }




    };


//stack using linked list
    template <class T>
    class stack
    {
    public:
        SLinkedList<T> L;
        int size;
        stack()
        {
            size = 0;
        }
        bool push(T d)
        {
            L.insertAtHead(d);
            size++;
            return true;
        }

        bool pop()
        {
            if (size == 0)
                return false;
            node<T>* temp=L.head;
            L.head = L.head->next;
            size--;
            delete temp;
            return true;
        }

        bool isEmpty()
        {
            if (size == 0)
                return true;
            return false;
        }
        bool print()
        {
            L.print();
            return true;
        }

        node<T>* Peek()
        {
            return (L.head);
        }
        int sizeofstack()
        {
            return size;
        }
        void clear()
        {
            while (size != 0)
            {
                pop();
            }
        }




    };

    int lengthOf(char* str);
    class String
    {

        char* data = nullptr;
        int length = 0;

    public:
        friend String operator+(const char* str1, const String& str2);
        friend String operator+(const char ch, const String& str);
        String();
        String(int);
        String(char*);
        String(const String&);
        String(const string& str)
        {
            length = str.length();
            data = new char[length + 1];
            for (int i = 0; i < length; i++)
            {
                data[i] = str[i];
            }
            data[length] = '\0';
        }
        String(const char& ch)
        {
            length = 1;
            data = new char[length + 1];
            data[0] = ch;
            data[length] = '\0';
        }


        String(double num)
        {
            length = 0;
            int temp = num;
            while (temp != 0)
            {
                temp /= 10;
                length++;
            }
            data = new char[length + 1];
            for (int i = length - 1; i >= 0; i--)
            {
                data[i] = (int(num) % 10) + '0';
                num /= 10;
            }
            data[length] = '\0';
        }

        ~String();
        int Length() const;
        void clear();
        bool empty();
        char* getdata() const;
        int find(char);
        int find(char, int);
        bool equals(char*);
        bool equalsIgnoreCase(char*);
        char* substring(char*, int);
        char* substring(char*, int, int);
        void print();

        void erase(int index,int n)
        {
            for (int i = index; i < length; i++)
            {
                data[i] = data[i + n];
            }
            length -= n;
        }
        bool operator==(const char* str)
        {
            return equals((char*)str);
        }
        bool operator==(const String& str)
        {
            return equals(str.data);
        }
        friend ostream &operator<<(ostream &out, String &str)
        {
            if(str.data)
                out << str.data;
            return out;
        }
        void operator+=(const char* str)
        {
            int len = lengthOf((char*)str);
            char* temp = new char[length + len + 1];
            for (int i = 0; i < length; i++)
            {
                temp[i] = data[i];
            }
            for (int i = length; i < length + len; i++)
            {
                temp[i] = str[i - length];
            }

            length += len;
            temp[length]='\0';


            delete[] data;
            data = temp;


        }
        void operator+=(const String& str)
        {
            int len = str.Length();
            char* temp = new char[length + len + 1];
            for (int i = 0; i < length; i++)
            {
                temp[i] = data[i];
            }
            for (int i = length; i < length + len; i++)
            {
                temp[i] = str.data[i - length];
            }

            length += len;
            temp[length]='\0';
            delete[] data;
            data = temp;
        }

        String operator+(const String& str)
        {
            String temp;
            temp.length = length + str.length;
            temp.data = new char[temp.length + 1];
            for (int i = 0; i < length; i++)
            {
                temp.data[i] = data[i];
            }
            for (int i = length; i < length + str.length; i++)
            {
                temp.data[i] = str.data[i - length];
            }
            temp.data[temp.length]='\0';

            return temp;
        }
        String operator+(const char* str)
        {
            String temp;
            int len = lengthOf((char*)str);
            temp.length = length + len;
            temp.data = new char[temp.length + 1];
            for (int i = 0; i < length; i++)
            {
                temp.data[i] = data[i];
            }
            for (int i = length; i < length + len; i++)
            {
                temp.data[i] = str[i - length];
            }
            temp.data[temp.length]='\0';
            return temp;
        }
        String operator+(const char ch)
        {
            String temp;
            temp.length = length + 1;
            temp.data = new char[temp.length + 1];
            for (int i = 0; i < length; i++)
            {
                temp.data[i] = data[i];
            }
            temp.data[temp.length-1] = ch;
            temp.data[temp.length]='\0';

            return temp;
        }



        String& operator=(const String& str)
        {
            // cout<<"this ran for "<<str.length<<endl;
            if (this != &str)
            {
                delete[] data;
                length = str.length;
                data=nullptr;
                data = new char[length + 1];
                for (int i = 0; i < length; i++)
                {
                    data[i] = str.data[i];
                }
                data[length] = '\0';
            }

            return *this;
        }
        String& operator=(const char* str)
        {
            clear();
            length = lengthOf((char*)str);
            data = new char[length + 1];
            for (int i = 0; i < length; i++)
            {
                data[i] = str[i];
            }
            data[length]='\0';
            return *this;
        }

        char& operator[](int index)
        {
            if(index<=length)
                return data[index];
            else
                cout<<"Index of of range\n";
        }
        void operator()(char* str)
        {
            clear();
            length = lengthOf(str);
            data = new char[length + 1];
            for (int i = 0; i < length; i++)
            {
                data[i] = str[i];
            }
            data[length]='\0';
        }
        bool operator!=(const char* str)
        {
            return !equals((char*)str);
        }
        bool operator!=(const String& str)
        {
            return !equals(str.data);
        }

        //To int with negative numbers
        int toInt()
        {
            if(!this->data)
                return 1;
            int num = 0;
            int i = 0;
            if (data[0] == '-')
            {
                i = 1;
            }
            for (; i < length; i++)
            {
                num = num * 10 + (data[i] - '0');
            }
            if (data[0] == '-')
            {
                num *= -1;
            }
            return num;
        }

        String substr(int index, int n)
        {
            String temp;
            temp.length = n;
            temp.data = new char[n + 1];
            for (int i = 0; i < n; i++)
            {

                temp.data[i] = data[index + i];
//                if(data[index+i]=='\0')
//                    break;
            }

            temp.data[temp.length]='\0';
            return temp;
        }
        String substr(int index)
        {
            String temp;
            temp.length = length - index;
            temp.data = new char[temp.length + 1];
            for (int i = 0; i < temp.length; i++)
            {
                temp.data[i] = data[index + i];
            }
            temp.data[temp.length]='\0';
            return temp;
        }
        void push_back(char ch)
        {
            char* temp = new char[length + 2];
            for (int i = 0; i < length; i++)
            {
                temp[i] = data[i];
            }
            temp[length] = ch;
            temp[length+1]='\0';
            delete[] data;
            data = temp;
            length++;
        }
        char pop_back()
        {
            char ch = data[length - 1];
            char* temp = new char[length];
            for (int i = 0; i < length - 1; i++)
            {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            length--;
            return ch;
        }
        void reverse()
        {
            for (int i = 0; i < length / 2; i++)
            {
                char temp = data[i];
                data[i] = data[length - i - 1];
                data[length - i - 1] = temp;
            }
        }

        //counts words while ignoring consecutive spaces
        int countWords()
        {
            int count = 0;
            for (int i = 0; i < length; i++)
            {
                if (data[i] == ' ')
                {
                    if (data[i + 1] != ' ')
                    {
                        count++;
                    }
                }
            }
            return count + 1;


        }
        //remove white spaces from the string
        void removeWhiteSpaces()
        {
            int count = 0;
            for (int i = 0; i < length; i++)
            {
                if (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\r')
                {
                    count++;
                }


            }
            char* temp = new char[count + 1];
            int j = 0;
            for (int i = 0; i < length; i++)
            {
                if (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\r')
                {
                    temp[j] = data[i];
                    j++;
                }

            }
            temp[count]='\0';
            delete[] data;
            data = temp;
            length = count;
        }

        //converts string to words while ignoring consecutive spaces
        String* toWords()
        {
            int count = countWords();
            String* words = new String[count];
            int index = 0;
            int wordIndex = 0;
            for (int i = 0; i < length; i++)
            {
                if (data[i] == ' ')
                {
                    if (!(data[i + 1] == ' '))
                    {
                        words[wordIndex] = substr(index, i - index);
                        words[wordIndex].removeWhiteSpaces();

                        wordIndex++;
                        index = i + 1;
                    }
                }
            }
            words[wordIndex] = substr(index, length - index);
            words[wordIndex].removeWhiteSpaces();
            return words;
        }

        // String* toWords()
        // {
        //     int count = countWords();
        //     String* words = new String[count + 1];
        //     int index = 0;
        //     int start = 0;
        //     for (int i = 0; i < length; i++)
        //     {
        //         if (data[i] == ' ')
        //         {
        //             words[index] = substr(start, i - start);
        //             start = i + 1;
        //             index++;
        //         }
        //     }
        //     words[index] = substr(start, length - start);
        //     return words;
        // }

        //bool conversion operator overload
        operator bool()
        {
            if (length == 0)
                return false;
            else
                return true;
        }
        friend ostream& operator<<(ostream& out, const String& str)
        {
            if (str.data)
                out << str.data;
            return out;
        }
        friend istream& operator>>(istream& in, String& str)
        {
            //cout<<"this ran";
            // istream.getline(str.data, str.length);
            str.clear();
            char* temp = new char[100];
            in >> temp;
            str.length = lengthOf(temp);

            str.data = new char[str.length + 1];
            for (int i = 0; i < str.length; i++)
            {
                str.data[i] = temp[i];
            }

            str.data[str.length] = '\0';

            delete[] temp;
            return in;
        }
        string to_string()
        {
            string temp;
            for (int i = 0; i < length; i++)
            {
                temp.push_back(data[i]);
            }
            return temp;
        }



    };
    int lengthOf(char* str)
    {
        int size = 0;

        for (int i = 0;str[i] != '\0';i++)
        {

            size++;
        }


        return size;



    }

    char toLower(char ch);




    String operator+(const char* str1, const String& str2)
    {
        String temp;
        int len = lengthOf((char*)str1);
        temp.length = len + str2.length;
        temp.data = new char[temp.length + 1];
        for (int i = 0; i < len; i++)
        {
            temp.data[i] = str1[i];
        }
        for (int i = len; i < len + str2.length; i++)
        {
            temp.data[i] = str2.data[i - len];
        }

        temp.data[temp.length]='\0';
        return temp;
    }

    String operator+(const char ch, const String& str)
    {
        String temp;
        temp.length = str.length + 1;
        temp.data = new char[temp.length + 1];
        temp.data[0] = ch;
        for (int i = 1; i < temp.length; i++)
        {
            temp.data[i] = str.data[i - 1];
        }

        temp[temp.length]='\0';
        return temp;
    }




    String::String()
    {

    }

//Constructors and Destructors
    String::String(int size)
    {
        length = size;

        data = new char[length];

        data[0] = '\0';

    }


    String::String(char* str)
    {
        clear();
        length = lengthOf(str);

        data = new char[length + 1];

        for (int i = 0;true;i++)
        {
            data[i] = str[i];

            if (str[i] == '\0')
                break;
        }


    }

    String::String(const String& str)
    {
        clear();
        length = str.Length();

        data = new char[length + 1];

        char* cpData = str.getdata();

        for (int i = 0;true;i++)
        {
            data[i] = cpData[i];

            if (cpData[i] == '\0')
                break;
        }

    }


    String::~String()
    {

        delete[] data;


    }



//Functions

    int String::Length() const
    {

        return length;

    }

    void String::clear()
    {
        delete []data;
        data = nullptr;
        length = 0;

    }

    bool String::empty()
    {
        if (data == nullptr)
            return true;
        else
            return false;


    }

    int String::find(char ch, int index)
    {
        for (int i = index; i < length; i++)
        {
            if (data[i] == ch)
                return i;
        }

        return -1;
    }
    int String::find(char c)
    {
        int index = -1;

        for (int i = 0; data[i] != '\0';i++)
        {
            if (data[i] == c)
            {
                index = i;
                break;
            }

        }

        return index;


    }
    char* String::getdata() const
    {

        return data;
    }

    bool String::equals(char* str)
    {
        if(!data)
            return false;

        bool result = true;
        for (int i = 0; true;i++)
        {
            if (str[i] != data[i])
            {
                result = false;
                break;
            }

            if (str[i] == '\0' && data[i] == '\0')
                break;


        }

        return result;


    }

    bool String::equalsIgnoreCase(char* str)
    {

        bool result = true;
        // char* str1=toLower(data);
        //    char*str2=toLower(str);


        for (int i = 0; true;i++)
        {
            if (toLower(str[i]) != toLower(data[i]))
            {
                result = false;
                break;
            }

            if (str[i] == '\0' && data[i] == '\0')
                break;


        }

        return result;

    }

    char* String::substring(char* substr, int startIndex)
    {
        char* returnStr;
        returnStr = nullptr;
        bool found = false;
        int index = 0;
        int i, j;

        for (i = startIndex, j = 0; data[i] != '\0';i++)
        {


            if (substr[j] == '\0')
                break;

            if (data[i] == substr[j])
            {
                if (!found)
                {
                    found = true;
                    index = i;
                }

                j++;
            }
            else
            {
                found = false;
                j = 0;
                // i--;
            }




            //  found=true;

        }
        if (found)
        {
            returnStr = new char[length - index + 1];

            for (int i = index, j = 0; true; i++, j++)
            {

                returnStr[j] = data[i];

                if (data[i] == '\0')
                    break;


            }




        }


        return returnStr;

    }

    char* String::substring(char* substr, int startIndex, int endIndex)
    {
        char* returnStr=new char(' ');
        // returnStr = nullptr;
        bool found = false;
        int index = 0;
        int i, j;

        for (i = startIndex, j = 0; data[i] != '\0';i++)
        {


            if (substr[j] == '\0')
                break;

            if (data[i] == substr[j])
            {
                if (!found)
                {
                    found = true;
                    index = i;
                }

                j++;
            }
            else
            {
                found = false;
                j = 0;
                // i--;
            }




            //  found=true;

        }
        if (found)
        {
            returnStr = new char[endIndex - startIndex + 2];
            int i, j;
            for (i = index, j = 0; true; i++, j++)
            {

                returnStr[j] = data[i];

                if (i == endIndex)
                    break;


            }
            returnStr[j + 1] = '\0';




        }


        return returnStr;

    }

    void String::print()
    {

        if (length == 0)
        {
            std::cout << "NULL";
        }
        else
        {
            std::cout << data;

        }




    }





    char toLower(char ch)
    {


        if (int(ch) >= 65 && int(ch) <= 90)
        {
            return  char(int(ch) + 32);

        }






    }






}






