#include <bits/stdc++.h>
#define MAXN 30000002

using namespace std;


int N, K;
int dataset[MAXN];

int med_of_med(int l, int r);
int prune_and_search(int l, int r, int k);


int med_of_med(int l, int r) {
    int num_block = (r - l + 4) / 5;
    for (int i = 0 ; i < num_block ; i++) {
        int block_l = l + i * 5, block_r = l + i * 5 + 5;
        block_r = (block_r > r) ? r : block_r;
        int id = prune_and_search(block_l, block_r, (block_r - block_l) / 2);
        swap(dataset[l + i], dataset[id]);
    }
    return prune_and_search(l, l + num_block, num_block / 2);

}

int prune_and_search(int l, int r, int k) {

    if (r - l <= 5) {
        for(int i = r - 1; i > l; i--)
            for(int j = l; j <= i-1; j++)
                if( dataset[j] > dataset[j+1]) swap(dataset[j], dataset[j+1]);
        return l + k - 1;
    }

    int id = med_of_med(l, r);
    swap(dataset[l], dataset[id]);
    int i = l;
    int pivot = dataset[l];
    for (int j = l + 1 ; j < r ; j++)
        if (dataset[j] <= pivot)
            swap(dataset[j], dataset[++i]);
    swap(dataset[i], dataset[l]);
    if(i - l + 1 == k) return i;
    else if (i - l + 1 < k) return  prune_and_search(i + 1, r , k - (i - l + 1));
    else return prune_and_search(l, i, k);
}


int main(void) {
    cin >> N >> K;
    for (int i = 0 ; i < N ; i++)
        cin >> dataset[i];
    int index = prune_and_search(0, N, K);
    cout << dataset[index] << endl;
    return 0;
}