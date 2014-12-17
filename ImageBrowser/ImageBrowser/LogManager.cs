using System;

namespace ImageBrowser
{
    class LogManager
    {
        public LogManager()
        {
            
        }

        public void Debug(string msg)
        {
            Console.WriteLine(msg);
        }

        public void Error(string msg, Exception e)
        {
            Console.WriteLine(msg);
            Console.WriteLine(e);
        }

        public void Error(string msg)
        {
            Console.WriteLine(msg);
        }
    }
}
