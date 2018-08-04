//
//  main.cpp
//  PA2
//
//  Created by Alejandro Santacoloma on 3/10/17.
//  Copyright © 2017 Alejandro Santacoloma. All rights reserved.
//

#include <iostream>
#include "pa2.h"
#include <cstring>

using namespace std;

int main(int argc, const char * argv[]) {
    bool UseBest;
    //command line input, check to make sure user gave command of whether to use best or worst,
    //if not, program is ended
    if (argc != 2)
    {
    cout<<"Did not enter whether bestfit or worstfit";
        return 0;
    }
    if (strcmp(argv[1],"best") == 0 )
    {
        UseBest = true;
    }
    else if(strcmp(argv[1],"false") ==0 )
    {
        UseBest = false;
    }
    else
    {
    cout<<"invalid input";
        return 0;
    }

    
    
    
  
    
    //32 pages of memory, each page of memory is 4KB
    
    //things to inilitaze outside while loop
    string ProgramName = "NULL";
    int menuchoice = -1; // user choice for menu
    //int totalfree = 32;
    int KBsize = 0;
    int Psize = 0;
    int useindex = -1;
    bool result = false;
   
    //Initialize memory linked list
    LinkList Memory;
    
    for(int ii = 0; ii < 32; ii++)
    {
        Memory.AddPage("Free");
    }
    
    

    //print out menu choices
    cout<<"1. Add program\n"<<"2. Kill program\n"<<"3. Fragmentation\n"<<"4. Print memory\n"<<"5. Exit\n";
    
    
    //while loop to run main menu
    while (menuchoice != 5)
    {
        //get input
        
        cin>>menuchoice;
        //check for valid input
//        if(menuchoice >=1 && menuchoice <= 5) //checks to make sure input is in range and is an integer
//        {
//            //
//        }
        if(menuchoice == 0){//check for strings
            std::cout<<"Real menuchoice brosky (that means no strings or 0s)\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            menuchoice = 0;
        }
        else if (menuchoice>5 || menuchoice<1)
        {
            std::cout<<"Integer input between 1 and 5 bro\n";
        }
        else
        {
        
        
        //if menuchoice == 1, add program using previously chosen algorithm
        if(menuchoice == 1)
        {
            
        cout<<"choice - 1\n"<<"Program name - ";
        cin>>ProgramName;
        if(ProgramName == "Free")
        {
            cout<< "Error, cannot have program named Free\n";
            continue;
        }
        cout<<"\n";
        cout<<"Program size (KB) -";
        cin>>KBsize;
        cout<<"\n";
            
            if (intcheck(KBsize) == false)
            {
                cout<<"Invalid input\n";
                continue;
            }
            
            //calculate page size needed for memory of program
            if (KBsize<4)
            {
                Psize = 1;
            }
            else if(KBsize%4 !=0)
            {
                Psize = (KBsize/4) + 1 ;
            }
            else
            {
                Psize = (KBsize/4);
            }
            cout<<"psize is "<<Psize<<"\n";
            
            //use best or worstfit algorithm
            
            useindex = Memory.BWFIT(ProgramName, Psize, UseBest);
            
            if (useindex >= 0)
            {
                //for loop to add page by page the program
                for(int ii = 0; ii < Psize; ii++)
                {
                result = Memory.ReplaceP(ProgramName, (useindex + ii));
                }
                if (result == true)
                {
                    cout<<"Program "<<ProgramName<<" added succesfully: "<<Psize<< "page(s) used\n";
                }
                else
                {
                     cout<<"Error, Program "<<ProgramName<<" not added succesfully\n";
                }
            }
            else if (useindex == -1 )
            {
                cout<<"Error, not enough memory for Program "<<ProgramName<<"\n";
            }
            else if (useindex == -2 )
            {
                cout<<"Error, Program "<<ProgramName<<" already running\n";
            }
            
        }
        
        
        //if menuchoice == 2, a program is killed
        else if (menuchoice == 2)
        {
            
        //ask for program to kill
        cout<<"choice - 2\nProgram name - ";
        cin>>ProgramName;
        cout<<"\n";
            
            if(ProgramName == "Free")
            {
                cout<< "Error, cannot kill Free\n";
            }
            Psize = Memory.KillP(ProgramName);
            if(Psize > 0 )
            {
                cout<<"Program "<< ProgramName << " sucessfully killed, "<< Psize <<" page(s) reclaimed.\n";
            }
            else
            {
                cout<<"Error, program "<< ProgramName << " unsucessfully killed.\n";
            }

        }
            
        //if menuchoice == 3 check for fragmentation
        else if(menuchoice == 3)
        {
            cout<<"choice - 3\n";
            Memory.FindFragments();
        }
        
        //if menuchoice == 4 print memory
        else if(menuchoice == 4)
        {
            cout<<"choice - 4\n";
            Memory.PrintLinkList();
        }
        
        
        //if menuchoice == 5 Exit
        else if(menuchoice == 5)
        {
            break;
        }
        
        }
    }
    return 0;
}
