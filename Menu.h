#pragma once
#include <iostream>
#include "Filehandling.h"
// #include "RBTree.h"
// #include "Others.h"


using namespace std;

// Function prototypes
//Menus
void Menu();
void searchKeyMenu();
void rangeSearchMenu();
void pointSearchMenu();



void DeleteMenu();
void pointDelete(string field);

void ClearScreen();
void pause();
int getIntChoice(string Prompt, int min, int max);
float getFloatChoice(string Prompt, float min, float max);
string getStringChoice(string Prompt);
void createIndexTreeMenu();
template <typename T>
void createAVLTree(AVLtree<T>* tree,string field);





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
            searchKeyMenu();
            
            break;
        }
        case 3:
            // RBTree();
            break;
        case 4:
            DeleteMenu();
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

void DeleteMenu()
{
    int choice;
    do
    {
        cout<<"1. Delete by ID"<<endl;
        cout<<"2. Delete by Year"<<endl;
        cout<<"3. Delete by Deaths"<<endl;
        cout<<"4. Delete by CauseNameString"<<endl;
        cout<<"5. Delete by CauseName"<<endl;
        cout<<"6. Delete by State"<<endl;
        cout<<"7. Delete by AgeAdjustedDeathRate"<<endl;
        cout<<"8. Back"<<endl;
        choice = getIntChoice("Enter your choice: ", 1, 8);

        switch (choice)
        {
        case 1:
            pointDelete("id");
            break;
        case 2:
            pointDelete("year");
            break;
        case 3:
            pointDelete("deaths");
            break;
        case 4:
            pointDelete("133cause");
            break;
        case 5:
            pointDelete("cause");
            break;
        
        case 6:
            pointDelete("state");
            break;
        default:
            break;
        }
       

    } while (choice!=8);
}

void searchKeyMenu()
{
    int choice;
    do
    {
        cout<<"1. Point Search"<<endl;
        cout<<"2. Range Search"<<endl;
        cout<<"3. Back"<<endl;
        choice = getIntChoice("Enter your choice: ", 1, 3);

        switch (choice)
        {
        case 1:
            pointSearchMenu();
            break;
        case 2:
            // rangeSearchMenu();
            break;
        default:
            break;
        }
       

    } while (choice!=3);
    



}


void pointDelete(string feild)
{
    // cout<<"point search";
    if(feild=="id")
    {
        if(TreeHistory.AVL_ID)
        {   
             //LOAD THE TREE
                AVL_ID = new AVLtree<int>;
                LoadAVLTree(AVL_ID,"./TreeData/AVL_ID.bin");

            
            int key;
            do
            {
                key = getIntChoice("[-1 to quit] Enter the ID to delete: ", -1, 1000000);
                if(key==-1)
                    break;

                Value<int> ValKey;
                ValKey.tuple = key;

                Node<int>* result = AVL_ID->Search(AVL_ID->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= ID Found ==========="<<endl;
                    result->val->print();
                
                    cout<<prntClr;
                    cout<<"Do you want to delete this record? (y/n): ";
                    char ch;
                    cin>>ch;
                    if(ch=='y')
                    {
                        
                        for(int i=0;i<result->val->Entries ;i++)
                        {
                            DeleteRowFromCSV(result->val->fileName[i],result->val->lineNumber[i]);
                         
                        }
                       
                          delete AVL_ID;
                            AVL_ID = new AVLtree<int>;
                            Read_all_files_AVL(AVL_ID,"id");

                        cout<<prntGreen;
                        cout<<"Record Deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    else
                    {
                        cout<<prntRed;
                        cout<<"Record not deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    
                }
                else
                {
                    cout<<prntRed;
                    cout<<" ============= ID Not Found ==========="<<endl;
                    cout<<prntClr;
                    pause();
                }
                
            } while (key!=-1);
            
             saveAVLTree(AVL_ID,"./TreeData/AVL_ID.bin");
        }
        else
        {
            cout<<prntRed;
            cout<<" ============= ID Tree Not Found ==========="<<endl;
            cout<<prntClr;
            pause();
        }
        
    }
    else if(feild=="year")
    {
        if(TreeHistory.AVL_Year)
        {   
             //LOAD THE TREE
                AVL_Year = new AVLtree<int>;
                LoadAVLTree(AVL_Year,"./TreeData/AVL_Year.bin");

            
            int key;
            do
            {
                key = getIntChoice("[-1 to quit] Enter the Year to delete: ", -1, 1000000);
                if(key==-1)
                    break;

                Value<int> ValKey;
                ValKey.tuple = key;

                Node<int>* result = AVL_Year->Search(AVL_Year->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Year Found ==========="<<endl;
                    result->val->print();
                
                    cout<<prntClr;
                    cout<<"Do you want to delete this record? (y/n): ";
                    char ch;
                    cin>>ch;
                    if(ch=='y')
                    {
                        for(int i=0;i<result->val->Entries ;i++)
                        {
                            DeleteRowFromCSV(result->val->fileName[i],result->val->lineNumber[i]);
                            
                            
                        }

                      delete AVL_Year;
                            AVL_Year = new AVLtree<int>;
                            Read_all_files_AVL(AVL_Year,"year");

                        cout<<prntGreen;
                        cout<<"Record Deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    else
                    {
                        cout<<prntRed;
                        cout<<"Record not deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    
                }
                else
                {
                    cout<<prntRed;
                    cout<<" ============= Year Not Found ==========="<<endl;
                    cout<<prntClr;
                    pause();
                }
                
            } while (key!=-1);
            
             saveAVLTree(AVL_Year,"./TreeData/AVL_Year.bin");
        }
        else
        {
            cout<<prntRed;
            cout<<" ============= Year Tree Not Found ==========="<<endl;
            cout<<prntClr;
            pause();
        }
        
    }
    else if(feild=="state")
    {
        if(TreeHistory.AVL_State)
        {   
             //LOAD THE TREE
                AVL_State = new AVLtree<string>;
                LoadAVLTree(AVL_State,"./TreeData/AVL_State.bin");

            
            string key;
            do
            {
                key = getStringChoice("[-1 to quit] Enter the State to delete: ");
                if(key=="-1")
                    break;

                Value<string> ValKey;
                ValKey.tuple = key;

                Node<string>* result = AVL_State->Search(AVL_State->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= State Found ==========="<<endl;
                    result->val->print();
                
                    cout<<prntClr;
                    cout<<"Do you want to delete this record? (y/n): ";
                    char ch;
                    cin>>ch;
                    if(ch=='y')
                    {
                        for(int i=0;i<result->val->Entries ;i++)
                        {
                            DeleteRowFromCSV(result->val->fileName[i],result->val->lineNumber[i]);
                            
                        }

                       
                        delete AVL_State;
                        AVL_State = new AVLtree<string>;
                        Read_all_files_AVL(AVL_State,"state");
                        cout<<prntGreen;
                        cout<<"Record Deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    else
                    {
                        cout<<prntRed;
                        cout<<"Record not deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    
                }
                else
                {
                    cout<<prntRed;
                    cout<<" ============= State Not Found ==========="<<endl;
                    cout<<prntClr;
                    pause();
                }
                
            } while (key!="-1");
            
             saveAVLTree(AVL_State,"./TreeData/AVL_State.bin");
        }
        else
        {
            cout<<prntRed;
            cout<<" ============= State Tree Not Found ==========="<<endl;
            cout<<prntClr;
            pause();
        }
        
    }
    else if(feild=="deaths")
    {
        if(TreeHistory.AVL_Deaths)
        {   
             //LOAD THE TREE
                AVL_Deaths = new AVLtree<int>;
                LoadAVLTree(AVL_Deaths,"./TreeData/AVL_Deaths.bin");

            
            int key;
            do
            {
                key = getIntChoice("[-1 to quit] Enter the Deaths to delete: ", -1, 1000000);
                if(key==-1)
                    break;

                Value<int> ValKey;
                ValKey.tuple = key;

                Node<int>* result = AVL_Deaths->Search(AVL_Deaths->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Deaths Found ==========="<<endl;
                    result->val->print();
                
                    cout<<prntClr;
                    cout<<"Do you want to delete this record? (y/n): ";
                    char ch;
                    cin>>ch;
                    if(ch=='y')
                    {
                        for(int i=0;i<result->val->Entries ;i++)
                        {
                            DeleteRowFromCSV(result->val->fileName[i],result->val->lineNumber[i]);
                            
                        }

                        delete AVL_Deaths;
                        AVL_Deaths = new AVLtree<int>;
                        Read_all_files_AVL(AVL_Deaths,"deaths");
                        cout<<prntGreen;
                        cout<<"Record Deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    else
                    {
                        cout<<prntRed;
                        cout<<"Record not deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    
                }
                else
                {
                    cout<<prntRed;
                    cout<<" ============= Deaths Not Found ==========="<<endl;
                    cout<<prntClr;
                    pause();
                }
                
            } while (key!=-1);
            
             saveAVLTree(AVL_Deaths,"./TreeData/AVL_Deaths.bin");
        }
        else
        {
            cout<<prntRed;
            cout<<" ============= Deaths Tree Not Found ==========="<<endl;
            cout<<prntClr;
            pause();
        }
        
    }
    else if(feild=="cause")
    {
        if(TreeHistory.AVL_CauseName)
        {   
             //LOAD THE TREE
                AVL_CauseName = new AVLtree<string>;
                LoadAVLTree(AVL_CauseName,"./TreeData/AVL_CauseName.bin");

            
            string key;
            do
            {
                key = getStringChoice("[-1 to quit] Enter the Cause to delete: ");
                if(key=="-1")
                    break;

                Value<string> ValKey;
                ValKey.tuple = key;

                Node<string>* result = AVL_CauseName->Search(AVL_CauseName->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Cause Found ==========="<<endl;
                    result->val->print();
                
                    cout<<prntClr;
                    cout<<"Do you want to delete this record? (y/n): ";
                    char ch;
                    cin>>ch;
                    if(ch=='y')
                    {
                        for(int i=0;i<result->val->Entries ;i++)
                        {
                            DeleteRowFromCSV(result->val->fileName[i],result->val->lineNumber[i]);
                            
                        }

                        delete AVL_CauseName;
                        AVL_CauseName = new AVLtree<string>;
                        Read_all_files_AVL(AVL_CauseName,"cause");
                        cout<<prntGreen;
                        cout<<"Record Deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    else
                    {
                        cout<<prntRed;
                        cout<<"Record not deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    
                }
                else
                {
                    cout<<prntRed;
                    cout<<" ============= Cause Not Found ==========="<<endl;
                    cout<<prntClr;
                    pause();
                }
                
            } while (key!="-1");
            
             saveAVLTree(AVL_CauseName,"./TreeData/AVL_Cause.bin");
        }
        else
        {
            cout<<prntRed;
            cout<<" ============= Cause Tree Not Found ==========="<<endl;
            cout<<prntClr;
            pause();
        }
        
    }
    else if(feild=="133cause")
    {
        if(TreeHistory.AVL_CauseNameString)
        {   
             //LOAD THE TREE
                AVL_CauseNameString = new AVLtree<string>;
                LoadAVLTree(AVL_CauseNameString,"./TreeData/AVL_CauseNameString.bin");

            
            string key;
            do
            {
                key = getStringChoice("[-1 to quit] Enter the 133 Cause to delete: ");
                if(key=="-1")
                    break;

                Value<string> ValKey;
                ValKey.tuple = key;

                Node<string>* result = AVL_CauseNameString->Search(AVL_CauseNameString->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= 133 Cause Found ==========="<<endl;
                    result->val->print();
                
                    cout<<prntClr;
                    cout<<"Do you want to delete this record? (y/n): ";
                    char ch;
                    cin>>ch;
                    if(ch=='y')
                    {
                        for(int i=0;i<result->val->Entries ;i++)
                        {
                            DeleteRowFromCSV(result->val->fileName[i],result->val->lineNumber[i]);
                            
                        }

                        delete AVL_CauseNameString;
                        AVL_CauseNameString = new AVLtree<string>;
                        Read_all_files_AVL(AVL_CauseNameString,"133cause");
                        cout<<prntGreen;
                        cout<<"Record Deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    else
                    {
                        cout<<prntRed;
                        cout<<"Record not deleted"<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    
                }
                else
                {
                    cout<<prntRed;
                    cout<<" ============= 133 Cause Not Found ==========="<<endl;
                    cout<<prntClr;
                    pause();
                }
                
            } while (key!="-1");
            
             saveAVLTree(AVL_CauseNameString,"./TreeData/AVL_133Cause.bin");
        }
        else
        {
            cout<<prntRed;
            cout<<" ============= 133 Cause Tree Not Found ==========="<<endl;
            cout<<prntClr;
            pause();
        }
        
    }
    else if(feild=="agedeathrates")
    {
        if(TreeHistory.AVL_AgeAdjustedDeathRate)
        {   
                //LOAD THE TREE
                    AVL_AgeAdjustedDeathRate = new AVLtree<float>;
                    LoadAVLTree(AVL_AgeAdjustedDeathRate,"./TreeData/AVL_AgeAdjustedDeathRate.bin");
    
                
                float key;
                do
                {
                    key = getFloatChoice("[-1 to quit] Enter the Age Adjusted Death Rate to delete: ",-1,1000);
                    if(key==-1)
                        break;
    
                    Value<float> ValKey;
                    ValKey.tuple = key;
    
                    Node<float>* result = AVL_AgeAdjustedDeathRate->Search(AVL_AgeAdjustedDeathRate->root,ValKey);
    
                    if(result)
                    {
                        cout<<prntGreen;
                        cout<<" ============= Age Adjusted Death Rate Found ==========="<<endl;
                        result->val->print();
                    
                        cout<<prntClr;
                        cout<<"Do you want to delete this record? (y/n): ";
                        char ch;
                        cin>>ch;
                        if(ch=='y')
                        {
                            for(int i=0;i<result->val->Entries ;i++)
                            {
                                DeleteRowFromCSV(result->val->fileName[i],result->val->lineNumber[i]);
                                
                            }
    
                            delete AVL_AgeAdjustedDeathRate;
                            AVL_AgeAdjustedDeathRate = new AVLtree<float>;
                            Read_all_files_AVL(AVL_AgeAdjustedDeathRate,"agedeathrates");
                            cout<<prntGreen;
                            cout<<"Record Deleted"<<endl;
                            cout<<prntClr;
                            pause();
                        }
                        else
                        {
                            cout<<prntRed;
                            cout<<"Record not deleted"<<endl;
                            cout<<prntClr;
                            pause();
                        }
                        
                    }
                    else
                    {
                        cout<<prntRed;
                        cout<<" ============= Age Adjusted Death Rate Not Found ==========="<<endl;
                        cout<<prntClr;
                        pause();
                    }
                    
                } while (key!=-1);
                
                saveAVLTree(AVL_AgeAdjustedDeathRate,"./TreeData/AVL_AgeAdjustedDeathRate.bin");
            }
            else
            {
                cout<<prntRed;
                cout<<" ============= Age Adjusted Death Rate Tree Not Found ==========="<<endl;
                cout<<prntClr;
                pause();
        }


    }

   
}
void pointSearch(string feild)
{
    // cout<<"point search";
    if(feild=="id")
    {
        if(TreeHistory.AVL_ID)
        {   
             //LOAD THE TREE
                AVL_ID = new AVLtree<int>;
                LoadAVLTree(AVL_ID,"./TreeData/AVL_ID.bin");

            
            int key;
            do
            {
                key = getIntChoice("[-1 to quit] Enter the ID to search: ", -1, 1000000);
                if(key==-1)
                    break;

                Value<int> ValKey;
                ValKey.tuple = key;

                Node<int>* result = AVL_ID->Search(AVL_ID->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= ID Found ==========="<<endl;
                    result->val->print();
                    cout<<endl;
                    cout<<prntClr;

                }
                else
                {
                    cout<<prntRed;
                    cout<<"ID Not Found"<<endl;
                    cout<<prntClr;
                }
    


            } while (true);
            
            
          


            
        }
        else
        {
            cout<<prntRed;
            cout<<"AVL Tree for ID is not created"<<endl;
            cout<<prntClr;
        }

    }
    else if(feild=="year")
    {
        if(TreeHistory.AVL_Year)
        {   
             //LOAD THE TREE
                AVL_Year = new AVLtree<int>;
                LoadAVLTree(AVL_Year,"./TreeData/AVL_Year.bin");

            
            int key;
            do
            {
                key = getIntChoice("[-1 to quit] Enter the Year to search: ", -1, 1000000);
                if(key==-1)
                    break;

                Value<int> ValKey;
                ValKey.tuple = key;

                Node<int>* result = AVL_Year->Search(AVL_Year->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Year Found ==========="<<endl;
                    result->val->print();
                    cout<<endl;
                    cout<<prntClr;

                }
                else
                {
                    cout<<prntRed;
                    cout<<"Year Not Found"<<endl;
                    cout<<prntClr;
                }
            }while (true);

        }
            







}
    else if (feild=="deaths")
    {
        if(TreeHistory.AVL_Deaths)
        {   
             //LOAD THE TREE
                AVL_Deaths = new AVLtree<int>;
                LoadAVLTree(AVL_Deaths,"./TreeData/AVL_Deaths.bin");

            
            int key;
            do
            {
                key = getIntChoice("[-1 to quit] Enter the Deaths to search: ", -1, 1000000);
                if(key==-1)
                    break;

                Value<int> ValKey;
                ValKey.tuple = key;

                Node<int>* result = AVL_Deaths->Search(AVL_Deaths->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Deaths Found ==========="<<endl;
                    result->val->print();
                    cout<<endl;
                    cout<<prntClr;

                }
                else
                {
                    cout<<prntRed;
                    cout<<"Deaths Not Found"<<endl;
                    cout<<prntClr;
                }
            }while (true);

        }

    






}
    else if (feild=="cause")
    {
        if(TreeHistory.AVL_CauseName)
        {   
             //LOAD THE TREE
                AVL_CauseName = new AVLtree<string>;
                LoadAVLTree(AVL_CauseName,"./TreeData/AVL_CauseName.bin");

            
            string key;
            do
            {
                key = getStringChoice("[-1 to quit] Enter the Cause to search: ");
                if(key=="-1")
                    break;

                Value<string> ValKey;
                ValKey.tuple = key;

                Node<string>* result = AVL_CauseName->Search(AVL_CauseName->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Cause Found ==========="<<endl;
                    result->val->print();
                    cout<<endl;
                    cout<<prntClr;

                }
                else
                {
                    cout<<prntRed;
                    cout<<"Cause Not Found"<<endl;
                    cout<<prntClr;
                }
            }while (true);

        }



}
    else if (feild=="state")
    {
        if(TreeHistory.AVL_State)
        {   
             //LOAD THE TREE
                AVL_State = new AVLtree<string>;
                LoadAVLTree(AVL_State,"./TreeData/AVL_State.bin");

            
            string key;
            do
            {
                key = getStringChoice("[-1 to quit] Enter the State to search: ");
                if(key=="-1")
                    break;

                Value<string> ValKey;
                ValKey.tuple = key;

                Node<string>* result = AVL_State->Search(AVL_State->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= State Found ==========="<<endl;
                    result->val->print();
                    cout<<endl;
                    cout<<prntClr;

                }
                else
                {
                    cout<<prntRed;
                    cout<<"State Not Found"<<endl;
                    cout<<prntClr;
                }
            }while (true);

        }




}
    else if (feild=="agedeathrate")
    {
        if (TreeHistory.AVL_AgeAdjustedDeathRate)
        {
            //LOAD THE TREE
                AVL_AgeAdjustedDeathRate = new AVLtree<float>;
                LoadAVLTree(AVL_AgeAdjustedDeathRate,"./TreeData/AVL_AgeAdjustedDeathRate.bin");

            
            float key;
            do
            {
                key = getFloatChoice("[-1 to quit] Enter the Age Adjusted Death Rate to search: ", -1, 1000000);
                if(key==-1)
                    break;

                Value<float> ValKey;
                ValKey.tuple = key;

                Node<float>* result = AVL_AgeAdjustedDeathRate->Search(AVL_AgeAdjustedDeathRate->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Age Adjusted Death Rate Found ==========="<<endl;
                    result->val->print();
                    cout<<endl;
                    cout<<prntClr;

                }
                else
                {
                    cout<<prntRed;
                    cout<<"Age Adjusted Death Rate Not Found"<<endl;
                    cout<<prntClr;
                }
            }while (true);

        }
    
    

}
    else if (feild=="133cause")
    {
        if (TreeHistory.AVL_CauseNameString)
        {
            //LOAD THE TREE
                AVL_CauseNameString = new AVLtree<string>;
                LoadAVLTree(AVL_CauseNameString,"./TreeData/AVL_CauseNameString.bin");

            
            string key;
            do
            {
                key = getStringChoice("[-1 to quit] Enter the Cause Name to search: ");
                if(key=="-1")
                    break;

                Value<string> ValKey;
                ValKey.tuple = key;

                Node<string>* result = AVL_CauseNameString->Search(AVL_CauseNameString->root,ValKey);

                if(result)
                {
                    cout<<prntGreen;
                    cout<<" ============= Cause Name Found ==========="<<endl;
                    result->val->print();
                    cout<<endl;
                    cout<<prntClr;

                }
                else
                {
                    cout<<prntRed;
                    cout<<"Cause Name Not Found"<<endl;
                    cout<<prntClr;
                }
            }while (true);

        }

    }
}
void pointSearchMenu()
{
    int choice;
    do
    {
        cout<<"1. ID Search"<<endl;
        cout<<"2. Year Search"<<endl;
        cout<<"3. Deaths Search"<<endl;
        cout<<"4. 133 Cause"<<endl;
        cout<<"5. Cause Name Search"<<endl;
        cout<<"6. State Search"<<endl;
        cout<<"7. Age Adjusted Death Rate Search"<<endl;
        cout<<"8. Back"<<endl;
        choice = getIntChoice("Enter your choice: ", 1, 8);

        switch (choice)
        {
        case 1:  
            pointSearch("id");
            break;
        case 2:
            pointSearch("year");
            break;
        case 3:
            pointSearch("deaths");
            break;
        case 4:
            pointSearch("133cause");
            break;
        case 5:
            pointSearch("cause");
             break;
        case 6:
            pointSearch("state");
            break;
        case 7:
            pointSearch("agedeathrate");
            break;
        default:
            break;
        }


    } while (choice!=8);

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

string getStringChoice(string Prompt)
{
    cin.ignore(1000, '\n');
    string choice;
    do
    {
        cout << Prompt; // Display the prompt
        getline(cin, choice); // Get the user's choice
        if (!cin.good())
        {
            cout << "Invalid Input!!" << endl; // Display error message
            cin.clear();

        }
        

    } while (!cin.good());

    return choice;

}

float getFloatChoice(string Prompt, float min, float max)
{
    float choice;
    do
    {
        cout << Prompt; // Display the prompt
        cin >> choice; // Get the user's choice
        if (!cin.good() || choice < min || choice > max)
        {
            cout << "Invalid Input!!" << endl; // Display error message
            cin.clear();

        }

    } while (!cin.good() || choice < min || choice > max);

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


