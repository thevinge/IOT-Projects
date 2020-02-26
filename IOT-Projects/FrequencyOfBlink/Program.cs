using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using FrequencyOfBlink.Communication;

namespace FrequencyOfBlink
{
    class Program
    {
        static void Main(string[] args)
        {
            var endDtSignalReceiver = new List<DateTime>();
            var serialSignalReceiver = new SignalReceiver("COM6");
            serialSignalReceiver.RunningMinutes = 1;
            serialSignalReceiver.dateTimes = endDtSignalReceiver;
          
            var threadReceiver = new Thread(serialSignalReceiver.Start);

            threadReceiver.Start();
            
            threadReceiver.Join();

            
            var writer = new StreamWriter("result.txt");
            foreach (var line in serialSignalReceiver.dateTimes)
            {
                writer.WriteLine(line.Ticks * 100);
            }
            writer.Flush();
            writer.Close();
        }
    }
}