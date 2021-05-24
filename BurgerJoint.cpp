#ifndef BurgerJoint_CPP
#define BurgerJoint_CPP
#include "BurgerJoint.h"

/*
    Helper function to tell whether the 
    given string is a number or not 
*/
bool isNumber(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if( !(isdigit((unsigned char)str[i])) )
        {
            return false;
        }
        
    }

    return true;
}


/*
    Constructor:
    1. Load topping priority from topping_priority.txt into
       topping_priority attribute
    2. Load every customers' unsorted toppings form 
       assembly line - load data from assembly.txt 
       into customers queue
    
    For you convenience this has been done!
*/
BurgerJoint::BurgerJoint()
{
   
    ifstream fin("topping_priority.txt");

    string line;

    int count = 0;

    while (getline (fin, line)) 
    {

        topping_priority[count] = line;
        count++;

    }

    //saving number of toppings
    number_of_toppings = count;

    fin.close();
    
    //loading customers' unsorted toppings from assembly line
    fin.open("assembly.txt");


    bool first_line = true;

    int total_customers;
    int cust_id;

    LinkedList<string> lines;

    //reading all lines
    while(getline (fin, line))
    {
        lines.insertAtTail(line);
    }

    fin.close();

    shared_ptr<ListItem<string>> ptr = lines.getHead();

    ptr = lines.getHead();

    //adding customers with correct id and toppings into
    //customers queue
    while(ptr != NULL)
    {
        line = ptr->value;
        if(first_line)
        {
            //noting down total customers
            total_customers = stoi(line);
            first_line = false;
            ptr = ptr -> next;
        }

        else
        {
            //noting down customer id
            cust_id = stoi(line);

            ptr = ptr->next;

            shared_ptr<customer> new_cust(new customer);
            new_cust->id = cust_id;

            //noting down customer unsorted toppings
            while(ptr != NULL)
            {  
                line = ptr->value;
                if(isNumber(ptr->value))
                {
                    break;
                }
                new_cust->order.push(line);
                ptr = ptr->next;
            }

            //enqueuing customer
            customers.enqueue(new_cust);
        }
        
    }

}


/*
    Function to fetch priority of a topping.
    Matches prioirity from topping_priority list.
*/
int BurgerJoint::getPriority(string item)
{
    for (int i=0; i<10; i++)
    {
        if (topping_priority[i]==item)
            return i;
    }
}

//destructor
BurgerJoint::~BurgerJoint()
{}

/*
    You have two stacks:
    1. unsorted_toppings
    2. temp_stack

    You have one variable:
    1. temp

    DONOT CREATE ANYMORE VARIABLES OR DATASTRUCTURES IN THIS FUNCTION

    Use the above mentioned variable and datastructures to sort the
    unsorted_toppings stack.
    You need to sort it according to "topping_priority"
*/
void BurgerJoint::assemble(Stack<string> &unsorted_toppings)
{
    //cout<<"abcd"<<endl;
    Stack<string>temp_stack;
    string temp;
     while (unsorted_toppings.isEmpty()) 
    { 
        // pop out the first element 
          temp = unsorted_toppings.pop(); 
  
        // while temporary stack is not empty and top 
        // of stack is greater than temp 
        while (temp_stack.isEmpty() && getPriority(temp_stack.top()) < getPriority(temp)) 
        { 
            // pop from temp and push 
            // it to the unsorted_toppings stack 
           unsorted_toppings.push(temp_stack.pop()); 
        } 
  
        // push temp in tempory stack 
        temp_stack.push(temp); 
    }

   /* cout<<"abc"<<endl;

    while(temp_stack.isEmpty())
        {
            cout<<temp_stack.pop()<<endl;
        }
        return ;*/


    //cout<<"efgh"<<endl;
    
    // transfering stack
    for (int j = temp_stack.length(); j > 0; j--)
    {
        temp = temp_stack.pop();
        //runs n-1 times the length of table and pushes those
        // elements in table2
        for (int i=j; i-1>0;i--)
        {
            unsorted_toppings.push(temp_stack.pop());//
        }
        temp_stack.push(temp);
        while (unsorted_toppings.length() > 0)
        {
            temp_stack.push(unsorted_toppings.pop());//pushing back to table 1
        }
        

    }
    //table 1 is reversed and now putting everything back to table 2
        while(temp_stack.length()>0)
        {
            unsorted_toppings.push(temp_stack.pop());
        }
        //cout<<unsorted_toppings.length()<<endl;
        /*while(unsorted_toppings.isEmpty())
        {
            cout<<unsorted_toppings.pop()<<endl;
        }*/
        

}

/*
    Generate an output file similar to assembly.txt.
    The toppings need to be in a sorted order in this file.
    Moreover, every customer needs to hace the correct toppings.

    NAME THE OUTPUT TEXT FILE takeaway.txt
*/
void BurgerJoint::generateOutput()
{
    fstream output_file("takeaway.txt",ios::out);
    shared_ptr<customer> temp;
    int total=customers.length();
    output_file<<total<<"\n";

    while(customers.isEmpty())
    {
        temp =customers.dequeue();
        output_file<<temp->id<<"\n";
        while(temp->order.isEmpty())
        {
            output_file<<temp->order.pop()<<"\n";
        }
        
    }
    output_file.close();
}

void BurgerJoint::takeawayCounter()
{
    shared_ptr<customer> temp;
    int flag=0;
    int length=customers.length();

    while(flag<length)
    {
        temp =customers.dequeue();
        assemble(temp->order);
       customers.enqueue(temp);
       flag++;

    }
    generateOutput();
}




#endif