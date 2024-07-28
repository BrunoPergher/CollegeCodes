using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Soccer
{
    internal class Torneio
    {
        public int id { get; set; }

        public Time Campeao { get; set; }

        public Time ViceCampeao { get; set; }

        public Time Terceiro { get; set; }

        public Time Quarto { get; set; }

        public int QtdTimes { get; set; }

        public Time confronto(Time a, Time b)
        {
            Random random = new Random();

            if (a.level > b.level)
            {
                var dif = a.level - b.level;
                int i = random.Next(0, 100);

                if (i <= (50 + dif / 2))
                {
                    return b;
                }
                else
                {
                    return a;
                }
            }
            else if(a.level < b.level)
            {
                var dif = b.level - a.level;
                int i = random.Next(0, 100);

                if (i <= (50 + dif / 2))
                {
                    return a;
                }
                else
                {
                    return b;
                }
            }
            else
            {
                int i = random.Next(0, 100);

                if (i >= 50)
                {
                    return a;
                }
                else
                {
                    return b;
                }
            }
        }

        public void print()
        {
            Console.WriteLine("os vencedores são:");
            Console.WriteLine("\nCampeão - " + Campeao.NomeDoTime);
            Console.WriteLine("\nVice Campeão - " + ViceCampeao.NomeDoTime);
            if (Terceiro != null)
            {
                Console.WriteLine("\n Terceiro - " + Terceiro.NomeDoTime);
            }
            if (Quarto != null)
            {
                Console.WriteLine("\n Quarto - " + Quarto.NomeDoTime);
            }
        }
    }
}
