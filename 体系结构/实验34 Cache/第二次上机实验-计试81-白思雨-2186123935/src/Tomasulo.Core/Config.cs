using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tomasulo.Core
{
    public class Config
    {
        public static List<Instruction> Example1 = new List<Instruction>
        {
            new Instruction{Name="LD", F1=1, F2=11},
            new Instruction{Name="ADDD", F1=4, F2=2, F3=3},
            new Instruction{Name="ADDD", F1=5, F2=3, F3=3},
            new Instruction{Name="SUBD", F1=6, F2=2, F3=3},
            new Instruction{Name="SUBD", F1=7, F2=3, F3=2},
            new Instruction{Name="MULD", F1=8, F2=2, F3=3},
            new Instruction{Name="DIVD", F1=9, F2=2, F3=3},
            new Instruction{Name="ST", F1=4, F2=12},
        };

        public static List<Instruction> Example2 = new List<Instruction>
        {
            new Instruction{Name="LD", F1=1, F2=11},
            new Instruction{Name="LD", F1=2, F2=22},
            new Instruction{Name="ADDD", F1=4, F2=1, F3=2},
            new Instruction{Name="LD", F1=3, F2=44},
            new Instruction{Name="SUBD", F1=5, F2=2, F3=3},
            new Instruction{Name="MULD", F1=6, F2=2, F3=5},
            new Instruction{Name="ST", F1=6, F2=33}
        };

        public static List<Instruction> Example3 = new List<Instruction>
        {
            new Instruction{Name="LD", F1=2, F2=22},
            new Instruction{Name="LD", F1=3, F2=33},
            new Instruction{Name="LD", F1=4, F2=44},
            new Instruction{Name="ADDD", F1=1, F2=2, F3=3},
            new Instruction{Name="SUBD", F1=3, F2=2, F3=1},
            new Instruction{Name="MULD", F1=3, F2=2, F3=3},
            new Instruction{Name="DIVD", F1=1, F2=1, F3=4},
        };
    }
}
