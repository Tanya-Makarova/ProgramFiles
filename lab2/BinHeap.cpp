#include <iostream>
#include <stdexcept> // äëÿ ðàáîòû ñ èñêëþ÷åíèÿìè
#include <vector>
using namespace std;

class BinHeap {
private:
    vector<int> heapvector; // Âåêòîð äëÿ õðàíåíèÿ ýëåìåíòîâ êó÷è, heapvector - äèíàìè÷åñêèé ìàññèâ äëÿ õðàíåíèÿ ýëåìåíòîâ
    int CurrentSize; // Òåêóùåå êîëè÷åñòâî ýëåìåíòîâ â êó÷å, CurrentSize - ñ÷åò÷èê ýëåìåíòîâ (èñêëþ÷àÿ ôèêòèâíûé ýëåìåíò)

public:
    BinHeap() {
        this->heapvector.push_back(0); // Ôèêòèâíûé ýëåìåíò äëÿ èíäåêñàöèè ñ 1
        this->CurrentSize = 0;
    }
    // Äîáàâëÿåì ôèêòèâíûé ýëåìåíò 0 â ïîçèöèþ 0
    // Ýòî ïîçâîëÿåò èñïîëüçîâàòü èíäåêñàöèþ ñ 1 äëÿ óäîáñòâà âû÷èñëåíèé
    // Èíèöèàëèçèðóåì ðàçìåð êó÷è êàê 0

    void percUp(int i) {
        while (i > 1) { // Ïîêà íå äîøëè äî êîðíÿ
            int parentIdx = i / 2; // Âû÷èñëÿåì èíäåêñ ðîäèòåëÿ
            if (this->heapvector[i] < this->heapvector[parentIdx]) {
                // Åñëè òåêóùèé ýëåìåíò ìåíüøå ðîäèòåëÿ - ìåíÿåì ìåñòàìè
                swap(this->heapvector[i], this->heapvector[parentIdx]);
                i = parentIdx; // Ïåðåõîäèì ê ðîäèòåëüñêîé ïîçèöèè
            }
            else {
                break; // Ñâîéñòâî êó÷è âîññòàíîâëåíî - âûõîäèì èç öèêëà
            }
        }
    }

    void insert(int k) {
        this->heapvector.push_back(k); // Äîáàâëÿåì ýëåìåíò â êîíåö âåêòîðà è óâåëè÷èâàåì ñ÷åò÷èê
        this->CurrentSize++;
        this->percUp(this->CurrentSize); // Âîññòàíàâëèâàåì ñâîéñòâà êó÷è
    }
    // Âû÷èñëÿåò èíäåêñû ëåâîãî è ïðàâîãî ïîòîìêîâ
    // Âîçâðàùàåò èíäåêñ ïîòîìêà ñ ìåíüøèì çíà÷åíèåì

    int minChild(int i) {
        int left = i * 2; // Èíäåêñ ëåâîãî ïîòîìêà
        int right = i * 2 + 1; // Èíäåêñ ïðàâîãî ïîòîìêà

        // Åñëè ïðàâîãî ïîòîìêà íåò, âîçâðàùàåì ëåâîãî
        if (right > this->CurrentSize) {
            return left;
        }
        // Èíà÷å âîçâðàùàåì ìåíüøåãî èç äâóõ
        else {
            return (this->heapvector[left] < this->heapvector[right]) ? left : right;
        }
    }
    // Âîññòàíàâëèâàåò ñâîéñòâî êó÷è ñâåðõó âíèç
    void percDown(int i) {
        while (i * 2 <= this->CurrentSize) {  // Ïîêà åñòü õîòÿ áû ëåâûé ïîòîìîê
            int mc = this->minChild(i);

            // Åñëè òåêóùèé óçåë áîëüøå íàèìåíüøåãî ïîòîìêà - ìåíÿåì
            if (this->heapvector[i] > this->heapvector[mc]) {
                swap(this->heapvector[i], this->heapvector[mc]);
                i = mc;  // Ïåðåõîäèì ê ïîçèöèè ïîòîìêà
            }
            else {
                break;  // Ñâîéñòâî êó÷è âîññòàíîâëåíî - âûõîäèì
            }
        }
    }

    int delMin() {
        if (this->CurrentSize == 0) { // Ïðîâåðêà íà ïóñòîòó
            throw runtime_error("Heap is empty");
        }

        int minVal = this->heapvector[1]; // Ñîõðàíÿåì ìèíèìàëüíûé ýëåìåíò (êîðåíü)
        this->heapvector[1] = this->heapvector[this->CurrentSize]; // Ïåðåìåùàåì ïîñëåäíèé ýëåìåíò â êîðåíü
        this->heapvector.pop_back(); // Óäàëÿåì ïîñëåäíèé ýëåìåíò
        this->CurrentSize--; // Óìåíüøàåì ñ÷åò÷èê

        if (this->CurrentSize > 0) {
            this->percDown(1);
        }

        return minVal; // Âîçâðàùàåì èçâëå÷åííûé ìèíèìàëüíûé ýëåìåíò
    }

    // Ïîñòðîåíèå êó÷è èç ìàññèâà:
    void buildheap(vector<int> avector) {
        // Î÷èùàåì êó÷ó
        this->heapvector = { 0 }; // Ñîçäàåì íîâûé âåêòîð ñ ôèêòèâíûì ýëåìåíòîì
        this->CurrentSize = 0; // Ñáðàñûâàåì ñ÷åò÷èê

        // Äîáàâëÿåì âñå ýëåìåíòû ÷åðåç insert
        for (int val : avector) {
            this->insert(val); // Êàæäûé ýëåìåíò äîáàâëÿåòñÿ ñ âîññòàíîâëåíèåì ñâîéñòâ êó÷è
        }
    }

    bool isEmpty() {
        return this->CurrentSize == 0;
    }

    void printHeap() { // Âûâîäèò âñå ýëåìåíòû êó÷è (íà÷èíàÿ ñ èíäåêñà 1)
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

    BinHeap* bh = new BinHeap(); // Ñîçäàíèå îáúåêòà êó÷è
    bh->buildheap(a); // Ïîñòðîåíèå êó÷è èç âåêòîðà

    cout << "Initial heap: ";
    bh->printHeap(); // Âûâîä íà÷àëüíîé êó÷è


    cout << "\nExtracting elements:\n";
    while (!bh->isEmpty()) { // Ïîêà êó÷à íå ïóñòà
        cout << "Extracted: " << bh->delMin() << endl; // Èçâëåêàåì ìèíèìàëüíûé ýëåìåíò
        if (!bh->isEmpty()) {
            cout << "Remaining heap: ";
            bh->printHeap(); // Âûâîä îñòàâøåéñÿ êó÷è
        }
    }

    delete bh;
    return 0;
}
