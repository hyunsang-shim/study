using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace List_Sort_Example
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> SampleList = new List<int>();
            SampleList.Add(12);
            SampleList.Add(1);
            SampleList.Add(38);
            SampleList.Add(19);
            SampleList.Add(63);
            SampleList.Add(99);

            System.Console.WriteLine("Natural(unsorted) Order:");
            foreach (int x in SampleList)
                System.Console.Write(" " + x);

            System.Console.WriteLine("");


            SampleList.Sort(delegate (int a, int b) { return a.CompareTo(b); });
            System.Console.WriteLine("Ascending Order:");
            foreach (int x in SampleList)
                System.Console.Write(" " + x);

            System.Console.WriteLine("");
            


            SampleList.Sort(delegate (int a, int b) { return b.CompareTo(a); });
            System.Console.WriteLine("Descending Order:");
            foreach (int x in SampleList)
                System.Console.Write(" " + x);

            System.Console.WriteLine("");

        }
    }
}
