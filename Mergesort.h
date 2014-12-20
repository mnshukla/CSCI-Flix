#include <vector>

class MergeSort
{
    public:
        template <class T>
        static std::vector<T> sort (std::vector<T> a) 
        {

           int vector_size = a.size();
            int mid = (vector_size+1)/2;

            // base case
            if (vector_size <= 1)
            {
                return a;
            }
 
            std::vector<T> left, right, returnVector;

            // divide into 2 
            for (int i = 0; i < mid; i++)
            {
                left.push_back(a[i]);
                right.push_back(a[mid+i]);
            }
         
            // recursive calls to make smaller vectors
            left = sort(left);
            right = sort(right);
            returnVector = merge(left, right);
          
            return returnVector;
        }

    private:
        template <class T>
        static std::vector<T> merge(std::vector<T> left, std::vector<T> right)
        {
            
            std::vector<T> returnVector;
            int left_size = left.size();
            int right_size = right.size();
            while (left_size > 0 || right_size > 0)
            {
                if (left_size > 0 && right_size > 0)
                {
                    if (left.front() <= right.front())
                    {
                        returnVector.push_back(left.front());
                        left.erase(left.begin());
                    }

                    else 
                    {
                        returnVector.push_back(right.front());
                        right.erase(right.begin());
                    }

                }

                else if (left_size > 0 )
                {
                    for (int i = 0; i < left_size; i++)
                    {
                        returnVector.push_back(left[i]);
                    }
                    break;
                }
                else if (right_size > 0)
                {
                    for (int i = 0; i < right_size; i++)
                    {
                        returnVector.push_back(right[i]);
                    }
                    break;
                }
                left_size = left.size();
                right_size = right.size();
            }

            return returnVector;
        }
};

