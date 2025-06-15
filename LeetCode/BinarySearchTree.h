#pragma once

template <typename T>
struct TreeNode {
    TreeNode() { }
    TreeNode(T val)
        : _data(val)
    {
    }
    TreeNode<T>* _left = nullptr;
    TreeNode<T>* _right = nullptr;
    T _data;
};

template <typename T>
class BSTree {
public:
    BSTree()
        : _root(nullptr)
    {
    }

public:
    void insert(T val);
    void remove(T val);
    TreeNode<T>** search(T val);

private:
    TreeNode<T>* _root;
};

// 模板在头文件中定义
template <typename T>
void BSTree<T>::insert(T val)
{
    if (*search(val)) {
        return;
    }
    TreeNode<T>** cur = &(this->_root);
    while (*cur) {
        if (val > (*cur)->_data) {
            cur = &((*cur)->_right);
        } else if (val < (*cur)->_data) {
            cur = &((*cur)->_left);
        }
    }
    *cur = new TreeNode<T>(val);
}

template <typename T>
TreeNode<T>** BSTree<T>::search(T val)
{
    TreeNode<T>** cur = &(this->_root);
    while (*cur) {
        if ((*cur)->_data == val) {
            return cur;
        } else if ((*cur)->_data > val) {
            cur = &((*cur)->_left);
        } else if ((*cur)->_data < val) {
            cur = &((*cur)->_right);
        }
    }
    return cur;
}

template <typename T>
void BSTree<T>::remove(T val)
{
    TreeNode<T>** pos = search(val);
    if (!pos) {
        return;
    }
    // 如果删除节点有左右子树
}