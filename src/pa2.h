//
//  pa2.h
//
//
//  Created by Alejandro Santacoloma on 3/10/17.
//  Copyright © 2017 Alejandro Santacoloma. All rights reserved.
//

#ifndef pa2_h
#define pa2_h


#include <iostream>

#include "stdio.h"

using namespace std;


void command(int argc, char *argv[]);


bool intcheck(int input)
{
    if(input == 0){//check for strings
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return false;
    }
    else if (input<1)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return false;
    }
    else
    {
        return true;
    }

}


class LinkList{ //linked list class


    
    
// private data for security purposes
private:

typedef struct node{
    
    string info;
    node *NextP;
    bool isfree;
    
}* nodePTR;

    nodePTR Head;
    nodePTR Current;
    
public:
    
    LinkList(); //Public functions
    
    void AddPage(string Addinfo);
    void FindFragments();
    void PrintLinkList();
    bool ReplaceP(string Program, int index);
    int KillP(string Program);
    bool BestWorstFit(string Program, int PageSize, bool Best);
    int BWFIT(string Program, int PageSize, bool Best);
    //bool BWFIT(string Program, int PageSize, bool Best);
    
    //Public variables
   
    bool Best;
    
};

//Link list object constructor
LinkList::LinkList()
{
    Head = NULL;
    Current = NULL;
    
}

//functions

//function to add a new node to linkedlist
void LinkList::AddPage(string Addinfo)
{
    nodePTR npt = new node;
    npt->NextP = NULL;
    npt->info = Addinfo;
    if(Head != NULL)
    {
        Current = Head;
        //while loop to go through linked list until end is reached, then a page is added to the end
            while(Current->NextP != NULL)
            {
                Current = Current->NextP;
            }
        Current-> NextP = npt;
    }
    else
    {
        Head = npt;
    }
        
}




bool LinkList::ReplaceP(string Program, int InitIndex)
{

Current = Head;


// for loop to go through linked list until index of interest is reached
    for(int ii = 0; ii < InitIndex; ii++)
{
    Current = Current->NextP;
}
//once at index of interest, if it is free, then program is "added" to this node
if (Current->info == "Free")
{
    Current->info = Program;
    return true;
}
else
{
    return false;
}
    
}



int LinkList::KillP(string Program)
{
    
    //start with head of linked list
    Current = Head;
    int killed = 0;
    
    //while loop to check nodes of linked list for program to kill
    while(Current-> NextP != NULL)
    {
        //if statement to find and kill target program
        if(Current-> info == Program)
        {
            Current-> info = "Free";
            killed++;
        }
        
        //if statement to go to next node if not already at end of linked list
        if(Current-> NextP != NULL)
        {
            Current = Current -> NextP;
        }
    }
    
    return killed;//return whether or not program was succesfully killed
    
}

void LinkList::FindFragments()
{
    int Frags = 0; // initialze fragment counter to 0
    bool Newfrag = true; // ensures same fragment isn't counted more than once
    
    Current = Head; // start at beginning of linked list
    string Prog;
    
    while(Current!= NULL)
    {
        //if statement to check for fragment and whether its a new fragment
        if(Current ->info == "Free" && Newfrag == true )
        {
            Frags = Frags + 1; //Increment Frag counter
            Newfrag = false;
            Current = Current->NextP;
        }
        else if (Current->info == "Free" && Newfrag == false)
        {
            Current = Current->NextP;
        }
        else
        {
            Current = Current ->NextP;
            Newfrag = true;
        }
            
    }
            
    cout<<"There are "<< Frags << " fragment(s)\n";
}

void LinkList::PrintLinkList()
{
    //for loop to print out every node of linked list
    Current = Head;
    for (int ii = 1; ii <= 32; ii++)
    {
            // if ii is divisible by 8, then new line is creeated in printing of linked list
            if(ii % 8 == 0)
            {
                cout<<Current->info<<" \n";
                Current = Current->NextP;
            }
            else
            {
                //Tab to help keep print of linked list uniform in length
                cout<<Current->info<<"\t";
                Current = Current->NextP;
            }
    }
}


int LinkList::BWFIT(string Program, int PageSize, bool Best)
{
    
    //bestfit algorithm
    //check all memory nodes, memory size found - memory needed for program, use memory slot
    //with closest difference to 0 but not less than 0
    
    
    //worstfit algorithm, use largest memory space possible
    
    
    Current = Head;
    
    int pagecounter = 0;
    int spot = 0;
    int tempspot = 0;
    bool Newfrag = true; // ensures same fragment isn't counted more than once
    int currentfit; // variable for current best fit or current worst fit size depending on which algorithm it is used in
    int targetindex = -1; // if targetindex (index of first page to place program in linked list) is still -1 by end of algorithm, then there wasn't enough space for the program
    bool endfrag = false;
    int fragsize = 0; //variable to keep count of current free fragment size
    
    //Bestfit algorithm
    if(Best == true)
    {
        currentfit = 33;
        //while loop to go through entire linklist
        while(Current != NULL)
        {
            //if statement to check if program to add is a new program
            if(Current->info == Program)
            {
            return -2;
            }
            //if statement to check for fragment and whether its a new fragment
            else if(Current ->info == "Free" && Newfrag == true )
            {   spot++;
                
                pagecounter = 1;
                fragsize = 1;
                Current = Current->NextP;
                Newfrag = false;
                endfrag = false;
                tempspot = spot-1;
                
                //while loop to check how much free space is in this memory fragment
                while(Current -> info == "Free")
                {
                    fragsize++;
                    //tempspot++;
                   
                    Current = Current->NextP;
                    if (Current == NULL)
                    {
                        break;
                    }
                
                }
                
                if(fragsize > PageSize && fragsize < currentfit)
                {
                    currentfit = fragsize;
                    targetindex = tempspot;
                }
                
                
            }
            else if (Current->info == "Free" && Newfrag == false)
            {
                spot++;
                pagecounter++;
                
                Current = Current->NextP;
                
            }
            //this only occurrs right after leaving a free fragment, now evaluate if fragment is really best fit
            else if (Current->info != "Free" && Newfrag == false)
            {
                spot++;
                endfrag  = true;
                Newfrag = true;
                
                //if statement to update currentfit only if the current free fragment is large enough to hold the program
                //and is smaller than current best size free fragment
                if(fragsize >= PageSize && fragsize < currentfit)
                {
                    targetindex = spot;
                }
                
            }
            
            else
            {
                //reset pagecounter once current free frag is done
                spot++;
                
                Current = Current ->NextP;
                pagecounter = 0;
            }
        }
        
        //targetindex = spot;
        return targetindex;
        
    }
    //worst fit algorithm
    else
    {
        currentfit = 0;
        //while loop to go through entire linklist
        while(Current!= NULL)
        {
            //if statement to check if program to add is a new program
            if(Current->info == Program)
            {
                return -2;
            }
            //if statement to check for fragment and whether its a new fragment
            else if(Current->info == "Free" && Newfrag == true )
            {
                spot++;
                pagecounter = 1;
                Current = Current->NextP;
                Newfrag = false;
                tempspot = spot-1;
                //while loop to check how much free space is in this memory fragment
                while(Current -> info == "Free")
                {
                    fragsize++;
                    
                   
                    Current = Current->NextP;
                    if (Current == NULL)
                    {
                        break;
                    }
                   
                }
                
                if(fragsize > PageSize && fragsize > currentfit)
                {
                    currentfit = fragsize;
                    targetindex = tempspot;
                }
                
            }
            else
            {
                //reset pagecounter once current free frag is done
                spot++;
                Current = Current->NextP;
                pagecounter = 0;
            }
        }
        
        return targetindex;
    }
    
}


        
#endif /* Header_h */
