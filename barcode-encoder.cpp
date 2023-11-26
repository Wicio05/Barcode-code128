#include <iostream>
#include "code128/code128.hpp"
#include "lodepng/lodepng.h"

void wrongFormat(char* argv0)
{
    std::cout << "Wrong format!\n";
    std::cout << "Format: [" << argv0 << "] [code to encode] [-options]\n";
    std::cout << "use -help for more information\n";
}

int main(int argc, char** argv)
{
    int m = 1;
    int h = 40;
    int p = 11;
    std::string n = "code128.png";
    std::string inst = argv[1];

    if(argc == 1)
    {
        wrongFormat(argv[0]);
        return 0;
    }

    if(inst[0] == '-' && inst != "-help")
    {
        std::cout << "No code to encode.\n";
        wrongFormat(argv[0]);
        return EXIT_FAILURE;
    }

    for(int i = 1; i < argc; ++i)
    {
        inst = argv[i];
        if(inst[0] == '-')
        {
            if(inst == "-help")
            {
                std::cout << "[-f n] - renames the image filename to [n].png\n"; 
                std::cout << "[-m m] - multipies width and height of the image, so that the demantions equal basicWidthOfImage * [m] x heightOfImage * [m]. It is the only way to resize width of the image. [m] = 1 as default.\n";
                std::cout << "[-h h] - makes an image of height = [h] * multiplier. [h] = 40px as default. !!!Keep in mind that it is affected by the multiplier!!!\n";
                std::cout << "[-p p] - adds padding on left and right side of the image. Image width = 2 * [p] + encoded message width(px). [p] = 11 as default.\n";
                return 0;
            }
            else if(inst == "-f")
            {
                if(i >= argc - 1)
                {
                    std::cout << "No value provided.\n";
                    return EXIT_FAILURE;
                }
                else if(argv[i + 1][0] == '-')
                {
                    std::cout << "You cannot start a filename with a dash(\"-\").\n";
                    return EXIT_FAILURE;
                }

                n = argv[i + 1];
                n += ".png";
            }
            else if(inst == "-m")
            {
                std::string tmp;
                if(i >= argc - 1)
                {
                    std::cout << "No value provided.\n";
                    return EXIT_FAILURE;
                }

                tmp = argv[i + 1];

                try
                {
                    m = std::stoi(tmp);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    return EXIT_FAILURE;
                }
            }
            else if (inst == "-h")
            {
                std::string tmp;
                if(i >= argc - 1)
                {
                    std::cout << "No value provided.\n";
                    return EXIT_FAILURE;
                }

                tmp = argv[i + 1];

                try
                {
                    h = std::stoi(tmp);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    return EXIT_FAILURE;
                }
            }
            else if(inst == "-p")
            {
                std::string tmp;
                if(i >= argc - 1)
                {
                    std::cout << "No value provided.\n";
                    return EXIT_FAILURE;
                }

                tmp = argv[i + 1];

                try
                {
                    p = std::stoi(tmp);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    return EXIT_FAILURE;
                }
            }
        }
    }

    Code128 code(argv[1]);

    code.setImgPadding(p);

    //get encoded code
    std::vector<int> out = code.getEncoded();

    //dementions of the image
    unsigned int width = code.getLength() * m;
    unsigned int height = h * m;

    std::vector<unsigned char> image(width * height * 4);

    //make an image using encoded code
    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            image[4 * width * y + 4 * x + 0] = image[4 * width * y + 4 * x + 1] = image[4 * width * y + 4 * x + 2] = !out[x/m] * 255;
            image[4 * width * y + 4 * x + 3] = 255;
        }
    }

    // Encode the image qith lodepng
    unsigned error = lodepng::encode(n, image, width, height);

    // if there's an error, display it
    if (error)
        throw error;
}
