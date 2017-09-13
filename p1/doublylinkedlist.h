/**
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & Kyle Kruskamp
 * @date 2/10/16
 */

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

template <class T>
class DoublyLinkedList {

   public:
      DoublyLinkedList();
      ~DoublyLinkedList();
      void append(T* data);
      bool empty() const { return (head == nullptr); }
      T* remove();
      T* first();
      T* next();

   private:
      class Node {
         public:
            Node();
            Node(T* data);
            Node* next;
            Node* prev;
            T* data;
      };
      Node* head;
      Node* tail;
      Node* current;
};

/**
 * @brief   Node constructor.
 */
template <class T>
DoublyLinkedList<T>::Node::Node()
{

   current = nullptr;
   next = nullptr;
   prev = nullptr;

}

//Sets the data
   template <class T>
DoublyLinkedList<T>::Node::Node(T* data)
{
   this->data = data;
}

/**
 * @brief   DoublyLinkedList constructor.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {

   head = nullptr;
   tail = nullptr;
   current = nullptr;

}

/**
 * @brief   DoublyLinkedList destructor.
 */
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

   if (!empty())
   {

      while (head->next != nullptr)
      {
         Node* ptr = head;
         head = head->next;
         delete ptr;
      }
   }

}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data) {


   if (empty())
   {
      Node* ptr = new Node(data);
      head = ptr;
      head->next = nullptr;
      head->prev = nullptr;
      tail = head;
      current = head;
   }

   else
   {
      Node* ptr = new Node(data);
      current = ptr;
      current->prev = tail;
      tail->next = current;
      tail = current;
      tail->next = nullptr;
      current->next = nullptr;
   }


}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first() {

   Node *temp = head;
   current = head;

   if (temp == nullptr)
   {
      return nullptr;
   }

   return temp->data;

}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next() {

   if (current == tail || current == nullptr)
   {
      return nullptr;
   }

   else if (head == nullptr || head->next == nullptr)
   {
      return nullptr;
   }

   else
   {
      current = current->next;
      return current->data;
   }

}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::remove() {

   Node* ptr = current;

   if (empty())
   {
      return nullptr;
   }

   else if (head == tail)
   {
      head = nullptr;
      tail = nullptr;
      current = nullptr;
      return nullptr;
   }

   else if (current == head)
   {
      ptr = head;
      head = head->next;
      head->prev = nullptr;
      current = head;
      delete ptr;
      return head->data;
   }

   else if (current == tail)
   {
      ptr = tail;
      tail = tail->prev;
      tail->next = nullptr;
      return nullptr;
   }

   else
   {
      ptr = current->prev;
      ptr->next = current->next;
      current = current->next;
      current->prev = ptr;
      return current->data;
   }

}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
