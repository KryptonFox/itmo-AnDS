#include <iostream>
#include <ostream>

struct Track {
  int number;
  int popularity;
  int stability;
};

/// Compare two Tracks and return a < b
bool Compare(Track* a, Track* b) {
  if (a->popularity != b->popularity) {
    return a->popularity < b->popularity;
  }
  if (a->stability != b->stability) {
    return a->stability < b->stability;
  }
  return a->number < b->number;
}

void Merge(Track* arr, int left, int mid, int right) {
  int it1 = 0;
  int it2 = 0;

  Track* result = new Track[right - left];

  while (left + it1 < mid && mid + it2 < right) {
    if (Compare(&arr[left + it1], &arr[mid + it2])) {
      result[it1 + it2] = arr[left + it1];
      it1++;
    } else {
      result[it1 + it2] = arr[mid + it2];
      it2++;
    }
  }

  while (left + it1 < mid) {
    result[it1 + it2] = arr[left + it1];
    it1++;
  }

  while (mid + it2 < right) {
    result[it1 + it2] = arr[mid + it2];
    it2++;
  }

  for (int i = 0; i < right - left; i++) {
    arr[left + i] = result[i];
  }

  delete[] result;
}

void MergeSort(Track* arr, int left, int right) {
  if (left + 1 >= right) return;
  int mid = (left + right) / 2;

  MergeSort(arr, left, mid);
  MergeSort(arr, mid, right);
  Merge(arr, left, mid, right);
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

  MergeSort(tracks, 0, n);

  for (int i = 0; i < n; i++) std::cout << tracks[i].number << " ";
  
  delete[] tracks;
}