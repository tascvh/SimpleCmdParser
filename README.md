# SimpleCmdParser

SimpleCmdParser is a minimalistic easy to use command line argument parser for modern C++ applications. It supports handling optional and normal variables, setting default values as well as displaying help messages related to the arguments. 

## Sample Usage

```cpp
#include "simple_cmd_parser.hpp"
...
int main(int argc, char **argv) {
  try {
    std::optional<std::string> device;
    std::string mode("f");
    int left(10);
    int right(10);
    int top(0);
    int bottom(15);

    SimpleParser sp(argc, argv);

    sp.read(device, "-d");
    sp.read(mode, "-m");
    sp.read(left, "-l");
    sp.read(right, "-r");
    sp.read(top, "-t");
    sp.read(bottom, "-b");
...
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Caught unknown exception" << std::endl;
  }
...
}
```
## Usage with help options

```cpp
#include "simple_cmd_parser.hpp"
...
int main(int argc, char **argv) {
  try {
    std::optional<std::string> device;
    std::string mode("f");
    int left(10);
    int right(10);
    int top(0);
    int bottom(15);

    SimpleParser sp(argc, argv);
    sp.read(sp.m_showHelp, "-h");
    if (sp.m_showHelp) {
      std::cout << "-h : Show this help message" << std::endl;
    }

    sp.read(device, "-d", "trackpad device filename (mandatory)");
    sp.read(mode, "-m", "Running mode options : p/s/f ");
    sp.read(left, "-l", "left percentage");
    sp.read(right, "-r", "right percentage");
    sp.read(top, "-t", "top percentage");
    sp.read(bottom, "-b", "bottom percentage");

    if (sp.m_showHelp) {
      std::cout << std::endl << "Example usage :" << std::endl;
      std::cout << "\tsp -d /dev/input/event0 -m f" << std::endl;
      return EXIT_SUCCESS;
    }

    if (!device) {
      auto s = "device argument is mandatory. Use -h for help";
      throw std::invalid_argument(s);
    }
...
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Caught unknown exception" << std::endl;
  }
...
}
```
Running the program above with parameter -h will show 

```bash
$ ./sp -h
-h : Show this help message
-d : (string) trackpad device filename (mandatory)
-m : (string) Running mode options : p/s/f  - Default value : f
-l : (int) left percentage - Default value : 10
-r : (int) right percentage - Default value : 10
-t : (int) top percentage - Default value : 0
-b : (int) bottom percentage - Default value : 15

Example usage :
	sp -d /dev/input/event0 -m f
```

## Limitations 
 -  Quotes in argument values are not supported
