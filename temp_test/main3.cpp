#include <iostream>
using namespace std;

// Task 3

struct Stack {
  struct Node {
    Node* Next = nullptr;
    int Data = 0;
  };

  // Указатель на вверхний элемент стека.
  Node* Top = nullptr;
};

void Construct(Stack& stack) { stack.Top = nullptr; }

void Destruct(Stack& stack) {
  Stack::Node* nodeIter;
  while (stack.Top != nullptr) {
    nodeIter = stack.Top;
    stack.Top = stack.Top->Next;
    delete nodeIter;
  }
}

void Push(Stack& stack, int value) {
  Stack::Node* nodeIter = nullptr;
  nodeIter->Data = value;
  if (stack.Top != nullptr) {
    stack.Top->Next = stack.Top;
  }
  stack.Top = nodeIter;
}

int Pop(Stack& stack) {
  if (stack.Top == nullptr) {
    return 0;
  }
  Stack::Node* temp = stack.Top;
  int data = stack.Top->Data;
  stack.Top = temp->Next;
  delete temp;
  return data;
}

bool Empty(const Stack& stack) { return stack.Top; }



int main() {
    Stack stack;
    Construct(stack);
    Push(stack, 0);

    return 0;
}
