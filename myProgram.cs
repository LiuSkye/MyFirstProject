public class MyArray
 {
     private static int[] arr;
     private static Random r = new Random();
     public MyArray(int size)
     {
         arr = new int[size];
         for (int i = 0; i < size; i++)
         {
             arr[i] = r.Next(0, 100);
         }
     }
     //选择排序算法
     public void Sort()
     {
         int maxIndex; //最大元素的索引 
         for (int i = 0; i < arr.Length - 1; i++)
         {
             maxIndex = i;
             for (int index = i + 1; index < arr.Length; index++)
             {
                 if (arr[index] > arr[maxIndex])
                 {
                     maxIndex = index;
                 }
             }
             Swap(i, maxIndex);
             Print();
         }
     }
     public void Swap(int first, int second)
     {
         int temp = arr[first];
         arr[first] = arr[second];
         arr[second] = temp;
     }
     //打印数组元素
     public void Print()
     {
         foreach (var item in arr)
         {
             Console.Write(item + " ");               
         }
         Console.WriteLine("\n");
     }
 }

class Program
{
    static void Main(string[] args)
    {
        MyArray myArray = new MyArray(10);
        Console.Write("排序前: ");
        myArray.Print();
        Console.WriteLine("排序后： ");
        myArray.Sort();
        Console.ReadKey();
    }
}