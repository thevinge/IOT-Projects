using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;

namespace Temperature_Sensor_Calibration
{
    class Program
    {
        static void Main(string[] args)
        {
            var serialTemperature = new TemperatureSensor("COM5");
            var threadReceiver = new Thread(serialTemperature.Start);

            threadReceiver.Start();

            var CollectedData = new List<Tuple<DateTime, string>>();
            var shutdown = false;
            while (!shutdown)
            {
                Console.Beep();
                Console.Beep();
                Console.WriteLine("Input temperature here:");
                var input = Console.ReadLine();
                if (input.Equals("shutdown"))
                {
                    serialTemperature.Shutdown();
                    shutdown = true;
                }
                else
                {
                    var temperature = new Tuple<DateTime, string>(DateTime.Now, input);
                    CollectedData.Add(temperature);
                }

                Thread.Sleep((60000*2));
            }

            WriteResultToFile("ESP32_Result.txt", serialTemperature.CollectedData);
            WriteResultToFile("Manual_Result.txt", CollectedData);
        }

        private static void WriteResultToFile(string path, List<Tuple<DateTime, string>> data)
        {
            var writer = new StreamWriter(path);
            foreach (var item in data)
            {
                writer.WriteLine($"{item.Item1} : {item.Item2}");
            }

            writer.Flush();
            writer.Close();
        }
    }
}