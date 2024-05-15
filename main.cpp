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

int main() {
//    node<int>* root= new node(7);
//    root->left= new node(4);
//    root->left->left=new node(3);
//    root->left->left->left= new node(2);
//    root->left->right= new node(5);
//    root->right= new node(10);
//    root->right->left=new node(9);
//    root->right->right= new node(20);
    //Testing...
    AVL<int> avl;
    avl.insert(5);
    avl.insert(4);
    avl.insert(3);
    avl.insert(8);
    avl.insert(9);
    avl.insert(7);
    avl.remove(8);
    avl.displayAscending();
    avl.displayDescending();
    ifstream file("items.txt");
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
    AVL<Item,Item::NameComparison> itemsAvl;
    for(auto it:items){
        itemsAvl.insert(it);
    }
    itemsAvl.displayAscending();
    cout<<"____________________________\n";
    itemsAvl.displayDescending();
    cout<<"____________________________\n";
//    Item i1("chocolate milk","drink",10),i2("banana","fruit",75),i3("pepsi","drink",20),i4("cheddar cheese","dairy",49),i5("tuna","meat",90);


    cout<<"Testing is done...";
}
