using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;
// like [ using namespae std ] on c++;
using static System.Console;


namespace C_Sharp
{   
    class Program       // tiypically, main class name matches in file name
    {
        // Main method should unique and come with static.
        // and notice that the 'M' in the ' Main() ' is Uppercase.
        static void Main(string[] args)
        {
            #region past
            /*
            System.Console.WriteLine("Hello, World! This is Honeybear!");
            // Console.WriteLine("Hello, World! This is Honeybear!");  // same as above

            string max;

            max = "Have Fun.";
            Console.WriteLine(max);

            string first, last;
            Console.Write("What's Your first name? ");  // .Write method won't add line feed.
            first = Console.ReadLine();
            Console.Write("and last name is? ");
            last = Console.ReadLine();

            Console.WriteLine($"Hello! {first} {last}! Nice To Meet you!");
            //Console.WriteLine("Hello! {0} {1}! Nice To Meet you!", first, last);    // same as above

            var response = "thank you. you're kind."; // var => local use only

            WriteLine(response);
            WriteLine(response.ToUpper());

            WriteLine("Really?");

            bool tmp = true;

            WriteLine($"{tmp.ToString()}");

            // Declairing array in C#
            int[] a;    // cf) c/c++   int a[];
            int[,] b;   // cf) c/c++   int a[][];


            string[] languages = new string[]
            {
                "C#", "COBOL", "Java", "C++", "Visual Basic", "Pascal",
                "Fortran", "Lisp", "j#"
            };

            System.Array.Sort(languages);

            string searchString = "COBOL";

            int index = System.Array.BinarySearch(languages, searchString);
            System.Console.WriteLine("The Wave of the Futre, " + $"{searchString}, is at index { index }.");
                        
            System.Console.WriteLine($"{ "First Element",-20}\t {"Last Element", -20 }");
            System.Console.WriteLine($"{"--------------",-20}\t{"--------------",-20}");
            System.Console.WriteLine(
                $"{languages[0],-20}\t{languages[languages.Length - 1],-20}");

            System.Array.Reverse(languages);
            System.Console.WriteLine($"{languages[0],-20}\t{languages[languages.Length-1]}");

            System.Array.Clear( languages, 0, languages.Length);
            System.Console.WriteLine($"{languages[0],-20}\t{languages[languages.Length - 1], -20}");
            System.Console.WriteLine($"After clearing, the array size is : {languages.Length}");



            decimal decimalNumber = 4.2M;
            double doubleNumber1 = 0.1F * 42F;
            double doubleNumber2 = 0.1D * 42D;
            float floatNumber = 0.1F * 42F;

            Trace.Assert(decimalNumber != (decimal)doubleNumber1);
            System.Console.WriteLine($"{decimalNumber} != {(decimal)doubleNumber1}");
            
            Trace.Assert((double)decimalNumber != doubleNumber1);
            System.Console.WriteLine($"{ (double)decimalNumber} != {doubleNumber1}");

            Trace.Assert((float)decimalNumber != floatNumber);
            Console.WriteLine($"(float){(float)decimalNumber}M != {floatNumber}F");

            // the book says, it's not same but Runtime error occurs when it runs
            // comparation edited from '!=' to '=='
            Trace.Assert(doubleNumber1 == (double)floatNumber);
            Console.WriteLine($"{doubleNumber1} == {doubleNumber2}");

            Trace.Assert(doubleNumber1 != doubleNumber2);
            Console.WriteLine($"{doubleNumber1} != {doubleNumber2}");

            Trace.Assert(floatNumber != doubleNumber2);
            System.Console.WriteLine($"{floatNumber}F != {doubleNumber2}D");

            Trace.Assert((double)4.2F != 4.2D);
            System.Console.WriteLine($"{(double)4.2F} != {4.2D}");

            Trace.Assert(4.2F != 4.2D);
            System.Console.WriteLine($"{4.2F}F != {4.2D}D");
            */
            #endregion past

            Employee employee1 = new Employee();

            employee1.FirstName = "INDIO";
            employee1.LastName = "MOMONGA";
            employee1.Salary = "Starving!";

            Employee employee2 = new Employee();
            employee2.SetName("Inigo", "Montoya");
            employee2.Save();

            // 
            IncreaseSalary(employee2);

            employee1 = DataStorage.Load("Inigo", "Montoya");

            Console.WriteLine($"{employee1.GetName()} : {employee1.Salary}");
        }

        static void IncreaseSalary(Employee employee)
        {
            employee.Salary = "Enough to Survive on";
        }

    }

    class Employee
    {
        public string FirstName;
        public string LastName;
        public string Salary;

        public void Save()
        {
            DataStorage.Store(this);
        }

        public string GetName()
        {
            return $"{FirstName} {LastName}";
        }

        public void SetName(string newFirstName, string newLastName)
        {
            this.FirstName = newFirstName;
            this.LastName = newLastName;
            Console.WriteLine($"Name Changed to '{ this.GetName()}'");
        }

        static void IncreaseSalary(Employee employee)
        {
            employee.Salary = "Enough to Survive on";
        }
    }

    class DataStorage
    {
        public static void Store(Employee employee)
        {
            FileStream stream = new FileStream(employee.FirstName + employee.LastName + ".dat", FileMode.Create);

            StreamWriter writer = new StreamWriter(stream);

            writer.WriteLine(employee.FirstName);
            writer.WriteLine(employee.LastName);
            writer.WriteLine(employee.Salary);

            writer.Close();

        }

        public static Employee Load(string firstName, string lastname)
        {
            Employee employee = new Employee();

            FileStream stream = new FileStream(firstName + lastname + ".dat", FileMode.Open);
            StreamReader reader = new StreamReader(stream);

            employee.FirstName = reader.ReadLine();
            employee.LastName = reader.ReadLine();
            employee.Salary = reader.ReadLine();

            reader.Close();

            return employee;

        }

    }

    
    
    
}
