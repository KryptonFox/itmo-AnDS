#include <iostream>

struct Track {
  int number;
  int popularity;
  int stability;
};

/// Compare two Tracks and return a < b
bool Compare(Track* a, Track* b) {
  if (a->popularity == b->popularity) {
    if (a->stability == b->stability) {
      return a->number < b->number;
    }
    return a->stability < b->stability;
  }
  return a->popularity < b->popularity;
}

// TODO replace to QuickSort after learning it
void InsertSort(Track* arr, int n) {
  int j;
  Track key;
  for (int i = 1; i < n; i++) {
    j = i - 1;
    key = arr[i];
    while (j >= 0 && Compare(&key, &arr[j])) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

int main() {
  int n;
  std::cin >> n;

  Track* tracks = new Track[n];
  for (int i = 0; i < n; i++) {
    tracks[i].number = i + 1;
    std::cin >> tracks[i].popularity;
    std::cin >> tracks[i].stability;
  }

  InsertSort(tracks, n);

  for (int i = 0; i < n; i++) std::cout << tracks[i].number << " ";
}