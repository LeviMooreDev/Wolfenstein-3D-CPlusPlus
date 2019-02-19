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
                            levelData += "s";
                        }
                        else if (pixel.R == 167 && pixel.G == 167 && pixel.B == 167)
                        {
                            levelData += "w";
                        }
                        else if (pixel.R == 76 && pixel.G == 76 && pixel.B == 76)
                        {
                            levelData += "b";
                        }
                        else if (pixel.R == 0 && pixel.G == 80 && pixel.B == 0)
                        {
                            levelData += "h";
                        }
                        else if (pixel.R == 0 && pixel.G == 255 && pixel.B == 0)
                        {
                            levelData += "p";
                        }
                        else if (pixel.R == 255 && pixel.G == 0 && pixel.B == 0)
                        {
                            levelData += "e";
                        }
                        else if (pixel.R == 145 && pixel.G == 0 && pixel.B == 0)
                        {
                            levelData += "k";
                        }
                        else if (pixel.R == 150 && pixel.G == 110 && pixel.B == 0)
                        {
                            levelData += "o";
                        }
                        else if (pixel.R == 255 && pixel.G == 255 && pixel.B == 0)
                        {
                            levelData += "g";
                        }
                        else if (pixel.R == 0 && pixel.G == 0 && pixel.B == 255)
                        {
                            levelData += "d";
                        }
                        else if (pixel.R == 100 && pixel.G == 0 && pixel.B == 100)
                        {
                            levelData += "x";
                        }
                        else
                        {
                            levelData += " ";
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
