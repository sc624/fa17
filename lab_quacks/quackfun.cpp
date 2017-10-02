/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    if(s.empty())
    return T();     // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
    T val = s.top();
    s.pop();
    T t = val + sum(s);
    s.push(val);
    return t;


}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;


T begin = q.front();
T start = s.top();
T poo = 1;


while (q.empty() == false) {
  if(poo % 2 != 0){
    if((int)q.size() < poo){
      poo = q.size();
      }
    for (int p = 0; p < poo; p++) {
      q2.push(q.front());
      q.pop();
    }
  }
  else if(poo % 2 == 0){
    if((int)q.size() < poo){
      poo = q.size();
      }
    for(int j = 0; j < poo; j++){
      s.push(q.front());
      q.pop();
    }
    for(int a = 0; a < poo; a++){
      q2.push(s.top());
      s.pop();
    }
  }
  poo++;
}

while(q2.empty() == false){
  q.push(q2.front());
  q2.pop();
}
// hi = q.front();
//    q2.push(hi);
//    q.pop();
//
// for(int i = 0; i < val; i++){
//     T qpop = q.front();
//     s.push(qpop);
//     q.pop();
//   }
// for(int x = 0 ; x < val; x++){
//     bye = s.top();
//    q2.push(bye);
//    s.pop();
// }
// val = val + 2;
// poo = poo + 2;
// q.push(q2.front);
}


/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional

    s.pop();
    T stack_ = q.front(); // rename :)

    if(s.top == true){
      retval = (verifySame(s,q) && retval);
    }

    T queue_ = s.front(); // rename me

    if(queue_ != stack_)
      retval = false;

    s.push(stack_);
    q.push(queue_);
        q.pop();
    return retval;
}
/*if(s.empty())
return T();     // stub return value (0 for primitive types). Change this!
            // Note: T() is the default value for objects, and 0 for
            // primitive types
T val = s.top();
s.pop();
T t = val + sum(s);
s.push(val);
return t;
*/
}
