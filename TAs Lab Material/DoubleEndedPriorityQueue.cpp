//Demo to implement double-ended priority queue using self balancing BST.

#include <bits/stdc++.h>
using namespace std;
 
struct DblEndedPQ {
    set<int> s;
 
    int size()
    {
       return s.size(); // Returns size of the queue. 
    }
 
 
    bool isEmpty()
    {
       return (s.size() == 0);
    }
 
    void insert(int x)
    {
        s.insert(x);
    }
 
    int getMin()
    {
        return *(s.begin()); // Returns minimum element.
    }
 
    int getMax()
    {
        return *(s.rbegin()); // Returns maximum element.
    }
   
    void deleteMin()
    {
        if (s.size() == 0)
            return;
        s.erase(s.begin());
    }
 
    
    void deleteMax() // Deletes maximum element. 
    {
         if (s.size() == 0)
            return;
        auto it = s.end();
        it--;
        s.erase(it);
    }
    void display()
    {
        set <int> :: iterator it;
        for (it = s.begin(); it != s.end(); ++it)
        cout << '\t' << *it;
        cout << '\n';
    }
};
 
// Driver code
int main()
{
    DblEndedPQ d;
    d.insert(10);
    d.insert(50);
    d.insert(40);
    d.insert(20);
    d.insert(25);
    d.insert(45);
    cout<<"Original Queue is: "<<endl;
    d.display();
    cout <<"Fist Minimum Element: " <<d.getMin() << endl;
    cout << "Fist Maximum Element: " <<d.getMax() << endl;
    cout<< "Deleting First max element... \n";
    d.deleteMax();
    cout << "Maximum Element after deleting first max element: "<< d.getMax() << endl;
    cout<< "Deleting First min element... \n";
    d.deleteMin();
    cout << "Minimum Element after deleting first min element: "<<d.getMin() << endl;
    return 0;
}