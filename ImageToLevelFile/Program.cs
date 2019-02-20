//converts images into Wolfenstein Real 3D level files


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
            //the user enters path to folder with images
            Console.WriteLine("Enter path to image folder");
            string imageFolder = Console.ReadLine();

            //loops files in folder
            foreach (var item in Directory.GetFiles(imageFolder))
            {
                bool first = true;
                string levelData = "";

                //read images
                Bitmap img = new Bitmap(item);
                for (int y = img.Height - 1; y >= 0; y--)
                {
                    for (int x = 0; x < img.Width; x++)
                    {
                        Color pixel = img.GetPixel(x, y);

                        //if it is the first pixel we read, add the size of the level
                        if (first)
                            levelData += img.Width;
                        first = false;
                        
                        //add , before all cells
                        levelData += ",";

                        //add the correct char based on the pixel color

                        //stone wall
                        if (pixel.R == 0 && pixel.G == 0 && pixel.B == 0)
                        {
                            levelData += "s";
                        }

                        //word wall
                        else if (pixel.R == 167 && pixel.G == 167 && pixel.B == 167)
                        {
                            levelData += "w";
                        }

                        //blue wall
                        else if (pixel.R == 76 && pixel.G == 76 && pixel.B == 76)
                        {
                            levelData += "b";
                        }

                        //health pickup
                        else if (pixel.R == 0 && pixel.G == 80 && pixel.B == 0)
                        {
                            levelData += "h";
                        }

                        //player start position
                        else if (pixel.R == 0 && pixel.G == 255 && pixel.B == 0)
                        {
                            levelData += "p";
                        }

                        //normal enemy
                        else if (pixel.R == 255 && pixel.G == 0 && pixel.B == 0)
                        {
                            levelData += "e";
                        }

                        //start enemy
                        else if (pixel.R == 145 && pixel.G == 0 && pixel.B == 0)
                        {
                            levelData += "k";
                        }

                        //object
                        else if (pixel.R == 150 && pixel.G == 110 && pixel.B == 0)
                        {
                            levelData += "o";
                        }

                        //gold
                        else if (pixel.R == 255 && pixel.G == 255 && pixel.B == 0)
                        {
                            levelData += "g";
                        }

                        //door
                        else if (pixel.R == 0 && pixel.G == 0 && pixel.B == 255)
                        {
                            levelData += "d";
                        }

                        //end game lever
                        else if (pixel.R == 100 && pixel.G == 0 && pixel.B == 100)
                        {
                            levelData += "x";
                        }

                        //empty
                        else
                        {
                            levelData += " ";
                        }
                    }
                }

                //write level file
                File.WriteAllText(imageFolder + Path.GetFileNameWithoutExtension(item) + ".l", levelData);
            }
            

            Console.WriteLine("Done");
            Console.Read();
        }
    }
}
