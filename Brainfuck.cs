using System;
using System.IO;

internal class Program
{
    private const int MemorySize = 4096;

    private static int Main(string[] args)
    {
        if (args.Length == 0)
        {
            Console.WriteLine("The source file wasn't provided");
            return 1;
        }

        string source;
        try
        {
            source = File.ReadAllText(args[0]);
        }
        catch
        {
            Console.WriteLine("The source file couldn't read");
            return 1;
        }

        byte[] memory = new byte[MemorySize];
        int pointer = 0;
        int index, scope;
        for (index = 0; index < source.Length; index++)
        {
            switch (source[index])
            {
                case '>':
                    pointer++;
                    break;

                case '<':
                    pointer--;
                    break;
            
                case '+':
                    memory[pointer]++;
                    break;
            
                case '-':
                    memory[pointer]--;
                    break;

                case '.':
                    Console.Write((char)memory[pointer]);
                    break;
            
                case ',':
                    memory[pointer] = (byte)Console.Read();
                    break;
            
                case '[':
                    if (memory[pointer] == 0)
                    {
                        scope = 1;
                        while (scope != 0)
                        {
                            index++;
                            if (index == source.Length)
                                break;
                        
                            if (source[index] == '[')
                                scope++;
                        
                            if (source[index] == ']')
                                scope--;
                        }
                    }

                    break;

                case ']':
                    if (memory[pointer] != 0)
                    {
                        scope = 1;
                        while (scope != 0)
                        {
                            index--;
                            if (index == -1)
                                break;
                        
                            if (source[index] == '[')
                                scope--;
                        
                            if (source[index] == ']')
                                scope++;
                        }
                    }

                    break;
            }
        }

        return 0;
    }
}
