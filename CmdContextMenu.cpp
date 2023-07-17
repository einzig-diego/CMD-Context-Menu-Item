#include <iostream>
#include <windows.h>
#include <string>

void InstallContextMenu()
{
    HKEY key;
    std::string command = "cmd.exe /k \"cd /d \"%V\"\"";

    // Create/Open the key for the "Open Command Prompt" context menu item
    RegCreateKey(HKEY_CLASSES_ROOT, "Directory\\Background\\shell\\OpenCommandPrompt", &key);
    RegSetValueEx(key, "", 0, REG_SZ, (BYTE*)"Command prompt", sizeof("Command prompt"));
    RegSetValueEx(key, "Icon", 0, REG_SZ, (BYTE*)"cmd.exe", 8);

    HKEY commandKey;
    RegCreateKey(key, "command", &commandKey);
    RegSetValueEx(commandKey, "", 0, REG_SZ, (BYTE*)command.c_str(), command.length() + 1);

    RegCloseKey(commandKey);
    RegCloseKey(key);
}

void UninstallContextMenu()
{
    std::cout << "Delete the following key: Computer\\HKEY_CLASSES_ROOT\\Directory\\Background\\shell\\OpenCommandPrompt" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "/uninstall") == 0)
    {
        UninstallContextMenu();
    }
    else
    {
        InstallContextMenu();
        std::cout << "Context menu extension installed successfully." << std::endl;
    }

    return 0;
}
