//
//  main.cpp
//  hw11
//
//  Created by Valeria Dudinova on 05.11.2024.
//

#include <iostream>
using namespace std;

class TreeNode
{
public:
    char englishWord[50];
    char russianTranslation[50];
    int count;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const char* eng, const char* rus)
    {
        strcpy(englishWord, eng);
        strcpy(russianTranslation, rus);
        count = 1;
        left = nullptr;
        right = nullptr;
    }
};

class Dictionary
{
private:
    TreeNode* root;

    // Вставка нового слова в дерево
    void insert(TreeNode*& node, const char* eng, const char* rus)
    {
        if (node == nullptr)
        {
            node = new TreeNode(eng, rus);
        } else if (strcmp(eng, node->englishWord) < 0)
        {
            insert(node->left, eng, rus);
        }
        else if (strcmp(eng, node->englishWord) > 0)
        {
            insert(node->right, eng, rus);
        }
        else
        {
            // Якщо слово вже існує, оновлюємо переклад та збільшуємо лічильник
            strcpy(node->russianTranslation, rus);
            node->count++;
        }
    }

    // Пошук слова в дереві
    TreeNode* search(TreeNode* node, const char* eng) {
        if (node == nullptr || strcmp(node->englishWord, eng) == 0) {
            return node;
        }
        return strcmp(eng, node->englishWord) < 0 ? search(node->left, eng) : search(node->right, eng);
    }

    // Обхід дерева для відображення
    void inOrder(TreeNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->englishWord << " - " << node->russianTranslation << " (Count: " << node->count << ")" << endl;
            inOrder(node->right);
        }
    }

    // Знаходження найбільш популярного слова
    TreeNode* findMostPopular(TreeNode* node) {
        if (node == nullptr) return nullptr;
        TreeNode* leftMost = findMostPopular(node->left);
        TreeNode* rightMost = findMostPopular(node->right);
        
        TreeNode* mostPopular = node;

        if (leftMost && leftMost->count > mostPopular->count) {
            mostPopular = leftMost;
        }
        if (rightMost && rightMost->count > mostPopular->count) {
            mostPopular = rightMost;
        }

        return mostPopular;
    }

    // Знаходження найменш популярного слова
    TreeNode* findLeastPopular(TreeNode* node) {
        if (node == nullptr) return nullptr;
        TreeNode* leftLeast = findLeastPopular(node->left);
        TreeNode* rightLeast = findLeastPopular(node->right);

        TreeNode* leastPopular = node;

        if (leftLeast && leftLeast->count < leastPopular->count) {
            leastPopular = leftLeast;
        }
        if (rightLeast && rightLeast->count < leastPopular->count) {
            leastPopular = rightLeast;
        }

        return leastPopular;
    }

    // Видалення слова з дерева
    void deleteNode(TreeNode*& node, const char* eng) {
        if (node == nullptr) return;

        if (strcmp(eng, node->englishWord) < 0) {
            deleteNode(node->left, eng);
        } else if (strcmp(eng, node->englishWord) > 0) {
            deleteNode(node->right, eng);
        } else {
            // Вузол знайдено
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                node = temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                node = temp;
            } else {
                // Вузол з двома дочірніми
                TreeNode* temp = node->right;
                while (temp && temp->left != nullptr) {
                    temp = temp->left;
                }
                strcpy(node->englishWord, temp->englishWord);
                strcpy(node->russianTranslation, temp->russianTranslation);
                node->count = temp->count;
                deleteNode(node->right, temp->englishWord);
            }
        }
    }

public:
    // Конструктор
    Dictionary() : root(nullptr) {}

    // Додавання слова
    void insert(const char* eng, const char* rus) {
        insert(root, eng, rus);
    }

    // Пошук слова
    TreeNode* search(const char* eng) {
        return search(root, eng);
    }

    // Відображення словника
    void display() {
        inOrder(root);
    }

    // Видалення слова
    void deleteWord(const char* eng) {
        deleteNode(root, eng);
    }

    // Відображення найбільш популярного слова
    void showMostPopular()
    {
        TreeNode* mostPopular = findMostPopular(root);
        if (mostPopular) {
            cout << "The most popular word: " << mostPopular->englishWord
                 << " - " << mostPopular->russianTranslation
                 << " (Count: " << mostPopular->count << ")" << endl;
        } else {
            cout << "The dictionary is empty." << endl;
        }
    }

    // Відображення найменш популярного слова
    void showLeastPopular() {
        TreeNode* leastPopular = findLeastPopular(root);
        if (leastPopular) {
            cout << "The least popular word: " << leastPopular->englishWord
                 << " - " << leastPopular->russianTranslation
                 << " (Count: " << leastPopular->count << ")" << endl;
        } else {
            cout << "The dictionary is empty." << endl;
        }
    }
};

int main()
{
    Dictionary dict;
    dict.insert("hello", "привет");
    dict.insert("world", "мир");
    dict.insert("cat", "кот");
    
    // Показати словник
    cout << "Dictionary content:" << endl;
    dict.display();

    // Перевірка популярності
    dict.showMostPopular();
    dict.showLeastPopular();

    // Видалення слова
    dict.deleteWord("cat");
    cout << "After removal 'cat':" << endl;
    dict.display();

    return 0;
}

