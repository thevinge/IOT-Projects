using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO.Ports;
using System.Threading;

namespace Temperature_Sensor_Calibration
{
    public class TemperatureSensor
    {
        private SerialPort sp;
        public List<Tuple<DateTime, string>> CollectedData { get; } = new List<Tuple<DateTime, string>>();
        private  Mutex mut = new Mutex();
        private bool _shutdown = false;
        public TemperatureSensor(string port)
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
                while (!DoShutdown())
                {
                    var result = sp.ReadLine();
                    var temperature = new Tuple<DateTime,string>(DateTime.Now, result);
                    CollectedData.Add(temperature);
                }
                sp.Close();
                sp.Dispose();
            }
            catch (TimeoutException e)
            {
                sp.Close();
                sp.Dispose();
                Console.WriteLine("Timeout");
                //Do not do shit   
            }
        }

        public void Shutdown()
        {
            mut.WaitOne();
            _shutdown = true;
            mut.ReleaseMutex();
            
        }
        private bool DoShutdown()
        {
            mut.WaitOne();
            var result = _shutdown;
            mut.ReleaseMutex();
            return result;

        }
    }
}