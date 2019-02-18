using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;

namespace ImageToLevelFile
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter path to image folder");
            string imageFolder = Console.ReadLine();

            foreach (var item in Directory.GetFiles(imageFolder))
            {
                bool first = true;
                string levelData = "";

                Bitmap img = new Bitmap(item);
                for (int y = img.Height - 1; y >= 0; y--)
                {
                    for (int x = 0; x < img.Width; x++)
                    {
                        Color pixel = img.GetPixel(x, y);

                        if (first)
                            levelData += img.Width;
                        first = false;
                        
                        levelData += ",";
                        if (pixel.R == 0 && pixel.G == 0 && pixel.B == 0)
                        {
                            levelData += "w";
                        }
                        else if (pixel.R == 0 && pixel.G == 255 && pixel.B == 0)
                        {
                            levelData += "p";
                        }
                        else if (pixel.R == 255 && pixel.G == 0 && pixel.B == 0)
                        {
                            levelData += "e";
                        }
                        else
                        {
                            levelData += "f";
                        }
                    }
                }

                File.WriteAllText(imageFolder + Path.GetFileNameWithoutExtension(item) + ".l", levelData);
            }
            

            Console.WriteLine("Done");
            Console.Read();
        }
    }
}
