/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
	if(head_==NULL){
		return;
	}
	ListNode *temp;
	while(head_ != NULL){
		temp = head_->next;
		delete head_;
		head_=temp;
	}
	head_=NULL;
	tail_ = NULL;
	return;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
	ListNode* node = new ListNode(ndata);
	if(head_==NULL){
		head_ = node;
		tail_ = node;
		length_=1;
		return;
	}
	head_->prev = node;
	node->next = head_;
	head_=node;
	length_++;
	return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
	if(tail_==NULL){
		head_ = new ListNode(ndata);
		tail_=head_;
		length_=1;
		return;
	}
	tail_->next = new ListNode(ndata);
	tail_->next->prev = tail_;
	tail_=tail_->next;
	length_++;
	return;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
	ListNode* BeforeStart = startPoint->prev;
	ListNode* AfterEnd = endPoint->next;
	ListNode* CurrNode = startPoint;
	std::queue<ListNode*> q;
	while(CurrNode != endPoint){
		q.push(CurrNode);
		CurrNode = CurrNode->next;
	}
	q.push(endPoint);
	endPoint = q.front();
	endPoint->next = AfterEnd;
	if(AfterEnd != NULL){
		AfterEnd->prev = endPoint;
	}
	CurrNode = endPoint;
	q.pop();
	while(!( q.empty() ) ){
		CurrNode->prev = q.front();
		q.front()->next = CurrNode;
		q.pop();
		CurrNode = CurrNode->prev;
	}
	startPoint = CurrNode;
	CurrNode->prev = BeforeStart;
	if(BeforeStart != NULL){
		BeforeStart->next = CurrNode;
	}
	return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if(n >= length_){
	  reverse();
	  return;
  }
  if(n <= 1){
	  return;
  }
	bool first =true;
  int AmountOfReversals = length_/n;
  ListNode* endPoint = head_;
  ListNode* startPoint = head_;
  for(int j=0;j<AmountOfReversals;j++){
	  startPoint = endPoint;
	  for(int i=1; i<n; i++){
		endPoint = endPoint->next;
	  }
	  reverse(startPoint,endPoint);
	  if(first){
		  head_=startPoint;
		  first=false;
	  }
	  if(AmountOfReversals*n == length_){
		  tail_=endPoint;
	  }
	  endPoint = endPoint->next;
  }
  if(AmountOfReversals*n != length_){
	  reverse(endPoint,tail_);
  }
  return;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
	if(head_==NULL){
		return;
	}
	int n=0;
	ListNode* CurrNode = head_;
	while(CurrNode != tail_){
		if(n%2==1){
			CurrNode->prev->next = CurrNode->next;
			CurrNode->next->prev = CurrNode->prev;
			tail_->next = CurrNode;
			CurrNode->prev = tail_;
			tail_ = CurrNode;
			CurrNode = CurrNode->next;
			tail_->next = NULL;
			n++;
		}else{
			CurrNode = CurrNode->next;
			n++;
		}
	}
	return;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
	if(start == NULL || splitPoint >= length_){
		return NULL;
	}
	for(int i=0;i<splitPoint;i++){
		start = start->next;
	}
	start->prev->next = NULL;
	start->prev = NULL;
	return start;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {	
	ListNode *head,*CurrNode;
	if(first->data < second->data){
		head = first;
		first = first->next;
	}else{
		head = second;
		second = second->next;
	}
	CurrNode = head;
	while(first != NULL && second != NULL){
		if(first->data < second->data){
			CurrNode->next = first;
			first->prev = CurrNode;
			CurrNode = first;
			first = first->next;
		}else{
			CurrNode->next = second;
			second->prev = CurrNode;
			CurrNode = second;
			second = second->next;
		}
	}
	if(first != NULL){
		CurrNode->next = first;
		return head;
	}else{
		CurrNode->next = second;
		return head;
	}
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
	if(chainLength == 1){
		return start;
	}
	ListNode* start2 = split(start, chainLength/2);
	start = mergesort(start,(chainLength/2));
	start2 = mergesort(start2, chainLength-(chainLength/2) );
	return merge(start,start2);
}
