using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO.Ports;

namespace FrequencyOfBlink.Communication
{
    public class SignalReceiver
    {
        private SerialPort sp;
        public List<DateTime> dateTimes { get; set; }
        
        public int RunningMinutes { get; set; }

        public SignalReceiver(string port)
        {
            sp = new SerialPort(port);
        }


        public void Start()
        {
            sp.BaudRate = 115200;
            sp.ReadTimeout = 5000;
            sp.Open();

            try
            {
                var startDate = DateTime.Now;

                while (DateTime.Now - startDate < TimeSpan.FromMinutes(RunningMinutes))
                {
                    var result = sp.ReadLine();

                    if (string.Compare(result, "1", CultureInfo.CurrentCulture, CompareOptions.IgnoreSymbols) == 0)
                    {
                        dateTimes.Add(DateTime.Now);
                    }
                }
            }
            catch (TimeoutException e)
            {
                sp.Close();
                sp.Dispose();
                Console.WriteLine("Timeout");
                //Do not do shit   
            }
        }
    }
}