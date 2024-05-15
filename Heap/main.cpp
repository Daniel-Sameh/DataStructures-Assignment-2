#include <bits/stdc++.h>
using namespace std;

const int N = 10000;

class ItemName {
private:
    string name;
    string category;
    int price;
public:
    ItemName(string name, string category, int price) : name(name), category(category), price(price) {}
    ItemName() : price(0) {}

    void setName(string name) { this->name = name; }
    void setCategory(string category) { this->category = category; }
    void setPrice(int price) { this->price = price; }

    friend ostream &operator<<(ostream &os, const ItemName &i) {
        os << i.name << '\n' << i.category << '\n' << i.price << '\n';
        return os;
    }
    bool operator<(const ItemName &b) const {
        return this->name < b.name;
    }
};

class ItemPrice {
private:
    string name;
    string category;
    int price;
public:
    ItemPrice(string name, string category, int price) : name(name), category(category), price(price) {}
    ItemPrice() : price(0) {}

    void setName(string name) { this->name = name; }
    void setCategory(string category) { this->category = category; }
    void setPrice(int price) { this->price = price; }

    friend ostream &operator<<(ostream &os, const ItemPrice &i) {
        os << i.name << ' ' << i.category << ' ' << i.price << ' ';
        return os;
    }
    bool operator<(const ItemPrice &b) const {
        return this->price < b.price;
    }
};

template<typename T>
class HeapTree {
private:
    T arr[N];
    int length = 0;

public:
    void max_heapify(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < length && arr[index] < arr[left]) {
            largest = left;
        }
        if (right < length && arr[largest] < arr[right]) {
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
        if (arr[parent] < arr[index]) {
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

int main() {
    HeapTree<ItemPrice> h;
    ItemPrice e("Guitar", "music", 3000);
    ItemPrice m("Violin", "music", 2000);
    ItemPrice g("sfsdfs", "music", 5000);
    ItemPrice j("Viol]ds", "music", 400);
    ItemPrice k("Vioadadad", "music", 250);
    ItemPrice l("Vsdsdli", "music", 4000);
    h.insertion(e);
    h.insertion(m);
    h.insertion(g);
    h.insertion(j);
    h.insertion(k);
    h.insertion(l);
    h.heapSort();
    h.print();

}

