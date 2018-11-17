# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
	stack<T> allValues;
	stack<T> minValues;
public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	return allValues.empty();
}

template <class T>
T& StackExt<T>::top() {
	return allValues.top();
}

template <class T>
void StackExt<T>::pop() {
	T val = allValues.top();
	if (!allValues.empty())
		allValues.pop();
	if (!minValues.empty() && minValues.top() == val)
		minValues.pop();
}

template <class T>
void StackExt<T>::push(const T& val) {
	allValues.push(val);
	if (minValues.empty() || val <= minValues.top())
		minValues.push(val);
}

template <class T>
T& StackExt<T>::findMin() {
	return minValues.top();
}
