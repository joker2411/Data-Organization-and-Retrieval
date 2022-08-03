#include <bits/stdc++.h>
using namespace std;

class Node
{
    
public:
    vector<int> values;
    Node* parent;
    Node* left;
    Node* right;
    
    Node()
    {
        left = right = parent = NULL;
    }
};

Node* root;
deque<Node*> Q;
Node* last_node = NULL;

void MIN_RECONSTRUCT(Node* node)
{
    if(node->parent == NULL)
        return ;
    
    if(node->values[0] < node->parent->values[0])
    {
        swap(node->values[0], node->parent->values[0]);
        MIN_RECONSTRUCT(node->parent);
    }
    return ;
}

void MAX_RECONSTRUCT(Node* node)
{
    if(node->parent == NULL)
        return ;
    
    if(node->values[1] > node->parent->values[1])
    {
        swap(node->values[1], node->parent->values[1]);
        MAX_RECONSTRUCT(node->parent);
    }
    return ;
}

void INSERT(int key)
{
    Node* top_node = Q.front();
    
    if(top_node->values.size() == 0)
    {
        top_node->values.push_back(key);
        
        if(top_node->parent != NULL && top_node->values[0] < top_node->parent->values[0]) 
            MIN_RECONSTRUCT(top_node);
        
        if(top_node->parent != NULL && top_node->values[0] > top_node->parent->values[1])
        {
            top_node->values.insert(top_node->values.begin(), INT_MIN);
            MAX_RECONSTRUCT(top_node);
            top_node->values.erase(top_node->values.begin());
        }
    }
    else
    {
        if(key < top_node->values[0])
        {
            int temp;
            temp = top_node->values[0];
            top_node->values[0] = key;
            top_node->values.push_back(temp);
            MIN_RECONSTRUCT(top_node);
        }
        else
        {
            top_node->values.push_back(key);
            MAX_RECONSTRUCT(top_node);
        }
        
        if(top_node->left == NULL)
        {
            top_node->left = new Node();
            top_node->left->parent = top_node;
        }
        
        if(top_node->right == NULL)
        {
            top_node->right = new Node();
            top_node->right->parent = top_node;
        }
        
        Q.push_back(top_node->left);
        Q.push_back(top_node->right);
        
        last_node = Q.front();
        Q.pop_front();
    }
    return ;
}

void PrintMinHeap()
{
    Node* node = root;
    queue<Node*> printQ;
    printQ.push(node);
    Node* temp;
    while(printQ.empty() != true)
    {
        temp = printQ.front();
        printQ.pop();
        if(temp->left) printQ.push(temp->left);
        if(temp->right) printQ.push(temp->right);
        
        if(temp->values.size() >= 1) cout<<temp->values[0]<<" ";
        
    }
    cout<<endl;
    return ;
}

void PrintMaxHeap()
{
    Node* node = root;
    queue<Node*> printQ;
    printQ.push(node);
    Node* temp;
    while(printQ.empty() != true)
    {
        temp = printQ.front();
        printQ.pop();
        if(temp->left) printQ.push(temp->left);
        if(temp->right) printQ.push(temp->right);
        
        if(temp->values.size() > 1) cout<<temp->values[1]<<" ";
        
    }
    cout<<endl;
    return ;
}

void PrintHeap()
{
    Node* node = root;
    queue<Node*> printQ;
    printQ.push(node);
    Node* temp;
    while(printQ.empty() != true)
    {
        temp = printQ.front();
        printQ.pop();
        
        if(temp->left) printQ.push(temp->left);
        if(temp->right) printQ.push(temp->right);
        
        if(temp->values.size() == 0);
        else if(temp->values.size() == 1) cout<<"( "<<temp->values[0]<<" ) ---> ";
        else cout<<"( "<<temp->values[0]<<" , "<<temp->values[1]<<" ) ---> ";
    }
    cout<<endl;
    return ;
}

void CHECK_SWAP(Node* node)
{
    if(node->values[0] > node->values[1])
        swap(node->values[0], node->values[1]);
    return ;
}

int POP_MINIMUM()
{
    Node* last_ptr;
    int last_minimum;
    int popped_minimum;
    
    if(root->values.size() < 1 )
    {
        cout<<"Error in fetching minimum value. Interval Heap may be empty"<<endl;
        return INT_MAX;
    }
    else if(root->values.size() == 1)
    {
        popped_minimum = root->values[0];
        root->values.erase(root->values.begin());
        return popped_minimum;
    }
    else if(Q.front()->parent == root && Q.back()->parent ==root && root->values.size() == 2)
    {
        popped_minimum = root->values[0];
        root->values.erase(root->values.begin());
        Q.push_front(root);
        Q.pop_back();
        Q.pop_back();
        return popped_minimum;
    }
        
    popped_minimum = root->values[0];
    
    if(Q.front()->values.size() == 0)
    {
        last_ptr = Q.back()->parent;
        last_minimum = last_ptr->values[0];
        last_ptr->values.erase(last_ptr->values.begin());
        Q.push_front(last_ptr);
        Q.pop_back();
        Q.pop_back();
    }
    else
    {
        last_ptr = Q.front();
        last_minimum = last_ptr->values[0];
        last_ptr->values.erase(last_ptr->values.begin());
    }
    
    root->values[0] = last_minimum;
    
    Node* node = root;
    bool check = true;
    while(check == true)
    {
        check = false;
        if((node->left->values.size() == 0) && (node->right->values.size() == 0))
        {
            check = false;
            break;
        }
        else if((node->left->values.size() != 0) && (node->right->values.size() == 0))
        {
            if(node->values[0] > node->left->values[0])
            {
                swap(node->values[0], node->left->values[0]);
                CHECK_SWAP(node->left);
                check = true;
                node = node->left;
            }
        }
        else if((node->left->values.size() == 0) && (node->right->values.size() != 0))
        {
            if(node->values[0] > node->right->values[0])
            {
                swap(node->values[0], node->right->values[0]);
                CHECK_SWAP(node->right);
                check = true;
                node = node->right;
            }
        }
        else
        {
            if((node->left->values[0] < node->right->values[0]) && (node->left->values[0] < node->values[0]))
            {
                swap(node->values[0], node->left->values[0]);
                CHECK_SWAP(node->left);
                check = true;
                node = node->left;
            }
            else if((node->left->values[0] >= node->right->values[0]) && (node->right->values[0] < node->values[0]))
            {
                swap(node->values[0], node->right->values[0]);
                CHECK_SWAP(node->right);
                check = true;
                node = node->right;
            }
        }
    }
    return popped_minimum;
}

int POP_MAXIMUM()
{
    Node* last_ptr;
    int last_maximum;
    int popped_maximum;
    
    if(root->values.size() < 1 )
    {
        cout<<"Error in fetching maximum value. Interval Heap may be empty"<<endl;
        return INT_MIN;
    }
    else if(root->values.size() == 1)
    {
        popped_maximum = root->values[0];
        root->values.erase(root->values.begin());
        return popped_maximum;
    }
    
    popped_maximum = root->values[1];
    
    if(Q.front()->values.size() == 0)
    {
        last_ptr = Q.back()->parent;
        last_maximum = last_ptr->values[1];
        last_ptr->values.erase(++last_ptr->values.begin());
        Q.push_front(last_ptr);
        Q.pop_back();
        Q.pop_back();
    }
    else
    {
        last_ptr = Q.front();
        last_maximum = last_ptr->values[0];
        last_ptr->values.erase(last_ptr->values.begin());
    }
    
    root->values[1] = last_maximum;
    
    Node* node = root;
    bool check = true;
    while(check == true)
    {
        check = false;
        if(((node->left->values.size() == 0) && (node->right->values.size() == 0))||((node->left->values.size() == 1) && (node->right->values.size() == 0)))
        {
            check = false;
            break;
        }
        else if((node->left->values.size() > 1) && (node->right->values.size() == 0))
        {
            if(node->values[1] < node->left->values[1])
            {
                swap(node->values[1], node->left->values[1]);
                CHECK_SWAP(node->left);
                check = true;
                node = node->left;
            }
        }
        else if((node->left->values.size() == 0) && (node->right->values.size() > 1))
        {
            if(node->values[1] < node->right->values[1])
            {
                swap(node->values[1], node->right->values[1]);
                CHECK_SWAP(node->right);
                check = true;
                node = node->right;
            }
        }
        else
        {
            if((node->left->values[1] > node->right->values[1]) && (node->left->values[1] > node->values[1]))
            {
                swap(node->values[1], node->left->values[1]);
                CHECK_SWAP(node->left);
                check = true;
                node = node->left;
            }
            else if((node->left->values[1] <= node->right->values[1]) && (node->right->values[1] > node->values[1]))
            {
                swap(node->values[1], node->right->values[1]);
                CHECK_SWAP(node->right);
                check = true;
                node = node->right;
            }
        }
    }
    return popped_maximum;
}

int main()
{
    root = NULL;
    root = new Node();
    
    Q.push_back(root);
    
    int minimum_value;
    int maximum_value;
    
    int num;
    cout<<"how many numbers"<<endl;
    cin>>num;

    cout<<"Enter "<<num<<" values one by one"<<endl;
    int element;
    for(int i=0; i<num; i++)
    {
        cin>>element;
        INSERT(element);
    }
    
    cout<<endl<<"Level order traversal is: "<<endl;
    PrintHeap();
    
    minimum_value = POP_MINIMUM();
    if(minimum_value == INT_MAX);
    else
    {
        cout<<endl<<"Removed minimum value from the Interval Heap is: "<<minimum_value<<endl;
        cout<<endl<<"Level order traversal after deletion is: "<<endl;
        if(root->values.size() == 0)
            cout<<"Interval Heap may be empty"<<endl<<endl;
        else
            PrintHeap();
    }
    
    maximum_value = POP_MAXIMUM();
    if(maximum_value == INT_MIN);
    else
    {
        cout<<endl<<"Removed maximum value from the Interval Heap is: "<<maximum_value<<endl;
        cout<<endl<<"Level order traversal after deletion is: "<<endl;
        if(root->values.size() == 0)
            cout<<"Interval Heap may be empty"<<endl<<endl;
        else
            PrintHeap();
    }
    
    cout<<endl<<"Enter any number for fresh insertion: "<<endl;
    int new_number_insert;
    cin>>new_number_insert;
    INSERT(new_number_insert);
    
    cout<<endl<<"Level order traversal after insertion is: "<<endl;
    PrintHeap();
    
    cout<<endl<<"PROGRAM EXECUTION SUCCESSFUL";
    return 0;
}
