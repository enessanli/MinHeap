#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class EHeap
{
    private:

        class HandleData
        {
            friend EHeap;
            private:    T mvalue;
                        int index;


        };


private:
        
         unsigned mCapacity;
         unsigned mSize;

void percolateUp(unsigned i)
        {Handle a;
       
            while (i > 1 and mHeap[i / 2]->mvalue > mHeap[i]->mvalue)
            {  
                         
                a=mHeap[i/2];
                mHeap[i/2]=mHeap[i];
                mHeap[i]=a;
                mHeap[i/2]->index=i/2;
                mHeap[i]->index=i;
                i = i / 2;
            }
           
        }



void percolateDown(unsigned i)
        { 
            
            while (2 * i <= mSize)
            {
                unsigned minChild;

                if (2 * i + 1 <= mSize and mHeap[2 * i + 1]->mvalue < mHeap[2 * i]->mvalue)
                {
                    minChild = 2 * i + 1;
                }
                else
                {
                    minChild = 2 * i;
                }

                if (mHeap[minChild]->mvalue < mHeap[i]->mvalue)
                {   Handle a;
                    a=mHeap[minChild];
                    mHeap[minChild]=mHeap[i];
                    mHeap[i]=a;
                    mHeap[i]->index=i;
                    mHeap[minChild]->index=minChild;
                    
                    i = minChild;
                }
                else
                {
                    break;
                }
            }
        }
  public:
        typedef HandleData * Handle;
        Handle *mHeap;
      
        EHeap(unsigned capacity) { 
            mCapacity= capacity;
            mSize=0;
            mHeap= new Handle[capacity + 1];
           
        }

        unsigned size() const { return mSize; }

        Handle push(T t) {  
            mSize++;
            Handle a;
            mHeap[mSize] = new HandleData;
            mHeap[mSize]->mvalue=t;
            mHeap[mSize]->index=mSize;
            a=mHeap[mSize];
            percolateUp(mSize);

            return a;
             }

        T pop() { 
  
            Handle a;
        
           
            T popped = mHeap[1]->mvalue;
            
            a = mHeap[1];
            mHeap[1]=mHeap[mSize];
            mHeap[mSize]=a;
            mHeap[mSize]->index=mSize;
            mHeap[1]->index=1;
            delete mHeap[mSize];
            mSize--;
          
            percolateDown(1);

            return popped;

           }

        T erase(Handle handle) { 
        int i;
        Handle a;
        T q;
        i=handle->index;
        q=mHeap[i]->mvalue;
        a=mHeap[i];
        mHeap[i]=mHeap[mSize];
        mHeap[mSize]=a;
        mHeap[mSize]->index=mSize;
        mHeap[i]->index=i;
        delete mHeap[mSize];
        mSize--;
        if ( i == 1 || mHeap[i/2]->mvalue < mHeap[i]->mvalue ) 
         {percolateDown(i);}
        else{
             percolateUp(i);   }
        


        return q;
             }

        ~EHeap() {  for(unsigned i=1;i<mSize+1;i++){delete mHeap[i];}
                    delete [] mHeap;
                  
                     }
};



int main()
{
  EHeap<int> e(7);
  int values[7] = {70, 60, 50, 10, 40, 30, 20};
  EHeap<int>::Handle handles[7];

  for(int i=0; i<7; i++){
    handles[i] = e.push(values[i]);
  }
  cout << e.size() << " items are pushed into the heap." << endl;

  cout << "Erased " << e.erase(handles[2]) << "." << endl;
  cout << "Popped " << e.pop() << "." << endl;
  cout << "Erased " << e.erase(handles[5]) << "." << endl;
  cout << "Popped " << e.pop() << "." << endl;
  cout << "Erased " << e.erase(handles[4]) << "." << endl;
  cout << "Popped " << e.pop() << "." << endl;
  cout << "Popped " << e.pop() << "." << endl;

  return 0;
}








