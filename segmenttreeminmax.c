#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct TreeNode {
    int sum;
    int minimum;
    int maximum;
    struct {
        int first;
        int second;
    } interval;
    struct TreeNode *left;
    struct TreeNode *right;
};

void build(int arr[], struct TreeNode *cur_node, int L, int R) {
    cur_node->interval.first = L;
    cur_node->interval.second = R;

    if (L == R) {
        cur_node->left = cur_node->right = NULL;
        cur_node->sum = cur_node->minimum = cur_node->maximum = arr[L];
        return;
    }

    cur_node->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    cur_node->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    build(arr, cur_node->left, L, (L + R) / 2);
    build(arr, cur_node->right, (L + R) / 2 + 1, R);

    cur_node->sum = cur_node->left->sum + cur_node->right->sum;
    cur_node->minimum = (cur_node->left->minimum < cur_node->right->minimum) ? cur_node->left->minimum : cur_node->right->minimum;
    cur_node->maximum = (cur_node->left->maximum > cur_node->right->maximum) ? cur_node->left->maximum : cur_node->right->maximum;
}

int querySum(struct TreeNode *cur_node, int start, int end) {
    int L = cur_node->interval.first;
    int R = cur_node->interval.second;

    if (R < start || L > end) {
        return 0;
    }
    if (start <= L && end >= R) {
        return cur_node->sum;
    }

    int left_index = querySum(cur_node->left, start, end);
    int right_index = querySum(cur_node->right, start, end);

    return left_index + right_index;
}

int queryMin(struct TreeNode *cur_node, int start, int end) {
    int L = cur_node->interval.first;
    int R = cur_node->interval.second;

    if (R < start || L > end) {
        return INT_MAX; // Return maximum value for elements comparison
    }
    if (start <= L && end >= R) {
        return cur_node->minimum;
    }

    int left_index = queryMin(cur_node->left, start, end);
    int right_index = queryMin(cur_node->right, start, end);

    return (left_index < right_index) ? left_index : right_index;
}

int queryMax(struct TreeNode *cur_node, int start, int end) {
    int L = cur_node->interval.first;
    int R = cur_node->interval.second;

    if (R < start || L > end) {
        return INT_MIN; // Return minimum value for elements comparison
    }
    if (start <= L && end >= R) {
        return cur_node->maximum;
    }

    int left_index = queryMax(cur_node->left, start, end);
    int right_index = queryMax(cur_node->right, start, end);

    return (left_index > right_index) ? left_index : right_index;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    build(arr, root, 0, n - 1);
    int start, end;
    printf("Enter the interval to search between 0 to %d: ", n - 1);
    scanf("%d %d", &start, &end);

    printf("The sum of interval [%d-%d]: %d\n", start, end, querySum(root, start, end));
    printf("The minimum of interval [%d-%d]: %d\n", start, end, queryMin(root, start, end));
    printf("The maximum of interval [%d-%d]: %d\n", start, end, queryMax(root, start, end));

    return 0;
}
