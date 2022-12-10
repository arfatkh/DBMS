#pragma once
#include <iostream>
#include "Filehandling.h"
// #include "RBTree.h"
// #include "Others.h"


using namespace std;

// Function prototypes
void Menu();
void ClearScreen();
void pause();
int getIntChoice(string Prompt, int min, int max);
string getStringChoice(string Prompt, string min, string max);
void createIndexTreeMenu();
template <typename T>
void createAVLTree(AVLtree<T>* tree,string field);


// //Special characters for printing in color
// string prntRed = "\033[1;31m";
// string prntGreen = "\033[1;32m";
// string prntYellow = "\033[1;33m";
// string prntBlue = "\033[1;34m";
// string prntPurple = "\033[1;35m";
// string prntCyan = "\033[1;36m";
// string prntWhite = "\033[1;37m";
// string prntClr = "\033[0m";



//Global Possible Tree Types
AVLtree<int>* AVL_ID =nullptr , * AVL_Year =nullptr , * AVL_Deaths =nullptr;
AVLtree<string>* AVL_CauseNameString =nullptr, *AVL_CauseName=nullptr, * AVL_State=nullptr;
AVLtree<float>* AVL_AgeAdjustedDeathRate=nullptr;


//Saves the history of trees made
struct TreesUsed
{
    bool AVL_ID = false, AVL_Year = false, AVL_Deaths = false;
    bool AVL_CauseNameString = false, AVL_CauseName = false, AVL_State = false;
    bool AVL_AgeAdjustedDeathRate = false;

    void SaveInFile()
    {
        ofstream file;
        file.open("TreesUsed.txt");
        file << AVL_ID << endl;
        file << AVL_Year << endl;
        file << AVL_Deaths << endl;
        file << AVL_CauseNameString << endl;
        file << AVL_CauseName << endl;
        file << AVL_State << endl;
        file << AVL_AgeAdjustedDeathRate << endl;
        file.close();
    }

    void ReadFromFile()
    {
        ifstream file;
        file.open("TreesUsed.txt");
        file >> AVL_ID;
        file >> AVL_Year;
        file >> AVL_Deaths;
        file >> AVL_CauseNameString;
        file >> AVL_CauseName;
        file >> AVL_State;
        file >> AVL_AgeAdjustedDeathRate;
        file.close();
    }

    void display()
    {
        ClearScreen();
        cout<<prntCyan;
        cout<<"==============AVL Trees Used================"<<endl;
        cout<< prntClr;

        AVL_ID ? cout<<prntClr<<prntGreen : cout<<prntRed;
        cout << "1. AVL_ID " <<endl;
        AVL_Year ? cout<<prntClr<<prntGreen : cout<<prntRed;
        cout << "2. AVL_Year " <<endl;
        AVL_Deaths ? cout<<prntClr<<prntGreen : cout<<prntRed;
        cout << "3. AVL_Deaths " <<endl;
        AVL_CauseNameString ? cout<<prntClr<<prntGreen : cout<<prntRed;
        cout << "4. AVL_CauseNameString " <<endl;
        AVL_CauseName ? cout<<prntClr<<prntGreen : cout<<prntRed;
        cout << "5. AVL_CauseName " <<endl;
        AVL_State ? cout<<prntClr<<prntGreen : cout<<prntRed;
        cout << "6. AVL_State " <<endl;
        AVL_AgeAdjustedDeathRate ? cout<<prntClr<<prntGreen : cout<<prntRed;
        cout << "7. AVL_AgeAdjustedDeathRate " <<endl;
        cout<<prntClr;

        cout<<prntCyan;
        cout<<"============================================"<<endl;
        cout<< prntClr;
     



      
    }

}TreeHistory;



void MenuMain()
{
    TreeHistory.ReadFromFile();
    int choice;

    do
    {
        // ClearScreen();

        cout<<prntCyan;
        cout<<"1. Create an Index"<<endl;
        cout<<"2. Search an Key"<<endl;
        cout<<"3. Update an Key"<<endl;
        cout<<"4. Delete an Key"<<endl;
        cout<<"5. Display all Trees Made"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<prntClr;
        choice = getIntChoice("Enter your choice: ", 1, 6);

        switch (choice)
        {
        case 1:
            createIndexTreeMenu();

            break;
        case 2:
        {
            ClearScreen();
            //clearing the Tree
            if(AVL_AgeAdjustedDeathRate)
            {
                delete AVL_AgeAdjustedDeathRate;
            }
            

          
            //Load the tree from file
            if(TreeHistory.AVL_AgeAdjustedDeathRate)
            {
                AVL_AgeAdjustedDeathRate = new AVLtree<float>();
                LoadAVLTree(AVL_AgeAdjustedDeathRate, "./TreeData/AVL_AgeAdjustedDeathRate.bin");

                //Printing the tree
                cout<<prntGreen;
                AVL_AgeAdjustedDeathRate->InOrderTraversal(AVL_AgeAdjustedDeathRate->root);
                cout<<prntClr;

            }
            else
            {
                cout<<prntRed;
                cout<<"No Index Created for AVLTree on AgeAdjustedDeathRate!"<<endl;
                cout<<prntClr;
                break;
            }
            pause();
            // system("pause");
            break;
        }
        case 3:
            // RBTree();
            break;
        case 4:
            // Others();
            break;
        case 5:
            TreeHistory.display();
            pause();
            ClearScreen();
            break;
        case 6:
            cout << "Thank you for using our program" << endl;
            break;
        default:
            cout << "Invalid Input!!" << endl;
            break;
        }

    } while (choice != 6);
    


       


}




void createIndexTreeMenu()
{
    int choice;
    string field, filename = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";

    do
    {

        cout << "1. Create an Index using AVL Tree" << endl;
        cout << "2. Create an Index using B Tree" << endl;
        cout << "3. Create an Index using Red Black Tree" << endl;
        cout << "4. Back" << endl;
        choice = getIntChoice("Enter your choice: ", 1, 4);

        switch (choice)
        {
        case 1:
            cout << "Which field you want to read?\n";
            cout<<"1. ID"<<endl;
            cout<<"2. Year"<<endl;
            cout<<"3. 113 Cause Name"<<endl;
            cout<<"4. Cause Name"<<endl;
            cout<<"5. State"<<endl;
            cout<<"6. Deaths"<<endl;
            cout<<"7. Age Adjusted Death Rate"<<endl;
            cout<<"8. Back"<<endl;
            choice = getIntChoice("Enter your choice: ", 1, 8);

            switch (choice)
            {
                case 1:
                {
                    createAVLTree<int>(AVL_ID, "id");
                    break;
                }
                case 2:
                {
                    createAVLTree<int>(AVL_Year, "year");
                    break;
                }
                case 3:
                {
                    createAVLTree<string>(AVL_CauseNameString, "133cause");
                    break;
                }
                case 4:
                {
                    createAVLTree<string>(AVL_CauseName, "cause");
                    break;
                }
                case 5:
                {
                    createAVLTree<string>(AVL_State, "state");
                    break;
                }
                case 6:
                {
                    createAVLTree<int>(AVL_Deaths, "deaths");
                    break;
                }
                case 7:
                {
                    createAVLTree<float>(AVL_AgeAdjustedDeathRate, "agedeathrate");
                    break;
                }
                case 8:
                {
                    break;
                }
            }

            // Read_all_field_AVL(field, filename);
            break;
        case 2:
            // BTree();
            break;
        case 3:
            // RBTree();
            break;
        case 4:
            // Others();
            break;
        default:
            cout << "Invalid Input!!" << endl;
            break;
        }

    } while (choice != 4);

}

template <typename T>
void createAVLTree(AVLtree<T> *tree, string field)
{
    string filename;

    if(field=="id")
    {    filename="./TreeData/AVL_ID.bin";
        AVL_ID = new AVLtree<int>();
                    
        if(Read_all_files_AVL(AVL_ID, field))
        {
            cout<<prntGreen;
            cout<<"Index Created Successfully for AVLTree on ID!"<<endl;
            cout<<prntClr;
            TreeHistory.AVL_ID = true;
            TreeHistory.SaveInFile();
            saveAVLTree(AVL_ID, filename);
        }
        else
        {
            cout<<prntRed;
            cout<<"Index Creation Failed for AVLTree on ID!"<<endl;
            cout<<prntClr;
        }
    }     
    else if(field== "year")
    {
        filename="./TreeData/AVL_Year.bin";
        AVL_Year = new AVLtree<int>();
                    
        if(Read_all_files_AVL(AVL_Year, field))
        {
            cout<<prntGreen;
            cout<<"Index Created Successfully for AVLTree on Year!"<<endl;
            cout<<prntClr;
            TreeHistory.AVL_Year = true;
            TreeHistory.SaveInFile();
            saveAVLTree(AVL_Year, filename);
        }
        else
        {
            cout<<prntRed;
            cout<<"Index Creation Failed for AVLTree on Year!"<<endl;
            cout<<prntClr;
        }
    }
    else if(field== "133cause")
    {
        filename="./TreeData/AVL_CauseNameString.bin";
        AVL_CauseNameString = new AVLtree<string>();
                    
        if(Read_all_files_AVL(AVL_CauseNameString, field))
        {
            cout<<prntGreen;
            cout<<"Index Created Successfully for AVLTree on 133CauseName!"<<endl;
            cout<<prntClr;
            TreeHistory.AVL_CauseNameString = true;
            TreeHistory.SaveInFile();
            saveAVLTree(AVL_CauseNameString, filename);
        }
        else
        {
            cout<<prntRed;
            cout<<"Index Creation Failed for AVLTree on 133CauseName!"<<endl;
            cout<<prntClr;
        }
    }
    else if(field== "cause")
    {
        filename="./TreeData/AVL_CauseName.bin";
        AVL_CauseName = new AVLtree<string>();
                    
        if(Read_all_files_AVL(AVL_CauseName, field))
        {
            cout<<prntGreen;
            cout<<"Index Created Successfully for AVLTree on CauseName!"<<endl;
            cout<<prntClr;
            TreeHistory.AVL_CauseName = true;
            TreeHistory.SaveInFile();
            saveAVLTree(AVL_CauseName, filename);
        }
        else
        {
            cout<<prntRed;
            cout<<"Index Creation Failed for AVLTree on CauseName!"<<endl;
            cout<<prntClr;
        }
    }
    else if (field == "state")
    {
        filename="./TreeData/AVL_State.bin";
        AVL_State = new AVLtree<string>();
                    
        if(Read_all_files_AVL(AVL_State, field))
        {
            cout<<prntGreen;
            cout<<"Index Created Successfully for AVLTree on State!"<<endl;
            cout<<prntClr;
            TreeHistory.AVL_State = true;
            TreeHistory.SaveInFile();
            saveAVLTree(AVL_State, filename);
        }
        else
        {
            cout<<prntRed;
            cout<<"Index Creation Failed for AVLTree on State!"<<endl;
            cout<<prntClr;
        }
    }
    else if(field== "deaths")
    {
        filename="./TreeData/AVL_Deaths.bin";
        AVL_Deaths = new AVLtree<int>();
                    
        if(Read_all_files_AVL(AVL_Deaths, field))
        {
            cout<<prntGreen;
            cout<<"Index Created Successfully for AVLTree on Deaths!"<<endl;
            cout<<prntClr;
            TreeHistory.AVL_Deaths = true;
            TreeHistory.SaveInFile();
            saveAVLTree(AVL_Deaths, filename);
        }
        else
        {
            cout<<prntRed;
            cout<<"Index Creation Failed for AVLTree on Deaths!"<<endl;
            cout<<prntClr;
        }
    }
    else if(field== "agedeathrate")
    {
        filename="./TreeData/AVL_AgeAdjustedDeathRate.bin";
        AVL_AgeAdjustedDeathRate = new AVLtree<float>();
                    
        if(Read_all_files_AVL(AVL_AgeAdjustedDeathRate, field))
        {
            cout<<prntGreen;
            cout<<"Index Created Successfully for AVLTree on AgeAdjustedDeathRate!"<<endl;
            cout<<prntClr;
            TreeHistory.AVL_AgeAdjustedDeathRate = true;
            TreeHistory.SaveInFile();
            saveAVLTree(AVL_AgeAdjustedDeathRate, filename);
        }
        else
        {
            cout<<prntRed;
            cout<<"Index Creation Failed for AVLTree on AgeAdjustedDeathRate!"<<endl;
            cout<<prntClr;
        }
    }
    else
    {
        cout<<prntRed;
        cout<<"Invalid Field!!"<<endl;
        cout<<prntClr;
    }
    
}


int getIntChoice(string Prompt, int min, int max)
{
    int choice;
    do
    {
        cout<<prntYellow;
        cout << Prompt; // Display the prompt
        cin >> choice; // Get the user's choice
        cout<<prntClr;
        if (!cin.good()  ||  choice < min || choice > max)
        {
            cout<<prntRed;
            cout << "Invalid Input!!" << endl; // Display error message
            cout<<prntClr;
            cin.clear();
            cin.ignore(1000, '\n');


        }

    } while (!cin.good() || choice < min || choice > max);

    return choice;

}

string getStringChoice(string Prompt, string min, string max)
{
    string choice;
    do
    {
        cout << Prompt; // Display the prompt
        cin >> choice; // Get the user's choice
        if (!cin.good())
        {
            cout << "Invalid Input!!" << endl; // Display error message
            cin.clear();

        }
        

    } while (!cin.good());

    return choice;

}


void ClearScreen()
{
    //If the system is windows
    #ifdef _WIN32
        system("cls");
    #else //If the system is not windows
        system("clear");
    #endif
}

void pause()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("pause");
    #else
        system("read -n 1 -s -p \"Press any key to continue...\"\n");
    #endif
}


struct Trunk
{
	Trunk *prev;
	string str;

	Trunk(Trunk *prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	cout << p->str;
}

void printTree(Node<int>* root, Trunk *prev, bool isLeft)
{
	if (root == nullptr) {
		return;
	}

	string prev_str = "    ";
	Trunk *trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true);

	if (!prev) {
		trunk->str = "———";
	}
	else if (isLeft)
	{
		trunk->str = ".———";
		prev_str = "   |";
	}
	else {
		trunk->str = "`———";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << " " << root->key << endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}


