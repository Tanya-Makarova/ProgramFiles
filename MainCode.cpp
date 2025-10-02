#include <iostream>
#include <stdexcept> // ��� ������ � ������������
#include <vector>
using namespace std;

class BinHeap {
private:
    vector<int> heapvector; // ������ ��� �������� ��������� ����, heapvector - ������������ ������ ��� �������� ���������
    int CurrentSize; // ������� ���������� ��������� � ����, CurrentSize - ������� ��������� (�������� ��������� �������)

public:
    BinHeap() {
        this->heapvector.push_back(0); // ��������� ������� ��� ���������� � 1
        this->CurrentSize = 0;
    }
    // ��������� ��������� ������� 0 � ������� 0
    // ��� ��������� ������������ ���������� � 1 ��� �������� ����������
    // �������������� ������ ���� ��� 0

    void percUp(int i) {
        while (i > 1) { // ���� �� ����� �� �����
            int parentIdx = i / 2; // ��������� ������ ��������
            if (this->heapvector[i] < this->heapvector[parentIdx]) {
                // ���� ������� ������� ������ �������� - ������ �������
                swap(this->heapvector[i], this->heapvector[parentIdx]);
                i = parentIdx; // ��������� � ������������ �������
            }
            else {
                break; // �������� ���� ������������� - ������� �� �����
            }
        }
    }

    void insert(int k) {
        this->heapvector.push_back(k); // ��������� ������� � ����� ������� � ����������� �������
        this->CurrentSize++;
        this->percUp(this->CurrentSize); // ��������������� �������� ����
    }
    // ��������� ������� ������ � ������� ��������
    // ���������� ������ ������� � ������� ���������

    int minChild(int i) {
        int left = i * 2; // ������ ������ �������
        int right = i * 2 + 1; // ������ ������� �������

        // ���� ������� ������� ���, ���������� ������
        if (right > this->CurrentSize) {
            return left;
        }
        // ����� ���������� �������� �� ����
        else {
            return (this->heapvector[left] < this->heapvector[right]) ? left : right;
        }
    }
    // ��������������� �������� ���� ������ ����
    void percDown(int i) {
        while (i * 2 <= this->CurrentSize) {  // ���� ���� ���� �� ����� �������
            int mc = this->minChild(i);

            // ���� ������� ���� ������ ����������� ������� - ������
            if (this->heapvector[i] > this->heapvector[mc]) {
                swap(this->heapvector[i], this->heapvector[mc]);
                i = mc;  // ��������� � ������� �������
            }
            else {
                break;  // �������� ���� ������������� - �������
            }
        }
    }

    int delMin() {
        if (this->CurrentSize == 0) { // �������� �� �������
            throw runtime_error("Heap is empty");
        }

        int minVal = this->heapvector[1]; // ��������� ����������� ������� (������)
        this->heapvector[1] = this->heapvector[this->CurrentSize]; // ���������� ��������� ������� � ������
        this->heapvector.pop_back(); // ������� ��������� �������
        this->CurrentSize--; // ��������� �������

        if (this->CurrentSize > 0) {
            this->percDown(1);
        }

        return minVal; // ���������� ����������� ����������� �������
    }

    // ���������� ���� �� �������:
    void buildheap(vector<int> avector) {
        // ������� ����
        this->heapvector = { 0 }; // ������� ����� ������ � ��������� ���������
        this->CurrentSize = 0; // ���������� �������

        // ��������� ��� �������� ����� insert
        for (int val : avector) {
            this->insert(val); // ������ ������� ����������� � ��������������� ������� ����
        }
    }

    bool isEmpty() {
        return this->CurrentSize == 0;
    }

    void printHeap() { // ������� ��� �������� ���� (������� � ������� 1)
        cout << "Heap elements: ";
        for (int i = 1; i <= this->CurrentSize; i++) {
            cout << this->heapvector[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int arr[] = { 3, 1, 23, 5, 6, 7, 43, 8, 864 };
    vector<int> a(arr, arr + (sizeof(arr) / sizeof(arr[0])));

    BinHeap* bh = new BinHeap(); // �������� ������� ����
    bh->buildheap(a); // ���������� ���� �� �������

    cout << "Initial heap: ";
    bh->printHeap(); // ����� ��������� ����


    cout << "\nExtracting elements:\n";
    while (!bh->isEmpty()) { // ���� ���� �� �����
        cout << "Extracted: " << bh->delMin() << endl; // ��������� ����������� �������
        if (!bh->isEmpty()) {
            cout << "Remaining heap: ";
            bh->printHeap(); // ����� ���������� ����
        }
    }

    delete bh;
    return 0;
}