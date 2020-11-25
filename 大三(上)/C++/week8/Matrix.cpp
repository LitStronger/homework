#include <iostream>
using namespace std;
class Matrix
{
public:
    Matrix(int new_arr[], int len)
    {
        arr = new int[10][10];
        edge_len = len;
        int k = 0;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                arr[i][j] = new_arr[k++];
            }
        }
    }
    Matrix(Matrix &mat)
    {
        arr = new int[10][10];
        edge_len = mat.edge_len;
        for (int i = 0; i < edge_len; i++)
        {
            for (int j = 0; j < edge_len; j++)
            {
                arr[i][j] = mat.arr[i][j];
            }
        }
    }
    ~Matrix(){
        delete [] arr;
    }
    
    void add(Matrix &mat)
    {
        for (int i = 0; i < mat.edge_len; i++)
        {
            for (int j = 0; j < mat.edge_len; j++)
            {
                arr[i][j] += mat.arr[i][j];
            }
        }
    }
    void my_print()
    {
        for (int i = 0; i < edge_len; i++)
        {
            for (int j = 0; j < edge_len; j++)
            {
                cout << "\t" << arr[i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }
    

private:
    int (*arr)[10];
    int edge_len;
};

int main()
{
    int a[9] = {1, 2, 3, 3, 4, 5, 3, 4, 5};
    Matrix mat1(a, 3);
    mat1.my_print();

    Matrix mat2(mat1);
    mat2.my_print();

    mat1.add(mat2);
    mat1.my_print();
    return 0;
}