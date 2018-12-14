using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;
// like [ using namespae std ] on c++;
using static System.Console;
using System.Threading;


#region old
namespace C_Sharp
{

//    class Program       // tiypically, main class name matches in file name
//    {
//        // Main method should unique and come with static.
//        // and notice that the 'M' in the ' Main() ' is Uppercase while lower case in C++ 
//        delegate int Calculate(int a, int b);

//        delegate string Concatenate(string[] args);




//        static void Main(string[] args)
//        {
//            #region past
//            /*
//            System.Console.WriteLine("Hello, World! This is Honeybear!");
//            // Console.WriteLine("Hello, World! This is Honeybear!");  // same as above

//            string max;

//            max = "Have Fun.";
//            Console.WriteLine(max);

//            string first, last;
//            Console.Write("What's Your first name? ");  // .Write method won't add line feed.
//            first = Console.ReadLine();
//            Console.Write("and last name is? ");
//            last = Console.ReadLine();

//            Console.WriteLine($"Hello! {first} {last}! Nice To Meet you!");
//            //Console.WriteLine("Hello! {0} {1}! Nice To Meet you!", first, last);    // same as above

//            var response = "thank you. you're kind."; // var => local use only

//            WriteLine(response);
//            WriteLine(response.ToUpper());

//            WriteLine("Really?");

//            bool tmp = true;

//            WriteLine($"{tmp.ToString()}");

//            // Declairing array in C#
//            int[] a;    // cf) c/c++   int a[];
//            int[,] b;   // cf) c/c++   int a[][];


//            string[] languages = new string[]
//            {
//                "C#", "COBOL", "Java", "C++", "Visual Basic", "Pascal",
//                "Fortran", "Lisp", "j#"
//            };

//            System.Array.Sort(languages);

//            string searchString = "COBOL";

//            int index = System.Array.BinarySearch(languages, searchString);
//            System.Console.WriteLine("The Wave of the Futre, " + $"{searchString}, is at index { index }.");

//            System.Console.WriteLine($"{ "First Element",-20}\t {"Last Element", -20 }");
//            System.Console.WriteLine($"{"--------------",-20}\t{"--------------",-20}");
//            System.Console.WriteLine(
//                $"{languages[0],-20}\t{languages[languages.Length - 1],-20}");

//            System.Array.Reverse(languages);
//            System.Console.WriteLine($"{languages[0],-20}\t{languages[languages.Length-1]}");

//            System.Array.Clear( languages, 0, languages.Length);
//            System.Console.WriteLine($"{languages[0],-20}\t{languages[languages.Length - 1], -20}");
//            System.Console.WriteLine($"After clearing, the array size is : {languages.Length}");



//            decimal decimalNumber = 4.2M;
//            double doubleNumber1 = 0.1F * 42F;
//            double doubleNumber2 = 0.1D * 42D;
//            float floatNumber = 0.1F * 42F;

//            Trace.Assert(decimalNumber != (decimal)doubleNumber1);
//            System.Console.WriteLine($"{decimalNumber} != {(decimal)doubleNumber1}");

//            Trace.Assert((double)decimalNumber != doubleNumber1);
//            System.Console.WriteLine($"{ (double)decimalNumber} != {doubleNumber1}");

//            Trace.Assert((float)decimalNumber != floatNumber);
//            Console.WriteLine($"(float){(float)decimalNumber}M != {floatNumber}F");

//            // the book says, it's not same but Runtime error occurs when it runs
//            // comparation edited from '!=' to '=='
//            Trace.Assert(doubleNumber1 == (double)floatNumber);
//            Console.WriteLine($"{doubleNumber1} == {doubleNumber2}");

//            Trace.Assert(doubleNumber1 != doubleNumber2);
//            Console.WriteLine($"{doubleNumber1} != {doubleNumber2}");

//            Trace.Assert(floatNumber != doubleNumber2);
//            System.Console.WriteLine($"{floatNumber}F != {doubleNumber2}D");

//            Trace.Assert((double)4.2F != 4.2D);
//            System.Console.WriteLine($"{(double)4.2F} != {4.2D}");

//            Trace.Assert(4.2F != 4.2D);
//            System.Console.WriteLine($"{4.2F}F != {4.2D}D");


//            Employee employee1 = new Employee();

//            employee1.FirstName = "INDIO";
//            employee1.LastName = "MOMONGA";
//            employee1.Salary = "Starving!";

//            Employee employee2 = new Employee();
//            employee2.SetName("Inigo", "Montoya");
//            employee2.Save();

//            // 
//            IncreaseSalary(employee2);

//            employee1 = DataStorage.Load("Inigo", "Montoya");

//            Console.WriteLine($"{employee1.GetName()} : {employee1.Salary}");


//            ClimateMonitor cli = new ClimateMonitor(new ConsoleLogger());
//            ClimateMonitor cli2 = new ClimateMonitor(new FileLogger("MyLog.txt"));
//            //cli.start();
//            cli2.start();


//            Property.BirthdayInfo birth = new Property.BirthdayInfo();
//            birth.name = "꿀곰";
//            birth.B_day = new DateTime(1980, 11, 11);

//            Console.WriteLine("Name : {0}", birth.name);
//            Console.WriteLine("Birthdat : {0}", birth.B_day.ToShortDateString());
//            Console.WriteLine("Age : {0}", birth.age);


//            int[] source = { 1, 2, 3, 4, 5, 6 };
//            int[] target = new int[source.Length];

//            CopyArray<int>(source, target);

//            foreach (int element in target)
//                Console.WriteLine(element);

//            string[] source2 = { "일", "이", "삼", "사", "오", "육" };
//            string[] target2 = new string[source2.Length];

//            CopyArray<string>(source2, target2);

//            foreach (string element in target2)
//                Console.WriteLine(element);
//        }

//        static void IncreaseSalary(Employee employee)
//        {
//            employee.Salary = "Enough to Survive on";
//        }

//        static void CopyArray<T>(T[] src, T[] dst)
//        {
//            for (int i = 0; i < src.Length; i++)
//                dst[i] = src[i];
//        }



//            Calculator Calc = new Calculator();
//            MyDelegate Callback;

//            Callback = new MyDelegate(Calc.Plus);
//            Console.WriteLine(Callback(3, 4));

//            Callback = new MyDelegate(Calculator.Minus);
//            Console.WriteLine(Callback(7, 5));
//            */
//            #endregion past
//            #region 20181211
//            /*
//            Notifier notifier = new Notifier();
//            EventListener listener1 = new EventListener("Listener1");
//            EventListener listener2 = new EventListener("Listener2");
//            EventListener listener3 = new EventListener("Listener3");

//            notifier.EventOccured += listener1.Somethinghappened;
//            notifier.EventOccured += listener2.Somethinghappened;
//            notifier.EventOccured += listener3.Somethinghappened;
//            notifier.EventOccured("You've got mail.");

//            Console.WriteLine();

//            notifier.EventOccured -= listener2.Somethinghappened;
//            notifier.EventOccured("Download Complete.");

//            Console.WriteLine();

//            notifier.EventOccured = new Notify(listener2.Somethinghappened)
//                + new Notify(listener3.Somethinghappened);
//            notifier.EventOccured("Nuclear Launch Detected.");

//            Console.WriteLine();

//            Notify notify1 = new Notify(listener1.Somethinghappened);
//            Notify notify2 = new Notify(listener2.Somethinghappened);

//            notifier.EventOccured = (Notify)Delegate.Combine(notify1, notify2);
//            notifier.EventOccured("Fire!!");

//            Console.WriteLine();

//            notifier.EventOccured = (Notify)Delegate.Remove(notifier.EventOccured, notify2);
//            notifier.EventOccured("RPG!");



//            Concatenate concat = (arr) =>
//            {
//                string result = "";
//                foreach (string s in arr)
//                    result += s;

//                return result;
//            };

//            Console.WriteLine(concat(args));
//            */
//            #endregion 20181211
//            #region 20181212
//            /*
//             *  Class[] arrClass =
//                {
//                new Class() { Name = "연두", Score = new int[] {99,80,70,24 } },
//                new Class() { Name = "분홍", Score = new int[] {60,45,87,72}},
//                new Class() { Name = "파랑", Score = new int[] {92,30,85,94}},
//                new Class() { Name = "노랑", Score = new int[] {90,88,0,17}}

//            };

//            var classes = from c in arrClass
//                          from s in c.Score
//                          where s < 60
//                          orderby s
//                          select new { c.Name, Lowest = s };

//            foreach (var c in classes)
//                Console.WriteLine("낙제: {0} ({1})", c.Name, c.Lowest);




//            Profile[] arrProfile = {
//                new Profile() {  Name = "정우성", Height = 186},
//                new Profile() {  Name = "김태희", Height = 158},
//                new Profile() {  Name = "고현정", Height = 172},
//                new Profile() {  Name = "이문세", Height = 178},
//                new Profile() {  Name = "하하", Height = 171}

//            };


//            var listProfile = from profile in arrProfile
//                              orderby profile.Height
//                              group profile by profile.Height < 175 into g
//                              select new { GroupKey = g.Key, Profiles = g };

//            foreach(var Group in listProfile)
//            {
//                Console.WriteLine("-175Cm 미만 : {0}", Group.GroupKey);

//                foreach(var profile in Group.Profiles)
//                {
//                    Console.WriteLine("      {0}, {1}", profile.Name, profile.Height);
//                }
//            }


//             Profile[] arrProfile = {
//                new Profile() {  Name = "정우성", Height = 186},
//                new Profile() {  Name = "김태희", Height = 158},
//                new Profile() {  Name = "고현정", Height = 172},
//                new Profile() {  Name = "이문세", Height = 178},
//                new Profile() {  Name = "하하", Height = 171}

//            };

//            Product[] arrProduct =
//            {
//                new Product() {Title = "비트", Star = "정우성"},
//                new Product() {Title = "CF 다수", Star = "김태희"},
//                new Product() {Title = "아이리스", Star = "김태희"},
//                new Product() {Title = "모래시계", Star = "고현정"},
//                new Product() {Title = "Solo 예찬", Star = "이문세"}
//            };

//            var listProfile = from profile in arrProfile
//                              join product in arrProduct on profile.Name equals product.Star
//                              select new
//                              {
//                                  Name = profile.Name,
//                                  Work = product.Title,
//                                  Height = profile.Height
//                              };

//            Console.WriteLine("--- 내부 조인 결과 ---");
//            foreach (var profile in listProfile)
//            {
//                Console.WriteLine("이름:{0}, 작품 : {1}, 키 : {2}Cm", profile.Name, profile.Work, profile.Height);
//            }

//            listProfile = from profile in arrProfile
//                          join product in arrProduct on profile.Name equals product.Star into ps
//                          from product in ps.DefaultIfEmpty(new Product() { Title = "그런거 없음" })
//                          select new
//                          {
//                              Name = profile.Name,
//                              Work = product.Title,
//                              Height = profile.Height
//                          };

//            Console.WriteLine();
//            Console.WriteLine("--- 외부 조인 결과 ---");
//            foreach (var profile in listProfile)
//            {
//                Console.WriteLine("이름:{0}, 작품 : {1}, 키 : {2}Cm", profile.Name, profile.Work, profile.Height);
//            }

//             */


//        MyClass obj = new MyClass();

//        obj.OldMethod();
//        obj.NewMethod();
//            #endregion 20181212
//        }

//    }

//    #region 20181212_class
//    class Product
//    {
//        public string Title { get; set; }
//        public string Star { get; set; }
//    }

//    class Profile
//    {
//        public string Name { get; set; }
//        public int Height { get; set; }
//    }

//    class Class
//        {
//            public string Name { get; set; }
//            public int[] Score { get; set; }
//        }

//    class MyClass
//    {
//        [Obsolete("OldMethod 는 폐기되었습니다. newMethod()를 이용하세요.")]

//        public void OldMethod()
//        {
//            Console.WriteLine("I'm Old");
//        }

//        public void NewMethod()
//        {
//            Console.WriteLine("I'm new");
//        }
//    }

//    #endregion 20181212_class


//} 
#endregion old

#region 2018-12-14_File_Control

//namespace Dir
//{

//    #region Dir/File_Info
//    //class MainApp
//    //{
//    //    static void Main(string[] args)
//    //    {
//    //        string directory;

//    //        if (args.Length < 1)
//    //            directory = ".";
//    //        else
//    //            directory = args[0];

//    //        Console.WriteLine("{0} directory info", directory);
//    //        Console.WriteLine("- Directories : ");

//    //        var directories = (from dir in Directory.GetDirectories(directory)
//    //                           let info = new DirectoryInfo(dir)
//    //                           select new
//    //                           {
//    //                               Name = info.Name,
//    //                               Attributes = info.Attributes
//    //                           }).ToList();

//    //        foreach (var d in directories)
//    //            Console.WriteLine("{0} : {1}", d.Name, d.Attributes);

//    //        Console.WriteLine("- Files :");
//    //        var files = (from file in Directory.GetFiles(directory)
//    //                     let info = new FileInfo(file)
//    //                     select new
//    //                     {
//    //                         Name = info.Name,
//    //                         FileSize = info.Length,
//    //                         Attributes = info.Attributes
//    //                     }).ToList();

//    //        foreach (var f in files)
//    //            Console.WriteLine("{0} : {1}. {2}",
//    //                f.Name, f.FileSize, f.Attributes);

//    //    }
//    //}
//    #endregion Dir/File_Info

//    #region Dir/File Create

//    #endregion Dir/File Create





//
}
#endregion 2018-12-14_File_Control

#region Thread
namespace BasicThread
{
    //class MainApp
    //{
    //    static void DoSomething()
    //    {
    //        try
    //        {
    //            for (int i = 0; i < 10000; i++)
    //            {
    //                Console.WriteLine("DoSomething : {0}", i);
    //                Thread.Sleep(10);
    //            }
    //        }
    //        catch(ThreadInterruptedException e)
    //        {

    //        }
    //        finally
    //        {

    //        }
    //    }

    //    static void Main(string[] args)
    //    {
    //        Thread t1 = new Thread(new ThreadStart(DoSomething));

    //        Console.WriteLine("Starting thread...");
    //        t1.Start();

    //        for (int i = 0; i < 5; i++)
    //        {
    //            Console.WriteLine("Main : {0}", i);
    //            Thread.Sleep(10);
    //        }

    //        Console.WriteLine("Wating Until thread stops...");

    //        t1.Interrupt();


    //        t1.Join();

    //        Console.WriteLine("Finihed");
    //    }

    //}
}

#endregion Thread

#region InterruptingThread
namespace InterruptingThread
{
    class SideTask
    {
        int count;

        public SideTask(int count)
        {
            this.count = count;
        }

        public void KeepAlive()
        {
            try
            {
                Console.WriteLine("Rinning thread isn't gonna be interrupted");
                Thread.SpinWait(1000000000);

                while (count > 0)
                {
                    Console.WriteLine("{0} left", count--);

                    Console.WriteLine("Entering into WaitJoinSleep State...");
                    Thread.Sleep(10);
                }

                Console.WriteLine("Count : 0");
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e);
            }
            finally
            {
                Console.WriteLine("Clearing resource...");
            }
        }           
    }

    class MainApp
    {
        static void Main(string[] args)
        {
            SideTask task = new SideTask(100);
            Thread t1 = new Thread(new ThreadStart(task.KeepAlive));

            t1.IsBackground = false;

            Console.WriteLine("Starting thread...");
            t1.Start();

            Thread.Sleep(100);

            Console.WriteLine("Interrupting thread..");
            t1.Interrupt();

            Console.WriteLine("Waiting until thread stops...");
            t1.Join();

            Console.WriteLine("Finished");
        }
    }
}
#endregion InterruptingThread