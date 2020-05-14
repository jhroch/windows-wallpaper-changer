///////////////////////////////////////////////////////////////////
//  CupWall.cpp - Jiri Hroch - 14 May 2020 - jhroch24@gmail.com  //
//  All credits to -> Nathan Higley - contact@nathanhigley.com   //
//  This is basically paste of his app but I made it only for PC //
///////////////////////////////////////////////////////////////////
//                                                               //
//  Description:                                                 //
//  This program sets different images as the desktop wallpaper  //
//  every second (or any other interval).                        //
//                                                               //
///////////////////////////////////////////////////////////////////
//                                                               //
//  Prerequisites:                                               //
//  A folder in the current working directory named "images"     //
//  with the wallpapers inside with the following scheme,        //
//  "img_<1-5>.png" contained inside.                            //
//                                                               //
///////////////////////////////////////////////////////////////////

// Libraries used
#include <Windows.h>
#include <string>

// Usage directives
using std::string;

// Function prototypes
bool setWallpaper(string);

int main()
{
    // Application running in background
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);
    // Wallpaper name arrays
    const string batt_walls[5] = { "img_1", "img_2", "img_3", "img_4", "img_5" };
    // Integer variables to store important data
    int current_wall{ -1 };
    int next_wall{ 0 };
    // Control variable
    bool wall_changed{ true };

    // Enter the event loop
    while (wall_changed)
    {
                // Change the wallpaper every second to the next charging wallpaper
                for (int x{ 0 }; x < 5; x++)
                {
                    // Attempt to change the wallpaper
                    wall_changed = setWallpaper(batt_walls[x]);
                    // Change wallpaper every 1000ms (1 second)
                    Sleep(1000);
                }
            // Reset the current wall number since the wallpaper changed
            current_wall = -1;
        
    }
    // Return the inverse of wall_changed since if it is 1 then the program exited normally, else it should be 0 which is an error
    return !wall_changed;
}

// Function to set the wallpaper to the filename.
// Requirements: images in a folder called "images" in the current working directory
// and images are png files
bool setWallpaper(string imageName)
{
    // Get the current directory and store it into a char string
    char buf[256];
    GetCurrentDirectoryA(256, buf);
    // Create the absolute path to the image
    string file = buf + string("\\images\\") + imageName + string(".png");
    // Convert the string to a wide string
    std::wstring widestr = std::wstring(file.begin(), file.end());
    // Convert the wide string to a c string
    const wchar_t* filenm = widestr.c_str();
    // Set the wallpaper to the given image
    return SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)filenm, SPIF_UPDATEINIFILE);
}