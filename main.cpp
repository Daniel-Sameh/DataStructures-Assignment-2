#include <bits/stdc++.h>
using namespace std;
class Item{
private:
    string name;
    string category;
    int price;
public:
    Item(string name, string category, int price){
        this->name=name;
        this->category=category;
        this->price= price;
    }
    Item(){price=0;}
    void setName(string name){this->name=name;}
    void setCategory(string category){this->category=category;}
    void setPrice(int price){this->price=price;}
    struct NameComparison{
        bool operator()(const Item& a, const Item& b){
            return a.name<b.name;
        }
    };
    struct PriceComparison{
        bool operator()(const Item&a, const Item&b){
            return a.price<b.price;
        }
    };

    friend ostream& operator<<(ostream& os, const Item& i){
        os<<i.name<<'\n'<<i.category<<'\n'<<i.price<<'\n';
        return os;
    }


};
vector<Item> readItems(string fileName){
    ifstream file(fileName);
    string line;
    getline(file, line);
    int n= stoi(line);
    vector<Item>items;
    while(getline(file,line)){
        string name=line;
        getline(file,line);
        string category=line;
        getline(file,line);
        int price= stoi(line);
        Item i(name,category,price);
        items.push_back(i);
    }
    return items;
}
/////////////////////////////////////////////

/// A V L TREE
template<typename T, typename Compare = std::less<T>>
class node{
public:
    T data;
    node* left;
    node* right;
    int height;
    node(T data){
        left= nullptr;
        right= nullptr;
        this->data=data;
        height=1;
    }
    node(){
        left= nullptr;
        right= nullptr;
        this->data=T();
        height=1;
    }
};
template<typename T, typename Compare = std::less<T>>
class AVL{
private:
    node<T>* head;
    Compare comparator;
    int height(node<T>* n){
        if (n== nullptr)
            return 0;
        int left = height(n->left);
        int right = height(n->right);
        return 1+max(left,right);
    }
    int getBalanceFactor(node<T>* n){
        if (n== nullptr)
            return 0;
        int left= height(n->left);
        int right= height(n->right);
        return left-right;
    }
    node<T>* rightRotate(node<T>* n){
        node<T>* rightOfLeft= n->left->right;
        node<T>* left= n->left;
        n->left->right= nullptr;
        n->left=rightOfLeft;
        left->right=n;
        return left;
    }
    node<T>* leftRotate(node<T>* n){
        node<T>* leftOfRight= n->right->left;
        node<T>* right= n->right;
        n->right->left= nullptr;
        n->right=leftOfRight;
        right->left=n;
        return right;
    }
    node<T>* insertNode(node<T>* n, T data){
        //Inserting the node in the right place:
        if (n== nullptr)
            return new node<T>(data);
        if (comparator(data, n->data))
            n->left= insertNode(n->left, data);
        else if (comparator(n->data, data))
            n->right= insertNode(n->right, data);
        else
            return n;

        //updating the balance factor:
        n->height= 1+ max(height(n->left), height(n->right));
        int balanceFactor = getBalanceFactor(n);
        if (balanceFactor>1){
            if (comparator(data, n->left->data)){
                return rightRotate(n);
            }else if (comparator(n->left->data, data)){
                n->left= leftRotate(n->left);
                return rightRotate(n);
            }
        }else if (balanceFactor < -1){
            if (comparator(n->right->data, data)){
                return leftRotate(n);
            }else if (comparator(data, n->right->data)){
                n->right= rightRotate(n->right);
                return leftRotate(n);
            }
        }
        return n;
    }
    node<T>* removeNode(node<T>* n,T data){
        if (n== nullptr)
            return n;
        if (comparator(data,n->data)){
            n->left= removeNode(n->left,data);
        }else if (comparator(n->data,data)){
            n->right= removeNode(n->right,data);
        }else{
            if (n->left== nullptr||n->right== nullptr){
                node<T>* tmp= n->left?n->left: n->right;
                if(tmp== nullptr) {
                    tmp = n;
                    n = nullptr; //a problem is here!
                }else{
                    n=tmp;
                }
                delete tmp;
            }else{
                node<T>* tmp= n->right;
                while(tmp->left!= nullptr){
                    tmp=tmp->left;
                }
                n->data=tmp->data;
                n->right= removeNode(n->right,tmp->data);
            }
        }

        //Updating the Balance Factor:
        if (n!= nullptr)
            n->height=1+max(height(n->left), height(n->right));
        int bf= getBalanceFactor(n);
        if (bf>1){
            if (getBalanceFactor(n->left)>=0){
                return rightRotate(n);
            }else{
                n->left= leftRotate(n->left);
                return rightRotate(n);
            }
        }else if (bf<-1){
            if (getBalanceFactor(n->right)<=0){
                return leftRotate(n);
            }else{
                n->right= rightRotate(n->right);
                return leftRotate(n);
            }
        }
        return n;
    }
    void inorder(node<T>* n){
        if (n!= nullptr){
            inorder(n->left);
            cout<<n->data<<' ';
            inorder(n->right);
        }
    };
    void reverseOrder(node<T>* n){
        if (n!= nullptr){
            reverseOrder(n->right);
            cout<<n->data<<' ';
            reverseOrder(n->left);
        }
    }
public:
    AVL():head(nullptr) {}
    AVL(node<T>* n):head(n) {}
    void insert(T data){
        head= insertNode(head, data);
    }
    void displayAscending(){
        inorder(head);
        cout<<"\n";
    }
    void displayDescending(){
        reverseOrder(head);
        cout<<'\n';
    }
    void remove(T data){
        head= removeNode(head,data);
    }


};

template<typename T,typename Compare = std::less<T>>
AVL<T,Compare> createAvl() {
    AVL<T,Compare> avl;
    return avl;
}
template<typename T,typename Compare = std::less<T>>
void avlOperations(AVL<T,Compare>& a){
    int op = 10;
    cout << "Choose one of the operation (0 to exit):\n";
    while (op) {
        cout << "     1)Insert all items from the file items.txt.\n";
        cout << "     2)Insert Item.\n";
        cout << "     3)Remove Item.\n";
        cout << "     4)Display Items Ascending\n";
        cout << "     5)Display Items Descending\n";
        cin >> op;
        if (op==1){
            auto items = readItems("items.txt");
            for(auto it:items){
                a.insert(it);
            }
        }else if (op==2){
            string name,category;
            int price;
            cout<<"Enter item name: "; cin>>name;
            cout<<"Enter item category: "; cin>>category;
            cout<<"Enter item price: "; cin>>price;
            Item i(name,category,price);
            a.insert(i);
        }else if (op==3){
            string name,category;
            int price;
            cout<<"Enter item name: "; cin>>name;
            cout<<"Enter item category: "; cin>>category;
            cout<<"Enter item price: "; cin>>price;
            Item i(name,category,price);
            a.remove(i);
        }else if (op==4){
            a.displayAscending();
        }else if (op==5){
            a.displayDescending();
        }
    }
}
/////////////////////////////////////////////////////

/// H E A P
const int N = 10000;
template<typename T,typename Compare = std::less<T>>
class HeapTree {
private:
    T arr[N];
    int length = 0;
    Compare comparator;
public:
    void max_heapify(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < length && comparator(arr[index], arr[left])) {
            largest = left;
        }
        if (right < length && comparator(arr[largest], arr[right])) {
            largest = right;
        }
        if (largest != index) {
            swap(arr[index], arr[largest]);
            max_heapify(largest);
        }
    }

    void heapify_low(int index) {
        if (index == 0) {
            return;
        }
        int parent = (index - 1) / 2;
        if (comparator(arr[parent], arr[index])) {
            swap(arr[index], arr[parent]);
            heapify_low(parent);
        }
    }

    void insertion(T element) {
        arr[length] = element;
        length++;
        heapify_low(length - 1);
    }

    void extract_max() {
        arr[0] = arr[length - 1];
        length--;
        max_heapify(0);
    }
    void print(){
        for (int i = 0; i < length; ++i) {
            cout<<arr[i]<<" ";
        }
    }
    void heapSort()
    {
        length-=1;
        int l=length;
        for (int i = l; i > 0; i--) {
            swap(arr[0], arr[i]);
            max_heapify(0);
            length-=1;
        }
        length=l+1;
    }
};
template<typename T,typename Compare = std::less<T>>
HeapTree<T,Compare> createHeap() {
    HeapTree<T,Compare> heap;
    return heap;
}
template<typename T,typename Compare = std::less<T>>
void heapOperations(HeapTree<T,Compare>& h){
    int op = 10;
    cout << "Choose one of the operation (0 to exit):\n";
    while (op) {
        cout << "     1)Insert all items from the file items.txt.\n";
        cout << "     2)Insert Item.\n";
        cout << "     3)Remove Item.\n";
        cout << "     4)Display Items Max heap sort\n";
        cout<<  "     5) print the tree "<<endl;
        cin >> op;
        if (op==1){
            auto items = readItems("items.txt");
            for (auto it: items)
                h.insertion(it);
            cout<<"After insertion: ";
            h.print();
            cout<<'\n';
        }else if (op==2){
            string name,category;
            int price;
            cout<<"Enter item name: "; cin>>name;
            cout<<"Enter item category: "; cin>>category;
            cout<<"Enter item price: "; cin>>price;
            Item i(name,category,price);
            h.insertion(i);
        }
        else if(op==3){
            h.extract_max();
        }
        else if(op==4){
            h.heapSort();
            h.print();
        }
        else if(op==5){
            h.print();
        }
    }
}
int main() {
    cout<<"Welcome to Our Items Management Program!\n";
    int type=-1;
    while (type){
        if(type==-1) {
            cout<<"Type the number of the Data Structure you want to use(to exit 0):\n";
            cout<<" 1)BST(Binary Search Tree)\n";
            cout<<" 2)AVL\n";
            cout<<" 3)Heap\n";
            cin>>type;
        }else if (type==2) {
            cout << "You chose AVL Tree, please specify how you want to store the items according to:\n";
            cout << " 1)Item Name.\n";
            cout << " 2)Item Price.\n";
            int comp = -1;
            cin >> comp;
            while (comp != 1 && comp != 2) {
                cout << "Enter a valid comparison type: ";
                cin >> comp;
            }
            //AVL<Item> itemsAvl;
            if (comp==1) {
                auto itemsAvl = createAvl<Item, Item::NameComparison>();
                avlOperations(itemsAvl);
            }else {
                auto itemsAvl = createAvl<Item, Item::PriceComparison>();
                avlOperations(itemsAvl);
            }
            type=-1;
            continue;

        }else if(type==1){
            cout<<"You Chose BST:\n";
            //Complete this
        }else if (type==3){
            cout<<"You Chose Heap, please specify how you want to store the items according to:\n";
            cout << " 1)Item Name.\n";
            cout << " 2)Item Price.\n";
            int comp = -1;
            cin >> comp;
            while (comp != 1 && comp != 2) {
                cout << "Enter a valid comparison type: ";
                cin >> comp;
            }
            if (comp==1) {
                auto itemsHeap = createHeap<Item, Item::NameComparison>();
                heapOperations(itemsHeap);
            }else {
                auto itemsHeap = createHeap<Item, Item::PriceComparison>();
                heapOperations(itemsHeap);
            }

        }else{
            cout << "Invalid Type! Try Again: ";
        }

    }

}
