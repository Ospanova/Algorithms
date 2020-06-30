int partition(int left, int right, vector <int>& nums) {
    int picked = left + (rand()%(right - left + 1));
    int l = left + 1;
    swap(nums[left], nums[picked]);
    cout << left << " " << right << " " << picked << " "<< nums[picked] << endl;
    for (int i = left + 1; i <= right; ++i) {
        if (nums[i] < nums[left])
            swap(nums[i], nums[l++]);  
    }
    swap(nums[l - 1], nums[left]);
    return l - 1;
}
int quickSort(int left, int right, vector <int>& nums, int k) {
    if (left == right) return nums[left];
    int p = partition(left, right, nums);
    if (p == k) 
        return nums[p];
    if (k < p)
        return quickSort(left, p - 1, nums, k);
    return quickSort(p + 1, right, nums, k);
}
int findKthLargest(vector<int>& nums, int k) {
    k = nums.size() - k;
    return quickSort(0, nums.size() - 1, nums, k);
}