#pragma once
int BiSearch(int data[], int n, int x) {
	int low = 0, mid = n / 2, high = n;
	while (low != high) {
		if (data[mid] > x) {
			high = mid;
			mid = low + (high - low) / 2;
		}
		else if (data[mid] < x) {
			low = mid;
			mid = low + (high - low) / 2;
		}
		else if (data[mid] == x) return mid;
	}
	return -1;//²éÕÒÊ§°Ü
}