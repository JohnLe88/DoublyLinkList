#include <iostream>

template < class T>
class SortedList{
	struct Node{
		T data_;
		Node * next_;
		Node * prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr){
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* first_;
	Node* last_;
public:
	class const_iterator{
		friend class SortedList<T>;
		Node* curr_;
	public:
		const_iterator(Node* p){
			curr_ = p;
		}
		const_iterator(){
			curr_ = nullptr;
		}
		const_iterator operator++(){
			//sets current position as next
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int){
			//sets current position as next then return the prev
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		bool operator==(const_iterator rhs){
			//returns true if lhs == rhs
			return curr_ == rhs.curr_;
		}
		bool operator!=(const_iterator rhs){
			//returns not true if lhs != rhs
			return curr_ != rhs.curr_;
		}
		const T& operator*() const{
			//returns the data the object is holding
			return curr_->data_;
		}
	};
	class iterator : public const_iterator{
		friend class SortedList<T>;
	public:
		iterator() :const_iterator(){}
		iterator(Node* n) :const_iterator(n){}
		iterator operator++(){
			//sets current position as next
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int){
			//sets current position as next and returns prev
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		bool operator==(iterator rhs){
			//returns true if lhs == rhs
			return this->curr_ == rhs.curr_;
		}
		bool operator!=(iterator rhs){
			//returns false if lhs != rhs
			return this->curr_ != rhs.curr_;
		}
		T& operator*() const{
			//returns the data the object is holding
			return this->curr_->data_;
		}
	};
	SortedList(){
		//constructor for SortedList
		first_ = new Node;
		last_ = new Node;
		//setting the nodes
		first_->next_ = last_;
		last_->prev_ = first_;
	}
	~SortedList(){
		//destructor for Sortedist
		while (first_->next_->next_ != nullptr){
			//makes a new node so we can set the next location to the next next and deletes the temp node
			Node* d = first_->next_;
			first_->next_ = first_->next_->next_;
			delete[] d;
		}
		//need to delete first and last
		delete[] first_;
		delete[] last_;
	}

	SortedList(const SortedList& sl){
		//copy constructor that uses equal operator
		*this = sl;
	}

	iterator insert(const T& in){ //sorted insert function
		//loops through the list which sets up the location
		iterator b = begin();
		while (b != end() && *b < in){
			++b;
		}

		Node * nn = new Node(in, b.curr_, b.curr_->prev_);
		//setting the new node's new location in the sortedlist
		nn->prev_->next_ = nn;
		nn->next_->prev_ = nn;
		return b;
	}

	bool remove(const T& rm){
		//using iterator to determine the spot in the list to delete
		iterator b = begin();
		while (b != end() && *b != rm){
			b++;
		}
		if (b == begin()){
			//if the spot to remove is the first spot, we set the next_ as the next_next_ and the new location of next_ as the first spot
			first_->next_ = first_->next_->next_;
			first_->next_->prev_ = first_;
			//deleting b and returning true
			delete[] b.curr_;
			return true;
		}
		if (b != end() && rm == *b){
			//deletes the spots needed to be deleted and sets the new locations
			//sets the before and after node to link to each other
			b.curr_->prev_->next_ = b.curr_->next_;
			b.curr_->next_->prev_ = b.curr_->prev_;
			delete[] b.curr_;
			return true;
		}
		return false;
	}

	const_iterator begin()const{ //returns the first item on the list
		return const_iterator(first_->next_);
	}

	const_iterator end()const{ //returns last item on the list 
		return const_iterator(last_);
	}

	iterator begin(){ //returns the first item on the list
		return iterator(first_->next_);
	}

	iterator end(){ //returns last item on the list
		return iterator(last_);
	}

	iterator erase(iterator i){
		// a function that deletes a certain spot on the list
		iterator next = begin();
		while (next != i){
			next++;
		}
		remove(*i);
		return next++;
	}
	iterator erase(iterator from, iterator to){
		// a function that deleted to to from in the SortedList
		iterator i = from;
		while (i != to){
			remove(*i);
			i++;
		}
		return to;
	}
	SortedList &operator=(const SortedList& sl){
		//copy operator
		first_ = new Node();
		last_ = new Node();
		first_->next_ = last_;
		last_->prev_ = first_;
		//set up iterator to iterator through the sl list
		iterator tmp = sl.first_->next_;

		while (tmp.curr_ != sl.last_){
			//using insert to copy over the list
			insert(*tmp);
			tmp++;
		}
		return *this;
	}
};

